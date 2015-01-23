TheLittleInvaders
=================

The Little Invaders is the classical invaders game realized as coding test for a game company and it is provided as a stand-alone application written in C++ using Visual Studio 2012.
**NOTE:** The entire code was realized in _6 days_ so minor issues and missing optimizations may appear here and there.

Info
====

The Little Invaders provides a basic invaders game and a Micro-engine to handle generic 2D games.
- The engine is a shared library able to link any graphical library (in this specific implementation: EasyPlatform)
- The game is another shared library seeking information from the engine using direct calls or event based procedures

The proposed solution, although still minimalist, aims to realize a Micro-engine meant to run any kind of 2D game provided in the Game library implementation.

Installation
============

Download the repository and compile on your local machine.
If you have Visual Studio Runtime you can then run Launcher.exe to load the application.

Configuration
=============

Configuration files are provided in the Release folder
* system.csv: used by the engine to load the graphic library as well as the main window
* variables.csv: game specific and, in this implementation, used to configure various properties and control objects speeds, player lives, number of aliens and so on

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
