

#include <stdlib.h>

#if defined(__APPLE__) && defined(__MACH__)
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#elif defined(__WIN32) || defined(__linux__)
  #include <GL/glut.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif


GLsizei wh = 1000, ww = 1000; 
GLfloat size = 3.0; 


void drawSquare(int x, int y)
{

  y=wh-y;
  glColor3ub( (char) rand()%256, (char) rand()%256, (char) rand()%256);
  glBegin(GL_POLYGON);
  glVertex2f(x+size, y+size);
  glVertex2f(x-size, y+size);
  glVertex2f(x-size, y-size);
  glVertex2f(x+size, y-size);
  glEnd();
  glFlush();
  glutSwapBuffers();

}

void myReshape(GLsizei w, GLsizei h)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); 
  glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  glViewport(0,0,w,h);
  glClearColor (0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();
  glutSwapBuffers();
  ww = w;
  wh = h; 
}

void myinit(void)
{

  glViewport(0,0,ww,wh);

  /* Pick 2D clipping window to match size of screen window 
     This choice avoids having to scale object coordinates
     each time window is resized */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); 
  glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

  /* set clear color to black and clear window */

  glClearColor (0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glFlush();

  /* callback routine for reshape event */

  glutReshapeFunc(myReshape);

}

void keyboard(unsigned char key,int x,int y){
  if(key == 'q' || key == 'Q'){
      glutDestroyWindow(glutGetWindow());
      exit(1);
  }
}

void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        size = 50.0;
    }else if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN){
        size = 2.00;
    }else if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        size = 20.00; 
    }
    else if(btn == GLUT_RIGHT_BUTTON && state==GLUT_UP){
       glutDestroyWindow(glutGetWindow());
       exit(1);
    }
}

/* display callback required by GLUT 3.0 */

void display(void)
{}

int main(int argc, char** argv)
{

  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutCreateWindow("square");
  myinit ();
  glutReshapeFunc (myReshape);
  glutMouseFunc (mouse);
  glutKeyboardFunc(keyboard);
  glutMotionFunc(drawSquare);
  glutDisplayFunc(display);
  glutMainLoop();

}
