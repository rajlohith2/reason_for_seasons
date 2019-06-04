#include <GL/glew.h>
#include <string.h>
#include <cstdio>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

GLfloat position1[]={0.0,0.0,1.5,1.0};
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
float ex,ey,ez;
float pathvertices[56][3]={{0,4,-10},{0.5,3.986,-10},{1,3.944,-10},{1.5,3.872,-10},{2,3.771,-10},{2.5,3.636,-10},{3,3.464,-10},{3.5,3.248,-10},
{4,2.981,-10},{4.5,2.645,-10},{5,2.211,-10},{5.5,1.598,-10},{5.75,1.142,-10},{5.875,0.8122,-10},{6,0,-10},{5.875,-0.8122,-10},{5.75,-1.142,-10},{5.5,-1.598,-10},{5,-2.211,-10},{4.5,-2.645,-10},{4,-2.981,-10},{3.5,-3.248,-10},
{3,-3.464,-10},{2.5,-3.636,-10},{2,-3.771,-10},{1.5,-3.872,-10},{1,-3.944,-10},{0.5,-3.986,-10},{0,-4,-10},{-0.5,-3.986,-10},{-1,-3.944,-10},{-1.5,-3.872,-10},
{-2,-3.771,-10},{-2.5,-3.636,-10},{-3,-3.464,-10},{-3.5,-3.248,-10},{-4,-2.981,-10},{-4.5,-2.645,-10},{-5,-2.211,-10},{-5.5,-1.598,-10},{-5.75,-1.142,-10},
{-5.875,-0.8122,-10},{-6,0,-10},{-5.875,0.8122,-10},{-5.75,1.142,-10},
{-5.5,1.598,-10},{-5,2.211,-10},{-4.5,2.645,-10},{-4,2.981,-10},{-3.5,3.248,-10},{-3,3.464,-10},{-2.5,3.636,-10},{-2,3.771,-10},{-1.5,3.872,-10}
,{-1,3.944,-10},{-0.5,3.986,-10}};

int result;
GLfloat diffuseMaterial[4]={1,0.5,0,1.0};

/*GLfloat mat_ambient[]={0.7,0.7,1.0};
GLfloat mat_diffuse[]={0.5,0.5,1.0};
GLfloat mat_specular[]={1,1,1,1};
const GLfloat mat_shininess[]={0.0};
GLfloat light_intensity[]={0.7,0.7,0.7,1.0};
GLfloat light_position[]={2.0,6.0,3.0,0.0};*/

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
GLfloat mat_specular[]={1.0,0.6,0,1.0};
GLfloat light_position[]={1.0,0.6,0.0,0.0};
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
 glClearColor(0,0,0,0);
 CreateSphere(80,0,0,0);
 glPopMatrix();
 }

 void DrawTextXY(double x,double y,double z,double scale,const char *s)
{
int i;
glPushMatrix();
glTranslatef(x,y,z);
glScalef(scale,scale,scale);
for (i=0;i < strlen(s);i++)
glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,s[i]);
glPopMatrix();
}

 void display(float ex,float ey,float ez)
{
	GLfloat position[]={0.0,0.0,3.5,0.5};
     glClearDepth(1);
     glClearColor(0/256.0,0/256.0,0/256.0,1.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 int ii;
 	glColor3f(0.7,0.7,0.7);
			 glBegin(GL_LINE_LOOP);
 	for(ii=0;ii<53;ii++)
 	{
			 glLineWidth(3);
 			glVertex3f(pathvertices[ii][0]*1.6,pathvertices[ii][1]*1.6+1,pathvertices[ii][2]);
  	}
  	glEnd();


  glPushMatrix();
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glColor3f(245/256.0,222/256.0,179/256.0);
  //glColor3f(0,0,1);
	 glTranslatef(ex,ey,ez);
     glRotatef(angle,0.3,1,0);
     angle=angle+10;
     DisplaySphere(0.65, texture[0]);
 	glPopMatrix();
glPushMatrix();
glColor3f(1.0,0.5,0.0);
glPushMatrix();
glRotatef((GLfloat)z,1.0,1.0,1.0);
glLightfv(GL_LIGHT0,GL_POSITION,position1);
glDisable(GL_LIGHTING);
glTranslatef(0,1,-10);
glutSolidSphere(1.2,40,16); /*draw sun*/
glPopMatrix();
glPushMatrix();
glLightfv(GL_LIGHT0,GL_POSITION,position1);
glDisable(GL_LIGHTING);
glEnable(GL_LIGHTING);
glColor3f(1,0.6,0.0);
glTranslatef(0,1,-10);
glutSolidTorus(0.4,1.5,10,20);
glPopMatrix();
glDisable(GL_LIGHTING);
glColor3f(0,1,1);
DrawTextXY(3,4,0.0,0.0007," Press f for faster revolution");
glColor3f(0,1,1);
DrawTextXY(3,3.7,0.0,0.0007," Press F for slower revolution");
glColor3f(1,1,1);
DrawTextXY(-1,4.5,0.0,0.0010," SPRING EQUINOX ");
glColor3f(1,1,1);
DrawTextXY(-1,4.3,0.0,0.0010," MARCH 21 ");
glColor3f(0.9,1,1);
DrawTextXY(-1,-1.8,0.0,0.0010," AUTUMN EQUINOX ");
glColor3f(0.9,1,1);
DrawTextXY(-1,-2,0.0,0.0010," SEPTEMBER 23 ");
glColor3f(1,1,1);
DrawTextXY(-6,1,0.0,0.0010," SUMMER SOLSTICE ");
glColor3f(1,1,1);
DrawTextXY(-6,0.8,0.0,0.0010," JUNE 21 ");
glColor3f(0.9,1,1);
DrawTextXY(4.4,1,0.0,0.0010," WINTER SOLSTICE ");
glColor3f(0.9,1,1);
DrawTextXY(4.4,0.8,0.0,0.0010," DECEMBER 22 ");

     glutSwapBuffers();

	 glFlush();
 }

 static int timex=30;

const float DEG2RAD = 3.14159/180.0;


float xForEarth, yForEarth;
int counterForEarth = 0;

 void ellipse()
 {
 	glBegin(GL_POINTS);
       for (int i=360; i < 0; i--)
       {
           float degInRad = i*DEG2RAD; //const float DEG2RAD = 3.14159/180.0;
           glVertex3f(cos(degInRad)*6.0,
               sin(degInRad)*4.0,0.0f);
       }
       glEnd();
       if(counterForEarth>359)
           counterForEarth = 0;//reset to 0 when becomes 360
       else
           counterForEarth++;//this will control the speed. Do counterForEarth += 2 to increase it's speed and vice-versa

       xForEarth = cos(counterForEarth*DEG2RAD)*6.0f;//to change the x co-ordinate
       yForEarth = sin(counterForEarth*DEG2RAD)*4.0f;
       display(xForEarth,yForEarth,-10);

 }

void cover()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glClearColor(55/256,36/256,109/256,0);
glTranslatef(0.0,0.0,-6.0);
glTranslatef(0.0,-1.3,0.0);
glColor3f(1.00,0.0,0.0);
glLoadName(TEXTID);
glColor3f(1,0,0);
DrawTextXY(-4,3.5,0.0,0.0020," BANGALORE INSTITUTE OF TECHNOLOGY ");
glColor3f(0,1,1);
DrawTextXY(-3,3.2,0.0,0.0015," DEPARTMENT OF COMPUTER SCIENCE ");
glColor3f(1.0,0.0,0.7);
DrawTextXY(-4,2.5,0.0,0.0015," MINI PROJECT ON GRAPHICAL IMPLEMENTATION OF ");

glColor3f(0.0,0.0,1.0);
DrawTextXY(-1.75,2,1.0,0.0014,"REASONS FOR SEASONS ");
glColor3f(1.0,1.0,0.0);
DrawTextXY(-3.25,1.5,0.0,0.0014," SUBMITTED BY :- ");
glColor3f(0.0,1.0,1.0);
DrawTextXY(-2.5,1.2,0.0,0.001,"KARTHIK J BHARADWAJ ");
DrawTextXY(-2.5,0.95,0.0,0.001,"LOHITH RAJ S N");
glColor3f(1.0,0.0,0.0);
DrawTextXY(1.009,1.2,0.0,0.001,"1BI16CS061");
DrawTextXY(1.015,0.95,0.0,0.001,"1BI16CS069");
glColor3f(1.0,0.0,0.0);
//DrawTextXY(-1.25,0,0.0,0.001," UNDER THE GUIDENCE OF : ");
//glColor3f(0.0,0.0,1.0);
glColor3f(1.0,0.0,1.0);
DrawTextXY(1.25,-1.25,0.0,0.0015," Press i to move on... ");
glFlush();
glutSwapBuffers();
}

