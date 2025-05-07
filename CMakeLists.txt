cmake_minimum_required(VERSION 3.15)

# version
set(BEGE_VERSION_MAJOR 0)
set(BEGE_VERSION_MINOR 1)
set(BEGE_VERSION_PATCH 1)
set(BEGE_VERSION_RELEASE_DATE 20250507)

set(BEGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# project
project(bege
    VERSION "${BEGE_VERSION_MAJOR}.${BEGE_VERSION_MINOR}.${BEGE_VERSION_PATCH}"
    DESCRIPTION "module library treatment for backend godot project"
    HOMEPAGE_URL "https://github.com/prothegee/bege"
    LANGUAGES CXX
)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BEGE_SOURCE_DIR}/addons/bege/bin") # skipped for now

# bege variables
## bege is debug
if(NOT DEFINED BEGE_IS_DEBUG)
    set(BEGE_IS_DEBUG true)
endif()
## bege build processor
if(NOT DEFINED BEGE_PROCESSOR_SYSTEM)
    set(BEGE_PROCESSOR_SYSTEM)
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" BEGE_PROCESSOR_SYSTEM)
endif()
##
if(NOT DEFINED BEGE_PROCESSOR_OUTPUT)
    set(BEGE_PROCESSOR_OUTPUT)
endif()
## bege build target info
if(NOT DEFINED BEGE_BUILD_TARGET_INFO)
    set(BEGE_BUILD_TARGET_INFO)

    if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        set(BEGE_IS_DEBUG false)
        set(BEGE_BUILD_TARGET_INFO "release")
    else()
        set(BEGE_BUILD_TARGET_INFO "debug")
    endif()
endif()
## bege build system info
if(NOT DEFINED BEGE_BUILD_SYSTEM_INFO)
    set(BEGE_BUILD_SYSTEM_INFO)
endif()
## bege godot-cpp dir
if(NOT DEFINED BEGE_GODOT_CPP_DIR)
    set(BEGE_GODOT_CPP_DIR)
endif()
## bege vcpkg triplet
if(NOT DEFINED BEGE_VCPKG_TRIPLET)
    set(BEGE_VCPKG_TRIPLET)
endif()
## bege vcpkg installed dir
if(NOT DEFINED BEGE_VCPKG_DIR)
    set(BEGE_VCPKG_DIR)
endif()
## bege python3
if(NOT DEFINED BEGE_PYTHON3_EXEC)
    set(BEGE_PYTHON3_EXEC)
endif()

# check requirements
## godot-cpp
set(BEGE_GODOT_CPP_FOUND false)
if(NOT "$ENV{GODOT_CPP_DIR}" STREQUAL "")
    set(BEGE_GODOT_CPP_DIR "$ENV{GODOT_CPP_DIR}")
    set(BEGE_GODOT_CPP_FOUND true)
else()
    message(FATAL_ERROR "-- becc: environemnt VPCKG_DIR is required")
endif()
## vcpkg
set(BEGE_VCPKG_FOUND false)
if(NOT "$ENV{VCPKG_DIR}" STREQUAL "")
    set(BEGE_VCPKG_DIR "$ENV{VCPKG_DIR}")
    set(BEGE_VCPKG_FOUND true)
else()
    message(FATAL_ERROR "-- becc: environemnt VPCKG_DIR is required")
endif()

# options
set(BEGE_BUILD_TESTS       "build project test/s (not godot examples tests)" OFF)
set(BEGE_BUILD_TOOLS       "build project tool/s" OFF)
set(BEGE_BUILD_EXAMPLES    "build project example/s" OFF)

# rules of options
## build tests
if(BEGE_BUILD_TESTS)
    set(BEGE_BUILD_TESTS true)
else()
    set(BEGE_BUILD_TESTS false)
endif()
## build tools
if(BEGE_BUILD_TOOLS)
    set(BEGE_BUILD_TOOLS true)
else()
    set(BEGE_BUILD_TOOLS false)
endif()
## build examples
if(BEGE_BUILD_EXAMPLES)
    set(BEGE_BUILD_EXAMPLES true)
else()
    set(BEGE_BUILD_EXAMPLES false)
endif()

# reserved: TODO - pre configur, if any

# include cmake
include(CheckIncludeFileCXX)
include(GenerateExportHeader)
include(CMakeDependentOption)
include(CMakeFindDependencyMacro)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

# sources files
if(NOT DEFINED BEGE_HEADERS_FILES)
    set(BEGE_HEADERS_FILES)
endif()

# sources files
if(NOT DEFINED BEGE_SOURCES_FILES)
    set(BEGE_SOURCES_FILES)
endif()
## sources files: append
list(APPEND
    BEGE_SOURCES_FILES
        # core
        sources/src/bege.cc
        # functions
        # nodes
        # objects
        # platforms: android
        # platforms: ios
        # platforms: linux
        # platforms: macos
        # platforms: windows
)

# reserved: a

