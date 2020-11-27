# FluidSimulation
Simple simulation of incompressible fluid/gas based on Navier-Stokes equations.
It is not a real physical simulation, but fluid movement looks believable.
This simulation is largely based on this article https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

## Video
https://www.youtube.com/watch?v=FLTG29HPuNQ

## Frameworks
The SFML library is used to render the window. https://www.sfml-dev.org/

## Compiling and running
You need:
+ SFML 2.5+ library
+ C++ compiler
+ CMake build system

#### For Windows(MinGw and VS) (do not change sfml directory hierarchy!):
if you are using minGW:
```
  > git clone https://github.com/Hamibar/FluidSimulation
  > cd FluidSimulation
  > mkdir build
  > cd build
  > cmake -DCMAKE_BUILD_TYPE=Release -DSFML_DIR="path to sfml lib" -G "MinGW Makefiles" ..
  > cmake --build .. 
  > cd bin
  > fl_sim.exe path_to_config_file
```
if you are using VS:
```
  > git clone https://github.com/Hamibar/FluidSimulation
  > cd FluidSimulation
  > mkdir build
  > cd build
  > cmake -DSFML_DIR="path to sfml lib" 
  > cmake --build . --config Release
  > cd bin/Release
  > fl_sim.exe path_to_config_file
```

#### For Linux:
```
  $ sudo apt-get install libsfml-dev  // if SFML is not installed:
  $ git clone https://github.com/Hamibar/FluidSimulation
  $ cd FluidSimulation
  $ mkdir build
  $ cd build
  $ cmake -DCMAKE_BUILD_TYPE=Release .
  $ cmake --build .
  $ cd bin
  $ ./fl_sim path_to_config_file
 ```
 
 ## Config file format
The config file format will be changed!
There no program constraints of parameters. I don't recommend to use unexpected values. It will be fixed soon.

Schematically config file looks like:
```
MainBlock { 
  Parameter_name : value
  SubBlock {
    Sub_block_parameter_name : value	
  }
}
```
Spaces between `BlockName` and `{` needed. You can find real examples after the parameter list.

#### GRAPHIC parameters:
* `WINDOW_RESOLUTION: float`:  defines the ratio of screen size to simulation size; **_2 by default_**
* `BI_COLORIZER_COLOR_1: int8 int8 int8`: start color for the 2-color filter;  **_0 0 0 by default_**
* `BI_COLORIZER_COLOR_2: int8 int8 int8`: end color for the 2-color filter; **_0 0 0 by default_**
* `SIMPLE_COLORIZER_COLOR: int8 int8 int8`: color for the simple filter;  **_0 0 0 by default_**
* `COLORIZER_TYPE: std::string`; **_SIMPLE by default_**
	
Colorizer types:
*  `WB`: black and white filter
*  `SIMPLE`: 1-color filter
*  `BI`: 2-color filter

#### CONTROLLER parameters:	
* `MOUSE_ENABLE: 1 or 0`:  1 - enable ability to add dye with mouse; **_0 by default_** 
* `MOUSE_POWER: int`: speed factor; **_0 by default_**
* `MOUSE_DENS: int`: the amount of dye produced by mouse; **_0  by default_**

#### SIMULATION parameters:
* `SIMULATION_SIZE: int`: side size of the vector field (recommend using value bigger than 160); **_200 by default_**
* `SIMULATION_VISC: float`: fluid viscosity value; **_0 by default_**
* `SIMULATION_DIFF: float`: fluid diffusion value; **_0 by default_**
* `SIMULATION_DT: float`: time passed by one simulation step; **_1 by default_**
* subBlock `SOURCE`:
    * `TYPE: std::string`; **_SIMPLE by default_**
    * `POS_X: int`: x coordinate; **_0 by default_**
    * `POS_Y: int`: y coordinate; **_0 by default_**
    * `POWER: float`: speed vector length; **_0 by default_**			
    * `DENS_AMOUNT: float`: dye amount per tick; **_0 by default_**
    * `START_ANGLE: float`: start direction in radians; **_0 by default_**
    * `ROT_SPEED: float`: rotation angle change per tick in radians(used in CIRCLE source type); **_0 by default_** </br>
   Source types: 
    * `SIMPLE`: constant source directed one way. 
    * `CIRCLE`: rotating constant source.
   
#### Example:
```
GRAPHIC {
  WINDOW_RESOLUTION: 2
  COLORIZER_TYPE: BI
  BI_COLORIZER_COLOR_1: 255 0 255
  BI_COLORIZER_COLOR_2: 255 255 0
}

SIMULATION {
  SIMULATION_SIZE: 260
  SIMULATION_VISC: 0.00001
  SIMULATION_DIFF: 0.0000001
  SIMULATION_DT: 0.1

  SOURCE {
    TYPE: CIRCLE
    POS_X: 130
    POS_Y: 130
    POWER: 0.9
    DENS_AMOUNT: 50
    START_ANGLE: 0
    ROT_SPEED: 0.05
  }

  SOURCE {
    TYPE: SIMPLE
    POS_X: 50
    POS_Y: 130
    POWER: 0.5
    DENS_AMOUNT: 20
    START_ANGLE: 0
  }

  SOURCE {
    TYPE: SIMPLE
    POS_X: 210
    POS_Y: 130
    POWER: 0.5
    DENS_AMOUNT: 20
    START_ANGLE: 3.14
  }
}
```
more examples you can find in a folder named configs

## Plans and improvement.
* change config file format
* add value constraints
* more informative errors
* add the ability to put solid objects inside the simulation
* better GUI
* add GUI editor
* add other sources and color filters
* make algorithm closer to reality
* use CUDA
