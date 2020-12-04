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


The OpenGL Extension Wrangler Library
Copyright (C) 2002-2007, Milan Ikits <milan ikits[]ieee org>
Copyright (C) 2002-2007, Marcelo E. Magallon <mmagallo[]debian org>
Copyright (C) 2002, Lev Povalahev
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, 
  this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright notice, 
  this list of conditions and the following disclaimer in the documentation 
  and/or other materials provided with the distribution.
* The name of the author may be used to endorse or promote products 
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.


Mesa 3-D graphics library
Version:  7.0

Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


Copyright (c) 2007 The Khronos Group Inc.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and/or associated documentation files (the
"Materials"), to deal in the Materials without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Materials, and to
permit persons to whom the Materials are furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Materials.

THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/


#include <windows.h>
#include "Gl/glew.h"
#include <Gl/gl.h>
#include <Gl/glu.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <fstream>

#include "globject.h"

#define mImageDir( fnm )\
    "..\\..\\data\\images\\"##fnm 

#define mModelDir( fnm )\
    "..\\..\\data\\models\\"##fnm

#define mShaderDir( fnm )\
    "..\\..\\data\\shaders\\"##fnm 

#pragma comment (lib, "glew32.lib")    

GLObject::GLObject()
    : m_isloaded(false)
    , m_nrtextures(2)
{
    GLenum err = glewInit();
    m_is_glew_ok = err == GLEW_OK;
    if ( !m_is_glew_ok )
	fprintf(stderr, "Error: %s\n", glewGetErrorString(err) );
}


void GLObject::drawPoints( float x1, float y1, float z1, float x2, float y2, float z2 )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDisable( GL_LIGHTING );
    glPointSize( 5.0 );
    glBegin( GL_POINTS );

	glVertex3f( x1, y1, z1 );
	glVertex3f( x2, y2, z2 );

    glEnd();
    glFlush();
}


void GLObject::drawLines( float x1, float y1, float z1, float x2, float y2, float z2 )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDisable( GL_LIGHTING );
    glBegin( GL_LINES );

	glVertex3f( x1, y1, z1 );
	glVertex3f( x2, y2, z2 );

    glEnd();
    glFlush();
}


void GLObject::drawFirstBox( float x,float z,float y,float u,float v, float w, bool isfilled )
{	
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glFrontFace( GL_CCW );

    if( isfilled )
    {
	glEnable( GL_LIGHT0 );						
	glEnable( GL_LIGHTING );						
	glEnable( GL_COLOR_MATERIAL );
     
	glBegin ( GL_QUADS ) ;

	    glNormal3f(0.0f,0.0f,1.0f);

	    glVertex3f ( -1*x+u, y+v, z+w ) ; // lt front
            
	    glVertex3f ( -1*x+u, -1*y+v , z+w ) ; // lb front
                
	    glVertex3f ( x+u, -1*y+v, z+w ) ;  // rb front
            
	    glVertex3f ( x+u, y+v, z+w ) ;  // rt front

	glEnd( ) ;

	glBegin ( GL_QUADS ) ;

	    glNormal3f(1.0f,0.0f,0.0f);	 

	    glVertex3f ( x+u, y+v, z +w) ;  // rt front

	    glVertex3f ( x+u, -1*y+v, z+w ) ;  // rb front

	    glVertex3f ( x+u, -1*y+v, -1*z+w ) ;  // rb back

	    glVertex3f ( x+u, y+v, -1*z+w ) ;  // rt back

	glEnd( ) ;
        
	glBegin ( GL_QUADS ) ;

	    glNormal3f(0.0f,0.0f,-1.0f);

	    glVertex3f ( x+u, y+v, -1*z+w ) ;  // rt back

	    glVertex3f ( x+u, -1*y+v, -1*z+w ) ;  // rb back

	    glVertex3f ( -1*x+u , -1*y+v , -1*z+w  ) ;  // lb back

	    glVertex3f ( -1*x+u , y+v, -1*z+w  ) ;  // lt back

	glEnd( ) ;

	glBegin ( GL_QUADS ) ;

	    glNormal3f(-1.0f,0.0f,0.0f);		

	    glVertex3f ( -1*x+u, y+v , -1*z+w ) ;  // lt back

	    glVertex3f ( -1*x+u, -1*y+v , -1*z+w  ) ;  // lb back

	    glVertex3f ( -1*x+u , -1*y+v , z+w  ) ;  // lb front

	    glVertex3f ( -1*x+u , y+v  , z+w  ) ;  // lt front

	glEnd( ) ;

	glBegin ( GL_QUADS ) ;
	    glNormal3f(0.0f,-1.0f,0.0f);

	    glVertex3f ( -1*x+u , -1*y+v ,  z+w  ) ;  // lb front

	    glVertex3f ( -1*x+u , -1*y+v, -1*z+w ) ;  // lb back

	    glVertex3f ( x+u , -1*y+v , -1*z+w  ) ;  // rb back

	    glVertex3f (  x+u  , -1*y+v , z+w   ) ;  // rb front

	glEnd();

	glBegin ( GL_QUADS ) ; 

	    glNormal3f(0.0f,1.0f,0.0f);

	    glVertex3f ( -1*x+u , y+v, -1*z  +w) ;  // lt back

	    glVertex3f ( -1*x+u , y+v,  z+w  ) ;  // lt front

	    glVertex3f (   x+u ,   y+v ,   z+w  ) ;  // rt front

	    glVertex3f (  x+u  ,    y+v , -1*z+w  ) ;  // rt back 

	glEnd( ) ;
	glDisable( GL_LIGHTING );
    }
    else 
    {
	glDisable( GL_LIGHTING );
	glColor3ub ( 255, 255, 255 ) ; 
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glHint( GL_LINE_SMOOTH_HINT, GL_DONT_CARE );
	glLineWidth (1.5);

	glBegin ( GL_LINE_STRIP ) ;

	    glVertex3f ( -1*x+u, y+v, z+w ) ; // lt front
    	 
	    glVertex3f ( -1*x+u, -1*y+v , z+w ) ; // lb front

	    glVertex3f ( x+u, -1*y+v, z+w ) ;  // rb front

	    glVertex3f ( x+u, y+v, z+w ) ;  // rt front

	    glVertex3f ( x+u, -1*y+v, z+w ) ;  // rb front

	    glVertex3f ( x+u, -1*y+v, -1*z+w ) ;  // rb back

	    glVertex3f ( x+u, y+v, -1*z+w ) ;  // rt back

	    glVertex3f ( x+u, -1*y+v, -1*z+w ) ;  // rb back

	    glVertex3f ( -1*x+u , -1*y+v , -1*z+w  ) ;  // lb back

	    glVertex3f ( -1*x+u , y+v, -1*z+w) ;  // lt back

	    glVertex3f ( -1*x+u , y+v,  z+w  ) ;  // lt front

	    glVertex3f (   x+u ,   y+v ,   z+w  ) ;  // rt front

	    glVertex3f (  x+u  ,    y+v , -1*z+w  ) ;  // rt back 

	    glVertex3f ( -1*x+u , y+v, -1*z +w) ;
    	
	    glVertex3f ( -1*x+u , -1*y+v ,  -1*z+w  ) ;
    	 
	    glVertex3f ( -1*x+u , -1*y+v ,   z+w  ) ;

	glEnd( ) ;
	glEnable( GL_LIGHT0 );						
	glEnable( GL_LIGHTING );						
	glEnable( GL_COLOR_MATERIAL );
	glDisable( GL_LINE_SMOOTH );
    }
  
   glFlush();
}


void GLObject::drawTexturedBox( float x, float y, float z )
{
    loadTexture( mImageDir("wood1.bmp") );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_TEXTURE_2D );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    drawSimpleBox( x, y, z );
    glFlush();
}


