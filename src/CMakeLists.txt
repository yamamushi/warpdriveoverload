include_directories(${WPOServer_SOURCE_DIR}/src/)

set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/
)

add_executable(client main.cpp
			ship.cpp
			player.cpp
			room.cpp
            sqlite.cpp
            shell.cpp
            game_engine.cpp
            term_control.cpp
            window.cpp
            menu.cpp
            graphchart.cpp
            interface.cpp
            debugWindow.cpp
            navigation.cpp
            TimeWidget.cpp
            teros.cpp
            terospolygon.cpp
            terosR3.cpp
            terostest.cpp
            TreasureChest.cpp
            drawing.cpp
            )

set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncurses")
