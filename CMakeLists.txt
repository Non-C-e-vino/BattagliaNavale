cmake_minimum_required(VERSION 3.0)

project(BattagliaNavale)

add_executable(battaglia_navale src/battaglia_navale.cpp)

add_executable(replay src/replay.cpp)

add_subdirectory(libs)

target_include_directories(battaglia_navale PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(gameLoops PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(ship PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(bot PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(player PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(humanPlayer PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_include_directories(coord PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(battaglia_navale gameLoops player humanPlayer bot ship coord)