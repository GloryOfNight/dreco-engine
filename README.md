# Dreco Engine
Student project with target of writing game engine and a small example game on it. Engine supports only 2D rendering space and uses OpenGL(ES) as rendering API. 
Depends on: SDL2, SDL2_image and SDL2_mixer.

# Improtant notes
Please note, a lot of work still Work In Progress state.

![UbuntuBuild](https://github.com/GloryOfNight/dreco-engine/workflows/Ubuntu-18.04/badge.svg)

# Install dependencies - Debian/Ubuntu and etc
> sudo apt-get update

> sudo apt-get install libsdl2-dev

> sudo apt-get install libsdl2-image-dev

> sudo apt-get install libsdl2-mixer-dev

# Build & Run
> cd your_preffered_clone_dir

> git clone https://github.com/GloryOfNight/dreco-engine

> cd dreco-engine 

> mkdir build && cd build

> cmake .. && make

> cd example-game/ && ./example-game

