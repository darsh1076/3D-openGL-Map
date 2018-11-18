#include "Header.h"
float angle = 0.0, deltaAngle = 0.0, ratio;
float x = 0.0f, y = 1.75f, z = 5.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
int deltaMove = 0, h, w;
int bitmapHeight = 13;

int frame, time, timebase = 0;
char s[30];
void initWindow();

void changeSize(int w1, int h1)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h1 == 0)
		h1 = 1;

	w = w1;
	h = h1;
	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);


}

//void init()
//{

//}


void lightsource(void)
{
	GLfloat mat_ambient[] = { 1,1,1,1.0f };
	GLfloat mat_diffuse[] = { 1,1,1,1.0f };
	GLfloat mat_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lightpos[] = { -400.0f,900.0f,1000.0f,0.0f };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

void lightsource1(void)
{
	GLfloat mat_ambient[] = { 0.8,0.8,0.8 };
	GLfloat mat_diffuse[] = { 0.2,0.2,0.2,1.0f };
	GLfloat mat_specular[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat lightpos[] = { 800.0f,900.0f,-500.0f,0.0f };
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void initScene()
{
	glEnable(GL_DEPTH_TEST);


}

void orientMe(float ang)
{


	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
}


void moveMeFlat(int i) {
	x = x + i*(lx)*100.0;
	z = z + i*(lz)*100.0;
	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);
	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();
	// reset matrix
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, w, 0, h);
	// invert the y axis, down is positive
	glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	glTranslatef(0, -h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
	// set the current matrix to GL_PROJECTION
	glMatrixMode(GL_PROJECTION);
	// restore previous settings
	glPopMatrix();
	// get back to GL_MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
}


void stars()
{
	int j = 0;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);

	for (j = 0; j <= 12; j++)
	{
		int p1 = rand() % 700;

		int p2 = rand() % 400;

		int p3 = rand() % 400;

		glVertex3f(-p1, p2, p3);
		glVertex3f(-p1, p2, -p3);
		glVertex3f(p1, p2, -p3);
		glVertex3f(p1, p2, p3);
	}
	glEnd();
	glFlush();

}

void tree() {

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	//glTranslatef(-10, 0, -10);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 5.5, 0);
	glRotatef(-60, 1.0, 1.0, 0.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 7.5, 0);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 4, 0);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glColor3f(0.22, 0.557, 0.235);
	glPushMatrix();
	glTranslatef(-2.0, 7, 2);//ball1
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(2.0, 8.5, 2);//ball2
	glutSolidSphere(1.8, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(2.0, 5, 3);//ball3
	glutSolidSphere(0.9, 100, 100);
	glPopMatrix();

	glColor3f(0.612, 0.8, 0.396);
	glPushMatrix();
	glTranslatef(0, 10, 0);//ball4
	glutSolidSphere(3, 100, 100);
	glPopMatrix();

	glPopAttrib();



}


void tree1() {

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(20, 0, 80);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, 5.5, 80);
	glRotatef(-60, 1.0, 1.0, 0.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 7.5, 80);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20, 4, 80);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glColor3f(0.22, 0.557, 0.235);
	glPushMatrix();
	glTranslatef(18.0, 7, 82);//ball1
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(20.0, 10, 81);//ball2
	glutSolidSphere(2.8, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(2.0, 5, 3);//ball3
	glutSolidSphere(0.9, 100, 100);
	glPopMatrix();

	glColor3f(0.612, 0.8, 0.396);
	glPushMatrix();
	glTranslatef(0, 10, 0);//ball4
	glutSolidSphere(3, 100, 100);
	glPopMatrix();


	glPopAttrib();



}


