cmake_minimum_required(VERSION 3.0.0)
project(utils VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(
    utils_include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set (all_sources "")
macro(add_sources group dir)
    set(_all "")

    file(GLOB _inc "include/utils/${dir}/*.h" "include/utils/${dir}/*.hpp" "include/utils/${dir}/*.inl")
    list(APPEND _all ${_inc})

    file(GLOB _src "src/${dir}/*.cpp" "src/${dir}/*.c")
    list(APPEND _all ${_src})

    list(APPEND all_sources ${_all})
    string(REPLACE "/" "\\" group_path "${group}")
    source_group(${group_path} FILES ${_all})

    unset(_inc)
    unset(_src)
    unset(_all)
endmacro(add_sources)

add_sources("src"               ".")
add_sources("src/interfaces"    "interfaces")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(${utils_include_dirs})

add_library(utils STATIC ${all_sources})

if (CMAKE_VERSION VERSION_GREATER 3.7.8)
    if (MSVC_IDE)
        option(VS_ADD_NATIVE_VISUALIZERS "Configure project to use Visual Studio native visualizers" TRUE)
    else()
        set(VS_ADD_NATIVE_VISUALIZERS FALSE CACHE INTERNAL "Native visualizers are a Visual Studio extension" FORCE)
    endif()

    # add natvis file to the library so it will automatically be loaded into Visual Studio
    if (VS_ADD_NATIVE_VISUALIZERS)
        target_sources(utils INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/types.natvis
        )
    endif()
endif()