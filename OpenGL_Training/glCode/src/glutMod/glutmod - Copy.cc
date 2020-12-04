#include "GL\glut.h"
#include <math.h>

#include "glutmod.h"

#define PI_ 3.14159265358979323846

GLuint theTorus;

static int mbutton = 0;
static int mousex = 0;
static int mousey = 0;
static int rotx = 0;
static int roty = 0;





/* Draw a torus */


/* Create display list with Torus and initialize state */
static void initGL(void)
{
   //glShadeModel(GL_FLAT);
   glClearColor(0.0, 0.0, 0.0, 0.0);
}

/* Clear window and draw torus */
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glCallList(theTorus);
   glFlush();
}

/* Handle window resize */
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    
}

/* Rotate about x-axis when "x" typed; rotate about y-axis
   when "y" typed; "i" returns torus to original view */
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 'x':
   case 'X':
      glRotatef(30.,1.0,0.0,0.0);
      glutPostRedisplay();
      break;
   case 'y':
   case 'Y':
      glRotatef(30.,0.0,1.0,0.0);
      glutPostRedisplay();
      break;
   case 'i':
   case 'I':
      glLoadIdentity();
      gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
      glutPostRedisplay();
      break;
   case 27:
      return;
   }
}


void mouse( int button, int state, int x, int y )
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    {
	mbutton = 1;
	mousex = x;
	mousey = y;
    }
    else
    {
	mbutton = 0;
    }
}


void motion( int x, int y )
{
    if ( mbutton )
    {
	rotx = x - mousex;
	roty = y - mousey;
	glRotatef(roty/3,1.0,0.0,0.0);
	glRotatef(rotx/3,0.0,1.0,0.0);
	glutPostRedisplay();
	mousex = x; mousey = y;
    }
}


glutWin::glutWin()
{}


glutWin::~glutWin()
{}


void glutWin::init( int argc, char** argv )
{
   glutInitWindowSize(640, 480);
   glutInit(&argc, argv);
   glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH );
   glutCreateWindow(argv[0]);
   initGL();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);

   glMatrixMode(GL_PROJECTION);
   gluPerspective(30, (GLfloat) 640/(GLfloat) 480, 0.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 100.0,  /* eye is at (0,0,30) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */
    glPushMatrix();       /* dummy push so we can pop on model
			    //recalc */
}


void glutWin::setDislayFunction( void (*func)() )
{
    glutDisplayFunc( func );
}


void glutWin::mainLoop()
{
    glutMainLoop();
}


void glutWin::swapBuffer()
{
    glutSwapBuffers();
}
