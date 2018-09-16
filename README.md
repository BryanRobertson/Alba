# Alba

Alba is a scratchpad for my hobby game-programming ideas. It's basically whatever I feel like working on at that particular moment, with shared/reusable code in a common framework that I can reuse later. 

Surprisingly for someone that works as a gameplay programmer, when I program in my spare time I usually get the itch to write my own engine rather than a game, so here we are. There's a lot of lower-level code that I don't really get the chance to touch at work because I have other things to do, so this is my outlet for my need to understand how things work.

The name is gaelic for "Scotland". I don't speak gaelic, but I wanted a name that was short, easy to spell and remember (so I could use its name as a namespace without hating myself everytime I had to type it), and that would be unlikely to have been taken already. I guess I was feeling pretty patriotic or something that day.

## Language

Alba is written in C++17, as I wanted to get some hands-on experience writing C++17 code, and particularly writing game/engine code using C++17 from the ground up.

## Syncing

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
