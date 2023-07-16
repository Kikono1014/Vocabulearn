cmake_minimum_required(VERSION 3.25 FATAL_ERROR)
project(Vocabulearn)


option(USE_STATIC "Use static library" ON)
message(STATUS "OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compile with static library? ${USE_STATIC}")


add_executable(Vocabulearn
    main.cpp
    lib/Key/Key.cpp
    Controller/Controller.cpp
    Dictionary/Dictionary.cpp
    Testing/Testing.cpp
    Evaluation/Evaluation.cpp
) 


add_subdirectory(lib/nlohmann_json)

target_link_libraries(Vocabulearn PRIVATE nlohmann_json)

