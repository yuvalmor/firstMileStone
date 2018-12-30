cmake_minimum_required(VERSION 3.12)
project(simulator9492yn_master)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

add_executable(simulator9492yn_master
        BinaryExpression.h
        UnaryExpression.h
        Divide.h
        Expression.h
        main.cpp
        Minus.h
        Multiply.h
        Num.h
        Plus.h
        Neg.h
        Var.h
        OpenServerCommand.cpp
        ConnectCommand.cpp
        ShuntingYard.cpp
        UpdateVarCommand.cpp
        BindCommand.cpp
        Parser.cpp
        Lexer.cpp
        IfCommand.cpp
        WhileCommand.cpp
        DefineCommand.cpp
        BooleanExpression.cpp
        ConditionCommand.h
        Threader.h
        TableManager.cpp
        Runner.h
        PrintCommand.h PrintCommand.cpp)

target_link_libraries(simulator9492yn_master ${CMAKE_THREAD_LIBS_INIT})