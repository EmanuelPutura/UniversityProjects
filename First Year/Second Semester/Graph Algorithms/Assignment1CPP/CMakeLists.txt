cmake_minimum_required(VERSION 3.17)
project(Assignment1CPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment1CPP main.cpp DirectedGraph/DirectedGraph.h DirectedGraph/DirectedGraph.cpp Testing/TestAll.h Testing/TestAll.cpp GraphGenerator/GraphRandomGenerator.h GraphGenerator/GraphRandomGenerator.cpp FileManager/FileManager.h FileManager/FileManager.cpp ConsoleUI/ConsoleUI.h ConsoleUI/ConsoleUI.cpp TextTable/TextTable.h TextTable/TextTable.cpp)