void GLObject::drawTransformedBoxes()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

 //   //glPushMatrix();
 //   //glMatrixMode( GL_MODELVIEW );

 //   //glLoadIdentity();
 //   glTranslatef( 0.0f, 10.0f, 0.0f );
 //   drawSimpleBox( 3, 3, 3 );
	////glPopMatrix();
	////glFlush();

	////glPushMatrix();
	////glMatrixMode(GL_MODELVIEW);
 //   glLoadIdentity();
 //   glTranslatef( 10.0f, 0.0f, 0.0f );
 //   drawSimpleSphere( 3, 0, 0, 0 );
 //   
 //  // glPopMatrix();

 // Set current matrix to modelview and reset
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//// Go 10 units up the y-axis
	//glTranslatef(0.0f, 10.0f, 0.0f);
	//// Draw the first sphere
	//drawSimpleBox(3, 3, 3);
	//// Reset modelview matrix again
	//glLoadIdentity();
	//// Go 10 units out the x-axis
	//glTranslatef(10.0f, 0.0f, 0.0f);
	//// Draw the second sphere
	//drawSimpleSphere(3, 0, 0, 0);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	// Go 10 units up the y-axis
	glTranslatef(0.0f, 10.0f, 0.0f);
	// Draw the first sphere
	drawSimpleBox(3, 3, 3);
	// Reset modelview matrix again
	glPushMatrix();
	// Go 10 units out the x-axis
	//glLoadIdentity();
	glTranslatef(10.0f, 0.0f, 0.0f);
	// Draw the second sphere
	drawSimpleSphere(3, 0, 0, 0);
	glPopMatrix();
	glFlush();
}


void GLObject::drawSimpleBox( float x, float y, float z )
{

    float vertices[8][3] =
    {
        { -x, -y, -z }, // 0
	{ -x,  y, -z }, // 1
	{  x,  y, -z }, // 2
	{  x, -y, -z }, // 3
	{ -x, -y,  z }, // 4
	{ -x,  y,  z }, // 5
	{  x,  y,  z }, // 6
	{  x, -y,  z }  // 7
    };

    GLfloat normals[6][3] = 
    {   /* Normals for the 6 faces of a cube. */
	{ 0.0, 0.0, -1.0 }, { -1.0, 0.0, 0.0 }, { 0.0,  0.0, 1.0 },
	{ 1.0, 0.0,  0.0 }, {  0.0, 1.0, 0.0 }, { 0.0, -1.0, 0.0 }
    };

    
 //   GLfloat normals[24][3] = 
 //   {   /* Normals for the 6 faces of a cube. */
	//{ 0.0, 0.0, -1.0 }, { 0.0, 0.0, -1.0 }, { 0.0, 0.0, -1.0 }, { 0.0, 0.0, -1.0 }, 
	//{ -1.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }, 
	//{ 0.0,  0.0, 1.0 }, { 0.0,  0.0, 1.0 }, { 0.0,  0.0, 1.0 }, { 0.0,  0.0, 1.0 },
	//{ 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, 
	//{ 0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, 
	//{ 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }
 //   };

    GLubyte indices[] = { 3, 2, 1, 0, 
			  0, 1, 5, 4,
			  4, 5, 6, 7,
			  7, 6, 2, 3,
			  1, 2, 6, 5,
			  0, 4, 7, 3 };
    
    GLfloat texcoords[4][2] =
    {
	{ 0.0, 0.0 },
	{ 0.0, 1.0 },
	{ 1.0, 1.0 },
	{ 1.0, 0.0 },
    };

    //glEnable( GL_COLOR_MATERIAL );
    //glEnable( GL_CULL_FACE );

    int ci = 0;
    for ( int nrfc = 0; nrfc<6; nrfc++ )
    {
	glBegin( GL_QUADS );
	glNormal3fv( normals[nrfc] );
	for ( int idx=0; idx<4; idx++ )
	{
	    glTexCoord2fv( texcoords[idx] ); 
	    glVertex3fv( vertices[indices[ci]] );
	    ci++;
	}

	glEnd();
	
    }

    //glFlush();
}


void GLObject::drawBoxVA( float x, float y, float z )
{

    float boxvertices[8][3] =
    {
        { -x, -y, -z }, // 0
	{ -x,  y, -z }, // 1
	{  x,  y, -z }, // 2
	{  x, -y, -z }, // 3
	{ -x, -y,  z }, // 4
	{ -x,  y,  z }, // 5
	{  x,  y,  z }, // 6
	{  x, -y,  z }  // 7
    };

    /*GLfloat normals[24][3] = 
    {
	{ 0.0, 0.0, -1.0 }, { 0.0, 0.0, -1.0 }, { 0.0, 0.0, -1.0 }, { 0.0, 0.0, -1.0 }, 
	{ -1.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }, { -1.0, 0.0, 0.0 }, 
	{ 0.0,  0.0, 1.0 }, { 0.0,  0.0, 1.0 }, { 0.0,  0.0, 1.0 }, { 0.0,  0.0, 1.0 },
	{ 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, 
	{ 0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, 
	{ 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }
    };*/


    GLfloat boxnormals[6][3] = 
    {   
	{ 0.0, 0.0, -1.0 }, { -1.0, 0.0, 0.0 }, { 0.0,  0.0, 1.0 },
	{ 1.0, 0.0,  0.0 }, {  0.0, 1.0, 0.0 }, { 0.0, -1.0, 0.0 }
    };


        
    GLubyte boxindices[] = { 3, 2, 1, 0, 
			     0, 1, 5, 4,
			     4, 5, 6, 7,
			     7, 6, 2, 3,
			     1, 2, 6, 5,
			     0, 4, 7, 3 };
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glShadeModel( GL_FLAT );
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, boxvertices );
    glNormalPointer( GL_FLOAT, 0, boxnormals );
    glDrawElements( GL_QUADS, 24, GL_UNSIGNED_BYTE, boxindices );

    glFlush();
}


void GLObject::drawVBOBox( float x, float y, float z )
{
    if ( !m_is_glew_ok )
	return;

    GLfloat vertices[24] =
    {
         -x, -y, -z, // 0
	 -x,  y, -z, // 1
	  x,  y, -z, // 2
	  x, -y, -z, // 3
	 -x, -y,  z, // 4
	 -x,  y,  z, // 5
	  x,  y,  z, // 6
	  x, -y,  z  // 7
    };

    /*GLfloat normals[24][3] = 
    {
	 0.0, 0.0, -1.0,  0.0, 0.0, -1.0, 0.0, 0.0, -1.0,  0.0, 0.0, -1.0, 
	-1.0, 0.0, 0.0 , -1.0, 0.0, 0.0, -1.0, 0.0, 0.0 , -1.0, 0.0, 0.0 , 
	 0.0,  0.0, 1.0,  0.0,  0.0, 1.0 },  0.0,  0.0, 1.0,  0.0,  0.0, 1.0,
	{ 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, { 1.0, 0.0,  0.0 }, 
	{ 0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, {  0.0, 1.0, 0.0 }, 
	{ 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, -1.0, 0.0 }
    };*/

    GLushort indices[] = { 3, 2, 1, 0, 
			  0, 1, 5, 4,
			  4, 5, 6, 7,
			  7, 6, 2, 3,
			  1, 2, 6, 5,
			  0, 4, 7, 3 };
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDisable( GL_LIGHTING );
    
    GLuint vertex_buffer;
    glGenBuffers( 1, &vertex_buffer );

    glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer );
    glBufferData( GL_ARRAY_BUFFER,
                     sizeof(vertices),
                     vertices,
                     GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    GLuint index_buffer;
    glGenBuffers( 1, &index_buffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_buffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                    sizeof(indices),
                    indices,
                    GL_STATIC_DRAW);

    glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0 );
    
    glFlush();
}


