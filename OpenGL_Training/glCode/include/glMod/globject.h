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
 */

#pragma once

#ifndef M_PI
#define M_PI 3.14159
#endif

#undef mExport
#ifdef glMod_EXPORTS
#define mExport  __declspec( dllexport )
#else
#define mExport  __declspec( dllimport )
#endif

#define AREA_SIZE    100            /* size of (square) map */
#define F            0.25           /* world scale of one height map cell */

class mExport GLObject
{
public:
			    GLObject();
			    ~GLObject(){};

	void		    drawPoints(float x1,float y1,float z1,float x2,float y2,float z2);
	void		    drawLines(float x1,float y1,float z1,float x2,float y2,float z2);
	void		    drawFirstBox(float x,float y, float z,float u=0,float v=0,float w=0,bool filled=true);
	void		    drawBoxIndexed(float x, float y, float z);
	void		    drawBoxVA(float x, float y, float z);
	void		    drawVBOBox(float x, float y, float z);
	void		    drawColoTriangle();
	void		    drawMaterialTriangle();
	void		    drawTransparentTriangles();
	void		    drawTexturedQuad(float x,float y);
	void		    drawTextureEnvironmentQuad(float x,float y);
	void		    drawMultiTexturedQuad(float x,float y);
	void		    drawTexturedBox(float x,float y,float z);
	void		    drawTransformedBoxes();
	void		    drawTeapot(float rad, bool filled=true); 
	void		    drawTeapotVS(float rad);
	void		    drawTeapotFS(float rad);
	void		    drawTeapotFS4IntelCards(float rad);
	
	void		    drawShaderBox( float x, float y, float z );
	void		    drawSphere(float rad,float posx=0,float posy=0,float posz=0);
	void		    drawMaterialSphere(float rad,float posx=0,float posy=0,float posz=0);
	void		    drawEarth(float rad,float u=0,float v=0,float w=0);
	void		    drawRealisticEarth(float rad, float u = 0, float v = 0, float w = 0);
 	void		    drawLayers(float x,float y, float z,float u=0,float v=0, float w=0,bool filled=true);
	void		    drawModel();
	void		    drawModelVA();
	void		    drawSurface(bool fill=true);

protected:

       void		    drawSimpleBox(float x,float y,float z);
       void		    drawSimpleEarth(float rad, float u = 0, float v = 0, float w = 0);
       void		    drawShaderEarth(float rad, float u, float v, float w);
       void		    drawSimpleSphere(float rad,float posx,float posy,float posz);
       void		    drawAtmosphere(float rad, float posx, float posy, float posz);
       void		    drawSimpleTeapot(float rad, bool filled=true); 
       void		    loadTexture(const char* fnm);
       void		    loadTextures(const char* fnm, unsigned int textnr);
       unsigned char*	    loadImage(const char* fnm, int& bmw, int& bmh);
       void		    loadModel(const char* fnm);
       void		    normalize(float vector[3]);
       void		    computeNormal(float v[3][3], float out[3]);
       void		    computeVertexNormals();
       const char*	    readShaderFile(const char* fnm);
       void		    initSurface();
       void		    calccolor(float height, float c[3]);

       float		    model_vertices[2154][3];
       float		    model_normals[2154][3];
       float		    model_texcoords[17176][2];
       unsigned		    model_indices[12612];
       unsigned int	    m_texids[2];
       int		    m_nrtextures;
       bool		    m_isloaded;
       bool		    m_is_glew_ok;

       float		    height_field[AREA_SIZE][AREA_SIZE];
       int		    step = 1;
       int		    choice = 1, tMode = 1;
       int		    xi = 0, yi = 0;
       float		    terraincolor[100][100][3];

};




