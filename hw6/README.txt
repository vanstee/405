Description:
This is a solution to homework 6 with the basic fuctionality implemented. 
The project has a structure similar to my hw5 solution and uses example 
code from the shader, hello, objload and mipmaps projects, with opengl
call backs and global variables that contain state information. Most
of the new functionality was implemented in the Draw method in the 
PolySurf.cpp file.

Name: Patrick Van Stee

Date: April 13, 2011

Instructions:
$ make clean && make
$ ./objview [tetrahedron.obj, cube.obj, Skeleton.obj or Mug.obj]
Press p to toggle between orthographic and perspective modes
Press w to toggle between wireframe and shaded viewing modes
Press l to toggle between a white infinite light and a point light
Press i to reinitialize the program
Press s to cycle through ambient only, ambient + diffuse only, and ambient + diffuse + specular shading (advanced)
Press q or ESC to quit the program
