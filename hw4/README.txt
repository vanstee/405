Description:
This is a solution to homework project 3 with basic requirements implemented.
Since it's a raycaster vectors are pointed through the pixels that make up the image
and are colored depending on what they hit (or nothing at all). The color is then
adjusted depending on the the ambient, diffuse and specular lights. The camera can be 
specified in camera.txt.

Name: Patrick Van Stee

Date: February 23, 2011

Instructions:
$ make clean && make
$ ./shady [l|v] [pixwidth] [filename.ext]
Press w to write the display to the file specified in as the [filename.ext] option
Press q or ESC to quit the program

Example camera.txt:
0.0 0.0 0.5     # viewpoint
0.0 0.0 -1.0    # view direction
1.0 0.0 0.0     # up direction
0.5             # focal length
1.25            # aspect ratio
0.5             # screen width
