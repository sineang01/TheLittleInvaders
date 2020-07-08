TheLittleInvaders
=================

The Little Invaders is the classical invaders game realized as coding test for a game company and then extended in my spare time to realize a Windows micro-engine meant to run any kind of 2D game provided in the implementation.

![TheLittleInvaders](https://i.ibb.co/DRs7wL4/little-invaders.png)

Info
====

The Little Invaders provides a basic invaders game and a micro-engine to handle generic 2D games.
- The engine is a shared library able to link any graphical library (in this specific implementation the graphic library is called _EasyPlatform.dll_ and it is a **x86 dll**)
- The game is another shared library seeking information from the engine using direct calls or event based procedures

Installation
============

Download the repository and compile on your local machine. You'll need CMake.
```
cd repository_folder
mkdir build
cd build
cmake ..
make
make install
```

`install` will copy all libraries and executables in the output/ directory.

Configuration
=============

Configuration files are provided in the output directory
* system.csv: used by the engine to load the graphic library as well as the main window
* variables.csv: game specific and, in this implementation, used to configure various properties and control objects speeds, player lives, number of aliens and so on

EasyPlatform
============

EasyPlatform is a Windows shared library for x86 and takes care of loading the graphical assets.
If you try The Little Invaders using EasyPlatform, you should compile it for x86!

License
=======

The Little Invaders is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The Little Invaders is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Little Invaders.  If not, see <http://www.gnu.org/licenses/>.
