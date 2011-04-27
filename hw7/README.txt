Description:
This is a solution to homework 7 with the basic requirements implemented. 
The project has a structure similar to the hello and shader example programs, with opengl
call backs and global variables that contain state information. The model displayed is of
a simple desk fan. The fan's blades rotate (keys q and w) as well as the base
(keys a and s), within a defined threshold.

Name: Patrick Van Stee

Date: April 27, 2011

Instructions:
$ make clean && make
$ ./viewer
Press p to toggle between orthographic and perspective modes
Press l to toggle between a white infinite light and a point light
Press i to reinitialize the program
Press q to rotate the blades counter-clockwise
Press w to rotate the blades clockwise
Press a to rotate the base starting to the right
Press s to rotate the base starting to the left
Press ESC to quit the program
