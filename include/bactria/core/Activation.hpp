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

/**
 * \file Activation.hpp
 * \brief Plugin activation file.
 *
 * This file contains functionality required for bactria's internal plugin handling. It should not be included
 * directly by the user.
 */

#pragma once

#include <cstdlib>

namespace bactria
{
    /**
     * \defgroup bactria_core Core functionality
     *
     * bactria's core functionality. Except for the Context class this part of bactria should never be used directly.
     */

    /**
     * \defgroup bactria_core_internal Internal documentation. Not intended or useful for the user.
     * \ingroup bactria_core
     *
     * \{
     */

    /**
     * \brief Checks whether the bactria library has been deactivated by the user.
     *
     * Checks whether bactria was deactivated by using the environment variable `BACTRIA_DEACTIVATE`. This function
     * should never be called by the user.
     *
     * \return true The library is active (`BACTRIA_DEACTIVATE` is not set).
     * \return false The library is inactive (`BACTRIA_DEACTIVATE` is set).
     */
    inline auto is_active() -> bool
    {
        static auto const active = (std::getenv("BACTRIA_DEACTIVATE") == nullptr);
        return active;
    }

    /**
     * \}
     */

    /**
     * \mainpage bactria - Broadly Applicable C++ Tracing and Instrumentation API
     *
     * \section about About this project
     * \subsection about_intro Introduction
     *
     * The **bactria** library is a header-only C++14 library for profiling and tracing. By annotating segments of your
     * code with bactria's classes you can gather fine-grained information about your application's performance without
     * introducing runtime overhead in other program parts.
     *
     * bactria itself is platform-independent and provides a unified modern C++ API to the user. The profiling and/or
     * tracing information are collected by its various plugins:
     *
     * * JSON: Supported on all platforms. Used for saving user-defined metrics to disk.
     * * stdout: Supported on all platforms. Used for tracing events and time spans and printing them to stdout.
     * * Score-P: Supported on Linux. Used for collecting various metrics (such as hardware counters) and saving them
     *   to disk for later analysis.
     * * NVTX: Supported on all platforms. Used for tracing events and time spans and visualizing them on NVIDIA's
     *   visual profilers.
     * * rocTX: Supported on Linux. Used for tracing events and time spans and visualizing them on Chrome's
     *   `about:tracing` tool (used by AMD's ROCm).
     *
     * \subsection about_differences Differences to similar projects
     * TODO: Fill this out!
     *
     * \section getting_started Getting started
     * \subsection getting_started_pre Prerequisites
     *
     * The user-facing API has no dependencies. However, most plugins require
     * [`toml11`](https://github.com/ToruNiina/toml11) to be present and additionally introduce their
     * platform-specific dependencies (such as Score-P, CUDA or ROCm).
     *
     * bactria assumes that all builds happen out-of-source. The easiest way to achieve this is to create a `build`
     * directory in bactria's top-level directory:
     *
     * ```zsh
     * git clone https://github.com/alpaka-group/bactria.git
     * cd bactria
     * mkdir build && cd build
     * ```
     *
     * \subsection getting_started_conf Configuration
     *
     * bactria uses CMake (>=3.18) as a build system. On top of the common CMake build options (such as the build
     * type) it supports the following configuration switches:
     *
     * * `bactria_BUILD_DOCUMENTATION` -- Build the Doxygen documentation. Default: `ON`.
     * * `bactria_BUILD_EXAMPLES` -- Build the examples (see the `examples` folder). Default: `ON`.
     * * `bactria_CUDA_PLUGINS` -- Build the CUDA ecosystem plugins. Default: `OFF`
     * * `bactria_JSON_PLUGINS` -- Build the JSON-based plugins. Default: `ON`
     *      * `bactria_SYSTEM_JSON` -- Use your local installation of the nlohnmann-json library. If set to `OFF`,
     *        bactria will attempt to download the library to its build directory. Default: `ON`.
     * * `bactria_ROCM_PLUGINS` -- Build the ROCm ecosystem plugins. Default: `OFF`.
     * * `bactria_SCOREP_PLUGINS` -- Build the Score-P plugins. Default: `OFF`.
     * * `bactria_STDOUT_PLUGINS` -- Build the `stdout` plugins. Default: `ON`.
     *      * `bactria_SYSTEM_FMT` -- Use your local installation of `{fmt}` if the `stdout` plugins are being built.
              If set to `OFF`, bactria will attempt to download the library to its build directory. Default: `ON`.
     * * `bactria_SYSTEM_TOML11` -- Use your local installation of toml11. If set to `OFF`, bactria will attempt to
     *   download the library to its build directory. Default: `ON`.
     *
     * The following example configures the build system for building the Doxygen documentation, the examples and the
     * plugins for CUDA, JSON, Score-P and `stdout` in `Release` mode:
     *
     * ```zsh
     * cmake -DCMAKE_BUILD_TYPE=Release -Dbactria_CUDA_PLUGINS=ON -Dbactria_SCOREP_PLUGINS=ON ..
     * ```
     *
     * \subsection getting_started_build Building
     *
     * If the previous step was successful all that is left to do is invoke the actual build command:
     *
     * ```zsh
     * cmake --build . --config Release -j[number of parallel jobs]
     * ```
     *
     * \section usage Usage
     *
     * After a successful bactria build the contents of your `build` directory will look similar to this structure
     * (Visual Studio and XCode builds may have another intermediate directory between `build` and the subdirectories
     * here):
     *
     * ```
     * build/
     * |
     * ----.cmake/
     * ----CMakeFiles/
     * ----examples/
     * ----src/
     * ----[some files]/
     * ```
     *
     * You should be interested in the contents of `examples` and `src`. In the subdirectories of the `examples`
     * folder you will find executables which already have built-in bactria support. In the subdirectories of the
     * `src` folder you will find the plugins that were built according to your configuration:
     *
     * ```
     * build/
     * |
     * ----examples/
     * |   |
     * |   ----simpleLoop/
     * |       |
     * |       ----simpleLoop
     * ----src/
     *     |
     *     ----metrics/
     *     |   |
     *     |   ----scorep/
     *     |       |
     *     |       ----libbactria_metrics_scorep.so
     *     ----ranges/
     *     |   |
     *     |   ----nvtx/
     *     |   |   |
     *     |   |   ----libbactria_ranges_nvtx.so
     *     |   ----roctx/
     *     |   ----stdout/
     *     |       |
     *     |       ----libbactria_ranges_stdout.so
     *     ----reports/
     *         |
     *         ----json/
     *             |
     *             ----libbactria_reports_json.so
     * ```
     *
     * \subsection usage_plugins Activating bactria plugins
     *
     * Switch to the directory with the built `simpleLoop` example:
     *
     * ```
     * cd examples/simpleLoop
     * ```
     *
     * If you just execute the program without any further configuration you will notice that there are no additional
     * output files produced. This is a design principle: If you do not want to use a certain aspect of bactria you do
     * not have to! Internally, bactria will disable this functionality if no plugin was selected at runtime.
     *
     * To enable bactria's plugins you have to set one (or more) of the following environment variables to the path of
     * your desired plugin:
     *
     * ```
     * export BACTRIA_METRICS_PLUGIN=/path/to/bactria/build/src/metrics/scorep/libbactria_metrics_scorep.so
     * export BACTRIA_RANGES_PLUGIN=/path/to/bactria/build/src/ranges/nvtx/libbactria_ranges_nvtx.so
     * export BACTRIA_REPORTS_PLUGIN=/path/to/bactria/build/src/reports/json/libbactria_reports_json.so
     * ./simpleLoop
     * ```
     *
     * After the program execution you should see some additional files in the directory that have not been present
     * before. These are the files you can now load into your favourite analysis / profiling tools for further
     * examination.
     *
     * In the next sections we will explain the concepts behind `metrics`, `ranges` and `reports`.
     *
     * \subsection usage_init Initialization
     *
     * Before you can use bactria you have to initialize the library. This is done by creating a `Context` (once per
     * process) and keeping it alive until you no longer require any functionality from bactria. The `Context` takes
     * care of loading your selected plugin(s) into memory so you can make use of bactria's user API. The easiest way
     * for managing a bactria `Context` is to create it at the beginning of `main` and keep it alive until the program
     * stops:
     *
     * \include main.cpp
     *
     * Note that the context is wrapped into a `try`/`catch` block. Should any internal errors occur in bactria's
     * user-facing parts a `std::runtime_error` will be thrown.
     *
     * \subsection usage_ranges Ranges
     *
     * bactria's ranges are a useful tool if you want to highlight / visualize certain events and time spans
     * (= ranges) in your application code. This gives you a high-level view onto your program's behaviour and can
     * help you with choosing the correct code segments to analyse in more detail.
     *
     * * `Event`s are single points in time and are simply triggered / `fire`d in the application code.
     * * `Range`s are time spans and are `start`ed and `stop`ped.
     * * Both `Event`s and `Range`s can be assigned to a `Category`. Through the configuration file you can filter out
     * all `Event`s and `Range`s part of a specific `Category`.
     *
     * `Event`s and `Range`s can freely overlap / be nested in any way you feel necessary. This is how it looks like
     * in code:
     *
     * \include foo.cpp
     *
     * As you may have noticed we have supplied a color to the range / event constructor. Some plugins support custom
     * colors to enhance the visualizer output (this depends on vendor APIs and is therefore not supported by all
     * available plugins). You can either use one of bactria's numerous pre-defined colors (see Colors.hpp) or supply
     * your own color in ARGB format:
     *
     * \include my_orange.cpp
     *
     * \subsection usage_metrics Metrics
     *
     * Once you have an idea of where your program spends most of its time you might want to optimize these portions.
     * In order to find the major bottlenecks it is useful to look at certain metrics like hardware counters, a more
     * detailed profiling, call stacks, and so on. Plugins implementing bactria's `metrics` functionality are built on
     * top of various vendors' APIs dedicated to this purpose. By using bactria's `metrics` API you can make use of
     * these APIs in a portable way.
     *
     * In the `metrics` API the following classes are available:
     *
     * * `Sector`s are used as annotations in your code and enable the detailed collection of metrics by your
     *   ecosystem's performance tools.
     * * `Tag`s are a special kind of metadata that some plugins can make use of. By default, all `Sector`s are
     *   assigned the `Generic` tag. Some plugins understand additional information supplied by other `Tag`s, such as
     *   `Function`,  `Loop`, `Body`, and so on, to provide you with more detailed results.
     * * `Phase`s are used to group `Sector`s (possibly in different scopes) into logical program phases. Some
     *   performance  tools can make use of this information to provide you with an analysis of these logical
     *   segments.
     *
     * Both `Sector`s and `Phase`s follow a stack-based / LIFO-based programming approach. This means that they have
     * to be correctly nested and cannot overlap freely (in contrast to the `ranges` API).
     *
     * Example:
     * \include bar.cpp
     *
     * \subsection usage_reports Reports
     *
     * Sometimes the metrics collected by the various vendor-specific plugins are not enough. For this case bactria
     * provides the `reports` API which enables you to save key-value pairs (where `key` is a `std::string` and
     * `value` an arithmetic type or a `std::string`). To do this, you first create a `IncidentRecorder` and use it to
     * create `Incident`s (the key-value pairs). Once your recording is complete you can submit a `Report` (which
     * matches the output file generated by the plugin):
     *
     * \include baz.cpp
     *
     * \section contrib Contributors
     *
     * \subsection contrib_core Maintainers and Core Developers
     *
     * * Jan Stephan (original author)
     *
     * \subsection contrib_thanks Former Members, Contributions and Thanks
     *
     * * Dr. Michael Bussmann
     * * René Widera
     *
     * \section ack Acknowledgements
     *
     * This work was partially funded by the
     * [Center of Advanced Systems Understanding (CASUS)](https://www.casus.science) which is financed by
     * [Germany's Federal Ministry of Education and Research (BMBF)](https://www.bmbf.de/en/index.html) and by the
     * [Saxon Ministry for Science, Culture and Tourism (SMWK)](https://www.smwk.sachsen.de) with tax funds on the
     * basis of the budget approved by the [Saxon State Parliament](https://www.landtag.sachsen.de/en/).
     *
     * \section licence Licence
     *
     * This free software is licensed unter the EUPL v1.2. Please refer to the `LICENSE` file in the top-level
     * source code directory for the concrete details of this licence.
     *
     */
} // namespace bactria
