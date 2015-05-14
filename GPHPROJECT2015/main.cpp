#include <windows.h>
#include <gl\gl.h>
#include <GL\glut.h>
#include<math.h>
#include <stdlib.h>
#include <gl\glut.h>
#include<iostream>
/*Variables*/
float  houseVertices[6][4][3] = { { { 0, 100, -0.5 }, { 0, 0, -0.5 }, { 100, 0, -0.5 }, { 100, 100, -0.5 } },
                                   	  { { 100, 100, -0.5 }, { 100, 0, -0.5 }, { 150, 0, -1.0 }, { 150, 130, -1.0 } } ,
									  { { 0, 100, -0.5 }, { 100, 100, -0.5 }, { 150, 130, -1 }, { 100, 130, -1 } } ,
									  { { 0, 100, -0.5 }, { 0, 0, -0.5 }, { 100, 0, -1 }, { 100, 130, -1 } } ,
									  { { 150, 130, -1 }, { 100, 130, -1 }, { 150, 0, -1}, { 100, 0, -1 } } , 
									  { { 0, 0, -0.5 }, { 100, 0, -0.5 }, { 150, 0, -1 }, {100, 0 , -1} } };
float houseColor[6][3] = { { 0.125 , 9863 , 0.856 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 1, 1, 0 }, {0 , 1 , 1} };

float windows[4][4][3] = { { {10 ,90 ,-0.48}, {30 , 90 , -0.48}, {30 ,70 , -0.48}, {10 ,70 , -0.48} }  ,
                                	{ { 60, 90, -0 }, { 80, 90, 0 }, { 80, 70, 0 }, { 60, 70, 0 } },
									{ { 10, 60, 0 }, { 30, 60, 0 }, { 30, 40, 0 }, { 10, 40, 0 } },
									{ { 60, 60, 0 }, { 80, 60, 0 }, { 80, 40, 0 }, { 60, 40, 0 } } };
float door[4][3] = { { 40, 35, -0.48 }, { 55, 35, -0.48 }, { 55, 0, -0.48 }, { 40, 0, -0.48 } };
const int   A = 1000;  /* length of a side of the monitor window */
const float B = 1000;  /* length of a side of the clipping rectangle */
const float C = 200;  /* length of a side of the square the program draws */
GLfloat pos_x = 0, pos_y = 0,circle1x=-40,circle1y=-200,circle2x=40,circle2y=-200,wheel=15,hieght=30;
GLfloat Cx=0,Cy=0,Cz=0,rightwheelx=0,leftwheelx=0,doorEngle=0,windowAngle=0;
double theta = 0,buffer,cycletheta=0,camerax=100,cameray=100,cameraz=100;
bool flag=0;

/*Prototypes*/
void specialKeys( int key, int x, int y );
void DrawCircle(float cx, float cy, float r, int num_segments);
void KeyBoardFun(unsigned char meg,int x,int y);
void MyMouseFunc(int button, int state, int x, int y);
void myinit(void);
void display( void );
void DrawCycle();
void DrawBuilding();

/*Main Function*/
int main(int argc, char** argv)
{
  glutInit(&argc,argv);
  glutInitWindowSize( A, A );       /* A x A pixel screen window  */
  glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("My Rectangle"); /* window title                   */
  glutDisplayFunc(display);         /* tell OpenGL main loop what     */
  glutSpecialFunc(specialKeys);
  glutKeyboardUpFunc(KeyBoardFun);
  glutMouseFunc(MyMouseFunc);       /*Get Mouse Commands*/
  myinit();/* set attributes*/
  glutMainLoop();                   /* pass control to the main loop  */
return 0;
}

/*The Functions*/
void myinit(void)
{
  glClearColor(0.0, 1.0, 0.5, 0.0); /* gray background */
  glMatrixMode(GL_PROJECTION);      /* In World coordinates: */
  glLoadIdentity();                 /* position the "clipping rectangle" */
  gluOrtho2D( -B/2, B/2, -B/2, B/2);/* at -B/2, its right edge at +B/2, its bottom */
  glMatrixMode(GL_MODELVIEW);       /* edge at -B/2 and its top edge at +B/2 */
}

void display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);     /* clear the window */
  glMatrixMode(GL_MODELVIEW);       /* The following coordinates are expressed */
  glLoadIdentity();  /* in terms of World coordinates */
  //gluLookAt(camerax, 10.0f, 10.0f,  (circle1x+circle2x)/2, (circle1y+circle2y)/2, 0, 0, 1, 0);
  //Draw the cycle
  DrawCycle();
  //Draw building
  DrawBuilding();
}

void KeyBoardFun(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'f':
		 Cx+=5;
		 glutPostRedisplay();
		break;
	case 'b':
		 Cx-=5;
		 glutPostRedisplay();
		break;
	case 'r':
		  rightwheelx+=3;
		  glutPostRedisplay();
		break;
	case 'l':
		 leftwheelx+=3; 
		 glutPostRedisplay();
		break;
    case 'o':
		 if(theta<25)
			theta+=5;
		 glutPostRedisplay();
		break;
    case 'c':
		 if(theta>0)
			theta-=5;
		 glutPostRedisplay();
		break;
	case 'O':
		if(windowAngle<25)
			windowAngle+=5;
		 glutPostRedisplay();
		break;
	case 'C':
		 if(windowAngle>0)
			 windowAngle-=5;
		 glutPostRedisplay();
		break;
	case 27: 
			exit(0); 
			break;
	}
}

