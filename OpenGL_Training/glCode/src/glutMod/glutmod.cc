/*
 * Copyright © 2017-2018 Ranojay Sen
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
  
  Freeglut Copyright
  ------------------
  
  Freeglut code without an explicit copyright is covered by the following 
  copyright:
  
  Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
  Permission is hereby granted, free of charge,  to any person obtaining a copy 
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction,  including without limitation the rights 
  to use, copy,  modify, merge,  publish, distribute,  sublicense,  and/or sell 
  copies or substantial portions of the Software.
  
  The above  copyright notice  and this permission notice  shall be included in 
  all copies or substantial portions of the Software.
  
  THE SOFTWARE  IS PROVIDED "AS IS",  WITHOUT WARRANTY OF ANY KIND,  EXPRESS OR 
  IMPLIED,  INCLUDING  BUT  NOT LIMITED  TO THE WARRANTIES  OF MERCHANTABILITY, 
  FITNESS  FOR  A PARTICULAR PURPOSE  AND NONINFRINGEMENT.  IN  NO EVENT  SHALL 
  PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM,  DAMAGES OR OTHER LIABILITY, WHETHER 
  IN  AN ACTION  OF CONTRACT,  TORT OR OTHERWISE,  ARISING FROM,  OUT OF  OR IN 
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  
  Except as contained in this notice,  the name of Pawel W. Olszta shall not be 
  used  in advertising  or otherwise to promote the sale, use or other dealings 
  in this Software without prior written authorization from Pawel W. Olszta.
*/



#include "glutmod.h"

#include "GL\glut.h"
#include <math.h>
#include <iostream>


#define PI_ 3.14159265358979323846

static int mbutton = 0;
static float mousex = 0;
static float mousey = 0;
static float rotx = 0;
static float roty = 0;
static float totrotx = 0;
static float totroty = 0;
static float zpos = 20;


struct Camera
{
	Camera(float x, float y, float z) : xPos(x), yPos(y), dist(z), up(1) { updatePos(); }
	
	void RotatateXY(float xangle, float yangle)
	{
		x_angle = ((xangle*3.14f) / 180.0f);
		y_angle = -((yangle*3.14f) / 180.0f);
		updatePos();
	}

	void MoveForward()
	{
		dist -= 0.1f;
		updatePos();
	}

	void MoveBackward()
	{
		dist += 0.1f;
		updatePos();
	}

	void updatePos()
	{
		float radius = dist;
		zPos = cos(y_angle) * cos(x_angle) * radius;
		xPos = sin(y_angle) * cos(x_angle) * radius;
		yPos = sin(x_angle) * radius;
		//up = x_angle > 3.14 ? -up : up;
	}

	float xPos;
	float yPos;
	float zPos;
	float dist;
	float up;
	float x_angle;
	float y_angle;
};

Camera cam(0, 0, zpos);

void initGL(void)
{
    glEnable( GL_LIGHT0 );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    
    //glMatrixMode( GL_PROJECTION );
    ////gluPerspective( 45, (GLfloat) 640/(GLfloat) 480, 1.0, 50 );
    //glMatrixMode( GL_MODELVIEW );
    //glLoadIdentity();
    ////glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    //gluLookAt( 0.0, 0.0, zpos,  /* eye is at (0,0,30) */
	   //    0.0, 0.0, 0.0,   /* center is at (0,0,0) */
	   //    0.0, 1.0, 0.0 ); /* up is in positive Y direction */
    //glPushMatrix();
}


void dumpGLInfo()
{
    std::cout << "\n GL Vendor   : " << (const char*) glGetString(GL_VENDOR) << std::endl;
    std::cout << " GL Renderer : " << (const char*) glGetString(GL_RENDERER) << std::endl;
    std::cout << " GL Version  : " << (const char*) glGetString(GL_VERSION) << std::endl;

}


void reshape( int w, int h )
{
    glViewport( 0, 0, (GLsizei) w, (GLsizei) h );
    float fAspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0f, fAspect, 0.1, 1000.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( cam.xPos, cam.yPos, cam.zPos, 0, 0, 0, 0, 1, 0 );
    glutPostRedisplay();
}


void keyboard( unsigned char key, int x, int y )
{
	switch (key)
	{
	case 'x':
	case 'X':
		glRotatef(30.0, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		glRotatef(30., 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		glLoadIdentity();
		gluLookAt(0, 0, zpos, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 'W':
	case 'w':
		cam.MoveForward();
		glLoadIdentity();
		gluLookAt(cam.xPos, cam.yPos, cam.zPos, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 'S':
	case 's':
		cam.MoveBackward();
		glLoadIdentity();
		gluLookAt(cam.xPos, cam.yPos, cam.zPos, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
		break;
	case 27:
		return;
	}
}


void mouse( int button, int state, int x, int y )
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mbutton = 1;
		mousex = x;
		mousey = y;
	}
	else
	{
		mbutton = 0;
	}

	if (button == 3 || button == 4)
	{
		if (button == 3)
		{
			cam.MoveBackward();
		}
		else if (button == 4)
		{
			cam.MoveForward();
		}

		glLoadIdentity();
		gluLookAt(cam.xPos, cam.yPos, cam.zPos, 0, 0, 0, 0, 1, 0);
		glutPostRedisplay();
	}
}


void motion(int x, int y)
{
	if (mbutton)
	{
		rotx = (x - mousex) / 5;
		roty = (y - mousey) / 5;
		totrotx += totrotx > 180 ? -rotx : rotx;
		totroty += totroty > 180 ? -roty : roty;
		
		glLoadIdentity();
		cam.RotatateXY(totroty, totrotx);
		gluLookAt(cam.xPos, cam.yPos, cam.zPos, 0, 0, 0, 0, cam.up, 0);

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
   glutInitWindowSize( 640, 480 );
   glutInit( &argc, argv );
   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
   glutCreateWindow( argv[0] );
   initGL();
   dumpGLInfo();
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutMotionFunc(motion);
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
