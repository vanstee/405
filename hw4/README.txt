Description:
This is a solution to homework project 4 with basic requirements implemented.
Since it's a raycaster, vectors are pointed through the pixels that make up the image
and are colored depending on what they hit (or nothing at all). The color is then
adjusted depending on the the ambient, diffuse and specular lights along with the 
reflections calculated with a recursive algorithm that accounts for light that bounces
off of other spheres. The camera, lights, and spheres can be specified in scene.txt.

Name: Patrick Van Stee

Date: March 18, 2011

Instructions:
$ make clean && make
$ ./raytrace [l|v] [pixwidth] scene.txt [filename.ext]
Press w to write the display to the file specified in as the [filename.ext] option
Press q or ESC to quit the program

Example scene.txt:
3 5             # light count and sphere count
camera
0.0 0.0 0.5     # viewpoint
0.0 0.0 -1.0    # view direction
0.0 1.0 0.0     # up direction
0.5             # focal length
1.25            # aspect ratio
0.5             # screen width
point light
2.0 0.5 0.0     # vector
1.0 1.0 0.9     # color
point light
1.0 0.5 -5.0    # vector
0.9 0.9 1.0     # color
point light
-1.0 1.0 5.0    # vector
1.0 1.0 0.9     # color
sphere
-0.3 0.1 -0.5   # vector
0.05            # radius
1.0 0.0 0.0     # color
0.1 0.2 100     # ambient, diffuse, specular
sphere
0.0 -0.2 -0.8   # vector
0.15            # radius
0.0 1.0 0.0     # color
0.1 0.2 100     # ambient, diffuse, specular
sphere
0.3 0.3 -1.1    # vector
0.30            # radius
0.0 0.0 1.0     # color
0.1 0.2 100     # ambient, diffuse, specular
sphere
0.1 0.2 -0.3    # vector
0.075           # radius
1.0 0.5 0.0     # color
0.1 0.2 100     # ambient, diffuse, specular
sphere
-0.2 -0.25 -0.4 # vector
0.225           # radius
0.5 0.0 1.0     # color
0.1 0.2 100     # ambient, diffuse, specular