void GLObject::drawTeapotVS( float rad )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_LIGHTING );
    glEnable( GL_COLOR_MATERIAL );
    glColor3ub( 255, 0, 0 );

    GLuint shader_program = glCreateProgram();
    GLuint vs = glCreateShader( GL_VERTEX_SHADER );
    
    const char* vsrc = readShaderFile( mShaderDir("spec_vs.txt") );
    glShaderSource( vs, 1, &vsrc, NULL );
   
    glCompileShader( vs );

    glAttachShader( shader_program, vs );

    glLinkProgram( shader_program );
    glUseProgram( shader_program );
    
    drawSimpleTeapot( rad );

    glFlush();
}


void GLObject::drawTeapotFS( float rad )
{
    static const char* toon_vertxsrc[] =
    {
    "varying vec3 normal;\n"
    "void main()\n"
    "{\n"
    " normal = normalize(gl_NormalMatrix * gl_Normal);\n"
    " gl_Position = ftransform();\n"
    "}\n"
    };

    static const char* toon_fragsrc[] =
    {
    "uniform vec4 color1;\n"
    "uniform vec4 color2;\n"
    "uniform vec4 color3;\n"
    "uniform vec4 color4;\n"
    "varying vec3 normal;\n"
    "void main()\n"
    "{\n"
    " float intensity = dot(vec3(gl_LightSource[0].position),normal);\n"
    " if (intensity > 0.95) gl_FragColor = color1;\n"
    " else if (intensity > 0.5) gl_FragColor = color2;\n"
    " else if (intensity > 0.25) gl_FragColor = color3;\n"
    " else gl_FragColor = color4;\n"
    "}\n"
    };

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_LIGHTING );
    glEnable( GL_COLOR_MATERIAL );

    GLuint shader_program = glCreateProgram();
    GLuint vs = glCreateShader( GL_VERTEX_SHADER );
    GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
    
    glShaderSource( vs, 1, toon_vertxsrc, NULL );
    glShaderSource( fs, 1, toon_fragsrc, NULL );

    glCompileShader( vs );
    GLint iscompiled = 0;
    glGetShaderiv( vs, GL_COMPILE_STATUS, &iscompiled);
    if( iscompiled == GL_FALSE )
    {
	GLint maxLength = 0;
	glGetShaderiv( vs, GL_INFO_LOG_LENGTH, &maxLength);
	
	GLchar* infoLog;
	glGetShaderInfoLog( vs, maxLength, &maxLength, &infoLog[0] );
	glDeleteShader( vs );
	return;
    }

    glCompileShader( fs );
    glGetShaderiv( fs, GL_COMPILE_STATUS, &iscompiled );
    if( iscompiled == GL_FALSE )
    {
	GLint maxLength = 0;
	glGetShaderiv( fs, GL_INFO_LOG_LENGTH, &maxLength );

	GLchar* infoLog;
	glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);

	glDeleteShader(fs);
	return;
    }

    glAttachShader( shader_program, vs );
    glAttachShader( shader_program, fs );

    glLinkProgram( shader_program );
    glUseProgram( shader_program );
    
    float color1[4] = { 1.0, 0.5, 0.5, 1.0 };
    float color2[4] = { 0.5, 0.2, 0.2, 1.0 };
    float color3[4] = { 0.2, 0.1, 0.1, 1.0 };
    float color4[4] = { 0.1, 0.05, 0.05, 1.0 };

    int color1_loc = glGetUniformLocation( shader_program, "color1" );
    glProgramUniform4fv( shader_program, color1_loc, 1, color1 );

    int color2_loc = glGetUniformLocation( shader_program, "color2" );
    glProgramUniform4fv( shader_program, color2_loc, 1, color2 );

    int color3_loc = glGetUniformLocation( shader_program, "color3" );
    glProgramUniform4fv( shader_program, color3_loc, 1, color3 );

    int color4_loc = glGetUniformLocation( shader_program, "color4" );
    glProgramUniform4fv( shader_program, color4_loc, 1, color4 );
    
    drawSimpleTeapot( rad );

    glFlush();
}


void GLObject::drawTeapotFS4IntelCards( float rad )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable( GL_LIGHTING );
    glEnable( GL_COLOR_MATERIAL );

    GLuint shader_program = glCreateProgram();
    GLuint vs = glCreateShader( GL_VERTEX_SHADER );
    GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );
    
    const char* toon_vertxsrc = readShaderFile( mShaderDir("toon_vs.txt") );
    glShaderSource( vs, 1, &toon_vertxsrc, NULL );
    const char* toon_fragsrc = readShaderFile( mShaderDir("toon_fs.txt") );
    glShaderSource( fs, 1, &toon_fragsrc, NULL );

    glCompileShader( vs );
    GLint iscompiled = 0;
    glGetShaderiv( vs, GL_COMPILE_STATUS, &iscompiled);
    if( iscompiled == GL_FALSE )
    {
	GLint maxLength = 0;
	glGetShaderiv( vs, GL_INFO_LOG_LENGTH, &maxLength);
	
	GLchar* infoLog;
	glGetShaderInfoLog( vs, maxLength, &maxLength, &infoLog[0] );
	glDeleteShader( vs );
	return;
    }

    glCompileShader( fs );
    glGetShaderiv( fs, GL_COMPILE_STATUS, &iscompiled );
    if( iscompiled == GL_FALSE )
    {
	GLint maxLength = 0;
	glGetShaderiv( fs, GL_INFO_LOG_LENGTH, &maxLength );

	GLchar* infoLog;
	glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);

	glDeleteShader(fs);
	return;
    }

    glAttachShader( shader_program, vs );
    glAttachShader( shader_program, fs );

    glLinkProgram( shader_program );
    glUseProgram( shader_program );
    
    drawSimpleTeapot( rad );

    glFlush();
}


void GLObject::drawShaderBox( float x, float y, float z )
{
    if ( !m_is_glew_ok )
	return;

    /*static const char* vertexsrc[] = 
    {
	"#version 120\n"
	"#extension GL_EXT_geometry_shader4 : enable\n"
	"varying vec3 normal;\n"
	"varying vec4 pos;\n"
	"void main()\n"
	"{\n"
	" normal = normalize(gl_NormalMatrix * gl_Normal);\n"
	" gl_Position = ftransform();\n"
	" pos = gl_Position;\n"
	"}\n"
    };

    static const char* fragmsrc[] =
    {
	"varying vec3 normal;\n"
	"varying vec4 pos;\n"
	"void main()\n"
	"{\n"
	" float intensity = dot(vec3(gl_LightSource[0].position),normal);\n"
	" vec4 col = pos.x < 1.0 ? vec4(0,1,0,0) : vec4(0,0,1,0); \n"
	" gl_FragColor = col;\n"
	"}\n"
    };*/
    
    GLfloat vertices[24] =
    {
         -x, -y, -z, // 0
	 -x,  y, -z, // 1
	  x,  y, -z, // 2
	  x, -y, -z, // 3
	 -x, -y,  z, // 4
	 -x,  y,  z, // 5
	  x,  y,  z, // 6
	  x, -y,  z  // 7
    };
    
    GLushort indices[] = { 3, 2, 1, 0, 
			  0, 1, 5, 4,
			  4, 5, 6, 7,
			  7, 6, 2, 3,
			  1, 2, 6, 5,
			  0, 4, 7, 3 };
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glDisable( GL_LIGHTING );
    
    GLuint vertex_buffer;
    glGenBuffers( 1, &vertex_buffer );

    glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer );
    glBufferData( GL_ARRAY_BUFFER,
                     sizeof(vertices),
                     vertices,
                     GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    GLuint index_buffer;
    glGenBuffers( 1, &index_buffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, index_buffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                    sizeof(indices),
                    indices,
                    GL_STATIC_DRAW);

    GLuint shader_program = glCreateProgram();
    GLuint vs = glCreateShader( GL_VERTEX_SHADER );
    GLuint fs = glCreateShader( GL_FRAGMENT_SHADER );

    const char* vsrc = readShaderFile( mShaderDir("first_vs.txt") );
    glShaderSource( vs, 1, &vsrc, NULL );
    const char* fsrc = readShaderFile( mShaderDir("first_fs.txt") );
    glShaderSource( fs, 1, &fsrc, NULL );

    glCompileShader( vs );
    glCompileShader( fs );

    glAttachShader( shader_program, vs );
    //glAttachShader( shader_program, fs );

    glLinkProgram( shader_program );
    glUseProgram( shader_program );
    glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0 );
    
    glFlush();
}


