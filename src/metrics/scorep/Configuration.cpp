/* Copyright 2021 Jan Stephan
 *
 * Licensed under the EUPL, Version 1.2 or - as soon they will be approved by
 * the European Commission - subsequent versions of the EUPL (the “Licence”).
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at:
 *
 *     http://ec.europa.eu/idabc/eupl.html
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an “AS IS” basis, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  Licence permissions and limitations under the Licence.
 */

#include <toml.hpp>

#include <ext/stdio_filebuf.h> // Okay, because Score-P only works with libstdc++ anyway

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    auto make_string(std::string const& val)
    {
        return val;
    }

    auto make_string(std::vector<std::string> const& val)
    {
        auto str = std::string{""};
        if(!val.empty())
        {
            std::for_each(std::begin(val), std::end(val) - 1, [&str](std::string const& s) { str += s + ','; });
            if(std::begin(val) != std::end(val))
                str += *(std::end(val) - 1);
        }

        return str;
    }

    auto make_string(bool val)
    {
        return std::string{val ? "true" : "false"};
    }

    auto make_string(std::int64_t val)
    {
        return std::to_string(val);
    }

    std::vector<char const*> set_envs;

    template <typename T, typename TToml>
    auto set_scorep_env(TToml const& section, char const* env_var, char const* conf_var, bool required = true)
    {
        if(required)
        {
            auto const env = std::getenv(env_var);
            if(env == nullptr)
            {
                auto const conf = toml::find<T>(section, conf_var);
                auto const string = make_string(conf);
                setenv(env_var, string.c_str(), 0);
                set_envs.push_back(env_var);
            }
        }
    }

    template <typename TToml>
    auto get_and_set_scorep_flag(TToml const& section, char const* env_var, char const* conf_var, bool& flag, bool required = true)
    {
        if(required)
        {
            auto const env = std::getenv(env_var);
            if(env == nullptr)
            {
                flag = toml::find<bool>(section, conf_var);
                setenv(env_var, (flag ? "true" : "false"), 0);
                set_envs.push_back(env_var);
            }
            else
                flag = (std::strcmp(env, "true") < 0) || (std::strcmp(env, "TRUE") < 0) || (std::strcmp(env, "1") < 0);
        }
    }
}
[[gnu::constructor]] auto initialize()
{
    try
    {
        auto const config_file = toml::parse("bactriaConfig.toml");

        auto const metrics = toml::find(config_file, "metrics");
        auto const scorep = toml::find(metrics, "scorep");

        /* Configuration */
        auto const config = toml::find(scorep, "config");
        set_scorep_env<std::string>(config, "SCOREP_TOTAL_MEMORY", "memory_limit");
        set_scorep_env<std::string>(config, "SCOREP_PAGE_SIZE", "page_size");
        set_scorep_env<std::string>(config, "SCOREP_MACHINE_NAME", "machine_name");
        set_scorep_env<std::string>(config, "SCOREP_TIMER", "timer");

        /* Profiling */
        auto const profiling = toml::find(scorep, "profiling");

        auto enable_profiling = bool{};
        get_and_set_scorep_flag(profiling, "SCOREP_ENABLE_PROFILING", "enable", enable_profiling);
        set_scorep_env<std::string>(profiling, "SCOREP_PROFILING_BASE_NAME", "base_name", enable_profiling);
        set_scorep_env<std::string>(profiling, "SCOREP_PROFILING_FORMAT", "format", enable_profiling);
        set_scorep_env<std::int64_t>(profiling, "SCOREP_PROFILING_MAX_CALLPATH_DEPTH", "max_callpath_depth", enable_profiling);

        /* Profiling->Clustering */
        auto clustering = toml::find(profiling, "clustering");
        auto enable_clustering = bool{};
        get_and_set_scorep_flag(clustering, "SCOREP_ENABLE_CLUSTERING", "enable", enable_clustering, enable_profiling);
        enable_clustering = enable_profiling && enable_clustering;
        set_scorep_env<std::string>(clustering, "SCOREP_PROFILING_CLUSTERED_REGION", "region", enable_clustering);
        set_scorep_env<std::int64_t>(clustering, "SCOREP_PROFILING_CLUSTER_COUNT", "count", enable_clustering);
        set_scorep_env<std::string>(clustering, "SCOREP_PROFILING_CLUSTERING_MODE", "mode", enable_clustering);

        /* Profiling->Debugging */
        set_scorep_env<bool>(profiling, "SCOREP_PROFILING_ENABLE_CORE_FILES", "enable_core_files", enable_profiling);

        /* Tracing */
        auto const tracing = toml::find(scorep, "tracing");
        set_scorep_env<bool>(tracing, "SCOREP_ENABLE_TRACING", "enable");

        /* Filtering */
        // Is there already a filtering file?
        auto const filter_env = std::getenv("SCOREP_FILTERING_FILE");
        if(filter_env == nullptr)
        {
            // No. We need to set up our own.
            auto const filter = toml::find(scorep, "filtering");
            auto const files = toml::find(filter, "files");
            auto const regions = toml::find(filter, "regions");

            // Filtering on the file level
            auto const excluded_files = toml::find<std::vector<std::string>>(files, "exclude");
            auto const included_files = toml::find<std::vector<std::string>>(files, "include");
            auto const filtering_files = excluded_files.empty() && included_files.empty();

            auto&& file_stream = std::stringstream{};
            if(filtering_files)
            {
                file_stream << "SCOREP_FILE_NAMES_BEGIN\n";
                if(!excluded_files.empty())
                {
                    file_stream << "  EXCLUDE";
                    for(auto const& f : excluded_files)
                        file_stream << ' ' << f;;
                    file_stream << '\n';
                }

                if(!included_files.empty())
                {
                    file_stream << "  INCLUDE ";
                    for(auto const& f : included_files)
                        file_stream << ' ' << f;
                    file_stream << '\n';
                }
                file_stream << "SCOREP_FILE_NAMES_END\n";
            }

            // Filtering on the region level
            auto const excluded_regions = toml::find<std::vector<std::string>>(regions, "exclude");
            auto const excluded_mangled_regions = toml::find<std::vector<std::string>>(regions, "exclude_mangled");
            auto const included_regions = toml::find<std::vector<std::string>>(regions, "include");
            auto const included_mangled_regions = toml::find<std::vector<std::string>>(regions, "include_mangled");
            auto const filtering_regions = excluded_regions.empty() && excluded_mangled_regions.empty()
                                            && included_regions.empty() && included_mangled_regions.empty();
            
            auto&& region_stream = std::stringstream{};
            if(filtering_regions)
            {
                region_stream << "SCOREP_REGION_NAMES_BEGIN\n";
                if(!excluded_regions.empty() || !excluded_mangled_regions.empty())
                {
                    region_stream << "  EXCLUDED";
                    for(auto const& r : excluded_regions)
                        region_stream << ' ' << r;

                    if(!excluded_mangled_regions.empty())
                    {
                        region_stream << " MANGLED";
                        for(auto const& r : excluded_mangled_regions)
                            region_stream << ' ' << r;
                    }
                    region_stream << '\n';
                }

                if(!included_regions.empty() || !included_mangled_regions.empty())
                {
                    region_stream << "  INCLUDED";
                    for(auto const& r: included_regions)
                        region_stream << ' ' << r;

                    if(!included_mangled_regions.empty())
                    {
                        region_stream << " MANGLED";
                        for(auto const& r : included_mangled_regions)
                            region_stream << ' ' << r;
                        region_stream << '\n';
                    }
                }
                region_stream << "SCOREP_REGION_NAMES_END\n";
            }

            if(filtering_files || filtering_regions)
            {
                auto file_template = std::array<char, 28>{"bactria_scorep_filterXXXXXX"};
                auto file_descriptor = mkstemp(file_template.data());
                auto filebuf = __gnu_cxx::stdio_filebuf<char>{file_descriptor, std::ios::out};
                auto&& file = std::ostream{&filebuf};

                if(filtering_files)
                    file << file_stream.rdbuf() << '\n';
                
                if(filtering_regions)
                    file << region_stream.rdbuf();

                setenv("SCOREP_FILTERING_FILE", file_template.data(), 0);
                set_envs.push_back("SCOREP_FILTERING_FILE");
            }
        }

        /* Selective recording */
        // Is there already a selective recording file?
        auto const sel_rec_env = std::getenv("SCOREP_SELECTIVE_CONFIG_FILE");
        if(sel_rec_env == nullptr)
        {
            // No. We need to set up our own.
            auto const selective_recording = toml::find(scorep, "selective_recording");
            auto const regions = toml::find(selective_recording, "regions");

            auto const arr = regions.as_array();
            if(!arr.empty())
            {
                auto file_template = std::array<char, 31>{"bactria_scorep_selectiveXXXXXX"};
                auto file_descriptor = mkstemp(file_template.data());
                auto filebuf = __gnu_cxx::stdio_filebuf<char>{file_descriptor, std::ios::out};
                auto&& file = std::ostream{&filebuf};

                // regions is likely a heterogeneous TOML array. We need to examine each entry by hand
                for(auto const& v : regions.as_array())
                {
                    if(v.is_string())
                    {
                        // No iteration number / range specified. Monitor all region iterations
                        file << v.as_string() << '\n';
                        continue;
                    }

                    if(v.is_array())
                    {
                        auto v_arr = v.as_array();

                        // First array entry must be a string
                        file << v_arr[0].as_string();
                        
                        // Check remaining entries
                        for(auto it = std::begin(v_arr) + 1; it != std::end(v_arr); ++it)
                        {
                            if(it->is_integer())
                            {
                                // Entry is a single iteration index
                                file << ' ' << it->as_integer();
                                continue;
                            }

                            if(it->is_array())
                            {
                                // Entry is an iteration range
                                file << ' ' << it->at(0) << ':' << it->at(1);
                                continue;
                            }
                        }
                        file << '\n';
                    }
                }

                setenv("SCOREP_SELECTIVE_CONFIG_FILE", file_template.data(), 0);
                set_envs.push_back("SCOREP_SELECTIVE_CONFIG_FILE");
            }
        }

        /* Metrics -> PAPI */
        auto const papi = toml::find(scorep, "papi");
        set_scorep_env<std::vector<std::string>>(papi, "SCOREP_METRIC_PAPI", "thread_counters");
        set_scorep_env<std::vector<std::string>>(papi, "SCOREP_METRIC_PAPI_PER_PROCESS", "process_counters");

        /* Metrics -> Resource Usage */
        auto const rusage = toml::find(scorep, "rusage");
        set_scorep_env<std::vector<std::string>>(rusage, "SCOREP_METRIC_RUSAGE", "thread_counters");
        set_scorep_env<std::vector<std::string>>(rusage, "SCOREP_METRIC_RUSAGE_PER_PROCESS", "process_counters");

        /* Metrics -> Linux Perf */
        auto const perf = toml::find(scorep, "perf");
        set_scorep_env<std::vector<std::string>>(perf, "SCOREP_METRIC_PERF", "thread_counters");
        set_scorep_env<std::vector<std::string>>(perf, "SCOREP_METRIC_PERF_PER_PROCESS", "process_counters");

        /* bactria's Score-P reports plugin */
        auto const reports_plugin = toml::find(scorep, "reports_plugin");
        auto reports_plugin_enabled = bool{};
        // Using a dummy environment variable here which doesn't exist in Score-P
        get_and_set_scorep_flag(reports_plugin, "SCOREP_ENABLE_BACTRIA_REPORTS_PLUGIN", "enable", reports_plugin_enabled);
        if(reports_plugin_enabled)
        {
            setenv("SCOREP_METRIC_PLUGINS", "bactria_reports_scorep", 0);
            set_envs.push_back("SCOREP_METRIC_PLUGINS");
        }
        set_scorep_env<std::vector<std::string>>(reports_plugin, "SCOREP_METRIC_BACTRIA_REPORTS_SCOREP", "reports", reports_plugin_enabled);

        /* MPI */
        auto const mpi = toml::find(scorep, "mpi");
        set_scorep_env<std::vector<std::string>>(mpi, "SCOREP_MPI_ENABLE_GROUPS", "groups");

        /* CUDA */
        auto const cuda = toml::find(scorep, "cuda");
        auto cuda_enabled = bool{};
        get_and_set_scorep_flag(cuda, "SCOREP_CUDA_ENABLE", "enable", cuda_enabled);
        set_scorep_env<std::string>(cuda, "SCOREP_CUDA_BUFFER", "buffer_size", cuda_enabled);
        set_scorep_env<std::string>(cuda, "SCOREP_CUDA_BUFFER_CHUNK", "buffer_chunk", cuda_enabled);

        /* OpenCL */
        auto const opencl = toml::find(scorep, "opencl");
        auto opencl_enabled = bool{};
        get_and_set_scorep_flag(opencl, "SCOREP_OPENCL_ENABLE", "enable", opencl_enabled);
        set_scorep_env<std::string>(opencl, "SCOREP_OPENCL_BUFFER", "buffer_size", opencl_enabled);
        set_scorep_env<std::string>(opencl, "SCOREP_OPENCL_BUFFER_QUEUE", "buffer_queue", opencl_enabled);

        /* OpenACC */
        auto const openacc = toml::find(scorep, "openacc");
        set_scorep_env<std::vector<std::string>>(openacc, "SCOREP_OPENACC_ENABLE", "enabled_features");

        /* Kokkos */
        auto const kokkos = toml::find(scorep, "kokkos");
        set_scorep_env<std::vector<std::string>>(kokkos, "SCOREP_KOKKOS_ENABLE", "enabled_features");

        /* Online Access */
        auto const online_access = toml::find(scorep, "online_access");
        set_scorep_env<std::string>(online_access, "SCOREP_ONLINEACCESS_REG_HOST", "hostname");
        set_scorep_env<std::int64_t>(online_access, "SCOREP_ONLINEACCESS_BASE_PORT", "port");
        set_scorep_env<std::string>(online_access, "SCOREP_ONLINEACCESS_APPL_NAME", "application_name");

        /* Substrate */
        auto const substrate = toml::find(scorep, "substrate");
        set_scorep_env<std::vector<std::string>>(substrate, "SCOREP_SUBSTRATE_PLUGINS", "plugins");
        set_scorep_env<std::string>(substrate, "SCOREP_EXPERIMENT_DIRECTORY", "directory");
        set_scorep_env<bool>(substrate, "SCOREP_OVERWRITE_EXPERIMENT_DIRECTORY", "overwrite");
    }
    catch(std::runtime_error const& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << "WARNING: Not setting any Score-P configuration. "
                  << "Refer to Score-P's documentation for the default values." << std::endl;
    }
    catch(toml::syntax_error const& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << "WARNING: Your Score-P configuration will be ignored." << std::endl;
    }
    catch(std::out_of_range const& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << "WARNING: Your Score-P configuration will be ignored." << std::endl;
    }
    catch(toml::type_error const& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << "WARNING: Your Score-P configuration will be ignored." << std::endl;
    }
}

[[gnu::destructor]] auto shutdown()
{
    // Clean up behind us: All environment variables that we set ourselves need to be unset
    for(auto env : set_envs)
        unsetenv(env);
}