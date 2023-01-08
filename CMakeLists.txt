cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Release)

project(BattagliaNavale)

#Come da consegna. Funziona solo per generatori a singola configurazione.
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(include)

add_executable(battaglia_navale src/battaglia_navale.cpp)

add_executable(replay src/replay.cpp)

add_subdirectory(libs)

target_link_libraries(battaglia_navale gameLoops gameHandler player bot humanPlayer ship coord admiral logger corazzata naveSupporto ricognitore)

target_link_libraries(replay replayLoops gameHandler ship coord admiral logger corazzata naveSupporto ricognitore)