# Alba

Alba is a scratchpad for my hobby game-programming ideas. It's basically whatever I feel like working on at that particular moment, with shared/reusable code in a common framework that I can reuse later. 

## Language

The programming style is probably is a bit more "modern C++" heavy than I'd write in code that has to ship. This is more of a testbed to get practical experience with certain language features, so I can evaluate them for myself. 

Alba is written in C++17, as I wanted to get some hands-on experience writing C++17 code, and particularly writing game/engine code using C++17 from the ground up. 

## Syncing

I'm sure no one will actually want to do this when there's much better tech out there, but I might as well document this in case I forget myself.

Clone the project from git, and then run the following commands from the root directory

    git submodule init
    git submodule update
    
This will pull in dependencies from other Git repositories I've linked to (in the Source/External directory). 
Right now I'm using:

* *EASTL* - Provides a more game-development friendly alternative to the C++ standard STL library (e.g. fixed-size vectors/strings, vectors/strings with a template-defined fixed size, so that heap allocations only occur when the container grows beyond that size)
* *imgui* - Debug UI (or Editor UI if I ever make something that requires one)
* *mathfu* - Vector/Matrix/Quaternion math. As much fun as it would be to write yet another math library, I'd like to actually see something on screen within a reasonable amount of time, so I figured I'd take advantage of the hours of testing that have gone into open-source alternatives 
* *remotery* - In-game profiling

## Building

Alba uses "Sharpmake" to generate Visual Studio projects (https://github.com/ubisoftinc/Sharpmake).
To generate the solution file, run "GenerateProjects.bat". The solution file will appear in Source\Sharpmake\generated

Currently, Alba uses Visual Studio 2017 to build. I've not tried any other compilers yet, as I generally run on Windows at home, and I don't have any pressing need to run on other platforms right now. I'll probably get it running on clang at some point if I feel the urge to make it run on Android. 
