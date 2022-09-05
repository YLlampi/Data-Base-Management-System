cmake_minimum_required(VERSION 3.16)
project(Data_Base_Management_System)

set(CMAKE_CXX_STANDARD 17)

add_executable(Data_Base_Management_System main.cpp NodeBPT.cpp NodeBPT.h BPTree.cpp BPTree.h Controller.cpp Controller.h DataBase.cpp DataBase.h Table.cpp Table.h NodeRegister.cpp NodeRegister.h)
