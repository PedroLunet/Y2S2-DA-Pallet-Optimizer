cmake_minimum_required(VERSION 3.10)
project(PalletPackingOptimizer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(PalletPackingOptimizer main.cpp)

# Enable warnings
if(MSVC)
    target_compile_options(PalletPackingOptimizer PRIVATE /W4)
else()
    target_compile_options(PalletPackingOptimizer PRIVATE -Wall -Wextra -Wpedantic)
endif()

# For Doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Set input and output files for Doxygen
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Configure the Doxyfile
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Add a custom target to run Doxygen
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM)
endif()
