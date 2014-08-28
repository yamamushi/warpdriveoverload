include_directories(${WPOServer_SOURCE_DIR}/src/)

set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/
)

add_executable(server main.cpp
			ship.cpp
			player.cpp
			room.cpp
            sqlite.cpp
            logger.cpp
            shell.cpp
            game_engine.cpp
            term_control.cpp
            )


set (CMAKE_CXX_FLAGS "-lsqlite3 -lboost_system -ltermcap -lncurses")