void GLObject::drawColoTriangle()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_COLOR_MATERIAL );
    // Draw the triangle
    glBegin( GL_TRIANGLES );
	// Red Apex
	glColor3ub( (GLubyte)255, (GLubyte)0, (GLubyte)0 );
	glVertex3f( 0.0f, 5.0f, 0.0f );
	// Green on the right bottom corner
	glColor3ub( (GLubyte)0, (GLubyte)255, (GLubyte)0 );
	glVertex3f( 5.0f, -2.0f , 0.0f );
	// Blue on the left bottom corner
	glColor3ub( (GLubyte)0, (GLubyte)0, (GLubyte)255 );
	glVertex3f( -5.0f, -2.0f, 0.0f );
    glEnd();
}


void GLObject::drawMaterialTriangle()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    float diffuse_reflectivity[] = { 0.0, 0.25f, 0.25f, 1.0f };
    float ambient_reflectivity[] = { 0.1, 0.1f, 0.1f, 1.0f };
    glMaterialfv( GL_FRONT, GL_AMBIENT, ambient_reflectivity );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse_reflectivity );
    glEnable( GL_LIGHTING );

    glBegin( GL_TRIANGLES );
	glNormal3f( 0.0, 0.0, 1.0 );
	glVertex3f( 0.0f, 5.0f, 0.0f );
	glVertex3f( 5.0f, -2.0f , 0.0f );
	glVertex3f( -5.0f, -2.0f, 0.0f );
    glEnd();
}


void GLObject::drawTransparentTriangles()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glEnable( GL_LIGHTING );
    glEnable( GL_COLOR_MATERIAL );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); 
    glFrontFace( GL_CW );

    glBegin( GL_TRIANGLES );
	glNormal3f( 0.0, 0.0, 1.0 );
	glColor4ub( 255, 0, 0, 255 );
	glVertex3f( 0.0f, 5.0f,   -2.0f );
	glVertex3f( 5.0f, -2.0f , -2.0f );
	glVertex3f( -5.0f, -2.0f, -2.0f );
    glEnd();

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glBegin( GL_TRIANGLES );
	glColor4ub( 0, 0, 255, 128 );
	glNormal3f( 0.0, 0.0, 1.0 );
	glVertex3f( 0.0f, 5.0f,   2.0f );
	glVertex3f( 5.0f, -2.0f , 2.0f );
	glVertex3f( -5.0f, -2.0f, 2.0f );
    glEnd();
    glDisable( GL_BLEND );
}


void  GLObject::drawSphere( float rad, float u, float v, float w )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    float x = 0, y = 0, z = 0;
    float t = 0, ra = 0, rs = 0, ha = 0, hs = 0;
    glEnable( GL_LIGHTING );
    glFrontFace( GL_CCW );

    drawSimpleSphere( rad, u, v, w );
    
    glDisable( GL_LIGHTING );
    glFlush();
}


void  GLObject::drawMaterialSphere( float rad, float u, float v, float w )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    float x = 0, y = 0, z = 0;
    float t = 0, ra = 0, rs = 0, ha = 0, hs = 0;
    glEnable( GL_LIGHTING );
    glFrontFace( GL_CCW );
    float diffuse_reflectivity[] = { 0.0, 0.25f, 0.25f, 1.0f };
    float ambient_reflectivity[] = { 0.15, 0.15f, 0.15f, 1.0f };
    float specular_reflectivity[] = { 0.5, 0.5f, 0.5f, 1.0f };
    glMaterialfv( GL_FRONT, GL_AMBIENT, ambient_reflectivity );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse_reflectivity );
    glMaterialfv( GL_FRONT, GL_SPECULAR, specular_reflectivity );
    glMateriali( GL_FRONT, GL_SHININESS, 128 );
    
    drawSimpleSphere( rad, u, v, w );
 
    glDisable( GL_LIGHTING );
    glFlush();
}


void  GLObject::drawRealisticEarth(float rad, float u, float v, float w)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawSimpleEarth(rad, u, v, w);
	drawAtmosphere(rad + 0.15, u, v, w);

	glFlush();
}

void  GLObject::drawEarth( float rad, float u, float v, float w )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    drawSimpleEarth( rad, u, v, w );
 
    glFlush();
}



void  GLObject::drawSimpleEarth(float rad, float u, float v, float w)
{
	glEnable(GL_LIGHTING);
	glFrontFace(GL_CCW);

	loadTexture(mImageDir("earth2.bmp"));
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_CULL_FACE);
	float diffuse_reflectivity[] = { 0.7, 0.7f, 0.7f, 1.0f };
	float ambient_reflectivity[] = { 0.25, 0.25f, 0.25f, 1.0f };
	float specular_reflectivity[] = { 0.5, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_reflectivity);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_reflectivity);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_reflectivity);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	drawSimpleSphere(rad, u, v, w);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void GLObject::drawAtmosphere(float rad, float u, float v, float w)
{
	static const char* atmos_vertxsrc[] =
	{
		"varying vec3 normal;\n"
		"void main()\n"
		"{\n"
		" normal = normalize(gl_NormalMatrix * gl_Normal);\n"
		" gl_Position = ftransform();\n"
		"}\n"
	};

	static const char* atmos_fragsrc[] =
	{
		"varying vec3 normal;\n"
		"void main()\n"
		"{\n"
		" float intensity = abs(dot(vec3(gl_LightSource[0].position),normal));\n"
		" vec4 color = vec4( 0.0, 0.9, 1.0, 1-(1.5*intensity));\n"
		" gl_FragColor = color;\n"
		"}\n"
	};

	glPushAttrib(GL_TEXTURE_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glDisable(GL_TEXTURE_2D);

	GLuint shader_program = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, atmos_vertxsrc, NULL);
	glShaderSource(fs, 1, atmos_fragsrc, NULL);

	glCompileShader(vs);
	GLint iscompiled = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &iscompiled);
	if (iscompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* infoLog;
		glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);
		glDeleteShader(vs);
		return;
	}

	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &iscompiled);
	if (iscompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar* infoLog;
		glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(fs);
		return;
	}

	glAttachShader(shader_program, vs);
	glAttachShader(shader_program, fs);

	glLinkProgram(shader_program);
	glUseProgram(shader_program);

	drawSimpleSphere(rad, u, v, w);

	glDetachShader(shader_program, vs);
	glDetachShader(shader_program, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glUseProgramObjectARB(0);
	glUseProgram(0);

	glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
}


void  GLObject::drawSimpleSphere( float rad, float u, float v, float w )
{
    float x = 0, y =0 ,z = 0;
    float t = 0, ra = 0, rs = 0, ha = 0, hs = 0;
    int res = 200;

    for ( int j=0; j<=res; j++ )
    {
	float anglv = ( float(j) * M_PI / float(res) );
	rs=rad*sin( anglv );
	hs=rad*cos( anglv );
 	glBegin(GL_QUAD_STRIP);

	for ( int i=0; i<=res; i++ )
	{
	    float anglh = M_PI/2 + float(i)* 2 * M_PI / float(res); 
		if (j != 0)
		{
			glNormal3f(sin(anglh)*ra / rad, ha / rad, cos(anglh)*ra / rad);
			glTexCoord2f((float)i / res, (float)j / res);
			glVertex3f(sin(anglh)*ra + u, ha + v, cos(anglh)*ra + w);
			glNormal3f(sin(anglh)*rs / rad, hs / rad, cos(anglh)*rs / rad);
			glTexCoord2f((float)i / res, (float)(j + 1) / res);
			glVertex3f(sin(anglh)*rs + u, hs + v, cos(anglh)*rs + w);
		}
	}
	
	ra = rs;
	ha = hs;
	glEnd();
    }

}


