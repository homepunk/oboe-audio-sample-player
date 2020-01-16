# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
### INCLUDE OBOE LIBRARY ###

# Set the path to the Oboe library directory (may not exist yet)
set(OBOE_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib-oboe)

# Get the absolute path to the Oboe library directory
get_filename_component(OBOE_DIR
        ${OBOE_RELATIVE_PATH}
        ABSOLUTE)

# If the Oboe library directory doesn't exist, clone it from github
if ((NOT EXISTS ${OBOE_DIR}) OR
(NOT EXISTS ${OBOE_DIR}/CMakeLists.txt))
    execute_process(COMMAND git clone
            https://github.com/google/oboe.git
            ${OBOE_DIR}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)
endif ()
# Set the path to the Oboe directory.
#set(OBOE_DIR ../../../../oboe)

# Add the Oboe library as a subdirectory in your project.
add_subdirectory(${OBOE_DIR} ./oboe)

# Specify the path to the Oboe header files.
include_directories(${OBOE_DIR}/include)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        engine/AudioFile.h
        engine/AudioEngine.cpp
        engine/AudioEngine.h
        util/Logger.cpp
        util/Logger.h
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        oboe

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})