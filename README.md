# Grapple Game

A simple endless runner game made with [raylib](https://www.raylib.com/).   
Music by Andrew Atkinson

## Download
To clone both this repo:      
`git clone https://github.com/ArchieAtkinson/Grapple-Game.git`      
Raylib source code is downloaded using CMake FetchContent.    

## Builing and running the Project

- Clone the repo and enter the directory in your terminal    
- Create a build directory with:
    - `mkdir build`    
- Configure CMake with 
    - `cmake -S . -B build` or using Ninja
    - `cmake -S . -B build -G Ninja`  
- Now to build the project 
    - `cmake --build build`    
- Now run the `Grapple.exe` from the build folder

