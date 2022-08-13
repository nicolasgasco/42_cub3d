
# 42_cube3d
# cube3d
42 group project done by [@nicolasgasco](https://github.com/nicolasgasco) and [@isolinis](https://github.com/isolinis). A small 3D video game inspired by Wolfenstein 3D that leverages raycasting to create a false sense of tridimensionality. Written in C using 42 homebrewed graphical API [miniLibX](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html).

![screencast-nimbus-capture-2022_08_12-17_53_56_lqj089](https://user-images.githubusercontent.com/73175085/184505477-a271ac22-ed26-4a7a-bd68-f12efd6a4ced.gif)

The map to render is represented by a scene description file that is passed as argument to the program. It roughly follows this scheme:
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
Since the scene description is not known beforehand, quite a lot of work was put into validating it in case the file is misconfigured.

The second part of the project involved doing all the necessary mathematical calculation to generate an apparently 3D scene from a bidimensional map. The scene had to be rerendered at every movement of the player, that moves both along the x and y axes as well as rotating clockwise and counterwise.