void inst()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glClearColor(52/256,49/256,50/256,1.0);
glTranslatef(0.0,0.0,-6.0);
glTranslatef(0.0,-1.3,0.0);
glColor3f(1.00,0.0,0.0);
glLoadName(TEXTID);
glColor3f(0.9,1,0);
glPointSize(2.0);
DrawTextXY(-4.7,3.5,0.0,0.0020," INSTRUCTIONS ");
glColor3f(100/256.0,191/256.0,180/256.0);
DrawTextXY(-1.25,2.7,0.0,0.0015," 1: r to get the description ");
DrawTextXY(-1.25,2.4,0.0,0.0015," 2: s to view summer slostice ");
DrawTextXY(-1.25,2.1,0.0,0.0015," 3: w to view winter solstice ");
DrawTextXY(-1.25,1.8,0.0,0.0015," 4: p to view spring equinox");
DrawTextXY(-1.25,1.5,0.0,0.0015," 5: a to view autumn equinox");
DrawTextXY(-1.25,1.2,0.0,0.0015," 6: F for faster revolution");
DrawTextXY(-1.25,0.9,0.0,0.0015," 7: f for slower revolution");
glColor3f(1.0,1.0,0);
DrawTextXY(1.25,-1.25,0.0,0.0015," Press d to move on... ");
glFlush();
glutSwapBuffers();
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

void keyboard(unsigned char key,int x,int y)
{
switch(key)
{
case 'q':exit(0);
case 27:exit(0);
		break;
	case 's':
			result=system("./experiment");
			break;
		case 'w':
    result=system("./experiment2x");
			break;
		case 'p':
    result=system("./experiment4x");
			break;
		case 'a':
    result=system("./experiment3x");
			break;
		case 'c':k=1;
			break;
		case 'i':k=2;
			break;
		case 'd':k=3;
			break;
		case 'F':timex+=10;
				break;
		case 'f':timex-=10;
				break;
		case 'R':angle+=20;
				break;
		case 'r':angle-=20;
				break;
default:break;
}
}

void dis()
{
	switch(k)
	{
	case 1: cover();
		break;
	case 2:inst();
		break;
	case 3: ellipse();
		break;
	case 4:exit(0);
		break;
	}
}

 int main(int argc, char **argv)
{
	//	PlaySound("C:\\Users\\KS1\\Desktop\\random\\178243__sclolex__spacemusic.wav",NULL,SND_SYNC);
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
      glutInitWindowSize(1350, 700);
      glutInitWindowPosition(0, 0);
      glutCreateWindow("OpenGL Earth");
      init();
     // myinit();
      //glutFullScreen();
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
