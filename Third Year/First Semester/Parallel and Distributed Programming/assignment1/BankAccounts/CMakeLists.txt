cmake_minimum_required(VERSION 3.16)
project(BankAccounts)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(BankAccounts main.cpp Bank/Bank.cpp Bank/Bank.h Account/Account.cpp Account/Account.h AccountLogEntry/AccountLogEntry.cpp AccountLogEntry/AccountLogEntry.h AccountOperation/AccountTransferOperation.cpp AccountOperation/AccountTransferOperation.h ThreadsManager/ThreadsManager.cpp ThreadsManager/ThreadsManager.h RandomGenerator/RandomGenerator.cpp RandomGenerator/RandomGenerator.h)
