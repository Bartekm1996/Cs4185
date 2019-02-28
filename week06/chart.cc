

#if defined(__APPLE__) && defined(__MACH__)
    #include <GLUT/glut.h>  
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#elif defined(__linux__)
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif


#include <stdlib.h>
#include <math.h>
#include <iostream>

#define BARCHART 1
#define PIECHART 2
#define LINECHART 3
#define ZOOMIN 4
#define ZOOMOUT 5
#define QUIT 6

int chart =1;
double resize = 0;
using namespace std;

class scrPt {
    public:
      GLint x, y;
};

const GLdouble twoPi = 6.283185;
void circleMidpoint (scrPt , GLint ); 

GLsizei winWidth = 400, winHeight = 300;    // Initial display window size.
GLint xRaster = 25, yRaster = 150; // Initial raster position

GLubyte label[36] = { 'J', 'a', 'n',   'F', 'e', 'b',   'M', 'a', 'r',
		      'A', 'p', 'r',   'M', 'a', 'y',   'J', 'u', 'n',
		      'J', 'u', 'l',   'A', 'u', 'g',   'S', 'e', 'p',
		      'O', 'c', 't',   'N', 'o', 'v',   'D', 'e', 'c' };

GLint dataValue[12] = { 420, 342, 324, 310, 262, 185,
			190, 196, 217, 240, 213, 438 };

void init (void)
{
  glClearColor (1.0, 1.0, 1.0, 1.0);
  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (0.0, (GLdouble)winWidth, 0.0, (GLdouble)winHeight);
}

int max(GLint *array){
    int max = array[0];
    for(int i = 1; i < 12; i++){
       
            if(max < array[i]){
                max = array[i];
            }
        
    }
    return max;
}

void winReshapeFcn (int newWidth, int newHeight)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    int _y = (newHeight + resize) - winHeight;
    int _x = (newWidth + resize) - winWidth;
    winWidth = newWidth + resize;
    winHeight = newHeight + resize;
    gluOrtho2D (0.0-resize, GLdouble (winWidth),0.0-resize, GLdouble (winHeight));
    glViewport(0,0,newWidth,newHeight);
    glutPostRedisplay();
}

void barChart (void)
{
  GLint month, k;

  glColor3f (1.0, 0.0, 0.0);           //  Set bar color to red.
  for (k = 0; k < 12; k++)
    glRecti (20 + k*50, 35, 40 + k*50, dataValue [k]);

  glColor3f (0.0, 0.0, 0.0);          //  Set text color to black.
  xRaster = 20;                       //  Display chart labels.
  for (month = 0; month < 12; month++) {
    glRasterPos2i (xRaster, yRaster-140);
    for (k = 3*month; k < 3*month + 3; k++)
      glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, label [k]);
    xRaster += 50;
  }

}

void lineChart (void)
{
  GLint x = 30;

  xRaster = 25;	yRaster = 150;

  glClear(GL_COLOR_BUFFER_BIT);	// clear display window

  glColor3f(0.0, 0.0, 1.0);	// set line colour to blue
  glBegin(GL_LINE_STRIP);
    for (int k = 0; k < 12; k++)
      glVertex2i(x + k*50, dataValue[k]);
  glEnd();

  glColor3f(1.0, 0.0, 0.0);	// Set marker colour to red
  for (int k = 0; k < 12; k++)
  {
    glRasterPos2i(xRaster + k*50, dataValue[k]-4);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
  }

  glColor3f(0.0, 0.0, 0.0);	// black
  xRaster = 20;
  for (int m = 0; m < 12; m++)
  {
    glRasterPos2i(xRaster, yRaster);
    for (int k = 3*m; k < 3*m+3; k++)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
    xRaster += 50;
  }

  glFlush();
}


