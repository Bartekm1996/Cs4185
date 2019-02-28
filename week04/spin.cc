#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <random>
#include <iostream>


#if defined(__APPLE__) && defined(__MACH__)
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#elif defined(__linux__)
  #include <GL/glut.h>
  #include <GL/gl.h>
  #include <GL/gl.h>
#endif

#define WINDOW_WIDTH        512
#define WINDOW_HEIGHT       512
#define DIRECTION           1
#define SPEED               2
#define QUIT                3
#define SPEED_X_2           4
#define SPEED_0_5           5
#define CLOCK_WISE          6
#define ANTI_CLOCK_WISE     7
#define REVERSE             8
#define RED                 9
#define GREEN               10
#define BLUE                11
#define RANDOM_COLOR        12


int timer = 0;
float angle = 0;
int rotate = 0;
float speed_angle = 0.1;
int direction = -1;
float r = 1.0, g = 1.0 ,b = 1.0;

void idle(void);
void processMenuEvents(int);
int get_ticks();
void set_speed(float);


void
display(void)
{
    int dt;
    glClear(GL_COLOR_BUFFER_BIT);
    dt = get_ticks() - timer;
    timer += dt;
    if (dt < 0) dt = 0;
    if (dt > 1000) dt = 1000;

    if (rotate) {
        if(direction == -1){
             angle -=  speed_angle * ((float) dt); 
        }else if(direction == 1){
            angle += speed_angle * ((float)dt);
        }
    }

    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glColor3f(r, g, b);
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
    float w = 1.0/20;
    glColor3f(0.0f, 0.0f, 0.0f);
    glRectf(-0.5f, 0.5f-w, -0.5f+w, 0.5f);
    glPopMatrix();
    glutSwapBuffers();

}

float randomColOfset(){
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<float> dist(0, 100);
    return dist(engine);
}

void selectEvents(int option){
    switch (option)
    {
        case SPEED_X_2:
            speed_angle *= 2.0f ;
            break;
        case SPEED_0_5:
            speed_angle *= 0.5f ;
            break;
        case RED:
            r = 1.0,g = 0,b = 0;
            break;
        case GREEN:
            g = 1.0,r = 0,b = 0;
            break;
        case BLUE:
            b = 1.0,g = 0,r = 0;
            break;
        case ANTI_CLOCK_WISE:
            direction = -1;
            break;
        case CLOCK_WISE:
            direction = 1;
            break;
        case REVERSE:
            direction = direction*-1;
            break;
        case RANDOM_COLOR:
            r = randomColOfset()/100, g = randomColOfset()/100, b = randomColOfset()/100;
            break;
		case QUIT : exit(0); 
            break;
        default:
            break;
    }
}

void createGLUTMenus() {

	int submenus = glutCreateMenu(selectEvents);
	               glutAddMenuEntry("x2",SPEED_X_2);
	               glutAddMenuEntry("x1/2",SPEED_0_5);

    int dirSubMenu = glutCreateMenu(selectEvents);
                     glutAddMenuEntry("Clockwise",ANTI_CLOCK_WISE);
                     glutAddMenuEntry("Anti Clcokwise",CLOCK_WISE);
                     glutAddMenuEntry("Reverse",REVERSE);

    int colorSubMenu = glutCreateMenu(selectEvents);
                        glutAddMenuEntry("RED",RED);
                        glutAddMenuEntry("GREEN",GREEN);
                        glutAddMenuEntry("BLUE",BLUE);
                        glutAddMenuEntry("RANDOM COLOR",RANDOM_COLOR);
                            
    int menu = glutCreateMenu(selectEvents);
	              glutAddSubMenu("Direction",dirSubMenu);
	              glutAddSubMenu("Speed",submenus);
                  glutAddSubMenu("Color",colorSubMenu);
	              glutAddMenuEntry("Quit",QUIT);
	              glutAttachMenu(GLUT_RIGHT_BUTTON);

}


int
get_ticks()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return 0;

    return tv.tv_sec * 1000 + (tv.tv_usec / 1000);
}


void
init_gl()
{
    glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
}




void
reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

void
keyboard(unsigned char key, int x, int y)
{
   if(key == 'Q' || key == 'q'){
       exit(0);
   }
}

void
special(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_LEFT:
            direction = 1;
            break;
        case GLUT_KEY_RIGHT:
            direction = -1;
            break;
        case GLUT_KEY_UP:
            speed_angle*=2.0f;
            break;
        case GLUT_KEY_DOWN:
            speed_angle*=0.5f;
            break;
        default:
            break;
    }

}

void
mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        timer = get_ticks();
        glutIdleFunc(idle); 
        rotate = 1; 
    }
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        rotate = 0; 
        glutIdleFunc(NULL); 
    }

}

void
motion(int x, int y)
{
}


void
idle(void)
{
    glutPostRedisplay();
}


int
main(int argc, char *argv[])
{

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Turning Rectangle");
    init_gl();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    createGLUTMenus();
    glutMainLoop();

    return EXIT_SUCCESS;
}

