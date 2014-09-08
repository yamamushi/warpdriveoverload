include_directories(${WARPDRIVEOVERLOADED_SOURCE_DIR}/src/
			${WARPDRIVEOVERLOADED_SOURCE_DIR}/deps/vmmlib/include/
			)

include_directories(${ProtobufIncludePath})


set(
CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/
)

set(WARPDRIVEOVERLOADED_CLIENT_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/client/main.cpp
  )

set(WARPDRIVEOVERLOADED_CLIENT_HEADERS)


add_subdirectory(messages)

add_subdirectory(client)
add_subdirectory(db)
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(graphics)
add_subdirectory(interfaces)
add_subdirectory(managers)
add_subdirectory(network)
add_subdirectory(teros)
add_subdirectory(terosmodels)
add_subdirectory(tr1)
add_subdirectory(util)
add_subdirectory(widgets)
add_subdirectory(wintypes)


set_source_files_properties(${PROTO_SRC} ${PROTO_HEADER} PROPERTIES GENERATED TRUE)

add_executable(warpclient ${WARPDRIVEOVERLOADED_CLIENT_SOURCE} ${WARPDRIVEOVERLOADED_CLIENT_HEADERS})

target_link_libraries(warpclient messages)




SET_TARGET_PROPERTIES(warpclient PROPERTIES  LINK_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncursesw -lprotobuf")

if(UNIX AND NOT APPLE)
        set (CMAKE_CXX_FLAGS "-std=c++0x -lsqlite3 -lboost_system -lpthread -ltermcap -lncurses -lprotobuf -lrt")
endif()

