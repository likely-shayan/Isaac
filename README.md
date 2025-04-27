In this branch, We will be working on creating a working prototype of Isaac that can render basic
2-D structures under the set up conditions of various forces, collision and laws of Newtonian Mechanics.
We will be strictly following Test-Driven Development (TDD).
We will begin our work by first creating a Kernel of Isaac exclusively for 2-D objects along with
their simple tests.
Since performance is critical, We will put maximum efforts in reducing
boilerplate code and including only what's necessary and keeping it straightforward.
Every Layer of Isaac (Kernel, Rendering and GUI) will have it's own dedicated folder in include/,  src/ and test/ along with a dedicated CMakeLists.txt. 