# cub3d

First-person 3D representation of a maze using raycasting, similar to Wolfenstein 3D (1992).

## Final grade : 115/115

Mandatory part : 100/100

Bonus : 15/15

### Prerequisites

The project runs using the MiniLibX, a simplified version of the Xlib. It can therefore only run in MacOSX, preferably on a computer with a solid CPU !

### The game

Just like B.J. Blazkowicz in Wolfenstein 3D, you have infiltrated a nazi stronghold.

You got what you needed, but you won't get out unnoticed. You're gonna have to fight your way out !

You should be able to survive if you get to the third floor, and kill everyone there. Good luck !

<p align="center">
  <img src="https://i.imgur.com/ll5P9RN.png" width="60%" />
</p>

### How to run it

Using ``make bonus`` will build the executable.

you can simply run the executable with ``./cub3D map.cub``.

### Controls

You can move around the maze with ``W`` ``A`` ``S`` ``D``.

You can also rotate the view with the directional arrows ``←`` and ``→``.

You can look up and down with the directional arrows ``↑`` and ``↓``.

To exit the game, press ``ESC`` or click the red cross.

### The mandatory part

The basic program that was required to pass. It only includes wall textures and a sprite ; no floor/ceiling textures, no weapons, no enemies, no game elements at all.

<p align="center">
  <img src="https://i.imgur.com/Vf1HLRE.png" width="60%" />
</p>

### How to run it (mandatory part only)

Using ``make`` will build the executable of the mandatory part.

you can simply run the executable with ``./cub3D map.cub``.

You can edit ``map.cub`` to change the resolution and the texture .

You can edit ``map.cub`` to change the texture you want but make sure to use 64/64 texture and it's ``.xpm``

You can also change ``map.cub`` file but make sure it's have the same structure and it ends with ``.cub``

### Controls (mandatory part only)

Controls are the same as the project with bonuses, but only ``W`` ``A`` ``S`` ``D`` to move and ``←`` ``→`` to turn are available.

### Acknowledgments

* The Coding Train (raycasting inspiration)
* Wolfenstein 3D (for the controversial textures)
* And macrespo (for this beautiful life bar)
