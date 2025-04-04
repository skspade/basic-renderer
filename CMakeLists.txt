cmake_minimum_required(VERSION 3.12...3.26)

get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT is_multi_config AND NOT (CMAKE_BUILD_TYPE OR DEFINED ENV{CMAKE_BUILD_TYPE}))
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Release default")
endif()

project(tinyrenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(iwyu "Run include-what-you-use")
if(iwyu)
  find_program(IWYU_EXE NAMES include-what-you-use REQUIRED)
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_EXE})
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|Intel")
  add_compile_options(-Wall)
endif()

# Make OpenMP optional with better error handling
option(USE_OPENMP "Enable OpenMP parallelization" OFF)
if(USE_OPENMP)
  find_package(OpenMP COMPONENTS CXX)
  if(NOT OpenMP_CXX_FOUND)
    message(WARNING "OpenMP not found. Building without parallelization support.")
    set(USE_OPENMP OFF)
  endif()
endif()

set(SOURCES 
    main.cpp 
    tgaimage.cpp
    geometry.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Only link OpenMP if it's found and enabled
if(USE_OPENMP AND OpenMP_CXX_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
  target_compile_options(${PROJECT_NAME} PRIVATE ${OpenMP_CXX_FLAGS})
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")