void pieChart (void)
{
    scrPt circCtr, piePt;
    GLint radius = winWidth / 4;               // Circle radius.

    GLdouble sliceAngle, previousSliceAngle = 0.0;

    GLint k, nSlices = 12;                     // Number of Slices. 
    GLfloat dataValues[12] = {10.0, 7.0, 13.0, 5.0, 13.0, 14.0,
                               3.0, 16, 5.0, 3.0, 17.0, 8.0};
    GLfloat dataSum = 0.0;
 
    circCtr.x = winWidth / 2;                  // Circle center position.
    circCtr.y = winHeight / 2;
    circleMidpoint (circCtr, radius);  // Call midpoint circle-plot routine.

    for (k = 0; k < nSlices; k++)
        dataSum += dataValues[k];

    for (k = 0; k < nSlices; k++) {
        sliceAngle = twoPi * dataValues[k] / dataSum + previousSliceAngle;
        piePt.x = (GLint) (circCtr.x + radius * cos (sliceAngle));
        piePt.y = (GLint) (circCtr.y + radius * sin (sliceAngle));
        glBegin (GL_LINES);
            glVertex2i (circCtr.x, circCtr.y);
            glVertex2i (piePt.x, piePt.y);
        glEnd ( );
        previousSliceAngle = sliceAngle;
    }

}

void displayFcn (void)
{
    glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.
    glColor3f (0.0, 0.0, 1.0);       //  Set circle color to blue.
 	    winWidth = glutGet(GLUT_WINDOW_WIDTH);
	    winHeight = glutGet(GLUT_WINDOW_HEIGHT); 

    switch (chart)
    {
        case 1:
            barChart();
            break;
        case 2:
            pieChart();
            break;
        case 3:
            lineChart();	
            break;
        default:
            break;
    }
    winReshapeFcn(winWidth,winHeight);			
    glutSwapBuffers ( );
}


void selectEvent(int option){
    switch (option)
    {
        case BARCHART:
        {
	    	chart = 1;
            break;
	    }
        case PIECHART:
        {
	    	chart = 2;
			break;
	    }
        case LINECHART:
        {
	    	chart = 3;
            break;
	    }
        case ZOOMIN:
            resize -= 10;
            break;
        case ZOOMOUT:
            resize += 10;
            break;
        case QUIT:
            exit(0);
        default:
            break;
    }
}

void createGLUTMenus() {

	int chartMenu = glutCreateMenu(selectEvent);
	                glutAddMenuEntry("Bar Chart",BARCHART);
	                glutAddMenuEntry("Pie Chart",PIECHART);
                    glutAddMenuEntry("Line Char",LINECHART);
                    glutAddMenuEntry("Zoom In + ",ZOOMIN);
                    glutAddMenuEntry("Zoom Out - ",ZOOMOUT);
                    glutAddMenuEntry("Quit",QUIT);
                    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

unsigned char toLower(unsigned char key){
	if(key >= 'A' && key <= 'Z'){
		return key+32;
	} 
	return key;
}
void keyBoard(unsigned char key, int x, int y){

    if(key == 'Z'){
            resize += 10;
	}
    else if(key == 'z'){
 	    resize -= 10;
	}
    else{			
    switch (toLower(key))
    {
        case 'p':
            selectEvent(2);
            break;
        case 'b':
            selectEvent(1);
            break;
        case 'l':
            selectEvent(3);
            break;
        case 'q':
            selectEvent(6);
            break;
        default:
            break;
    }
	}
}

/*
void motion_func (int x, int y) {
        x_pos -= x;
        y_pos -= y;
}
*/

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    
    switch(chart){
	case 1:
		winWidth = xRaster + (12*50),winHeight = max(dataValue)+100;
		glutInitWindowSize(winWidth,winHeight);
		break;
	case 2:
		winWidth = winWidth/2, winHeight = winWidth;
		glutInitWindowSize(winWidth,winHeight);
		break;
	case 3:
		winWidth = xRaster+(12*50), winHeight = max(dataValue);
		glutInitWindowSize(winWidth,winHeight);
		break;

    }	
    int _x = glutGet(GLUT_SCREEN_WIDTH)/2 - (winWidth/2);
    int _y = glutGet(GLUT_SCREEN_HEIGHT)/2 - (winHeight/2);
    glutInitWindowPosition (_x, _y);
    glutCreateWindow ("Charts");
    init ( );
    glutDisplayFunc (displayFcn);
    glutKeyboardFunc(keyBoard);
    glutReshapeFunc (winReshapeFcn);
    //glutMotionFunc(motion_func);
    createGLUTMenus();
    glutMainLoop ( );
}
