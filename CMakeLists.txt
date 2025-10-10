# cmake_minimum_required(VERSION 4.0.0)
# project(SDL_fire)

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# add_compile_options(-O3 -march=native -flto)
# link_libraries(SDL2)
# include_directories(${CMAKE_SOURCE_DIR}/include)
# add_library(${PROJECT_NAME} SHARED src/SDL_fire.c)
# add_library(${PROJECT_NAME}-static STATIC src/SDL_fire.c)
# install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-static DESTINATION /usr/local/lib)
# install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION /usr/local/include)

# add_executable(example EXCLUDE_FROM_ALL example/example.c)
# target_link_libraries(example PRIVATE SDL2 SDL_fire)
# target_link_options(example PRIVATE -L/usr/local/lib)
# target_compile_options(example PRIVATE -Wall -Wextra -Werror -Wunused-result -Wconversion)

cmake_minimum_required(VERSION 4.0.0)
project(SDL_fire)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# link_libraries(SDL2)

add_executable(example EXCLUDE_FROM_ALL example/example.c)
target_link_libraries(example PRIVATE SDL_fire)
target_compile_options(
	example PRIVATE -Wall -Wextra -Werror -Wconversion -Wunused-result)

add_compile_options(-O3 -march=native -flto)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} SHARED src/SDL_fire.c)
add_library(${PROJECT_NAME}-static STATIC src/SDL_fire.c)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-static DESTINATION /usr/local/lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION /usr/local/include)
