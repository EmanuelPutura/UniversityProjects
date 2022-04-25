cmake_minimum_required(VERSION 3.17)
project(AppTemplates)

set(CMAKE_CXX_STANDARD 14)

add_executable(AppTemplates main.cpp infrastructure/DynamicVector/DynamicVector.h infrastructure/DynamicVector/DynamicVector.inl infrastructure/Repository/Repository.h infrastructure/Repository/Repository.inl testing/TestAll.h testing/TestAll.cpp presentation/TextTable/TextTable.h presentation/TextTable/TextTable.cpp presentation/consoleUI/ConsoleUI.cpp presentation/consoleUI/ConsoleUI.h examples/stl_examples/StlExamples.cpp examples/stl_examples/StlExamples.h)