# main cmake toolchain file
if(NOT "${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
    message(NOTICE "-- bege: default toolchain from -DCMAKE_TOOLCHAIN_FILE is \"${CMAKE_TOOLCHAIN_FILE}\"")
    include("${CMAKE_TOOLCHAIN_FILE}")
else()
    message(NOTICE "-- bege: default toolchain from -DCMAKE_TOOLCHAIN_FILE is empty")
endif()

# subdir: core
## godot-cpp
add_subdirectory("${BEGE_GODOT_CPP_DIR}" BEGE_GODOT_CPP)
## triplet and processor
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

    set(BEGE_BUILD_SYSTEM_INFO "android")

    message(STATUS "TODO: include dir from java")
    message(STATUS "TODO: include dir from android")
elseif(WIN32)
    # windows architectures
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(BEGE_VCPKG_TRIPLET "x64-windows")
        set(BEGE_PROCESSOR_OUTPUT "x86_64")
    # elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86") # not gonna support it
    #     set(BEGE_VCPKG_TRIPLET "x86-windows")
    #     set(BEGE_PROCESSOR_OUTPUT "x86_32")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
        set(BEGE_VCPKG_TRIPLET "x64-windows")
        set(BEGE_PROCESSOR_OUTPUT "x86_64")
    else()
        message(FATAL_ERROR "-- bege: unsupported windows architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()

    set(BEGE_BUILD_SYSTEM_INFO "windows")
elseif(APPLE)
    # macOS/iOS architectures
    if(IOS)
        set(BEGE_VCPKG_TRIPLET "arm64-ios")
        set(BEGE_BUILD_SYSTEM_INFO "ios")
        set(BEGE_PROCESSOR_OUTPUT "arm64")
    else()
        if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
            set(BEGE_VCPKG_TRIPLET "arm64-osx")
            set(BEGE_PROCESSOR_OUTPUT "arm64")
        else()
            set(BEGE_VCPKG_TRIPLET "x64-osx")
            set(BEGE_PROCESSOR_OUTPUT "x64")
        endif()

        set(BEGE_BUILD_SYSTEM_INFO "osx")
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # assume x64 for Linux
    set(BEGE_VCPKG_TRIPLET "x64-linux")
    set(BEGE_BUILD_SYSTEM_INFO "linux")
    set(BEGE_PROCESSOR_OUTPUT "x64")
else()
    message(FATAL_ERROR "-- bege: unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

## vcpkg
### vcpkg: default triplet
set(VCPKG_TARGET_TRIPLET "${BEGE_VCPKG_TRIPLET}")
### vcpkg: toolchain
include("${BEGE_VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake")
### vcpkg: installed directory
set(BEGE_VCPKG_DIR_INSTALLED "${BEGE_VCPKG_DIR}/installed/${BEGE_VCPKG_TRIPLET}")
### vcpkg: configure
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
    message(FATAL_ERROR "-- ${PROJECT_NAME}: vpckg error")
endif()

# package
## find: python3, required to build object docs
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

# project lib
## project core lib
add_library(${PROJECT_NAME} SHARED ${BEGE_SOURCES_FILES})
## project core lib output
set(BEGE_SHARED_OUTPUT_NAME "bege.${BEGE_BUILD_SYSTEM_INFO}.${BEGE_PROCESSOR_OUTPUT}.${BEGE_BUILD_TARGET_INFO}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF

    POSITION_INDEPENDENT_CODE ON
    BUILD_RPATH_USE_ORIGIN ON

    LINK_SEARCH_START_STATIC ON
    LINK_SEARCH_END_STATIC ON

    LIBRARY_OUTPUT_DIRECTORY "$<1:${CMAKE_BINARY_DIR}>"
    RUNTIME_OUTPUT_DIRECTORY "$<1:${CMAKE_BINARY_DIR}>"
    PDB_OUTPUT_DIRECTORY     "$<1:${CMAKE_BINARY_DIR}>"

    OUTPUT_NAME "${BEGE_SHARED_OUTPUT_NAME}"
)
### any specific?

# link libraries
## godot-cpp
target_link_libraries(${PROJECT_NAME} PRIVATE godot-cpp)
## openssl
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
## sdl3
## sdl3-image
## zxing-cpp

# target include dirs
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/sources/inc
)

# target source
target_sources(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/src
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
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
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /wd4996
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "[Cc]lang")
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
    message(NOTICE "-- ${PROJECT_NAME}: -DCMAKE_CXX_COMPILER_ID is not supported as ${CMAKE_CXX_COMPILER_ID}")
endif()

# # TMP: do not remove, generate docs class
# ## kinda bothering for now & too lazy @prothegee
# if(BEGE_IS_DEBUG AND BEGE_PYTHON3_EXEC)
#     message(NOTICE "-- bege: creating documentation for debug")

#     set(BEGE_DOC_DATA_GEN_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/sources/src/documentations.gen.cc")

#     # force remove before generating again
#     file(REMOVE "${BEGE_DOC_DATA_GEN_SOURCE}")

#     file(GLOB_RECURSE BEGE_DOC_XML
#         LIST_DIRECTORIES NO
#         CONFIGURE_DEPENDS
#         "${CMAKE_CURRENT_SOURCE_DIR}/sources/xml/*.xml"
#     )

#     generate_doc_source("${BEGE_DOC_DATA_GEN_SOURCE}" "${BEGE_DOC_XML}")

#     target_sources(${PROJECT_NAME} PRIVATE "${BEGE_DOC_DATA_GEN_SOURCE}")
# endif()

# reserved: config

# reserved: export

# reserved: TODO - post build, if any