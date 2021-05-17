if(bactria_JSON_BACKENDS)
    add_library(bactria_reports_json MODULE Reports.cpp)
    target_link_libraries(bactria_reports_json PRIVATE bactria nlohmann_json::nlohmann_json)
endif()
