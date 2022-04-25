cmake_minimum_required(VERSION 3.17)
project(WrittenExamBeverage)

set(CMAKE_CXX_STANDARD 14)

add_executable(WrittenExamBeverage main.cpp Beverage.cpp Beverage.h Coffee.cpp Coffee.h Tea.cpp Tea.h BeverageWithMilk.cpp BeverageWithMilk.h BeverageMachine.cpp BeverageMachine.h)