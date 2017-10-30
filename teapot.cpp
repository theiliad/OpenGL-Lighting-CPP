#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>

/*  Light + Teapot
 *
 * 
 */

int ang = 0;	//angle for rotating cube
int cnt = 0;
float eye[] = {5,5,5};

/* LIGHTING */
float light_pos[] = {5.0, 5.0, 5.0, 1.0};

float amb0[4] = {1, 1, 1, 1};
float diff0[4] = {0.5, 0.5, 0.5, 1};
float spec0[4] = {1, 1, 1, 1};

void drawCube()
{
    
    glBegin(GL_QUADS);
    
    //front
    
    glColor3f(1, 0, 0);
    glNormal3f(-1,1,1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glNormal3f(1,-1,1);
    glVertex3f(1, 1, 1);
    glNormal3f(1,1,1);
    glVertex3f(-1, 1, 1);
    glNormal3f(-1,1,1);
    
    //top
    glColor3f(0, 1, 0);
    glNormal3f(-1,1,1);
    glVertex3f(-1,1,1);
    glNormal3f(-1,1,1);
    glVertex3f(1,1,1);
    glNormal3f(1,1,1);
    glVertex3f(1,1,-1);
    glNormal3f(-1,1,-1);
    glVertex3f(-1,1,-1);
    
    
    //bottom
    glColor3f(0, 1, 0);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);
    
    //left side
    glColor3f(0, 0, 1);
    glVertex3f(-1,1,1);
    glVertex3f(-1,-1,1);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,1,-1);
    
    //right side
    glColor3f(1,0,1);
    glVertex3f(1,1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    
    //back side
    glColor3f(1,1,0);
    glVertex3f(-1,1,-1);
    glVertex3f(-1,-1,-1);
    glVertex3f(1,-1,-1);
    glVertex3f(1,1,-1);
    
    glEnd();
}


void draw3DScene(){
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 1, 100);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);
    
    cnt++;
    //increment the rotation angle every 100th display cycle
    if(cnt % 5 == 0)
    {
        ang++;
        cnt = 0;
    }
    
    //optionally draw the axis
    //	drawAxis();
    
    
    /* LIGHTING */
    glLightfv(GL_LIGHT0, GL_POSITION, light_post);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);
    
    //push the current modelview matrix onto the matrix stack
    //  this allows us to rotate, then pop the stack so as to only
    //  rotate our cube, and only by the specified amount
    glPushMatrix();
    
    //do the rotation - rotate about the Y axis by angle ang
    glRotatef(ang, 0, 1, 0);
    
    //draw the teapot + MATERIALS
    glColor3f(1,0,0);
    glutSolidTeapot(1);
    

    
    //pop the matrix back to what it was prior to the rotation
    glPopMatrix();

}
/* drawCube() -- draws a cube with different coloured sides using QUAD primitives */

/* drawAxis() -- draws an axis at the origin of the coordinate system
 *   red = +X axis, green = +Y axis, blue = +Z axis
 */
void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0,0,0);
	glVertex3f(50,0,0);
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,50,0);
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,50);
	glEnd();
}

/* display() - the OpenGL display function, this draws the screen
 *  it displays a spinning cube
 */
void display()
{

    draw3DScene();
    glutSwapBuffers();

	//force a redisplay, to keep the animation running
	glutPostRedisplay();
}

/* kbd -- the GLUT keyboard function 
 *  key -- the key pressed
 *  x and y - mouse x and y coordinates at the time the function is called
 */
void kbd(unsigned char key, int x, int y)
{
	//if the "q" key is pressed, quit the program
	if(key == 'Q' || key == 'q')
	{
		exit(0);
	}
}


void special(int key, int x, int y){
  switch(key){
     case GLUT_KEY_LEFT:
        eye[0]-=0.1;
        break;
      case GLUT_KEY_RIGHT:
       eye[0]+=0.1;
        break;
      case GLUT_KEY_UP:
       eye[2]+=0.1;
        break;
      case GLUT_KEY_DOWN:
          eye[2]-=0.1;
          break;
  }
}
int main(int argc, char** argv)
{
	//glut initialization stuff:
	// set the window size, display mode, and create the window
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Spinning Teapot");
    
    /* LIGHTING */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    
	//enable Z buffer test, otherwise things appear in the order they're drawn
	glEnable(GL_DEPTH_TEST);

	//setup the initial view
	// change to projection matrix mode, set the extents of our viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
       
	//set clear colour to white
	glClearColor(1, 1, 1, 0);

    
	//register glut callbacks for keyboard and display function
	glutKeyboardFunc(kbd);
	glutDisplayFunc(display);
	glutSpecialFunc(special);

   
	//start the program!
	glutMainLoop();

	return 0;
}















