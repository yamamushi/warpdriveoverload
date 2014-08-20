include_directories(${WPOServer_SOURCE_DIR}/src/)

set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/
)

add_executable(server main.cpp
			ship.cpp
			player.cpp
			room.cpp
            sqlite.cpp
            )


set (CMAKE_CXX_FLAGS "-lsqlite3")
