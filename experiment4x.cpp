#include <cstdlib>
#include <cstdio>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <iostream>

GLuint texture[1];   // hold texture
double angle = 15;   // angle of rotation
typedef struct
 {
 int X;      // texture coordinates
 int Y;
 int Z;
 double U;    // texture coordinate of current vertex
 double V;
 }VERTICES;

const double PI = 3.1415926535897;
const double space = 0.5;
const int VertexCount = int((90 / space) * (360 / space) * 4);   // total amount of vertices
VERTICES *VERTEX=new VERTICES[VertexCount];								// vertices going to use
GLuint LoadTextureRAW( const char *filename );

static int m=0,M=0,v=0,V=0,E=0,e=0,r=0,R=0,j=0,J=0,s=0,S=0,U=0,u=0,n=0,N=0,X=0,z=0,B=0,b=0,c=0,k=1;
static GLint axis=2;
#define TEXTID 5
int f=1;

GLfloat diffuseMaterial[4]={0.5,0.5,0.5,1.0};

void DisplaySphere(double R, GLuint texture)
{
 int b;											// This variable will control which vertex we are currently working with
 glScalef(0.0125 * R, 0.0125 * R, 0.0125 * R);  // have chosen to scale it here to 0.0125 times its original size, and then increase it by R as the original sphere is rather large
 glRotatef(90, 1, 0, 0);                        // rotating it

 glBindTexture(GL_TEXTURE_2D, texture);     // bind the texure

 glBegin(GL_TRIANGLE_STRIP);				//  to begin drawing the sphere itself

 // looping through each vertex
 for ( b = 0; b <= VertexCount; b++)
 {
// Assigning the texture coordinates of the current vertex, And the drawing the specified vertex with the Z coordinate inverted. Because the creation code only draws half a sphere,
 glTexCoord2f(VERTEX[b].U, VERTEX[b].V);
 glVertex3f(VERTEX[b].X, VERTEX[b].Y, -VERTEX[b].Z);   // this loop again for the other half below
 }
// invert the V(y) texture coordinate.

  for ( b = 0; b <= VertexCount; b++)
 {
  glTexCoord2f(VERTEX[b].U, -VERTEX[b].V);
  glVertex3f(VERTEX[b].X, VERTEX[b].Y, VERTEX[b].Z);
  }
   glEnd();   // Then end the shape
 }
//  input R as the number of subdivisions, H as the translation on the horizontal axis,
// K as the translation on the vertical axis, and Z as the translation on the Z axis
void CreateSphere(double R, double H, double K, double Z)
{
 int n = 0;  // Set n to 0 to start off with the first vertex
 double a;  //  While a and b are used to control our loops.
 double b;
 // Assign  b loop to go through 90 degrees in intervals of the variable space
 for( b = 0; b <= 90 - space; b+=space)
 {
	 // Assign  a loop to go through 360 degrees in intervals of the variable space
      for( a = 0; a <= 360 - space; a+=space)
	 {

 VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
// used (2*b) as the texture is twice as wide as it is high. Hence 2:1. You can remove the (2*) to use a texture with the same width and height, or increase it accordingly
 VERTEX[n].V = (2 * b) / 360;
 VERTEX[n].U = (a) / 360;
 n++;
 VERTEX[n].X = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
 VERTEX[n].V = (2 * (b + space)) / 360;
 VERTEX[n].U = (a) / 360;
 n++;
 VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b) / 180 * PI) - Z;
 VERTEX[n].V = (2 * b) / 360;
 VERTEX[n].U = (a + space) / 360;
 n++;
 VERTEX[n].X = R * sin((a + space) / 180 * PI) * sin((b + space) / 180 * PI) - H;
 VERTEX[n].Y = R * cos((a + space) / 180 * PI) * sin((b + space) / 180 * PI) + K;
 VERTEX[n].Z = R * cos((b + space) / 180 * PI) - Z;
 VERTEX[n].V = (2 * (b + space)) / 360;
 VERTEX[n].U = (a + space) / 360;
 n++;
   }
  }
 }

void init(void)
{
 glEnable(GL_DEPTH_TEST);          // enabling depth testing, texturing and face culling
 glEnable(GL_TEXTURE_2D);          // set the front face for culling to Counter Clock Wise, as triangle strips cull the opposite face to most other shapes.
 glDepthFunc(GL_LEQUAL);
 glCullFace(GL_BACK);
 glFrontFace(GL_CCW);
 glEnable(GL_CULL_FACE);
 texture[0] = LoadTextureRAW( "earth.raw" );   // load our texture to be used. It will be stored in texture[0]
 texture[1] = LoadTextureRAW( "sun.raw" );
 glClearColor(0.0,0.0,0.0,0.0);
glShadeModel(GL_SMOOTH);
GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
GLfloat light_position[]={1.0,1.0,1.0,0.0};
glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseMaterial);
glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
glMaterialf(GL_FRONT,GL_SHININESS,25.0);
//glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glColorMaterial(GL_FRONT,GL_DIFFUSE);
glEnable(GL_COLOR_MATERIAL);
  glPushMatrix();
 glTranslated(0.4,0,0.4);
 glRotated(30,0,1,0);
 CreateSphere(80,0,0,0);
 glPopMatrix();
 }

 void keyboard(unsigned char key,int x,int y)
{
switch(key)
{
case 'q':exit(0);
case 27:exit(0);
		break;
case 'w':k=2;
		break;
case 'n':k=1;
		break;
default:break;
}
}


