## What is Isaac?

Isaac is a computer software aimed at making interactive simulations of physical objects under the influence of various forces as per the laws of Newtonian Mechanics. Besides that, Isaac also provides tools for creating customized 2D, 3D shapes and modify physical constants to see how the behaviour of such system changes.

## How is Isaac going to be developed?

The rendering of Isaac is going to be done using OpenGL. However, In the unfortunate case of poor performance or a higher number of contributors, the rendering will be done by Vulkan for optimal performance.

The GUI of Isaac will be done in Qt to ensure a nice blending with its purely C++ codebase as well as to create Isaac as a cross - platform software.

Finally, Computations related to Linear Algebra and Numerical Methods are going to be done using Eigen. Everything else such as the Shapes objects, Other advanced computation Algorithms (specifically related to integration) are going to be custom - made.

## Is Isaac free?

Since free and open source software are forming the backbone of Isaac, We have decided to ship Isaac as a completely Free and Open Source Project. Open Source enthusiasts and contributors are encouraged to assist in improving Isaac.

## What next?

There are plans for making different version of Isaac suited for different use cases. If Isaac is well appreciated by its targeted users, then we will continue working on customized versions of Isaac for students, teachers and researchers. We also have plans to develop more similar software created specifically for Fluid Dynamics, Electromagnetism and Astrophysics.