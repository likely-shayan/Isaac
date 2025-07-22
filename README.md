[![ci](https://github.com/likely-shayan/Isaac/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=main&event=push)](https://github.com/likely-shayan/Isaac/actions/workflows/cmake-multi-platform.yml)

## What is Isaac?

Isaac is a computer software aimed at making interactive simulations of physical objects under the influence of various forces as per the laws of Newtonian Mechanics. Besides that, Isaac also provides tools for creating customized 2D, 3D shapes and modify physical constants to see how the behaviour of such system changes.

## How is Isaac going to be developed?

The rendering of Isaac is going to be done using OpenGL. However, In the unfortunate case of poor performance or a higher number of contributors, the rendering will be done by Vulkan for optimal performance.

The GUI of Isaac will be done in imGUI to ensure a nice blending with its purely C++ codebase as well as to create Isaac as a cross - platform software.

Finally, Computations related to Linear Algebra and Numerical Methods are going to be done using Eigen library. Everything else such as the Shapes objects, Other advanced computation Algorithms (specifically related to integration) are going to be custom - made.

However, Since the computations are the only part that can be optimized by us, We are going to be trying out all different libraries and implementation during development as well as after development to find out the most optimized way.

## Is Isaac free?

Since free and open source software are forming the backbone of Isaac, We have decided to ship Isaac as a completely Free and Open Source Project. Open Source enthusiasts and contributors are encouraged to assist in improving Isaac.

## How to try out Isaac?
Currently, GUI has not been develop so to try out Isaac you have to write code manually and then build it.
There is a main.cpp file in source directory in which you can write the main code where all the polygons, mesh and window are defined.
For getting started, Consider to copy-paste any code of your choice from the examples directory.

<h3>Building and Installing Isaac</h3>

```
mkdir build
cd build
cmake ..
make
./Isaac
```
You should see something like "<b>Isaac built successfully</b>"

To run an example, Simply copy-paste it's code into src/main.cpp and run:
```
make
./Isaac
```
<h3>Camera Controls</h3>
<ul>
  <li>Arrow Key Up: Move inwards in the Window</li>
  <li>Arrow Key Down: Move outwards in the Window</li>
  <li>Arrow Key Left: Move leftwards in the Window</li>
  <li>Arrow Key Right: Move rightwards in the Window</li>
  <li>Escape Key: Close the Window</li>
  <li>Mouse/TrackPad: Move the camera</li>
</ul>
