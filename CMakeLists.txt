project( test)
cmake_minimum_required( VERSION 3.1 )

# set default build type
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")
endif()

include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11"   COMPILER_SUPPORTS_CXX11 )
if( COMPILER_SUPPORTS_CXX11 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-permissive -fpermissive")
endif()

#########################
include_directories("/usr/local/include")
link_directories("/usr/local/lib")
include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(. DIR_SRCS)
add_executable( ${PROJECT_NAME} ${DIR_SRCS} )

target_link_libraries(${PROJECT_NAME}
    pthread
    rt
    dl
    cpr
    curl
    boost_system
    boost_filesystem
)
