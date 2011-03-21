#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

GLfloat angle = 0.0;
void cube (void) {
    glRotatef(angle / 10.0, 1.0, 0.0, 0.0);
    glRotatef(angle / 10.0, 0.0, 1.0, 0.0);
    glRotatef(angle / 10.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(2);
}
void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}
void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();  
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    cube();
    glutSwapBuffers();
    angle ++;
}
void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode (GL_MODELVIEW);
}
int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("A basic OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (display);
    //glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
}
