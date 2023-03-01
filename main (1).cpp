/*******************************************************
 * Homework 2: OpenGL                                  *
 *-----------------------------------------------------*
 * First, you should fill in problem1(), problem2(),   *
 * and problem3() as instructed in the written part of *
 * the problem set.  Then, express your creativity     *
 * with problem4()!                                    *
 *                                                     *
 * Note: you will only need to add/modify code where   *
 * it says "TODO".                                     *
 *                                                     *
 * The left mouse button rotates, the right mouse      *
 * button zooms, and the keyboard controls which       *
 * problem to display.                                 *
 *                                                     *
 * For Linux/OS X:                                     *
 * To compile your program, just type "make" at the    *
 * command line.  Typing "make clean" will remove all  *
 * computer-generated files.  Run by typing "./hw2"    *
 *                                                     *
 * For Visual Studio:                                  *
 * You can create a project with this main.cpp and     *
 * build and run the executable as you normally would. *
 *******************************************************/

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "./freeglut-3.2.1/include/GL/freeglut.h"

using namespace std;

bool leftDown = false, rightDown = false;
int lastPos[2];
float cameraPos[4] = {0,1,4,1};
int windowWidth = 640, windowHeight = 480;
double yRot = 0;
int curProblem = 1; // TODO: change this number to try different examples

float specular[] = { 1.0, 1.0, 1.0, 1.0 };
float shininess[] = { 50.0 };

void problem1() {

  // number on tea pots, in this case is 10
  int ntea = 10;

    // Find the angle we have to rotate each teapot to fill the ring
	int agl = 360/ntea;

	for (int i = 0; i < 360; i+=agl) {

  glPushMatrix();  
  // Rotate  teapot around the z axis with above angle 
	glRotatef(i, 0.0f, 0.0f, 1.0f); 
  // Translate with radius of 1
	glTranslatef (1, 0, 0); 
  // Then make the teapot in the location
	glutSolidTeapot(0.2); 

	glPopMatrix();
	}
}

void problem2() {
  // Number of steps, in this case is 19
  int nsteps = 19; 
	glPushMatrix(); 
	// Start from -1.6 on x axis
	glTranslatef(-2,0,0);	
  //each row
	for (int i = 0; i < nsteps; i++) {
	//each column
	for(int j = 0; j <= i; j++){
	 glPushMatrix();
			// Each cup is higher than next one 0.25
	 glTranslatef(i*0.2,0.25*j*0.2,0);
	 glutSolidCube(0.2);
	 glPopMatrix();
		}
	}
	glPopMatrix();
}

void problem3() {
  // number row triangle, in this case is 6
  int h = 6;

  // Distance from one to another by 1
  float dist = 1;
  float x = -2;
  float y = 1;
  // loop for each row
	for (int i = 0; i < h; i++) {
	// For for each column
	for (int j = i; j < h; j++) {
    
		glPushMatrix();  
	// draw the teapot
		glTranslatef (x+j*dist, y, 0);
		glutSolidTeapot(0.2);
		    glPopMatrix();
      }
    
      
		x = x-dist/2;
		y = y-0.5;
	}
}

void problem4() {
  glPushMatrix();

	//rotate to  our desired location
	glTranslatef (0.1, 0.2, 0);
	glPushMatrix();  

	// make each segment by using a cube horizontally

  glutSolidCube(0.2);
	glTranslatef (0, 0.3, 0);
	glutSolidCube(0.2);
	glTranslatef (0, 0.3, 0);
	glutSolidCube(0.2);
  
  glPopMatrix();
  
  // make each segment by using a cube vertically
  glTranslatef (-0.3, 0, 0);
  glPushMatrix(); 
  glTranslatef (0, 0.3, 0);
	glutSolidCube(0.2);
  glPopMatrix();

  glTranslatef (0.6, 0, 0);
  glPushMatrix(); 
  glTranslatef (0, 0.3, 0);
	glutSolidCube(0.2);
  glPopMatrix();
  glPopMatrix();
}

void display() {
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
		glColor3f(1,0,0); glVertex3f(0,0,0); glVertex3f(1,0,0); // x axis
		glColor3f(0,1,0); glVertex3f(0,0,0); glVertex3f(0,1,0); // y axis
		glColor3f(0,0,1); glVertex3f(0,0,0); glVertex3f(0,0,1); // z axis
	glEnd(/*GL_LINES*/);

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,windowWidth,windowHeight);

	float ratio = (float)windowWidth / (float)windowHeight;
	gluPerspective(50, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_POSITION, cameraPos);

	glRotatef(yRot,0,1,0);

	if (curProblem == 1) problem1();
	if (curProblem == 2) problem2();
	if (curProblem == 3) problem3();
	if (curProblem == 4) problem4();

	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) leftDown = (state == GLUT_DOWN);
	else if (button == GLUT_RIGHT_BUTTON) rightDown = (state == GLUT_DOWN);

	lastPos[0] = x;
	lastPos[1] = y;
}

void mouseMoved(int x, int y) {
	if (leftDown) yRot += (x - lastPos[0])*.1;
	if (rightDown) {
		for (int i = 0; i < 3; i++)
			cameraPos[i] *= pow(1.1,(y-lastPos[1])*.1);
	}


	lastPos[0] = x;
	lastPos[1] = y;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	curProblem = key-'0';
    if (key == 'q' || key == 'Q' || key == 27){
        exit(0);
    }
	glutPostRedisplay();
}

void reshape(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("HW2");
//   int curProblem = 1;
//   do
//   {
//     cout << endl
//     << " 1 - Problem1\n"
//     << " 2 - Problem2\n"
//     << " 3 - Problem3\n"
//     << " 4 - Problem4\n"
//     << " 5 - Exit"
//     << " Enter your choice: ";
//     cin >> curProblem;

// switch (curProblem)
// {
// case 1:
//   glutDisplayFunc(display);
//   glutMotionFunc(mouseMoved);
// 	glutMouseFunc(mouse);
// 	glutReshapeFunc(reshape);
// 	glutKeyboardFunc(keyboard);;
//   break;
// case 2:
//   glutDisplayFunc(display);
//   break;
// case 3:
//   glutDisplayFunc(display);
//   break;
// case 4:
//   glutDisplayFunc(display);
//   break;
// case 5:
// cout << "End of Program.\n";
//   break;
// default:
// cout << "Not a Valid Choice. \n"
//     << "Choose again.\n";
//   break;
// }
// }while (curProblem !=5);
  

	glutDisplayFunc(display);
	glutMotionFunc(mouseMoved);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
  

	glutMainLoop();

 

	return 0;
}
