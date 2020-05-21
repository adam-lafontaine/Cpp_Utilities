#### C++ Utilities
A collection of small utilities I like having around

* stopwatch.hpp
    * C++11
    * Wraps std::chrono to easily time code execution    

* win32_leak_check.h
    * Allows checking for memory leaks using Visual Studio

* directoryhelper
    * C++17
    * Provides file paths in a directory of a given extension

* normalize
    * C++17
    * For custom scaling of values from one range to another
    * convert_config.hpp
        * Set minimum and maximum values type of scaling e.g. linear or sigmoidal
        * Add any scaling schemes
    * normalize.hpp
        * Uses values set in convert_config.hpp to normalize a given value
    * charmap.hpp
        * Used with normalize.hpp to convert a given value to a character
        * Multiple values can be saved as strings
    * convert.hpp/cpp
        * Used with charmap.hpp to convert multiple values into a string