void GLObject::drawLayers( float x,float z, float y,float u,float v, float w, bool filled )
{
    glPushMatrix();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    int i,j;
    float vec[3][3],xf,yf,zf,step=1,f=0.1,F=0.5,*q,k=0,l=0,tmp;
    float normal[3];
    static float **p;

    p = new float * [x*2];
    for ( i = 0; i <=2*x; i++ ) 
    {
        p[i] = new float [z*2];
    }


    l=0;
    for ( i=0; i<=2*x; i++ )
    {
	k=0;
	for ( j=0; j<=2*z+1; j++ )
	{
	    p[i][j] = sin((2*3.14/60)*(i-60*i)) + 2*cos((2*3.14/50)*(j-50*j));
	    k+=1;
	    f+=0.01;
	}	
	l++;
    }


    if( filled )
    {	
	glEnable( GL_LIGHT0 );						
	glEnable( GL_LIGHTING );						
	glEnable( GL_COLOR_MATERIAL );
	glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL ) ;
	glColor3ub ( 255, 132, 0 ) ;
    }
    else
    {
	glDisable( GL_LIGHTING );
	glLineWidth ( 1.0 );
	glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE ) ;
	glColor3ub ( 255, 0, 0 ) ;
    }
    
    for ( xf = -x,i=0; xf<x;i++, xf+=step )
    {
  	glBegin(GL_TRIANGLE_STRIP);

	for ( zf = -z,j=0; zf <= z;j++, zf+=step )
	{
	    vec[0][0]=(xf+step);
	    vec[0][1]=p[i+1][j];
	    vec[0][2]=zf;
	    vec[1][0]=xf;
	    vec[1][1]=p[i][j];
	    vec[1][2]=zf;
	    vec[2][0]=xf;
	    vec[2][1]= p[i][j+1];
	    vec[2][2]=zf+step;
	   
	    computeNormal(vec,normal);	
	     
	    glNormal3fv(normal);
	    glVertex3f(u+F*xf,w+p[i][j]+ y/2, v+F*zf);
	    glNormal3fv(normal);
	    glVertex3f(u+F*(xf+step),w+p[i+1][j]+  y/2, v+F*zf);
        
	}
	
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	for( zf = -z,j=0; zf <= z;j++, zf+=step )
	{
	    vec[1][0]=(xf+step);
	    vec[1][1]=p[i+1][j];
	    vec[1][2]=zf;
	    vec[0][0]=xf;
	    vec[0][1]=p[i][j];
	    vec[0][2]=zf;
	    vec[2][0]=xf;
	    vec[2][1]= p[i][j+1];
	    vec[2][2]=zf+step;
	    
	    computeNormal(vec,normal);	
    	
	    glNormal3fv(normal);
	
	    glVertex3f(u+F*xf, w+ p[i][j]+(-y/2), v+F*zf);

	    glVertex3f(u+F*(xf+step), w+p[i+1][j]+(-y/2), v+F*zf);
	}
	glEnd();
    }


	glBegin(GL_TRIANGLE_STRIP);
	
	for(xf = -x,j=0; xf <= x;j++, xf+=step)
	{
	    glNormal3f(0.0f,0.0f,1.0f);	 
		
	    glVertex3f(u+F*xf, w+ p [j][int(2*z)]+(-y/2),v+z/2 );

	    glVertex3f(u+F*xf, w+p[j][int(2*z)]+y/2,v+z/2);
			
	}

	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	
	for(xf = -x,j=0; xf <= x;j++, xf+=step)
	{
	    glNormal3f(0.0f,0.0f,-1.0f);	 

	    glVertex3f(u+F*xf, w+p[j][0]+(-y/2),-z/2+v );

	    glVertex3f(u+F*xf, w+p[j][0]+y/2,-z/2+v);
        
	}

	glEnd();
	

	glBegin(GL_TRIANGLE_STRIP);
	for(zf = -z,j=0; zf <= z;j++, zf+=step)
	{
	    glNormal3f(-1.0f,0.0f,0.0f);	
	
	    glVertex3f(-x/2+u,p[0][j]+(-y/2)+w, F*zf+v );

	    glVertex3f(-x/2+u, p[0][j]+(y/2)+w,F*zf+v);
			
	}

	glEnd();	

	glBegin(GL_TRIANGLE_STRIP);
	
	for(zf = -z,j=0; zf <= z;j++, zf+=step)
	{
	    glNormal3f(1.0f,0.0f,0.0f);	
	
	    glVertex3f(u+x/2,w+p[int(2*x)][j]+(-y/2), v+F*zf );
	
	    glVertex3f(u+x/2, w+p[int(2*x)][j]+y/2,v+F*zf);
       
	}

	glEnd();
	glFlush();
        glPopMatrix();
}


void GLObject::drawTexturedQuad( float x, float y )
{
    loadTexture( mImageDir("freecell.bmp") );
   
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   				
    glEnable( GL_LIGHT0 );						
    glEnable( GL_LIGHTING );						
    glEnable( GL_COLOR_MATERIAL ); 
    glFrontFace( GL_CW );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); 
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_COLOR_MATERIAL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glBegin ( GL_QUADS ) ;

	glNormal3f(0.0f,0.0f,1.0f);

	glTexCoord2f( 0.0, 0.0 ); 
	glVertex3f ( -1*x, y, 0 ) ; 

	glTexCoord2f( 1.0, 0.0 ); 
	glVertex3f ( x, y, 0 );

	glTexCoord2f( 1.0, 1.0 ); 
	glVertex3f ( x, -1*y, 0 ) ; 
    	
	glTexCoord2f( 0.0, 1.0 ); 
	glVertex3f ( -1*x, -1*y, 0 ) ; 

    glEnd() ;

    glFlush();
}


void GLObject::drawTextureEnvironmentQuad( float x, float y )
{
    loadTexture( mImageDir("freecell.bmp") );
   
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   				
    glEnable( GL_LIGHT0 );						
    glEnable( GL_LIGHTING );						
    glEnable( GL_COLOR_MATERIAL ); 
    glFrontFace( GL_CW );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); 
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_COLOR_MATERIAL );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    /*glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

    GLfloat fColor[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND );
    glTexEnvfv( GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, fColor );*/

   // glColor3ub( 0, 0, 255 );
    glBegin ( GL_QUADS ) ;

	glNormal3f(0.0f,0.0f,1.0f);

	glTexCoord2f( 0.0, 0.0 ); 
	glVertex3f ( -1*x, y, 0 ) ; 

	glTexCoord2f( 1.0, 0.0 ); 
	glVertex3f ( x, y, 0 );

	glTexCoord2f( 1.0, 1.0 ); 
	glVertex3f ( x, -1*y, 0 ) ; 
    	
	glTexCoord2f( 0.0, 1.0 ); 
	glVertex3f ( -1*x, -1*y, 0 ) ; 

    glEnd() ;

    glFlush();
}


