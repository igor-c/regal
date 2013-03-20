/*
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS"
 * AND WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF
 * THIRD PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE
 * POSSESSION, USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*  checker.c
 *  This program texture maps a checkerboard image onto
 *  two rectangles.
 *
 *  If running this program on OpenGL 1.0, texture objects are
 *  not used.
 */

#include <GL/Regal.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/RegalGLUT.h>
#endif

#include <GL/RegalGLU.h>

#include <stdlib.h>
#include <stdio.h>

/******************************************************************/

/*
#define USE_VERSION_1_1 0
*/

#ifndef USE_VERSION_1_1
#define USE_VERSION_1_1 1
#endif

/* 0 through 7 work on Mac OSX with and without Regal emulation */
/* 0 through 3 work on Nvidia Win7 without Regal emulation      */
/* 0 through 7 work on Nvidia Win7 with Regal emulation         */

/*
#define USE_UNIT (GL_TEXTURE0+8)
*/

/******************************************************************/

#if USE_VERSION_1_1
static GLuint texName;
#endif

/*	Create checkerboard texture	*/
#define	checkImageWidth 64
#define	checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

void makeCheckImage(void)
{
   int i, j, c;

   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

void init(void)
{
   /* Report the number of available texture units */

   GLint textureUnits,vertexUnits,fragmentUnits,combinedUnits;
   GLint vertexAttribs;

   glGetIntegerv(GL_MAX_TEXTURE_UNITS,               &textureUnits);  
   glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,         &fragmentUnits);
   glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,  &vertexUnits);
   glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,&combinedUnits);

   printf("%d texture units, %d fragment, %d vertex and %d combined texture units.\n",textureUnits,fragmentUnits,vertexUnits,combinedUnits);

   glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &vertexAttribs);

   printf("%u vertex attributes.\n",vertexAttribs);

   /* Initialize OpenGL */

   glClearColor (0.0, 1.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

#ifdef USE_UNIT
   glActiveTexture(USE_UNIT);
#endif

   makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#if USE_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
#endif

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#if USE_VERSION_1_1
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#else
   glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#endif
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
#if USE_VERSION_1_1
   glBindTexture(GL_TEXTURE_2D, texName);
#endif

   glBegin(GL_QUADS);

#ifdef USE_UNIT
   glMultiTexCoord2f(USE_UNIT, 0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
   glMultiTexCoord2f(USE_UNIT, 0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
   glMultiTexCoord2f(USE_UNIT, 1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
   glMultiTexCoord2f(USE_UNIT, 1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

   glMultiTexCoord2f(USE_UNIT, 0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
   glMultiTexCoord2f(USE_UNIT, 0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
   glMultiTexCoord2f(USE_UNIT, 1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
   glMultiTexCoord2f(USE_UNIT, 1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
#else
   glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

   glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
   glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
#endif
   glEnd();
   glFlush();
   glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -3.6);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(250, 250);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
