cmake_minimum_required(VERSION 3.0)

project(BattagliaNavale)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(battaglia_navale src/battaglia_navale.cpp)

add_executable(replay src/replay.cpp)

add_subdirectory(libs)

target_link_libraries(battaglia_navale gameLoops gameHandler player humanPlayer bot ship coord admiral replayer logger corazzata naveSupporto)