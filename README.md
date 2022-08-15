
# Cube3D
42 group project done by [@nicolasgasco](https://github.com/nicolasgasco) and [@isolinis](https://github.com/isolinis). Small 3D video game inspired by _Wolfenstein 3D_ that leverages [raycasting](https://en.wikipedia.org/wiki/Ray_casting) to create a sense of tridimensionality. Written in C using 42 homebrewed graphical API [miniLibX](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html).

![screencast-nimbus-capture-2022_08_12-17_53_56_lqj089](https://user-images.githubusercontent.com/73175085/184505477-a271ac22-ed26-4a7a-bd68-f12efd6a4ced.gif)

The map to render is represented by a scene description file that is passed as argument to the program. It roughly follows this scheme:

## Project division
The project roughly involved:
- Parsing and validating the scene description file passed as argument to the program, as shown in this example:
  ```
  NO ./path_to_the_north_texture
  SO ./path_to_the_south_texture
  WE ./path_to_the_west_texture
  EA ./path_to_the_east_texture
  F 220,100,0
  C 225,30,0
  111111
  100001
  111111
  ```
- Transforming the data in a way that can be easily fed to the graphical API
- Doing the raycasting calculation to render the scene and adding player movement

## Features
- Different texture for each orientation (North, South, West, East)
- Customizable ceiling and floor colors
- Player movement (vertical with `W` and `S`, horizontal with `A` and `D`, and view rotation with left and right arrow keys.