void tree2() {

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(100, 0, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(100, 5.5, 100);
	glRotatef(-60, 1.0, 1.0, 0.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 7.5, 100);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 4, 100);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glColor3f(0.22, 0.557, 0.235);
	glPushMatrix();
	glTranslatef(98.0, 7, 101);//ball1 x-2 y+1
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(100.0, 10, 100);//ball2
	glutSolidSphere(2.8, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(102.0, 5, 103);//ball3 x+2 y+3
	glutSolidSphere(0.9, 100, 100);
	glPopMatrix();

	glColor3f(0.612, 0.8, 0.396);
	glPushMatrix();
	glTranslatef(102, 8, 101);//ball4 x+2 y+!
	glutSolidSphere(3, 100, 100);
	glPopMatrix();


	glPopAttrib();



}


void tree3() {

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(-100, 0, 100);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-100, 5.5, 100);
	glRotatef(-60, 1.0, 1.0, 0.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 7.5, 100);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, 4, 100);
	glRotatef(60, 0.0, 1.0, 1.0);
	gluCylinder(obj, 0.3, 0.2, 4, 20, 20);
	glPopMatrix();

	glColor3f(0.22, 0.557, 0.235);
	glPushMatrix();
	glTranslatef(-102, 7, 101);//ball1 x-2 y+1
	glutSolidSphere(2, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(-100.0, 10, 100);//ball2
	glutSolidSphere(2.8, 100, 100);
	glPopMatrix();

	glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(-98.0, 5, 103);//ball3 x+2 y+3
	glutSolidSphere(0.9, 100, 100);
	glPopMatrix();

	glColor3f(0.612, 0.8, 0.396);
	glPushMatrix();
	glTranslatef(-97, 7, 101);//ball4 x+2 y+!
	glutSolidSphere(3, 100, 100);
	glPopMatrix();


	glPopAttrib();



}

