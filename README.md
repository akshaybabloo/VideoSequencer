# Video-Sequencer

Generates video sequence and converts it into images

## Requirements

1. Conan package manager
2. Qt 6.2+

## Install Packages

This project depends on Boost and OpenCV.

### For Jetbrains CLion

Enter the following from the IDE terminal

```shell
conan install . -if=cmake-build-debug -pr=default -c tools.cmake.cmaketoolchain:generator="NMake Makefiles"
```

### For Qt Creator

Open an external Terminal app and change the directory to the current project folder so that `conanfil.txt` is in the root and type in the following:

```shell
conan install . -pr:b=default -if=<path to build folder> -c tools.cmake.cmaketoolchain:generator="Ninja cmake" -s build_type=Debug
```
