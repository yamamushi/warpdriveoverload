include_directories(${WARPDRIVEOVERLOADED_SOURCE_DIR}/src/
			${WARPDRIVEOVERLOADED_SOURCE_DIR}/deps/vmmlib/include/
			)

include_directories(${ProtobufIncludePath})


set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/
)



add_executable(client main.cpp
            GraphicsDriverManager.cpp
            NcursesManager.cpp
			ship.cpp
			player.cpp
			room.cpp
            sqlite.cpp
            shell.cpp
            game_engine.cpp
            term_control.cpp
            window.cpp
            graphchart.cpp
            interface.cpp
            debugWindow.cpp
            navigation.cpp
            TimeWidget.cpp
            teros.cpp
            terospolygon.cpp
            terosobject.cpp
            teroscam.cpp
            terostest.cpp
            TreasureChest.cpp
            drawing.cpp
            TRModel.cpp
            SphereModel.cpp
            logger.cpp
            bresenham2d.cpp
            MenuWidget.cpp
            WidgetManager.cpp
            ColorManager.cpp
            Clock.cpp
            windowthread.cpp
            Hermes.cpp
            ncurseswindow.cpp
            sdlwindow.cpp
            aalibwindow.cpp
            )
            
target_link_libraries(client messages)

#set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncurses -lprotobuf")
SET_TARGET_PROPERTIES(client PROPERTIES  LINK_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncursesw -lprotobuf")

if(UNIX AND NOT APPLE)
	set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncurses -lprotobuf -lrt")
endif()