void specialKeys( int key, int x, int y ) 
{
    const float step = 10.0;
    if (key == GLUT_KEY_RIGHT)
	{
       camerax+=3;
	   std::cout<<camerax;
	}
    else if (key == GLUT_KEY_LEFT)
        pos_x -= step;
    else if (key == GLUT_KEY_UP)
        pos_y += step;
    else if (key == GLUT_KEY_DOWN)
        pos_y -= step;
    glutPostRedisplay();
}

void DrawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex3f(x + cx, y + cy,1.0);//output vertex 
		//glVertex3f(.5*(x + cx), .5*(y + cy),1.0);
    }
    glEnd();
}

void MyMouseFunc(int button, int state, int x, int y)
{
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		camerax=x;
		cameray=y;
		if (state==GLUT_DOWN) // LEFT-BUTTON DOWN
		{
			 flag=1;
			 glutPostRedisplay();
		}
		else // LEFT-BUTTON UP
		{
		}
		break;
	case GLUT_RIGHT_BUTTON:
		flag=0;
	    glutPostRedisplay();
		break;
	};
}

void DrawCycle()
{
	glPushMatrix();
	 // glTranslatef(.3,.5,-.5);
	  glTranslatef(Cx,Cy,Cz);
	  //glTranslatef(-100,-100,-.5);
	  GLfloat d=1*cycletheta;
	  glRotatef(d,0,1,0.3);
	  //glTranslatef(100,100,+.5);
      glLineWidth(2.5); 
      glColor3f ( 0.0, 0.0, 0.0);
	  //Draw wheels
	  //right
	  glPushMatrix();
	      glTranslatef(circle2x, circle2y, 0);
		  glRotatef(rightwheelx,0,0,1);
		  glTranslatef(-circle2x, -circle2y, 0);
		  DrawCircle(circle2x,circle2y,wheel,100);
	   glPopMatrix();
	   //left
	   glPushMatrix();
	       glTranslatef(circle1x, circle1y, 0);
		   glRotatef(leftwheelx,0,0,1);
		   glTranslatef(-circle1x, -circle1y, 0);
	       DrawCircle(circle1x,circle1y,wheel,100);  
	   glPopMatrix();
	  //Draw lines
      glBegin(GL_LINES);
	     glVertex3f(circle1x, circle1y, 1.0);
	     glVertex3f(circle2x, circle1y, 1);
	     GLfloat uppery=(circle1y<0?hieght+circle1y:circle1y-hieght);
         glVertex3f((circle1x+circle2x)/2,uppery , 1.0);
         glVertex3f((circle1x+circle2x)/2, circle1y, 1.0);
		 glVertex3f(circle1x*.25,uppery , 1.0);
         glVertex3f(-circle1x*.25, uppery, 1.0); 
		 glVertex3f(circle2x, circle2y, 1.0);
         glVertex3f(circle2x, uppery, 1);
		 glVertex3f(circle2x, uppery, 1);
		 glVertex3f(circle2x-10, uppery, 1);
      glEnd();
   glPopMatrix();
   if(flag)
   {
	   cycletheta+=10;
	   //rightwheelx+=3;
	   //leftwheelx+=3;
	   glutPostRedisplay();
   }
}

void DrawBuilding()
{
	glLoadIdentity();
	//Draw the walls of the house
	for (int i = 4; i >=0; i--)
	{
	   glColor3f(houseColor[i][0], houseColor[i][1], houseColor[i][2]);
	   glBegin(GL_POLYGON);
	      for (int j = 0; j < 4; j++)
		  {
			  glVertex3f(houseVertices[i][j][0], houseVertices[i][j][1], houseVertices[i][j][2]);
		  }
	   glEnd();
	}
	//Draw The windows of the house
	glPushMatrix();
	   for (int i = 3; i >= 0; i--)
	   {
		   glColor3f(0,0, 1);
		   glTranslatef(windows[i][0][0], windows[i][0][1], windows[i][0][2]);
		              GLfloat bu=windowAngle*-1;
				      glRotatef(bu,0.0f,1.0f,0.0f);
		   glTranslatef(-windows[i][0][0],-windows[i][0][1],-windows[i][0][2]);
		   glBegin(GL_POLYGON);
		      for (int j = 0; j < 4; j++)
			  {
				  glVertex3f(windows[i][j][0], windows[i][j][1], windows[i][j][2]);
			  }
		   glEnd();
	    }
     glPopMatrix();
	//Draw the door of the house
	glPushMatrix();
	glTranslatef(40, 35, -0.48);
	buffer  = theta *-1;
	glRotatef(buffer, 0.0f,1.0f, 0.0f);
	glTranslatef(-40, -35, +0.48);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	for (int j = 0; j < 4; j++)
		glVertex3f(door[j][0], door[j][1], door[j][2]);
	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers(); //Send the 3D scene to the screen
}