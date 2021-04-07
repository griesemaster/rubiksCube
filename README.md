# Rubik's Cube Simulator
3D Rubik's Cube simulator implemented in C++ using OpenGL with the GLFW library. 


## How to run:
1. Clone the repository to visual studio
2. Change the following line 111 in main.cpp (the one which creates the shader it might have moved)
    the first arguement is the path to the vertex shader, the second is the path to the fragment shader.
    If anyone knows how to change this to a relative path, please let me know or change it yourself. I can't get it to work for the life of me. 

3. Compile and run main.cpp

## Controls:
1-2 Controls the front face.

3-4 Controls the right face.

5-6 Controls the up face. 

0 resets the cube

9 applies the "superflip" pattern

WASD and mouse for movement within the world. If the camera jitters when you start it, the cube should be down to the bottom left. A new camera system is coming soon in a new release.


Methods exist for controling the other faces in the "cubetroller" class but I simply don't have them bound currently. 
