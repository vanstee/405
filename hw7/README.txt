Description:
This is a solution to homework 7 with the basic requirements implemented. 
The project has a structure similar to the hello and shader example programs, with opengl
call backs and global variables that contain state information. The model displayed is of
a simple desk fan. The fan's blades rotate (keys f and v) as well as the base
(keys g and b), within a defined threshold.

Name: Patrick Van Stee

Date: April 27, 2011

Instructions:
$ make clean && make
$ ./viewer
Press p to toggle between orthographic and perspective modes
Press w to toggle between wireframe and shaded viewing modes
Press l to toggle between a white infinite light and a point light
Press i to reinitialize the program
Press s to cycle through ambient only, ambient + diffuse only, and ambient + diffuse + specular shading (advanced)
Press f to rotate the blades counter-clockwise
Press v to rotate the blades clockwise
Press g to rotate the base starting to the right
Press b to rotate the base starting to the left
Press q or ESC to quit the program
