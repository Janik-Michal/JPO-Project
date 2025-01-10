# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(Filters)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Specify the directories containing header files
include_directories(src)

# Specify the sources (all .cpp files in the src directory)
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Enable compiler warnings
# - Wall: Enable all the warnings.
# - Wextra: Enable additional warnings.
# - Wpedantic: Enable more strict checking (optional).
if(MSVC)
    # Specific flags for MSVC
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    # Specific flags for GCC/Clang
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Optional: Set debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Optional: Set release flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

# Add a custom target for cleaning (optional)
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean.cmake
)

# Optional: Include an external dependency (e.g., Boost)
# find_package(Boost REQUIRED)
# include_directories(${Boost_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Print some information about the build (useful for debugging)
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "Source files: ${SOURCES}")
