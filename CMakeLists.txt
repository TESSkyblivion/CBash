# Settings passed on the command line:
#
# BUILD_SHARED_LIBS
# PROJECT_STATIC_RUNTIME
# CBASH_NO_BOOST_ZLIB

##############################
# General Settings
##############################

cmake_minimum_required (VERSION 3.0)
project (CBash)

option(BUILD_SHARED_LIBS "Build a shared library" ON)
option(PROJECT_STATIC_RUNTIME "Build with static runtime libs (/MT)" ON)
option(CBASH_NO_BOOST_ZLIB "Build with external Zlib" OFF)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME PROJECT_STATIC_RUNTIME)

file (GLOB_RECURSE CBASH_FONV "${CMAKE_SOURCE_DIR}/FalloutNewVegas/*.cpp")
file (GLOB_RECURSE CBASH_OBLIVION "${CMAKE_SOURCE_DIR}/Oblivion/*.cpp")
file (GLOB_RECURSE CBASH_SKYRIM "${CMAKE_SOURCE_DIR}/Skyrim/*.cpp")

set (CBASH_SRC  "${CMAKE_SOURCE_DIR}/CBash.cpp"
                "${CMAKE_SOURCE_DIR}/Collection.cpp"
                "${CMAKE_SOURCE_DIR}/Common.cpp"
                "${CMAKE_SOURCE_DIR}/GenericChunks.cpp"
                "${CMAKE_SOURCE_DIR}/GenericRecord.cpp"
                "${CMAKE_SOURCE_DIR}/ModFile.cpp"
                "${CMAKE_SOURCE_DIR}/TES4Record.cpp"
                "${CMAKE_SOURCE_DIR}/TES4RecordAPI.cpp"
                "${CMAKE_SOURCE_DIR}/Visitors.cpp"
                "${CMAKE_SOURCE_DIR}/CBash.rc"
                ${CBASH_FONV}
                ${CBASH_OBLIVION}
                ${CBASH_SKYRIM}
                )

IF (CBASH_NO_BOOST_ZLIB)
    add_definitions(-DCBASH_NO_BOOST_ZLIB)
    find_package(Boost REQUIRED COMPONENTS iostreams)
    find_package(ZLIB REQUIRED)
    set (CBASH_LIBS ${ZLIB_LIBRARY})
ELSE ()
    find_package(Boost REQUIRED COMPONENTS iostreams zlib)
    find_package(ZLIB)
    set (CBASH_LIBS "")
ENDIF ()

# Include source and library directories.
include_directories ("${CMAKE_SOURCE_DIR}/FalloutNewVegas"
                     "${CMAKE_SOURCE_DIR}/Oblivion"
                     "${CMAKE_SOURCE_DIR}/Skyrim"
                     ${Boost_INCLUDE_DIRS}
                     ${ZLIB_INCLUDE_DIR})

link_directories ()


##############################
# System-Specific Settings
##############################

# Settings when compiling for Windows. Since it's a Windows-only app this is always true, but useful to check for copy/paste into other projects.
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions (-DUNICODE -D_UNICODE -DNDEBUG -DWIN32 -D_WINDOWS)
    IF (BUILD_SHARED_LIBS)
        add_definitions (-DCBASH_DLL)
    ELSE ()
        add_definitions (-DCBASH_STATIC)
    ENDIF ()
ENDIF ()

IF (MSVC)
    IF (MSVC_VERSION EQUAL 1800)
        set (CMAKE_GENERATOR_TOOLSET "v120_xp" CACHE STRING "Platform Toolset" FORCE)
    ELSEIF (MSVC_VERSION EQUAL 1700)
        set (CMAKE_GENERATOR_TOOLSET "v110_xp" CACHE STRING "Platform Toolset" FORCE)
    ENDIF ()

    # Force static C++ runtime linkage.
    IF (PROJECT_STATIC_RUNTIME)
        FOREACH(flag
            CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
            CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
            STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
            SET("${flag}" "${${flag}} /EHsc")
        ENDFOREACH()
    ENDIF ()

    set (CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
ENDIF ()


##############################
# Actual Building
##############################

# Build CBash.
add_library           (CBash ${CBASH_SRC})
target_link_libraries (CBash ${Boost_LIBRARIES} ${CBASH_LIBS})