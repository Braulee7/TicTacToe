cmake_minimum_required(VERSION 3.28)
project("Tic-Tac-Toe" VERSION 0.0.1 )
set(CMAKE_DEBUG_POSTFIX d)

add_subdirectory(HevNet)

set(sources
${PROJECT_SOURCE_DIR}/src/practice.cpp
${PROJECT_SOURCE_DIR}/src/tictactoe.cpp
${PROJECT_SOURCE_DIR}/src/peer.cpp
${PROJECT_SOURCE_DIR}/src/game.cpp

)

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE HevNet)
