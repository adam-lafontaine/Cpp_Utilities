#### C++ Utilities
A collection of small utilities I like having around

* allocator
    * Memory allocator on the cheap
    * Stack behavior for pre-allocated memory
    * CUDA version available

* command_line
    * C++17
    * For processing command line arguments
    * Demonstrated in example_main.cpp    

* config_reader
    * C++ 17
    * Read configuration file of key value pairs
    * key=value or key = value
    * Comment lines with '#'
    * Overload for specifying required keys

* cuda
    * Helpers and macros for CUDA programming
    * Templated stack for managing device memory

* directory_helper
    * C++17
    * Provides file paths of a given extension in a directory

* execute
    * C++17
    * Easy parallel execution

* for_each_in_range
    * C++17
    * Iterate over 1D and 2D integer ranges
    * Sequential or parallel

* leak_check
    * Check for memory leaks using Visual Studio

* libimage
    * Basic image processing library using Boost GIL or stb_image
    * Now deprecated by https://github.com/adam-lafontaine/SimpleImage
    * Boost GIL
        * C++17
        * Add _CRT_SECURE_NO_WARNINGS to Preprocessor Definitions in Visual Studio
        * Sequential and parallel for_each and transform algorithms
        * Has problems with color bmp images
    * stb_image        
        * C++17
        * Similar interface to boost::gil::image_t and image_view_t
        * Create an image object and load image data into it
        * Image exposes begin and end pointers to raw memory
        * Create a view from the image
        * A view is a subsection of the original image and points to the image's memory
        * Process the view if operations are non-trivial

* libuvc
    * Single header file created from the Libuvc library (https://github.com/libuvc/libuvc)
        
* make_start
    * Makefile starting point

* memory_buffer
    * Templated stack implementation

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
        * TODO: bytemap.hpp
    * convert.hpp/cpp
        * Used with charmap.hpp to convert multiple values into a string

* profiler
    * Simple profiler for function calls

* ring_buffer
    * Templated ring/circular buffer

* stopwatch
    * C++17
    * Wraps std::chrono to easily time code execution