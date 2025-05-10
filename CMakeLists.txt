cmake_minimum_required(VERSION 3.15)

# package
set(BEGE_VERSION_MAJOR 0)
set(BEGE_VERSION_MINOR 1)
set(BEGE_VERSION_PATCH 0)
set(BEGE_VERSION_RELEASE_DATE 20250509)

# package project
project(bege
    VERSION "${BEGE_VERSION_MAJOR}.${BEGE_VERSION_MINOR}.${BEGE_VERSION_PATCH}"
    DESCRIPTION "module library treatment for backend godot project"
    HOMEPAGE_URL "https://github.com/prothegee/bege"
    LANGUAGES CXX C
)

# option/s
option(BEGE_BUILD_TESTS         "build project test/s" OFF)
option(BEGE_BUILD_TOOLS         "build project tool/s" OFF)
option(BEGE_BUILD_EXAMPLES      "build project example/s" OFF)
option(BEGE_BUILD_SYSTEM_TARGET "build system target; 1:linux 2:windows 3:macos/osx 4:android 5:ios" OFF)

## rules of options

## build tests as bool
if(BEGE_BUILD_TESTS)
    set(BEGE_BUILD_TESTS true)
else()
    set(BEGE_BUILD_TESTS false)
endif()

## build tools as bool
if(BEGE_BUILD_TOOLS)
    set(BEGE_BUILD_TOOLS true)
else()
    set(BEGE_BUILD_TOOLS false)
endif()

## build type
if(NOT CMAKE_BEGE_BUILD_TYPE)
    set(CMAKE_BEGE_BUILD_TYPE "Debug")
endif()

