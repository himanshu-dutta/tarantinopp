file(GLOB_RECURSE SRC tarantinopp/*.cc)
file(GLOB_RECURSE INCLUDE tarantinopp/*.h)

message(STATUS "Adding the following source files to the library: ${SRC}")
message(STATUS "Adding the following include files to the library: ${INCLUDE}")

add_library(tarantinopp ${SRC} ${INCLUDE})
set_target_properties(tarantinopp PROPERTIES LINKER_LANGUAGE CXX)


# packages which can be fetched
include(FetchContent)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.zip
    CMAKE_ARGS
        -DCMAKE_BUILD_TYPE:STRING=Release
)

FetchContent_MakeAvailable(spdlog)



target_include_directories(tarantinopp 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(tarantinopp
    PRIVATE pthread
    PUBLIC spdlog::spdlog
)