cmake_minimum_required(VERSION 2.4)

set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} "")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /usr/local/lib/)
LINK_DIRECTORIES(/usr/local/lib)

include (FindPkgConfig)
if (PKG_CONFIG_FOUND)
  pkg_check_modules(Protobuf protobuf)
endif()
find_package(Protobuf REQUIRED)


include_directories(${ProtobufIncludePath})

project(wpoclient)

SET(WARPDRIVEOVERLOADED_VERSION 0.02)
SET(PROJECT_NAME wpoclient)
SET(CMAKE_INCLUDE_CURRENT_DIR TRUE)

add_subdirectory(data)
set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES GENERATED TRUE)

add_subdirectory(src)



