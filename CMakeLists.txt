# Project details
cmake_minimum_required(VERSION 3.20)
project(SDL_fire)

# Global options

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
# set(TEST_DIR "${CMAKE_SOURCE_DIR}/test")
set(EXAMPLE_DIR "${CMAKE_SOURCE_DIR}/example")
set(SRC "${SRC_DIR}/${PROJECT_NAME}.c")
set(INC "${INC_DIR}/${PROJECT_NAME}.h")
# set(TEST_MAIN "${TEST_DIR}/test.c")
set(EXAMPLE_MAIN "${EXAMPLE_DIR}/example.c")
set(LIB_ST "${PROJECT_NAME}-static")
set(LIB_SH "${PROJECT_NAME}")
find_package(SDL2 REQUIRED)

# Targets

add_library(${LIB_ST} STATIC ${SRC})
add_library(${LIB_SH} SHARED ${SRC})
# add_executable(test EXCLUDE_FROM_ALL ${TEST_MAIN})
add_executable(example EXCLUDE_FROM_ALL ${EXAMPLE_MAIN})

# Target specific options

set_target_properties(${LIB_ST} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
target_include_directories(${LIB_SH} PRIVATE ${INC_DIR})
target_include_directories(${LIB_ST} PRIVATE ${INC_DIR})
target_include_directories(example PRIVATE ${INC_DIR})
# target_include_directories(test PRIVATE ${INC_DIR})
# target_link_libraries(test PRIVATE SDL2)
target_link_libraries(example PRIVATE SDL2 ${LIB_SH})

install(TARGETS ${LIB_ST} ARCHIVE DESTINATION lib)
install(TARGETS ${LIB_SH} LIBRARY DESTINATION lib)
install(FILES ${INC} DESTINATION include)

# Platform specific options
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
	message("Compiling with Gcc/Clang")
	target_compile_options(${LIB_ST} PRIVATE -O3 -march=native -flto)
	target_compile_options(${LIB_SH} PRIVATE -O3 -march=native -flto)
	# target_compile_options(test PRIVATE -Wall -Wextra -Werror -Wunused-result -Wconversion)
	target_compile_options(example PRIVATE -Wall -Wextra -Werror -Wunused-result -Wconversion)
endif()

