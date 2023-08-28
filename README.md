## RUN TESTS
build cmake project

then run `/build/tests/TestClawk`

## Checking the compiler

The compiler CMake is using gets stored in the CMakeCache.txt file in your build directory. 

You can open this file and look for entries named CMAKE_CXX_COMPILER and CMAKE_C_COMPILER to see which C++ and C compilers respectively CMake is using.

If you want CMake to use a specific compiler, you can pass it during the configuration step, e.g.,

At the moment of recording, it is:
```
//CXX compiler
CMAKE_CXX_COMPILER:FILEPATH=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++

```

## Format doc in clion

`command + option + L`