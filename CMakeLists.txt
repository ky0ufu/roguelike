cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED true)
SET(COMPILE_FLAGS "-lncurses")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")

project(main)

cmake_policy(SET CMP0135 NEW)

# ADDING LIBS

add_library(CHARACTER
    STATIC Entities/Character.cpp
)

add_library(PLAYER
    STATIC Entities/Player.cpp
)
add_library(ENEMY
    STATIC Entities/Enemy.cpp
)
add_library(MAP
    STATIC Scene/Map.cpp
)
add_library(BALANCE
    STATIC ./Balance.cpp
)
add_library(SPAWNERS
    STATIC Entities/Spawner.cpp
)

add_library(GAME
    STATIC Scene/Game.cpp
)
# ADDING MAIN EXECUTABLE FILE
add_library(MANAGER
    STATIC Entities/SpawnManager.cpp
)
add_executable(main
    ./main.cpp
)

#LINKING LIBRARIES

target_link_libraries(ENEMY
    PUBLIC CHARACTER
    PUBLIC BALANCE
)

target_link_libraries(PLAYER 
    PUBLIC CHARACTER
    PUBLIC ENEMY
    PUBLIC BALANCE
    )

target_link_libraries(SPAWNERS
    PUBLIC ENEMY
    PUBLIC BALANCE
)
target_link_libraries(MANAGER
    PUBLIC ENEMY
    PUBLIC BALANCE
)
target_link_libraries(MAP
    PUBLIC PLAYER
    PUBLIC ENEMY
)

target_link_libraries(GAME
    PUBLIC MAP
    PUBLIC ENEMY
    PUBLIC PLAYER
    PUBLIC SPAWNERS
    PUBLIC MANAGER
)

target_link_libraries(main
    PUBLIC PLAYER
    PUBLIC GAME
)

# GOOGLETEST FRAMEWORK

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

# TESTS


# COPYING BINARIES TO BIN FOLDER

set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Добавление команды копирования файла в папку ./bin
# add_custom_command(TARGET main POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E make_directory ${BIN_DIR}
#     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:main> ${BIN_DIR})