void GLObject::drawMultiTexturedQuad( float x, float y )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   				
    glEnable( GL_LIGHT0 );						
    glEnable( GL_LIGHTING );						
    glEnable( GL_COLOR_MATERIAL ); 
   /* glFrontFace( GL_CW );
    glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); */
    glEnable( GL_TEXTURE_2D );
    
    if ( !m_isloaded )
    {
	glGenTextures( 2, m_texids );
	m_isloaded = true;
	loadTextures( mImageDir("freecell.bmp"), 0 );
	loadTextures( mImageDir("test.bmp"), 1 );
    }

    glBindTexture( GL_TEXTURE_2D, m_texids[0] );

    glBegin ( GL_QUADS ) ;

	glNormal3f(0.0f,0.0f,1.0f);

	glTexCoord2f( 0.0, 0.0 ); 
	glVertex3f ( -1*x, y, -5 ) ; 

	glTexCoord2f( 1.0, 0.0 ); 
	glVertex3f ( x, y, -5 );

	glTexCoord2f( 1.0, 1.0 ); 
	glVertex3f ( x, -1*y, -5 ) ; 
    	
	glTexCoord2f( 0.0, 1.0 ); 
	glVertex3f ( -1*x, -1*y, -5 ) ; 

    glEnd() ;

    glBindTexture( GL_TEXTURE_2D, m_texids[1] );

    glBegin ( GL_QUADS ) ;

	glNormal3f(0.0f,0.0f,1.0f);

	glTexCoord2f( 0.0, 0.0 ); 
	glVertex3f ( -1*x, y, 5 ) ; 

	glTexCoord2f( 1.0, 0.0 ); 
	glVertex3f ( x, y, 5 );

	glTexCoord2f( 1.0, 1.0 ); 
	glVertex3f ( x, -1*y, 5 ) ; 
    	
	glTexCoord2f( 0.0, 1.0 ); 
	glVertex3f ( -1*x, -1*y, 5 ) ; 

    glEnd() ;

    glFlush();
}

void GLObject::drawTeapot( float rad, bool filled )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   				
    glEnable( GL_LIGHT0 );						
    glEnable( GL_LIGHTING );						
    glEnable( GL_COLOR_MATERIAL ); 

    drawSimpleTeapot( rad, filled );

    glFlush();
     
}


void GLObject::drawSimpleTeapot( float rad, bool filled )
{
    static int patchdata[][16] =
    {
	/* rim */
      {102, 103, 104, 105, 4, 5, 6, 7, 8, 9, 10, 11,
	12, 13, 14, 15},
	/* body */
      {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
	24, 25, 26, 27},
      {24, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35, 36,
	37, 38, 39, 40},
	/* lid */
      {96, 96, 96, 96, 97, 98, 99, 100, 101, 101, 101,
	101, 0, 1, 2, 3,},
      {0, 1, 2, 3, 106, 107, 108, 109, 110, 111, 112,
	113, 114, 115, 116, 117},
	/* bottom */
      {118, 118, 118, 118, 124, 122, 119, 121, 123, 126,
	125, 120, 40, 39, 38, 37},
	/* handle */
      {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
	53, 54, 55, 56},
      {53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
	28, 65, 66, 67},
	/* spout */
      {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	80, 81, 82, 83},
      {80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
	92, 93, 94, 95}
    };
   

    static float cpdata[][3] =
    {
	{0.2, 0, 2.7}, {0.2, -0.112, 2.7}, {0.112, -0.2, 2.7}, {0,
	-0.2, 2.7}, {1.3375, 0, 2.53125}, {1.3375, -0.749, 2.53125},
	{0.749, -1.3375, 2.53125}, {0, -1.3375, 2.53125}, {1.4375,
	0, 2.53125}, {1.4375, -0.805, 2.53125}, {0.805, -1.4375,
	2.53125}, {0, -1.4375, 2.53125}, {1.5, 0, 2.4}, {1.5, -0.84,
	2.4}, {0.84, -1.5, 2.4}, {0, -1.5, 2.4}, {1.75, 0, 1.875},
	{1.75, -0.98, 1.875}, {0.98, -1.75, 1.875}, {0, -1.75,
	1.875}, {2, 0, 1.35}, {2, -1.12, 1.35}, {1.12, -2, 1.35},
	{0, -2, 1.35}, {2, 0, 0.9}, {2, -1.12, 0.9}, {1.12, -2,
	0.9}, {0, -2, 0.9}, {-2, 0, 0.9}, {2, 0, 0.45}, {2, -1.12,
	0.45}, {1.12, -2, 0.45}, {0, -2, 0.45}, {1.5, 0, 0.225},
	{1.5, -0.84, 0.225}, {0.84, -1.5, 0.225}, {0, -1.5, 0.225},
	{1.5, 0, 0.15}, {1.5, -0.84, 0.15}, {0.84, -1.5, 0.15}, {0,
	-1.5, 0.15}, {-1.6, 0, 2.025}, {-1.6, -0.3, 2.025}, {-1.5,
	-0.3, 2.25}, {-1.5, 0, 2.25}, {-2.3, 0, 2.025}, {-2.3, -0.3,
	2.025}, {-2.5, -0.3, 2.25}, {-2.5, 0, 2.25}, {-2.7, 0,
	2.025}, {-2.7, -0.3, 2.025}, {-3, -0.3, 2.25}, {-3, 0,
	2.25}, {-2.7, 0, 1.8}, {-2.7, -0.3, 1.8}, {-3, -0.3, 1.8},
	{-3, 0, 1.8}, {-2.7, 0, 1.575}, {-2.7, -0.3, 1.575}, {-3,
	-0.3, 1.35}, {-3, 0, 1.35}, {-2.5, 0, 1.125}, {-2.5, -0.3,
	1.125}, {-2.65, -0.3, 0.9375}, {-2.65, 0, 0.9375}, {-2,
	-0.3, 0.9}, {-1.9, -0.3, 0.6}, {-1.9, 0, 0.6}, {1.7, 0,
	1.425}, {1.7, -0.66, 1.425}, {1.7, -0.66, 0.6}, {1.7, 0,
	0.6}, {2.6, 0, 1.425}, {2.6, -0.66, 1.425}, {3.1, -0.66,
	0.825}, {3.1, 0, 0.825}, {2.3, 0, 2.1}, {2.3, -0.25, 2.1},
	{2.4, -0.25, 2.025}, {2.4, 0, 2.025}, {2.7, 0, 2.4}, {2.7,
	-0.25, 2.4}, {3.3, -0.25, 2.4}, {3.3, 0, 2.4}, {2.8, 0,
	2.475}, {2.8, -0.25, 2.475}, {3.525, -0.25, 2.49375},
	{3.525, 0, 2.49375}, {2.9, 0, 2.475}, {2.9, -0.15, 2.475},
	{3.45, -0.15, 2.5125}, {3.45, 0, 2.5125}, {2.8, 0, 2.4},
	{2.8, -0.15, 2.4}, {3.2, -0.15, 2.4}, {3.2, 0, 2.4}, {0, 0,
	3.15}, {0.8, 0, 3.15}, {0.8, -0.45, 3.15}, {0.45, -0.8,
	3.15}, {0, -0.8, 3.15}, {0, 0, 2.85}, {1.4, 0, 2.4}, {1.4,
	-0.784, 2.4}, {0.784, -1.4, 2.4}, {0, -1.4, 2.4}, {0.4, 0,
	2.55}, {0.4, -0.224, 2.55}, {0.224, -0.4, 2.55}, {0, -0.4,
	2.55}, {1.3, 0, 2.55}, {1.3, -0.728, 2.55}, {0.728, -1.3,
	2.55}, {0, -1.3, 2.55}, {1.3, 0, 2.4}, {1.3, -0.728, 2.4},
	{0.728, -1.3, 2.4}, {0, -1.3, 2.4}, {0, 0, 0}, {1.425,
	-0.798, 0}, {1.5, 0, 0.075}, {1.425, 0, 0}, {0.798, -1.425,
	0}, {0, -1.5, 0.075}, {0, -1.425, 0}, {1.5, -0.84, 0.075},
	{0.84, -1.5, 0.075}
    };

    static float tex[2][2][2] =
    {
      { {0, 0},
	{1, 0}},
      { {0, 1},
	{1, 1}}
    };


GLint grid = 10;
GLdouble scale = rad;
GLenum type = filled ? GL_FILL : GL_LINE;

float p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
  long i, j, k, l;

  glPushAttrib(GL_ENABLE_BIT | GL_EVAL_BIT);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);
  glEnable(GL_MAP2_VERTEX_3);
  glEnable(GL_MAP2_TEXTURE_COORD_2);
  glPushMatrix();
  glRotatef(270.0, 1.0, 0.0, 0.0);
  glScalef(0.5 * scale, 0.5 * scale, 0.5 * scale);
  glTranslatef(0.0, 0.0, -1.5);
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 4; j++) {
      for (k = 0; k < 4; k++) {
        for (l = 0; l < 3; l++) {
          p[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
          q[j][k][l] = cpdata[patchdata[i][j * 4 + (3 - k)]][l];
          if (l == 1)
            q[j][k][l] *= -1.0;
          if (i < 6) {
            r[j][k][l] =
              cpdata[patchdata[i][j * 4 + (3 - k)]][l];
            if (l == 0)
              r[j][k][l] *= -1.0;
            s[j][k][l] = cpdata[patchdata[i][j * 4 + k]][l];
            if (l == 0)
              s[j][k][l] *= -1.0;
            if (l == 1)
              s[j][k][l] *= -1.0;
          }
        }
      }
    }
    glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2,
      &tex[0][0][0]);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &p[0][0][0]);
    glMapGrid2f(grid, 0.0, 1.0, grid, 0.0, 1.0);
    glEvalMesh2(type, 0, grid, 0, grid);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
      &q[0][0][0]);
    glEvalMesh2(type, 0, grid, 0, grid);
    if (i < 6) {
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &r[0][0][0]);
      glEvalMesh2(type, 0, grid, 0, grid);
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4,
        &s[0][0][0]);
      glEvalMesh2(type, 0, grid, 0, grid);
    }
  }

  glPopMatrix();
  glPopAttrib();
}