void DrawTextXY(double x,double y,double z,double scale,const char *s)
{
int i;
glPushMatrix();
glTranslatef(x,y,z);
glScalef(scale,scale,scale);
for (i=0;i < strlen(s);i++)
glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
glPopMatrix();
}

 void display(void)
{
	GLfloat position[]={0.0,2.5,3.5,0.5};
     glClearDepth(1);
     glClearColor(0.0,0.0,0.0,1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glColor3f(245/256.0,222/256.0,179/256.0);
      glTranslatef(0,-3,-10);
     glRotatef(angle,0.3,1,0);
     angle++;
     DisplaySphere(1.8, texture[0]);   // To display the sphere funtion which will set the size of it to 5 and assign the texture specified. it inputs the radius and texture
	glPopMatrix();
//glPushMatrix();
//glRotatef((GLfloat)z,1.0,1.0,1.0);
//glTranslated(2.5,0.0,3);
//DisplaySphere(4,texture[1]); //draw sun
//glPopMatrix();
glPushMatrix();
glLightfv(GL_LIGHT0,GL_POSITION,position);
//glDisable(GL_LIGHTING);
glEnable(GL_LIGHTING);
glTranslated(0,2.5,3);
glColor3f(1.5,0.5,0.0);
glutSolidTorus(0.6,1.6,6,20);
glPopMatrix();
/*glColor3f(1,0,0);
DrawTextXY(-3,6,-10,0.0040," SUMMER SOLSTICE ");
glColor3f(1,0,0);
DrawTextXY(-5.5,2.7,-10,0.0040," / ");
glColor3f(1,0,0);
DrawTextXY(-6,3.2,-10,0.0020," 23 DEGREE TILT ");
DrawTextXY(-1,1,-10,0.0080," <");
DrawTextXY(-0.2,1.25,-10,0.0020,"----------------------");
DrawTextXY(-1,-1,-10,0.0080," <");
DrawTextXY(-0.2,-0.75,-10,0.0020,"----------------------");
DrawTextXY(-3.4,1,-10,0.0020,"--TROPIC OF CANCER");
DrawTextXY(-4,-5,-10,0.0020,"DIRECT SUN RAYS ON TROPIC OF CANCER"); */
	 glutSwapBuffers();

	 glFlush();
 }

void display2(void)
{
	GLfloat position[]={0.0,2.5,3.5,0.5};
     glClearDepth(1);
     glClearColor(0.0,0.0,0.0,1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glColor3f(245/256.0,222/256.0,179/256.0);
      glTranslatef(0,-3,-10);
     glRotatef(angle,0.3,1,0);
     angle++;
     DisplaySphere(1.8, texture[0]);   // To display the sphere funtion which will set the size of it to 5 and assign the texture specified. it inputs the radius and texture
	glPopMatrix();
//glPushMatrix();
//glRotatef((GLfloat)z,1.0,1.0,1.0);
//glTranslated(2.5,0.0,3);
//DisplaySphere(4,texture[1]); //draw sun
//glPopMatrix();
glPushMatrix();
glLightfv(GL_LIGHT0,GL_POSITION,position);
//glDisable(GL_LIGHTING);
glEnable(GL_LIGHTING);
glTranslated(0,2.5,3);
glColor3f(1.5,0.5,0.0);
glutSolidTorus(0.6,1.6,6,20);
glPopMatrix();
glColor3f(1,0,0);
DrawTextXY(6,-5,-10,0.0060," SPRING EQUINOX ");
glColor3f(1,0,0);
DrawTextXY(1.05,-2.1,-10,0.0040," / ");
glColor3f(1,0,0);
DrawTextXY(1.05,-1.5,-10,0.0020," 23 DEGREE TILT ");
DrawTextXY(-0.95,0,-10,0.0080," V");
DrawTextXY(-2.95,0,-10,0.0080," V");
DrawTextXY(1.05,0,-10,0.0080," V");
DrawTextXY(-2.11,1,-10,0.020," |");
DrawTextXY(-4.11,1,-10,0.020," |");
DrawTextXY(-0.11,1,-10,0.020," |");
DrawTextXY(-5,-5,-10,0.0020,"EQUATOR ---------");
DrawTextXY(2.5,0,-10,0.0020,"DIRECT SUN RAYS ON EQUATOR");
DrawTextXY(-11,-1,-10,0.0020,"AUTUMN IN NORTHERN HEMISPHERE");
DrawTextXY(-11,-3,-10,0.0020,"SPRING IN SOUTHERN HEMISPHERE");
	 glutSwapBuffers();

	 glFlush();
 }

void dis()
{
	switch(k)
	{
	case 1: display();
		break;
	case 2:display2();
		break;
	case 4:exit(0);
		break;
	}
}

 void reshape(int w,int h)
{
glViewport(0,0,(GLsizei)w,(GLsizei)h);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,20.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
}
 int main(int argc, char **argv)
{
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
      glutInitWindowSize(1000, 1000);
      glutInitWindowPosition(0, 0);
      glutCreateWindow("OpenGL Earth");
      init();
     // myinit();
      glutFullScreen();
      glutDisplayFunc(dis);
      glutIdleFunc(dis);
      glutKeyboardFunc(keyboard);
      glutReshapeFunc(reshape);
      glutMainLoop();
      return 0;
 }
GLuint LoadTextureRAW( const char *filename )
 {
   GLuint texture;
   int width, height;
   unsigned char *data;
   FILE *file;
   file = fopen( filename, "rb" );
    if ( file == NULL )
	   return 0;
    width = 1024;
    height = 512;
    data = (unsigned char *) malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );
    glGenTextures( 1, &texture );
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data );
   return texture;
   }
