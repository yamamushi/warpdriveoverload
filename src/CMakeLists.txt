include_directories(${WPOServer_SOURCE_DIR}/src/)

set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/
)

add_executable(client main.cpp
			ship.cpp
			player.cpp
			room.cpp
            sqlite.cpp
            logger.cpp
            shell.cpp
            game_engine.cpp
            term_control.cpp
            window.cpp
            )

set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lboost_thread-mt -ltermcap -lncurses")
