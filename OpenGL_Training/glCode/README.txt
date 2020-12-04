glCode - Example Code
---------------------

These are example code provided just to give the basic idea about
programming in OpenGL with C/C++. The project is build on CMake make
system, so it needs CMake tool to build the projects/make files


Building on Windows
-------------------

This project can be built using CMake which can be installed from
CMake's official website https://cmake.org/. Once downloaded and installed

* Once CMake is installed run CMake-ui and select the 32 bit Visual Studio
  compiler and press configure and generate to generate the necessary 
  projects and solutions

* There might be some linker problems while building the solution
  like "glut32.lib(glut32.dll) : error LNK2026: module unsafe for SAFESEH image." 
  In order to solve this, open the project properties for "glutMod" go to 
  Linker -> Advanced option, and turn the (Yes/SAFESEH) to (No/SAFESEH)
  