void GLObject::loadModel( const char* fnm )
{
    if ( m_isloaded )
	return;

    m_isloaded = true;

    int i = 0, j = 0, k = 0, l = 0;
    char ch = 0;
	
    FILE *fp = fopen( mModelDir("foot.obj"), "rt" );

    while ( !feof(fp) )
    {
	ch = fgetc(fp);
	switch ( ch )
	{
	    case 'v':
		ch = fgetc( fp );
		switch ( ch )
		{
		    case ' ':
			fscanf( fp, "%f %f %f", &model_vertices[i][0], &model_vertices[i][1], &model_vertices[i][2] );
			i++;
			break;
		    case 't':
			fscanf( fp, "%f %f", &model_texcoords[j][0], &model_texcoords[j][1] );
			j++;
			break;
		    case 'n':
			fscanf( fp, "%f %f %f", &model_normals[k][0], &model_normals[k][1], &model_normals[k][2] );	
			k++;
			break;
		}
		break;
	    
	    case 'f':				
		unsigned int v1, v2, v3, vt1, vt2, vt3;
		fscanf( fp, "%u/%u %u/%u %u/%u", &v1, &vt1, &v2, &vt2, &v3, &vt3 );
		model_indices[l++] = v1 - 1;
		model_indices[l++] = v2 - 1;
		model_indices[l++] = v3 - 1;
		break;
	    
	    default:		
		break;
	}
    }
    
    fcloseall();
    computeVertexNormals();
}


void GLObject::computeVertexNormals()
{
    unsigned int nrshared = 0;  
    float vec[3][3];  
    float avg_norms[3];	

    for ( int idx=0; idx<12612-2; idx++ )
    {
	vec[0][0] = model_vertices[model_indices[idx]][0];
	vec[0][1] = model_vertices[model_indices[idx]][1];
	vec[0][2] = model_vertices[model_indices[idx]][2]; 
	vec[1][0] = model_vertices[model_indices[idx+1]][0];
	vec[1][1] = model_vertices[model_indices[idx+1]][1];
	vec[1][2] = model_vertices[model_indices[idx+1]][2]; 
	vec[2][0] = model_vertices[model_indices[idx+2]][0];
	vec[2][1] = model_vertices[model_indices[idx+2]][1];
	vec[2][2] = model_vertices[model_indices[idx+2]][2];

	computeNormal( vec, model_normals[idx] );	
    }
    
    for( int i=0; i<2154; i++ )
    {
	for( int j=0; j<12612; j++ )
	{
	    if( model_indices[j] == i )
	    {
		avg_norms[0] += model_normals[j][0];
		avg_norms[1] += model_normals[j][1];
		avg_norms[2] += model_normals[j][2];
		nrshared++;
	    }
	}

	avg_norms[0] /= nrshared;
	avg_norms[1] /= nrshared;
	avg_norms[2] /= nrshared;
	
	normalize( avg_norms );

	model_normals[i][0] = avg_norms[0];
	model_normals[i][1] = avg_norms[1];
	model_normals[i][2] = avg_norms[2];
	nrshared = 0;
    }
}


void GLObject::drawModel()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    loadModel( "foot.obj" );
    //glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE);
    glEnable( GL_LIGHTING );
    for ( int idx=0; idx<12612-3; idx+=3 )
    {
	glBegin (GL_TRIANGLES ) ;
	    glNormal3fv( model_normals[model_indices[idx]] );   glVertex3fv( model_vertices[model_indices[idx]] ) ;
	    glNormal3fv( model_normals[model_indices[idx+1]] ); glVertex3fv( model_vertices[model_indices[idx+1]] ) ;
	    glNormal3fv( model_normals[model_indices[idx+2]] ); glVertex3fv( model_vertices[model_indices[idx+2]] ) ;
	glEnd( ) ;
    }
    glDisable( GL_LIGHTING );
    glFlush();
}


void GLObject::drawModelVA()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    loadModel( "foot.obj" );
    glEnable( GL_LIGHTING );
    
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, model_vertices );
    glEnableClientState( GL_NORMAL_ARRAY );
    glNormalPointer( GL_FLOAT, 0, model_normals );
    glDrawElements( GL_TRIANGLES, 12612, GL_UNSIGNED_INT, model_indices );

    glDisable( GL_LIGHTING );
    glFlush();
}


void GLObject::normalize( float vector[3] )
{
    float length = (float)sqrt((vector[0]*vector[0]) + 
					    (vector[1]*vector[1]) +
					    (vector[2]*vector[2]));
    if( length == 0.0f )
	length = 1.0f;

    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}


// Points p1, p2, & p3 specified in counter clock-wise order
void GLObject::computeNormal( float v[3][3], float out[3] )
{
    float v1[3],v2[3];
    const int x = 0;
    const int y = 1;
    const int z = 2;

    // Calculate two vectors from the three points
    v1[x] = v[0][x] - v[1][x];
    v1[y] = v[0][y] - v[1][y];
    v1[z] = v[0][z] - v[1][z];

    v2[x] = v[1][x] - v[2][x];
    v2[y] = v[1][y] - v[2][y];
    v2[z] = v[1][z] - v[2][z];

    // Take the cross product of the two vectors to get
    // the normal vector which will be stored in out
    out[x] = v1[y]*v2[z] - v1[z]*v2[y];
    out[y] = v1[z]*v2[x] - v1[x]*v2[z];
    out[z] = v1[x]*v2[y] - v1[y]*v2[x];

    // Normalize the vector (shorten length to one)
    normalize( out );
}


unsigned char* GLObject::loadImage( const char* fnm, int& bmw, int& bmh )
{
    unsigned char* buffer = 0;
    if ( !buffer )
    {
	HBITMAP hBitmap = (HBITMAP) LoadImage( 0, fnm, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	if ( !hBitmap )
	    return 0;

	BITMAP bm;
	GetObject( hBitmap , sizeof(bm) , &bm );
	bmw = bm.bmWidth;
	bmh = bm.bmHeight;
	const int bufsz = bmw * bmh * 4;
	buffer = new unsigned char[ bufsz ];
	GetBitmapBits( hBitmap, bufsz, (LPVOID)buffer );
    }

    bool testdata = false;
    if ( testdata )
    {
	int ci = 0;
	for ( int i = 0; i<bmh; i++ ) 
	{   
	    for ( int j = 0; j<bmw; j++ ) 
	    {
		unsigned char c =  (i+1)*20;
		buffer[ ci+0 ] = (GLubyte) c;
		buffer[ ci+1 ] = (GLubyte) c;
		buffer[ ci+2 ] = (GLubyte) 255;
		buffer[ ci+3 ] = (GLubyte) 255;
		ci += 4;
	  }
       }
    }
	
    return buffer;
}


void GLObject::loadTexture( const char* fnm )
{
    if ( m_isloaded )
	return;

    m_isloaded = true;

    int bmwidth, bmheight;
    unsigned char* imagebuffer = loadImage( fnm, bmwidth, bmheight );
        
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, bmwidth, bmheight, 0,
			    GL_BGRA_EXT, GL_UNSIGNED_BYTE, imagebuffer );
	//gluBuild2DMipmaps( GL_TEXTURE_2D, 4, bmwidth, bmheight, GL_BGRA_EXT, GL_UNSIGNED_BYTE,  imagebuffer );
    free( imagebuffer );
}


