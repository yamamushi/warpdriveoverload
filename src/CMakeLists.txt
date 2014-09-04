include_directories(${wpoclient_SOURCE_DIR}/src/ 
			${wpoclient_SOURCE_DIR}/src/vmmlib/include/
			)

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
            TRModel.cpp
            SphereModel.cpp
            vector2d.cpp
            vector3d.cpp
            logger.cpp  
            )

set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncurses")
