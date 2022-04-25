cmake_minimum_required(VERSION 3.17)
project(WrittenExam)

set(CMAKE_CXX_STANDARD 14)

add_executable(WrittenExam main.cpp SecondaryDate/main.cpp SecondaryDate/Vector.cpp SecondaryDate/Vector.h SecondaryDate/SmartPointer.cpp SecondaryDate/SmartPointer.h SecondaryDateV2/main.cpp SecondaryDateV2/Vector.cpp SecondaryDateV2/Vector.h SecondaryDateV2/Iterator.cpp SecondaryDateV2/Iterator.h SecondaryDateV2/SmartPointer.cpp SecondaryDateV2/SmartPointer.h)