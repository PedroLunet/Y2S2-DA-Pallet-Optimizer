cmake_minimum_required(VERSION 3.30)
project(project2_da_leic)

set(CMAKE_CXX_STANDARD 14)

add_executable(project2_da_leic
        main.cpp
        menu/Menu.cpp
        menu/Menu.h
        optimizer/PalletPackingOptimizer.cpp
        optimizer/PalletPackingOptimizer.h
        data/DataManager.cpp
        data/DataManager.h)

# For Doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Set input and output files for Doxygen
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/../Doxyfile)

    # Configure the Doxyfile
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Add a custom target to run Doxygen
    add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM)
endif()