void tree4() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(-100, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(-100, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(-100, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(-100, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();
	

	glPopAttrib();

	//glEnable(GL_LIGHTING);

}


void tree5() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(-75, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(-75, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(-75, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(-75, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree6() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(-50, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(-50 ,2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(-50, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(-50, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree7() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(-25, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(-25, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(-25, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(-25, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree8() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(0, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(0, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(0, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(0, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}


void tree9() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(25, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(25, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(25, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(25, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}
void tree10() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(50, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(50, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(50, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(50, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree11() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(75, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(75, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(75, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(75, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree12() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(-75, 0, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(-75, 2, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(-75, 4, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(-75, 6, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree13() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(50, 0, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(50, 2, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(50, 4, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(50, 6, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree14() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(0, 0, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(0, 2, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(0, 4, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(0, 6, 50);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}

void tree15() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(50, 0, -25);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(50, 2, -25);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(50, 4, -25);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(50, 6, -25);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}


/*
void tree4() {
	//glDisable(GL_LIGHTING);
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.64f, 0.16, 0.16f);
	glPushMatrix();
	glTranslatef(-100, 0, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.5, 0.3, 10, 20, 20);
	glPopMatrix();

	glColor3f(0.298f, 0.686, 0.314f);
	glPushMatrix();
	glTranslatef(-100, 2, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.3, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.22f, 0.557, 0.235f);
	glPushMatrix();
	glTranslatef(-100, 4, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 3.1, 0.3, 8, 20, 20);
	glPopMatrix();

	glColor3f(0.106f, 0.369, 0.125f);
	glPushMatrix();
	glTranslatef(-100, 6, 140);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 2.9, 0.3, 6, 20, 20);
	glPopMatrix();


	glPopAttrib();

	//glEnable(GL_LIGHTING);

}*/
void extrabase() {

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glColor3f(1.0, 1.588, 0.533);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-25.0f, -0.0f, 100.0f);
		glVertex3f(0.0f, -0.0f, 175.0f);
		glVertex3f(37.0f, -0.0f, 200.0f);
		glVertex3f(84.0f, -0.0f, 250.0f);
		glVertex3f(112.0f, -0.0f, 275.0f);
		glVertex3f(150.0f, -0.0f, 284.0f);
		glVertex3f(200.0f, -0.0f, 300.0f);
		glVertex3f(200.0f, -0.0f, 225.0f);
		glVertex3f(150.0f, -0.0f, 200.0f);
		glVertex3f(100.0f, -0.0f, 164.0f);
		glVertex3f(75.0f, -0.0f, 134.0f);
		glVertex3f(50.0f, -0.0f, 100.0f);

		glEnd();
	}

	glPopAttrib();



}





void mountain() {

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLUquadric *obj = gluNewQuadric();
	glColor3f(0.306, 0.204, 0.18);
	glPushMatrix();
	glTranslatef(-40, 0, -110);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 40, 0.1, 20, 25, 25);
	glPopMatrix();


	glColor3f(0.243, 0.153, 0.137);
	glPushMatrix();
	glTranslatef(40, 0, -90);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 50, 0.1, 30, 25, 25);
	glPopMatrix();


	glColor3f(0.333, 0.545, 0.184);
	glPushMatrix();
	glTranslatef(40, 0, -60);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 50, 0.1, 6, 25, 25);
	glPopMatrix();

	//glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(60, 0, 20);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 20, 0.1, 3, 25, 25);
	glPopMatrix();


	//glColor3f(0.545, 0.765, 0.29);
	glPushMatrix();
	glTranslatef(-90, 0, -90);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 50, 0.1, 6, 25, 25);
	glPopMatrix();
	//mountain in water
	glColor3f(1.64f, 1.16, 0.16f);
	glPushMatrix();
	glTranslatef(280, -40, 120);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 80, 20.0, 30, 25, 25);
	glPopMatrix();

	//pillars
	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-280, 0, 227);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-285, 0, 227);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-290, 0, 227);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-295, 0, 227);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-300, 0, 227);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	//set 2 pillars

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-300, 0, 280);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-300, 0, 285);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-300, 0, 290);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-300, 0, 295);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();

	glColor3f(1.64f, 1.16, 0.0);
	glPushMatrix();
	glTranslatef(-300, 0, 300);
	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(obj, 0.3, 0.6, 11, 25, 25);
	gluCylinder(obj, 0.6, 0.3, 11, 25, 25);
	glPopMatrix();
	glPopAttrib();



}


void cloud()
{
	//int i = 1;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(8.6, 15, 9);//ball3
	glutSolidSphere(1.3, 100, 100);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(10.5, 15, 9);//ball3
	glutSolidSphere(1.9, 100, 100);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(12.0, 15, 9);//ball3
	glutSolidSphere(1.3, 100, 100);
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glColor3f(0.984, 0.753, 0.176);
	glPushMatrix();
	glTranslatef(12.0, 50, -99);//sun
	glutSolidSphere(10, 100, 180);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPopAttrib();
}
void renderScene(void) {

	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	glDisable(GL_LIGHTING);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.502, 0.871, 0.918, 1.0);
	// Draw ground

	glColor3f(0.106, 0.369, 0.125);
	glBegin(GL_QUADS);
	glVertex3f(-150.0f, 0.0f, -150.0f);
	glVertex3f(-150.0f, 0.0f, 150.0f);
	glColor3f(0.106, 0.369, 0.125);
	glVertex3f(150.0f, 0.0f, 150.0f);
	glColor3f(0.22, 0.557, 0.235);
	glVertex3f(150.0f, 0.0f, -150.0f);
	glEnd();

	//draw edge

	glColor3f(0.365, 0.251, 0.216);
	glBegin(GL_QUADS);
	glVertex3f(-150.0f, -0.0f, -150.0f);
	glVertex3f(150.0f, -0.0f, -150.0f);
	glVertex3f(150.0f, -40.0f, -150.0f);
	glVertex3f(-150.0f, -40.0f, -150.0f);
	glEnd();

	glColor3f(0.475, 0.333, 0.282);
	glBegin(GL_QUADS);
	glVertex3f(-150.0f, -0.0f, -150.0f);
	glVertex3f(-150.0f, -0.0f, 150.0f);
	glVertex3f(-150.0f, -40.0f, 150.0f);
	glVertex3f(-150.0f, -40.0f, -150.0f);
	glEnd();

	glColor3f(0.475, 0.333, 0.282);
	glBegin(GL_QUADS);
	glVertex3f(150.0f, -0.0f, 150.0f);
	glVertex3f(150.0f, -0.0f, -150.0f);
	glVertex3f(150.0f, -40.0f, -150.0f);
	glVertex3f(150.0f, -40.0f, 150.0f);
	glEnd();

	glColor3f(0.365, 0.251, 0.216);
	glBegin(GL_QUADS);
	glVertex3f(-150.0f, -0.0f, 150.0f);
	glVertex3f(150.0f, -0.0f, 150.0f);
	glVertex3f(150.0f, -40.0f, 150.0f);
	glVertex3f(-150.0f, -40.0f, 150.0f);
	glEnd();


	//island 2

	glColor3f(0.22, 0.557, 0.235);
	glBegin(GL_QUADS);
	glVertex3f(-450.0f, 0.0f, 200.0f);
	glVertex3f(-450.0f, 0.0f, 400.0f);
	glVertex3f(-250.0f, 0.0f, 400.0f);
	glColor3f(0.106, 0.369, 0.125);
	glVertex3f(-250.0f, 0.0f, 200.0f);
	glEnd();

	/*glBegin(GL_QUADS);
	{
		glVertex3f(-400.0f, 0.0f, 200.0f);
		glVertex3f(-300.0f, 0.0f, 200.0f);
		glVertex3f(-300.0f, 10.0f, 200.0f);
		glColor3f(0.106, 0.369, 0.125);
		glVertex3f(-400.0f, 10.0f, 200.0f);
		glEnd();
	}*/

	//edge
	glColor3f(0.365, 0.251, 0.216);
	glBegin(GL_QUADS);
	glVertex3f(-450.0f, 0.0f, 200.0f);
	glVertex3f(-450.0f, 0.0f, 400.0f);
	glColor3f(0.243, 0.153, 0.137);
	glVertex3f(-450.0f, -30.0f, 400.0f);
	glVertex3f(-450.0f, -30.0f, 200.0f);
	glEnd();

	glColor3f(0.475, 0.333, 0.282);
	glBegin(GL_QUADS);
	glVertex3f(-450.0f, 0.0f, 200.0f);
	glVertex3f(-250.0f, 0.0f, 200.0f);
	glColor3f(0.243, 0.153, 0.137);
	glVertex3f(-250.0f, -30.0f, 200.0f);
	glVertex3f(-450.0f, -30.0f, 200.0f);
	glEnd();

	glColor3f(0.365, 0.251, 0.216);
	glBegin(GL_QUADS);
	glVertex3f(-250.0f, 0.0f, 200.0f);
	glVertex3f(-250.0f, 0.0f, 400.0f);
	glColor3f(0.243, 0.153, 0.137);
	glVertex3f(-250.0f, -30.0f, 400.0f);
	glVertex3f(-250.0f, -30.0f, 200.0f);
	glEnd();

	glColor3f(0.365, 0.251, 0.216);
	glBegin(GL_QUADS);
	glVertex3f(-450.0f, 0.0f, 200.0f);
	glVertex3f(-250.0f, 0.0f, 200.0f);
	glColor3f(0.243, 0.153, 0.137);
	glVertex3f(-250.0f, -30.0f, 200.0f);
	glVertex3f(-450.0f, -30.0f, 200.0f);
	glEnd();
	//back land
	/*glBegin(GL_QUADS);
	glVertex3f(-50.0f, 0.0f, -100.0f);
	glVertex3f(50.0f, 0.0f, 100.0f);
	glVertex3f(50.0f, 0.0f, -200.0f);
	glVertex3f(-50.0f, 0.0f, -200.0f);
	glEnd();*/

	//white floor for house
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 0.01f, 375.0f);
	glVertex3f(-400.0f, 0.01f, 225.0f);
	glVertex3f(-325.0f, 0.01f, 225.0f);
	glVertex3f(-325.0f, 0.01f, 375.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-325.0f, 0.01f, 375.0f);
	glVertex3f(-325.0f, 0.01f, 325.0f);
	glVertex3f(-300.0f, 0.01f, 325.0f);
	glVertex3f(-300.0f, 0.01f, 375.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-325.0f, 0.01f, 275.0f);
	glVertex3f(-325.0f, 0.01f, 250.0f);
	glVertex3f(-300.0f, 0.01f, 250.0f);
	glVertex3f(-300.0f, 0.01f, 275.0f);
	glEnd();

	//floor design
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-390.0f, 0.02f, 235.0f);
	glVertex3f(-335.0f, 0.02f, 235.0f);
	glVertex3f(-335.0f, 0.02f, 290.0f);
	glVertex3f(-390.0f, 0.02f, 290.0f);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-385.0f, 0.03f, 285.0f);
	glVertex3f(-340.0f, 0.03f, 285.0f);
	glVertex3f(-340.0f, 0.03f, 240.0f);
	glVertex3f(-385.0f, 0.03f, 240.0f);
	glEnd();

	//
	//roof for house

	glColor3f(0.502, 0.796, 0.769);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 10.01f, 375.0f);
	glVertex3f(-400.0f, 10.01f, 225.0f);
	glVertex3f(-275.0f, 10.01f, 225.0f);
	glVertex3f(-275.0f, 10.01f, 375.0f);
	glEnd();

	//roof edges

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 10.01f, 375.0f);
	glVertex3f(-400.0f, 10.01f, 225.0f);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-400.0f, 12.0f, 225.0f);
	glVertex3f(-400.0f, 12.0f, 375.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	
	glBegin(GL_QUADS);
	
	glVertex3f(-275.0f, 10.0f, 225.0f);
	glVertex3f(-275.0f, 10.0f, 375.0f);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-275.0f, 12.0f, 375.0f);
	glVertex3f(-275.0f, 12.0f, 225.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-400.0f, 10.0f, 225.0f);
	glVertex3f(-275.0f, 10.0f, 225.0f);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-275.0f, 12.0f, 225.0f);
	glVertex3f(-400.0f, 12.0f, 225.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-400.0f, 10.0f, 375.0f);
	glVertex3f(-275.0f, 10.0f, 375.0f);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-275.0f, 12.0f, 375.0f);
	glVertex3f(-400.0f, 12.0f, 375.0f);
	glEnd();

	//swimming pool
	glColor3f(0.565, 0.643, 0.682);
	glBegin(GL_QUADS);

	glVertex3f(-290.0f, 0.8f, 350.0f);
	glVertex3f(-285.0f, 0.8f, 350.0f);
	//glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-285.0f, 0.8f, 275.0f);
	glVertex3f(-290.0f, 0.8f, 275.0f);
	glEnd();

	//glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);

	glVertex3f(-255.0f, 0.8f, 275.0f);
	glVertex3f(-255.0f, 0.8f, 350.0f);
	//glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-260.0f, 0.8f, 350.0f);
	glVertex3f(-260.0f, 0.8f, 275.0f);
	glEnd();

	//glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);

	glVertex3f(-285.0f, 0.8f, 275.0f);
	glVertex3f(-260.0f, 0.8f, 275.0f);
	//glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-260.0f, 0.8f, 280.0f);
	glVertex3f(-285.0f, 0.8f, 280.0f);
	glEnd();

	//glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);

	glVertex3f(-285.0f, 0.8f, 350.0f);
	glVertex3f(-260.0f, 0.8f, 350.0f);
	//glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-260.0f, 0.8f, 345.0f);
	glVertex3f(-285.0f, 0.8f, 345.0f);
	glEnd();
	
	//edges
	glColor3f(0.69, 0.745, 0.773);
	glBegin(GL_QUADS);

	glVertex3f(-290.0f, 0.0f, 275.0f);
	glVertex3f(-255.0f, 0.0f, 275.0f);
	glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-255.0f, 0.8f, 275.0f);
	glVertex3f(-290.0f, 0.8f, 275.0f);
	glEnd();

	glColor3f(961.0, 0.961, 0.961);
	glBegin(GL_QUADS);

	glVertex3f(-255.0f, 0.0f, 275.0f);
	glVertex3f(-255.0f, 0.0f, 350.0f);
	glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-255.0f, 0.8f, 350.0f);
	glVertex3f(-255.0f, 0.8f, 275.0f);
	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(-255.0f, 0.0f, 350.0f);
	glVertex3f(-290.0f, 0.0f, 350.0f);
	glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-290.0f, 0.8f, 350.0f);
	glVertex3f(-255.0f, 0.8f, 350.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.961, 0.961, 0.961);
	glVertex3f(-290.0f, 0.0f, 350.0f);
	glVertex3f(-290.0f, 0.0f, 275.0f);
	glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-290.0f, 0.8f, 275.0f);
	glVertex3f(-290.0f, 0.8f, 350.0f);
	glEnd();
	//inside edges
	glBegin(GL_QUADS);
	glColor3f(1.161, 0.714, 0.965);
	glVertex3f(-285.0f, 0.8f, 280.0f);
	glVertex3f(-260.0f, 0.8f, 280.0f);
	glVertex3f(-260.0f, 0.5f, 280.0f);
	glVertex3f(-285.0f, 0.5f, 280.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.161, 0.714, 0.965);
	
	glVertex3f(-260.0f, 0.8f, 280.0f);
	glVertex3f(-260.0f, 0.8f, 345.0f);
	glVertex3f(-260.0f, 0.5f, 345.0f);
	glVertex3f(-260.0f, 0.5f, 280.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.161, 0.714, 0.965);
	
	glVertex3f(-260.0f, 0.8f, 345.0f);
	glVertex3f(-285.0f, 0.8f, 345.0f);
	glVertex3f(-285.0f, 0.5f, 345.0f);
	glVertex3f(-260.0f, 0.5f, 345.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.161, 0.714, 0.965);
	glVertex3f(-285.0f, 0.8f, 280.0f);
	glVertex3f(-285.0f, 0.8f, 345.0f);
	glVertex3f(-285.0f, 0.5f, 345.0f);
	glVertex3f(-285.0f, 0.5f, 280.0f);
	glEnd();

	//water inside pool
	glBegin(GL_QUADS);
	glColor3f(0.161, 0.714, 0.965);
	glVertex3f(-285.0f, 0.5f, 280.0f);
	glVertex3f(-260.0f, 0.5f, 280.0f);
	glVertex3f(-260.0f, 0.5f, 345.0f);
	glVertex3f(-285.0f, 0.5f, 345.0f);
	glEnd();
	//fallceiling
	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 9.0f, 250.0f);
	glVertex3f(-350.0f, 9.0f, 250.0f);
	glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-350.0f, 9.0f, 275.0f);
	glVertex3f(-375.0f, 9.0f, 275.0f);
	glEnd();

	//edges
	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 10.0f, 250.0f);
	glVertex3f(-350.0f, 10.0f, 250.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-350.0f, 9.0f, 250.0f);
	glVertex3f(-375.0f, 9.0f, 250.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 10.0f, 250.0f);
	glVertex3f(-375.0f, 10.0f, 275.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-375.0f, 9.0f, 275.0f);
	glVertex3f(-375.0f, 9.0f, 250.0f);
	glEnd();


	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 10.0f, 275.0f);
	glVertex3f(-350.0f, 10.0f, 275.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-350.0f, 9.0f, 275.0f);
	glVertex3f(-375.0f, 9.0f, 275.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-350.0f, 10.0f, 275.0f);
	glVertex3f(-350.0f, 10.0f, 250.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-350.0f, 9.0f, 250.0f);
	glVertex3f(-350.0f, 9.0f, 275.0f);
	glEnd();

	//fallceiling2
	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 9.0f, 350.0f);
	glVertex3f(-350.0f, 9.0f, 350.0f);
	glColor3f(0.69, 0.745, 0.773);
	glVertex3f(-350.0f, 9.0f, 325.0f);
	glVertex3f(-375.0f, 9.0f, 325.0f);
	glEnd();

	//edges
	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 10.0f, 325.0f);
	glVertex3f(-375.0f, 10.0f, 350.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-375.0f, 9.0f, 350.0f);
	glVertex3f(-375.0f, 9.0f, 325.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 10.0f, 325.0f);
	glVertex3f(-350.0f, 10.0f, 325.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-350.0f, 9.0f, 325.0f);
	glVertex3f(-375.0f, 9.0f, 325.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-350.0f, 10.0f, 325.0f);
	glVertex3f(-350.0f, 10.0f, 350.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-350.0f, 9.0f, 350.0f);
	glVertex3f(-350.0f, 9.0f, 325.0f);
	glEnd();

	glColor3f(0.812, 0.847, 0.863);
	glBegin(GL_QUADS);

	glVertex3f(-375.0f, 10.0f, 350.0f);
	glVertex3f(-350.0f, 10.0f, 350.0f);
	glColor3f(0.69, 0.745, 0.0);
	glVertex3f(-350.0f, 9.0f, 350.0f);
	glVertex3f(-375.0f, 9.0f, 350.0f);
	glEnd();
	/*glBegin(GL_QUADS);
	glVertex3f(-325.0f, 10.01f, 375.0f);
	glVertex3f(-325.0f, 10.01f, 325.0f);
	glVertex3f(-300.0f, 10.01f, 325.0f);
	glVertex3f(-300.0f, 10.01f, 375.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-325.0f, 10.01f, 275.0f);
	glVertex3f(-325.0f, 10.01f, 250.0f);
	glVertex3f(-300.0f, 10.01f, 250.0f);
	glVertex3f(-300.0f, 10.01f, 275.0f);
	glEnd();
	*/
	//house
	//1
	glColor3f(0.584, 0.459, 0.804);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 0.0f, 275.0f);
	
	glVertex3f(-400.0f, 0.0f, 225.0f);
	glVertex3f(-400.0f, 10.0f, 225.0f);
	glVertex3f(-400.0f, 10.0f, 275.0f);
	glEnd();


	//2
	glColor3f(1.0, 0.541, 0.396);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 0.0f, 225.0f);
	glVertex3f(-325.0f, 0.0f, 225.0f);
	//glColor3f(0.82, 0.769, 0.914);
	glVertex3f(-325.0f, 1.0f, 225.0f);
	glVertex3f(-400.0f, 1.0f, 225.0f);
	glEnd();

	//glColor3f(0.584, 0.459, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 10.0f, 225.0f);
	glVertex3f(-325.0f, 10.0f, 225.0f);
	//glColor3f(0.82, 0.769, 0.914);
	glVertex3f(-325.0f, 6.0f, 225.0f);
	glVertex3f(-400.0f, 6.0f, 225.0f);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 0.0f, 226.0f);
	glVertex3f(-325.0f, 0.0f, 226.0f);
	//glColor3f(0.82, 0.769, 0.914);
	glVertex3f(-325.0f, 1.0f, 226.0f);
	glVertex3f(-400.0f, 1.0f, 226.0f);
	glEnd();

	glColor3f(0.82, 0.769, 0.914);
	glBegin(GL_QUADS);
	glVertex3f(-400.0f, 1.0f, 225.0f);
	glVertex3f(-325.0f, 1.0f, 225.0f);
	glColor3f(0.82, 0.769, 0.919);
	glVertex3f(-325.0f, 1.0f, 226.0f);
	glVertex3f(-400.0f, 1.0f, 226.0f);
	glEnd();

	//3
	glColor3f(0.584, 0.459, 0.804);
	glBegin(GL_QUADS);
	glVertex3f(-325.0f, 0.0f, 225.0f);
	glVertex3f(-325.0f, 0.0f, 250.0f);
	glColor3f(0.82, 0.769, 0.914);
	glVertex3f(-325.0f, 10.0f, 250.0f);
	glVertex3f(-325.0f, 10.0f, 225.0f);
	glEnd();

	//4
	glColor3f(0.584, 0.490, 0.804);
	glBegin(GL_POLYGON);
	glVertex3f(-325.0f, 0.0f, 250.0f);
	glVertex3f(-325.0f, 5.0f, 250.0f);
	glVertex3f(-310.0f, 5.0f, 250.0f);
	glVertex3f(-310.0f, 0.0f, 250.0f);
	glEnd();

	glColor3f(0.584, 0.490, 0.804);
	glBegin(GL_POLYGON);
	glVertex3f(-325.0f, 0.0f, 250.0f);
	glVertex3f(-325.0f, 5.0f, 250.0f);
	glVertex3f(-303.0f, 5.0f, 250.0f);
	glVertex3f(-303.0f, 0.0f, 250.0f);
	glEnd();

	glColor3f(0.584, 0.490, 0.804);
	glBegin(GL_POLYGON);
	glVertex3f(-325.0f, 5.0f, 250.0f);
	glVertex3f(-300.0f, 5.0f, 250.0f);
	glVertex3f(-300.0f, 10.0f, 250.0f);
	glVertex3f(-325.0f, 10.0f, 250.0f);
	glEnd();

	//5
	glColor3f(0.584, 0.490, 0.804);
	glBegin(GL_POLYGON);
	glVertex3f(-300.0f, 0.0f, 250.0f);
	glVertex3f(-300.0f, 0.0f, 275.0f);
	glVertex3f(-300.0f, 10.0f, 275.0f);
	glVertex3f(-300.0f, 10.0f, 250.0f);
	glEnd();

	//6
	glColor3f(0.584, 0.490, 1.804);
	glBegin(GL_POLYGON);
	glVertex3f(-300.0f, 0.0f, 275.0f);
	glVertex3f(-325.0f, 0.0f, 275.0f);
	glVertex3f(-325.0f, 10.0f, 275.0f);
	glVertex3f(-300.0f, 10.0f, 275.0f);
	glEnd();

	//7
	glColor3f(0.584, 0.490, 1.804);
	glBegin(GL_POLYGON);
	glVertex3f(-325.0f, 0.0f, 275.0f);
	glVertex3f(-325.0f, 0.0f, 372.0f);
	glVertex3f(-325.0f, 5.0f, 372.0f);
	glVertex3f(-325.0f, 5.0f, 275.0f);
	glEnd();

	glColor3f(0.584, 0.490, 1.804);
	glBegin(GL_POLYGON);
	glVertex3f(-325.0f, 5.0f, 275.0f);
	glVertex3f(-325.0f, 5.0f, 375.0f);
	glVertex3f(-325.0f, 10.0f, 375.0f);
	glVertex3f(-325.0f, 10.0f, 275.0f);
	glEnd();

	//8
	glColor3f(1.0, 0.541, 0.396);
	glBegin(GL_POLYGON);
	glVertex3f(-325.0f, 0.0f, 325.0f);
	glVertex3f(-300.0f, 0.0f, 325.0f);
	glVertex3f(-300.0f, 10.0f, 325.0f);
	glVertex3f(-325.0f, 10.0f, 325.0f);
	glEnd();

	//9
	glColor3f(1.0, 0.671, 0.569);
	glBegin(GL_POLYGON);
	glVertex3f(-300.0f, 0.0f, 325.0f);
	glVertex3f(-300.0f, 0.0f, 375.0f);
	glVertex3f(-300.0f, 10.0f, 375.0f);
	glVertex3f(-300.0f, 10.0f, 325.0f);
	glEnd();

	//10
	glColor3f(0.584, 0.490, 1.804);
	glBegin(GL_POLYGON);
	glVertex3f(-300.0f, 0.0f, 375.0f);
	glVertex3f(-400.0f, 0.0f, 375.0f);
	glVertex3f(-400.0f, 10.0f, 375.0f);
	glVertex3f(-300.0f, 10.0f, 375.0f);
	glEnd();

	//11
	glColor3f(0.584, 0.490, 1.804);
	glBegin(GL_POLYGON);
	glVertex3f(-400.0f, 0.0f, 375.0f);
	glVertex3f(-400.0f, 0.0f, 275.0f);
	glVertex3f(-400.0f, 10.0f, 275.0f);
	glVertex3f(-400.0f, 10.0f, 375.0f);
	glEnd();

	//15
	glColor3f(1.0, 0.541, 0.396);
	glBegin(GL_POLYGON);
	glVertex3f(-400.0f, 0.0f, 300.0f);
	glVertex3f(-350.0f, 0.0f, 300.0f);
	glVertex3f(-350.0f, 5.0f, 300.0f);
	glVertex3f(-400.0f, 5.0f, 300.0f);
	glEnd();

	//glColor3f(0.584, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-400.0f, 5.0f, 300.0f);
	glVertex3f(-325.0f, 5.0f, 300.0f);
	glVertex3f(-325.0f, 10.0f, 300.0f);
	glVertex3f(-400.0f, 10.0f, 300.0f);
	glEnd();

	//glColor3f(0.584, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(-347.0f, 0.0f, 300.0f);
	glVertex3f(-325.0f, 0.0f, 300.0f);
	glVertex3f(-325.0f, 5.0f, 300.0f);
	glVertex3f(-347.0f, 5.0f, 300.0f);
	glEnd();


	//water
	glColor3f(0.0, 0.588, 0.533);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-500.0f, -5.0f, -500.0f);
		glColor3f(0, 0.376, 0.392);
		glVertex3f(-500.0f, -5.0f, 500.0f);
		
		glVertex3f(500.0f, -5.0f, 500.0f);
		glVertex3f(500.0f, -5.0f, -500.0f);
		glEnd();
	}

	glEnable(GL_LIGHTING);

	//gluQuadricDrawStyle(obj, GLU_LINE);

	tree();
	tree1();
	tree2();
	tree3();
	tree4();
	tree5();
	tree6();
	tree7();
	tree8();
	tree9();
	tree10();
	tree11();
	tree12();
	tree13();
	tree14();
	tree15();
	mountain();
	
	cloud();
	//extrabase();
	stars();

	glColor3f(0.0f, 1.0f, 1.0f);
	setOrthographicProjection();
	glPushMatrix();
	glLoadIdentity();
	glPopMatrix();
	resetPerspectiveProjection();
	//gluPerspective(-10, -1.7, 100, 0);
	
	glutPostRedisplay();
	glFlush();
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 'q')
		exit(0);
}

void pressKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
	case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
	case GLUT_KEY_UP: deltaMove = 1; break;
	case GLUT_KEY_DOWN: deltaMove = -1; break;
	}

}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT: if (deltaAngle < 0.0f)
		deltaAngle = 0.0f;
		break;
	case GLUT_KEY_RIGHT: if (deltaAngle > 0.0f)
		deltaAngle = 0.0f;
		break;
	case GLUT_KEY_UP: if (deltaMove > 0)
		deltaMove = 0;
		break;
	case GLUT_KEY_DOWN: if (deltaMove < 0)
		deltaMove = 0;
		break;
	}
}

void initWindow() {
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	initScene();

}

void  mainpage2()
{
	//glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1550, 795);
	glutCreateWindow("3d Nature Explorer");
	lightsource();
	//lightsource1();
	//lightsource2();
	// register all callbacks
	initWindow();

	glutMainLoop();

}