void GLObject::loadTextures( const char* fnm, unsigned int nr )
{
    int bmwidth, bmheight;
    unsigned char* imagebuffer = loadImage( fnm, bmwidth, bmheight );
    
    glBindTexture(GL_TEXTURE_2D, m_texids[nr] );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, bmwidth, bmheight, 0,
			    GL_BGRA_EXT, GL_UNSIGNED_BYTE, imagebuffer );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    free( imagebuffer );
}


const char* GLObject::readShaderFile( const char* fnm )
{
    std::ifstream& ifstrm = *new std::ifstream( fnm, std::ios::binary | std::ios::ate );
    ifstrm.seekg( 0, std::ios::end );
    const int filesz = ifstrm.tellg();
    ifstrm.seekg( std::ios::beg );
    char* buf = new char[filesz+1];
    ifstrm.read( buf, filesz ) ; buf[filesz] = '\0';
    return buf;
}



//void  GLObject::drawShaderEarth(float rad, float u, float v, float w)
//{
//	/*static const char* earth_vertxsrc[] =
//	{
//		"varying vec3 normal;\n"
//		"void main()\n"
//		"{\n"
//		" normal = normalize(gl_NormalMatrix * gl_Normal);\n"
//		" gl_Position = ftransform();\n"
//		"}\n"
//	};*/
//
//
//	static const char* earth_vertxsrc[] =
//	{
//		"varying vec4 vertexpos;\n"
//		"varying vec3 normal;\n"
//		"void main()\n"
//		"{\n"
//		" vertexpos = gl_Vertex;\n"
//		" gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
//		" normal = normalize(gl_NormalMatrix * gl_Normal);\n"
//		" gl_Position = ftransform();\n"
//		"}\n"
//	};
//
//	/*static const char* earth_vertxsrc[] =
//	{ 
//		"varying vec4 vertexpos;\n"
//		"varying vec3 normal;\n"
//		"void main(void)\n"
//		"{\n"
//		"	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
//		"\n"
//		"	vertexpos = gl_Vertex;\n"
//		"	gl_Position = ftransform();\n"
//		"	normal = gl_Normal;\n"
//		"\n"
//		"	vec3 fragNormal = normalize(gl_NormalMatrix * normal);\n"
//		"\n"
//		"	vec4 diffuse = vec4(0.0,0.0,0.0,0.0);\n"
//		"	vec4 ambient = vec4(0.0,0.0,0.0,0.0);\n"
//		"	vec4 specular = vec4(0.0,0.0,0.0,0.0);\n"
//		"	vec4 specularlight = vec4(0.2,0.2,0.2,1.0);\n"
//		"\n"
//		"\n"
//		"	for (int light = 0; light<1; light++)\n"
//		"	{\n"
//		"		vec3 lightDir = normalize(vec3(gl_LightSource[light].position));\n"
//		"		float NdotL = abs(dot(fragNormal, lightDir));\n"
//		"\n"
//		"		diffuse += gl_LightSource[light].diffuse * NdotL;\n"
//		"		ambient += gl_LightSource[light].ambient;\n"
//		"		float pf = 0.0;\n"
//		"		if (NdotL != 0.0)\n"
//		"		{\n"
//		"			float NdotH = abs(dot(fragNormal, vec3(gl_LightSource[light].halfVector)));\n"
//		"			if (NdotH != 0.0 || gl_FrontMaterial.shininess != 0.0)\n"
//		"				pf = pow(NdotH, gl_FrontMaterial.shininess);\n"
//		"		}\n"
//		"		specular += gl_LightSource[light].specular * pf;\n"
//		"	}\n"
//		"\n"
//		"	gl_FrontColor = gl_FrontLightModelProduct.sceneColor +\n"
//		"		ambient  * gl_FrontMaterial.ambient +\n"
//		"		diffuse  * gl_FrontMaterial.diffuse +\n"
//		"		specular * gl_FrontMaterial.specular;\n"
//		"}\n"
//
//	};*/
//
//	/*static const char* earth_fragsrc[] =
//	{
//		"varying vec3 normal;\n"
//		"void main()\n"
//		"{\n"
//		" float intensity = dot(vec3(gl_LightSource[0].position),normal);\n"
//		" vec4 color = vec4(1.0,0.0,0.0,1.0) * intensity;\n"
//		" gl_FragColor = color;\n"
//		"}\n"
//	};*/
//
//
//	static const char* earth_fragsrc[] =
//	{
//		"varying vec4 vertexpos;\n"
//		"uniform sampler2D texture0;\n"
//		"uniform vec2 texsize0;\n"
//		"varying vec3 normal;\n"
//		"void main()\n"
//		"{\n"
//		" float intensity = dot(vec3(gl_LightSource[0].position),normal);\n"
//		" vec4 color = vec4(1.0,0.0,0.0,1.0) * intensity;\n"
//		" gl_FragColor = texture2D(texture0, gl_TexCoord[0].st);\n"
//		"}\n"
//	};
//
//
//	/*static const char* earth_fragsrc[] =
//	{
//		"varying vec4 vertexpos;\n"
//		"uniform sampler2D texture0;\n"
//		"uniform vec2 texsize0;\n"
//		"varying vec3 normal;\n"
//		"void main(void)\n"
//		"{\n"
//		"	gl_FragColor = texture2D(texture0, gl_TexCoord[0].st);\n"
//			"gl_FragColor.a *= gl_FrontMaterial.diffuse.a;\n"
//			"gl_FragColor.rgb *= gl_Color.rgb;\n"
//		"}\n"
//	};*/
//
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glEnable(GL_LIGHTING);
//	glEnable(GL_COLOR_MATERIAL);
//
//	GLuint shader_program = glCreateProgram();
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//
//	glShaderSource(vs, 1, earth_vertxsrc, NULL);
//	glShaderSource(fs, 1, earth_fragsrc, NULL);
//
//	glCompileShader(vs);
//	GLint iscompiled = 0;
//	glGetShaderiv(vs, GL_COMPILE_STATUS, &iscompiled);
//	if (iscompiled == GL_FALSE)
//	{
//		GLint maxLength = 0;
//		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);
//
//		GLchar* infoLog;
//		glGetShaderInfoLog(vs, maxLength, &maxLength, &infoLog[0]);
//		glDeleteShader(vs);
//		return;
//	}
//
//	glCompileShader(fs);
//	glGetShaderiv(fs, GL_COMPILE_STATUS, &iscompiled);
//	if (iscompiled == GL_FALSE)
//	{
//		GLint maxLength = 0;
//		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);
//
//		GLchar* infoLog;
//		glGetShaderInfoLog(fs, maxLength, &maxLength, &infoLog[0]);
//
//		glDeleteShader(fs);
//		return;
//	}
//
//	glAttachShader(shader_program, vs);
//	glAttachShader(shader_program, fs);
//
//	glLinkProgram(shader_program);
//	glUseProgram(shader_program);
//
//	drawSimpleEarth(rad, u, v, w);
//
//	glDetachShader(shader_program, vs);
//	glDetachShader(shader_program, fs);
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//	glUseProgramObjectARB(0);
//	glUseProgram(0);
//}