## cxx standard required
if(NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
## cxx extensions
if(NOT DEFINED CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

## cxx standard
### by default build is set for gnu linux environment
if(NOT DEFINED CMAKE_CXX_STANDARD)
    # automatic standard detection from compiler flags
    set(_detected_standard 17)
    # check for Unix-style flags (-std=c++XX or -std=gnu++XX)
    string(REGEX MATCH "-std=([c|gnu]\\+\\+)([0-9]+)" _ "${CMAKE_CXX_FLAGS}")
    if(CMAKE_MATCH_2)
        set(_detected_standard ${CMAKE_MATCH_2})
    endif()
    # check for MSVC flags (/std:c++XX or /std:c++latest)
    if(NOT _detected_standard AND MSVC)
        string(REGEX MATCH "/std:c\\+\\+latest" _ "${CMAKE_CXX_FLAGS}")
        if(CMAKE_MATCH_0)
            set(_detected_standard latest) # map /std:c++latest to C++20
        else()
            string(REGEX MATCH "/std:c\\+\\+([0-9]+)" _ "${CMAKE_CXX_FLAGS}")
            if(CMAKE_MATCH_1)
                set(_detected_standard ${CMAKE_MATCH_1})
            endif()
        endif()
    endif()
    set(CMAKE_CXX_STANDARD ${_detected_standard} CACHE STRING "C++ standard to use (17, 20, etc.)")
else()
    set(CMAKE_CXX_STANDARD "${CMAKE_CXX_STANDARD}" CACHE STRING "C++ standard to use (17, 20, etc.)" FORCE)
endif()

## cxx flags
### by default build is set for gnu linux environment
if(NOT DEFINED CMAKE_CXX_FLAGS)
    if(MSVC)
        if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
            set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc")
        else()
            set(CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD} /EHsc")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
else()
    # clean existing flags
    string(REGEX REPLACE "-std=[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "/std:c\\+\\+[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REGEX REPLACE "/EH[^ ]+" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # remove old /EH flags
    string(REPLACE "/MP" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")  # remove /MP
    if(MSVC)
        if(CMAKE_CXX_STANDARD GREATER_EQUAL 20)
            set(CMAKE_CXX_FLAGS "/std:c++latest /EHsc")
        else()
            set(CMAKE_CXX_FLAGS "/std:c++${CMAKE_CXX_STANDARD} /EHsc")
        endif()
    else()
        set(CMAKE_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD}")
    endif()
endif()

## rest of the world is debug except Release & MinSizeRel
set(BEGE_IS_DEBUG true)
set(BEGE_BUILD_TYPE)
if(CMAKE_BEGE_BUILD_TYPE STREQUAL "Release")
    set(BEGE_IS_DEBUG false) 
    set(BEGE_BUILD_TYPE "release")
elseif(CMAKE_BEGE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(BEGE_IS_DEBUG false) 
    set(BEGE_BUILD_TYPE "release")
else()
    set(BEGE_IS_DEBUG true)
    set(BEGE_BUILD_TYPE "debug")
endif()
## bege godot-cpp dir
if(NOT DEFINED BEGE_GODOT_CPP_DIR)
    set(BEGE_GODOT_CPP_DIR)
endif()
## bege vcpkg triplet
if(NOT DEFINED BEGE_VCPKG_TRIPLET)
    set(BEGE_VCPKG_TRIPLET)
endif()
## system name
if(NOT DEFINED BEGE_SYSTEM_NAME)
    set(BEGE_SYSTEM_NAME "")
endif()
string(TOLOWER "${CMAKE_SYSTEM_NAME}" BEGE_SYSTEM_NAME)
### rules of os
if(${BEGE_SYSTEM_NAME} STREQUAL "macos")
    set(BEGE_SYSTEM_NAME "osx")
elseif(${BEGE_SYSTEM_NAME} STREQUAL "darwin")
    set(BEGE_SYSTEM_NAME "osx")
else()
    # force otherwise
    string(TOLOWER "${CMAKE_SYSTEM_NAME}" BEGE_SYSTEM_NAME)
endif()

## system process
if(NOT DEFINED BEGE_PROCESSOR_SYSTEM)
    set(BEGE_PROCESSOR_SYSTEM "")
endif()
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" BEGE_PROCESSOR_SYSTEM)

# include base
include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakeFindDependencyMacro)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

# files
## headers files
if(NOT DEFINED BEC_HEADERS_FILES)
    set(BEC_HEADERS_FILES)
endif()

## sources files
if(NOT DEFINED BEGE_SOURCES_FILES)
    set(BEGE_SOURCES_FILES)
endif()

list(APPEND
    BEGE_SOURCES_FILES
        sources/src/bege.cc
        # functions
        # nodes
        # objects
        # platforms:linux
        # platforms:windows
        # platforms:osx
        # platforms:android
        # platforms:ios
)

# packages, lib related
## 
## base toolchain
if(NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    message(NOTICE "-- bege: default toolchain from -DCMAKE_TOOLCHAIN_FILE is \"${CMAKE_TOOLCHAIN_FILE}\"")
    include("${CMAKE_TOOLCHAIN_FILE}")
else()
    message(NOTICE "-- bege: default toolchain from -DCMAKE_TOOLCHAIN_FILE is empty")
endif()
##
## triplet & processor
if(ANDROID)
    if(ANDROID_ABI STREQUAL "")
        message(FATAL_ERROR "-- bege: ANDROID_ABI is empty, please provide 1; armeabi-v7a for arm32, arm64-v8a for arm64, x86_64 for x86_64 emulator?")
    endif()
    if(NOT ANDROID_PLATFORM)
        message(WARNING "-- bege: ANDROID_PLATFORM is not set, using default min api, see https://en.wikipedia.org/wiki/Android_version_history#Overview")
    endif()

    message(NOTICE "-- becc: ANDROID_ABI: ${ANDROID_ABI}")
    message(NOTICE "-- becc: ANDROID_PLATFORM: ${ANDROID_PLATFORM}")

    if(ANDROID_ABI STREQUAL "armeabi-v7a")
        set(BEGE_VCPKG_TRIPLET "arm-neon-android")  # explicitly use NEON-enabled ARM triplet
        set(BEGE_PROCESSOR_OUTPUT "arm32")
    elseif(ANDROID_ABI STREQUAL "arm64-v8a")
        set(BEGE_VCPKG_TRIPLET "arm64-android")
        set(BEGE_PROCESSOR_OUTPUT "arm64")
    elseif(ANDROID_ABI STREQUAL "x86_64")
        set(BEGE_VCPKG_TRIPLET "x64-android")
        set(BEGE_PROCESSOR_OUTPUT "x86_64")
    else()
        message(FATAL_ERROR "-- bege: unsupported android ABI: ${ANDROID_ABI}")
    endif()

    set(BEGE_BUILD_SYSTEM_TARGET 4)
    set(BEGE_BUILD_SYSTEM_TARGET_NAME "android")

    message(STATUS "TODO: include dir from java")
    message(STATUS "TODO: include dir from android")
elseif(WIN32)
    # windows architectures
    if(BEGE_PROCESSOR_SYSTEM STREQUAL "x86_64")
        set(BEGE_VCPKG_TRIPLET "x64-windows")
        set(BEGE_PROCESSOR_OUTPUT "x86_64")
    # elseif(BEGE_PROCESSOR_SYSTEM STREQUAL "x86") # not gonna support it
    #     set(BEGE_VCPKG_TRIPLET "x86-windows")
    #     set(BEGE_PROCESSOR_OUTPUT "x86_32")
    elseif(BEGE_PROCESSOR_SYSTEM STREQUAL "amd64")
        set(BEGE_VCPKG_TRIPLET "x64-windows")
        set(BEGE_PROCESSOR_OUTPUT "x86_64")
    else()
        message(FATAL_ERROR "-- bege: unsupported windows architecture: ${BEGE_PROCESSOR_SYSTEM}")
    endif()

    set(BEGE_BUILD_SYSTEM_TARGET 2)
    set(BEGE_BUILD_SYSTEM_TARGET_NAME "windows")
elseif(APPLE)
    # macOS/iOS architectures
    if(IOS)
        set(BEGE_VCPKG_TRIPLET "arm64-ios")
        set(BEGE_PROCESSOR_OUTPUT "arm64")
        set(BEGE_BUILD_SYSTEM_TARGET 5)
        set(BEGE_BUILD_SYSTEM_TARGET_NAME "ios")
    else()
        if(BEGE_PROCESSOR_SYSTEM STREQUAL "arm64")
            set(BEGE_VCPKG_TRIPLET "arm64-osx")
            set(BEGE_PROCESSOR_OUTPUT "arm64")
        else()
            set(BEGE_VCPKG_TRIPLET "x64-osx")
            set(BEGE_PROCESSOR_OUTPUT "x86_64")
        endif()

        set(BEGE_BUILD_SYSTEM_TARGET 3)
        set(BEGE_BUILD_SYSTEM_TARGET_NAME "osx")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # assume x64 for Linux
    set(BEGE_VCPKG_TRIPLET "x64-linux")
    set(BEGE_PROCESSOR_OUTPUT "x86_64")
    
    set(BEGE_BUILD_SYSTEM_TARGET 1)
    set(BEGE_BUILD_SYSTEM_TARGET_NAME "linux")
else()
    message(FATAL_ERROR "-- bege: unsupported platform: ${CMAKE_SYSTEM_NAME}")
    set(BEGE_BUILD_SYSTEM_TARGET 0)
endif()
##
## godot-cpp
set(BEGE_GODOT_CPP_FOUND false)
if(NOT "$ENV{GODOT_CPP_DIR}" STREQUAL "")
    set(BEGE_GODOT_CPP_DIR "$ENV{GODOT_CPP_DIR}")
    set(BEGE_GODOT_CPP_FOUND true)
else()
    if("${GODOT_CPP_DIR}" STREQUAL "")
        message(FATAL_ERROR "-- becc: environemnt GODOT_CPP_DIR is empty & config -DGODOT_CPP_DIR is also empty")
    else()
        set(BEGE_GODOT_CPP_DIR "${GODOT_CPP_DIR}")
        set(BEGE_GODOT_CPP_FOUND true)
    endif()
endif()
add_subdirectory("${BEGE_GODOT_CPP_DIR}" BEGE_GODOT_CPP)
##
## package manager: vcpkg
set(BEGE_VCPKG_FOUND false)
if(NOT "$ENV{VCPKG_DIR}" STREQUAL "")
    set(BEGE_VCPKG_DIR "$ENV{VCPKG_DIR}")
    set(BEGE_VCPKG_FOUND true)
else()
    # 2nd attempt but using -DVCPKG_DIR
    if("${VCPKG_DIR}" STREQUAL "")
        message(AUTHOR_WARNING "-- becc: environemnt VPCKG_DIR is empty & config -DVCPKG_DIR is also empty")
    else()
        set(BEGE_VCPKG_DIR "${VCPKG_DIR}")
        set(BEGE_VCPKG_FOUND true)
    endif()
endif()
if(BEGE_VCPKG_FOUND)
    ### vcpkg: default triplet
    set(VCPKG_TARGET_TRIPLET "${BEGE_VCPKG_TRIPLET}")

    include("${BEGE_VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")

    ## should not happen
    if(VCPKG_TARGET_TRIPLET STREQUAL "")
        message(FATAL_ERROR "-- bege: this shouldn't happen")
    endif()
endif()
set(BEGE_VCPKG_DIR_INSTALLED "${BEGE_VCPKG_DIR}/installed/${BEGE_VCPKG_TRIPLET}")
if(EXISTS "${BEGE_VCPKG_DIR_INSTALLED}")
    # link bin dirs
    include_directories(    "${BEGE_VCPKG_DIR_INSTALLED}/bin")
    link_directories(BEFORE "${BEGE_VCPKG_DIR_INSTALLED}/bin")
    include_directories(    "${BEGE_VCPKG_DIR_INSTALLED}/debug/bin")
    link_directories(BEFORE "${BEGE_VCPKG_DIR_INSTALLED}/debug/bin")

    # include dirs
    include_directories(    "${BEGE_VCPKG_DIR_INSTALLED}/include")
    link_directories(BEFORE "${BEGE_VCPKG_DIR_INSTALLED}/include")
    include_directories(    "${BEGE_VCPKG_DIR_INSTALLED}/debug/include")
    link_directories(BEFORE "${BEGE_VCPKG_DIR_INSTALLED}/debug/include")

    # link lib dirs
    include_directories(    "${BEGE_VCPKG_DIR_INSTALLED}/lib")
    link_directories(BEFORE "${BEGE_VCPKG_DIR_INSTALLED}/lib")
    include_directories(    "${BEGE_VCPKG_DIR_INSTALLED}/debug/lib")
    link_directories(BEFORE "${BEGE_VCPKG_DIR_INSTALLED}/debug/lib")

    # link share dirs
    include_directories(    "${BEGE_VCPKG_DIR_INSTALLED}/share")
    link_directories(BEFORE "${BEGE_VCPKG_DIR_INSTALLED}/share")
else()
    message(AUTHOR_WARNING "-- ${PROJECT_NAME}: vpckg environment variable not found")
endif()
##
## python3
## bege python3
if(NOT DEFINED BEGE_PYTHON3_EXEC)
    set(BEGE_PYTHON3_EXEC)
endif()
if(NOT DEFINED Python3_EXECUTABLE)
    set(Python3_EXECUTABLE)
endif()
find_package(Python3)
if(Python3_FOUND)
    message(NOTICE "-- bege: found python3 as \"${Python3_EXECUTABLE}\"")
    set(BEGE_PYTHON3_EXEC "${Python3_EXECUTABLE}")
else()
    if(Python3_EXECUTABLE STREQUAL "")
        message(FATAL_ERROR "-- bege: python3 required, if package not found, try add -DPython3_EXECUTABLE=to/path/python3_exec")
    else()
        message(NOTICE "-- bege: can't found python3 package, but able to found python3 exec")
        set(BEGE_PYTHON3_EXEC "${Python3_EXECUTABLE}")
    endif()
endif()
##
## openssl
find_package(OpenSSL REQUIRED)
if(OpenSSL_FOUND)
    message(NOTICE "-- ${PROJECT_NAME}: openssl package found")
else()
    message(FATAL_ERROR "-- ${PROJECT_NAME}: openssl package not found")
endif()

# reserved: pre build

# project lib
## object core lib
add_library(${PROJECT_NAME} OBJECT ${BEGE_SOURCES_FILES})
## static core lib
add_library(bege_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}>)
## shared code lib
add_library(bege_shared SHARED $<TARGET_OBJECTS:${PROJECT_NAME}>)
### lib/s name
#### lib output
set(BEGE_OUTPUT_NAME "bege")
#### lib output suffix
set(BEGE_OUTPUT_SUFFIX_NAME "${BEGE_BUILD_SYSTEM_TARGET}.${BEGE_PROCESSOR_OUTPUT}.${BEGE_BUILD_TYPE}")
#### libs windows and else
if(WIN32)
    set_target_properties(bege_static PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
    set_target_properties(bege_shared PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
else()
    set_target_properties(bege_static PROPERTIES
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
    set_target_properties(bege_shared PROPERTIES
        OUTPUT_NAME "${BEGE_OUTPUT_NAME}"
    )
endif()

# post build prep
if(NOT DEFINED BEGE_BUILD_FILES)
    set(BEGE_BUILD_FILES)
endif()
if(NOT DEFINED BEGE_BUILD_FILES_DIR)
    set(BEGE_BUILD_FILES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/addons/bege/bin/${BEGE_BUILD_SYSTEM_TARGET_NAME}/${BEGE_BUILD_TYPE}/${BEGE_PROCESSOR_OUTPUT}")

    if(NOT EXISTS "${BEGE_BUILD_FILES_DIR}")
        file(MAKE_DIRECTORY "${BEGE_BUILD_FILES_DIR}")
    endif()
endif()
if(WIN32)
    file(GLOB BEGE_BUILD_FILES "${CMAKE_BINARY_DIR}/bege.*")
else()
    file(GLOB BEGE_BUILD_FILES "${CMAKE_BINARY_DIR}/libbege.*")
endif()

# compiler options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(BEGE_COMPILER_ID    1)
    set(BEGE_COMPILER_GNU   true)
    set(BEGE_COMPILER_MSVC  false)
    set(BEGE_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-value
        -Wno-unused-variable
        -Wno-reorder
        -Wno-parentheses
        -Wno-switch
        -Wno-format
        -Wno-invalid-offsetof
        -Wno-multichar
        -Wno-char-subscripts
        -Wno-empty-body
        -Wno-unused-function
        -Wno-deprecated-declarations
        -lm
        -fPIC
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(BEGE_COMPILER_ID    2)
    set(BEGE_COMPILER_GNU   false)
    set(BEGE_COMPILER_MSVC  true)
    set(BEGE_COMPILER_CLANG false)

    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /wd4996
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
    set(BEGE_COMPILER_ID    3)
    set(BEGE_COMPILER_GNU   false)
    set(BEGE_COMPILER_MSVC  false)
    set(BEGE_COMPILER_CLANG true)

    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-value
        -Wno-unused-variable
        -Wno-reorder
        -Wno-parentheses
        -Wno-switch
        -Wno-format
        -Wno-dynamic-class-memaccess
        -Wno-unused-private-field
        -Wno-invalid-offsetof
        -Wno-multichar
        -Wno-char-subscripts
        -Wno-null-conversion
        -Wno-empty-body
        -Wno-unused-lambda-capture
        -Wno-unused-function
        -Wno-tautological-constant-out-of-range-compare
        -Wno-deprecated-declarations
        -fPIC
    )
else()
    set(BEGE_COMPILER_ID    0)
    set(BEGE_COMPILER_GNU   false)
    set(BEGE_COMPILER_MSVC  false)
    set(BEGE_COMPILER_CLANG false)

    message(NOTICE "-- ${PROJECT_NAME}: -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
endif()

if(BEGE_COMPILER_GNU) # gcc 12.2
    target_link_libraries(${PROJECT_NAME} PRIVATE -lm)

    if(EXISTS "/usr/lib/x86_64-linux-gnu/libm.so")
        target_link_libraries(${PROJECT_NAME} PRIVATE "/usr/lib/x86_64-linux-gnu/libm.so") # somehow build not error
    else()
        message(WARNING "-- ${PROJECT_NAME}: for gcc has error, be warn")
    endif()
endif()

## warning?

# bege config
## n/a

# bege export
## n/a

# bege shared definitions
target_compile_definitions(bege_shared PRIVATE BEGE_SHARED)

# target include dirs
## core include: src/inc
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/sources/inc
)

# target source
## dont expand this yet
target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/src
)

# dependencies for static & shared
## loop dependencies target
foreach(BEGE_TARGET ${PROJECT_NAME} bege_static bege_shared)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(${BEGE_TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wno-unused-value
            -Wno-unused-variable
            -Wno-reorder
            -Wno-parentheses
            -Wno-switch
            -Wno-format
            -Wno-invalid-offsetof
            -Wno-multichar
            -Wno-char-subscripts
            -Wno-empty-body
            -Wno-unused-function
            -Wno-deprecated-declarations
            -lm
            -fPIC
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${BEGE_TARGET} PRIVATE
            /W4
            /wd4996
            /EHsc
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
        target_compile_options(${BEGE_TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wno-unused-value
            -Wno-unused-variable
            -Wno-reorder
            -Wno-parentheses
            -Wno-switch
            -Wno-format
            -Wno-dynamic-class-memaccess
            -Wno-unused-private-field
            -Wno-invalid-offsetof
            -Wno-multichar
            -Wno-char-subscripts
            -Wno-null-conversion
            -Wno-empty-body
            -Wno-unused-lambda-capture
            -Wno-unused-function
            -Wno-tautological-constant-out-of-range-compare
            -Wno-deprecated-declarations
            -fPIC
        )
    else()
        message(NOTICE "-- ${PROJECT_NAME}: -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
    endif()

    ##
    ## godot-cpp
    target_link_libraries(${BEGE_TARGET} PRIVATE godot-cpp)
    ##
    ## openssl
    target_link_libraries(${BEGE_TARGET} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

    ## post build copy lib
    if(NOT "${BEGE_TARGET}" STREQUAL ${PROJECT_NAME})
        foreach(FILE ${BEGE_BUILD_FILES})
            add_custom_command(
                TARGET ${BEGE_TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${FILE}
                    ${BEGE_BUILD_FILES_DIR}
                    COMMENT "copying ${file} to addons of bege"
            )
        endforeach()
        # Use a custom script or alternative method for directory copy if needed
        add_custom_command(
            TARGET ${BEGE_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/addons
                ${PROJECT_SOURCE_DIR}/examples/addons
                COMMENT "copying addons to examples"
        )
    endif()
endforeach()

# version shared lib
set_target_properties(bege_shared PROPERTIES
    VERSION "${BEGE_VERSION_MAJOR}.${BEGE_VERSION_MINOR}.${BEGE_VERSION_PATCH}"
    SOVERSION "${BEGE_VERSION_MAJOR}.${BEGE_VERSION_MINOR}.${BEGE_VERSION_PATCH}"
)

# build tests
if(BEGE_BUILD_TESTS)
    # n/a
endif(BEGE_BUILD_TESTS)

# build tools
if(BEGE_BUILD_TOOLS)
    # n/a
endif(BEGE_BUILD_TOOLS)

# check
## cxx flags
if(CMAKE_CXX_FLAGS STREQUAL "")
    message(WARNING "-- bege: cxx flags is empty for some reason")
else()
    message(NOTICE "-- bege: build info\n   -DCMAKE_CXX_FLAGS=\"${CMAKE_CXX_FLAGS}\"")
endif()