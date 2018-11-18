#include"Header.h"

void textPrint(float x, float y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i<len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void welcomeScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-700, 700, -400, 400);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_POLYGON); //right bottom tri
	glColor3f(0.149, 0.196, 0.22);
	glVertex2f(700, 375);
	glVertex2f(225, -400);
	glVertex2f(700, -400);
	//glVertex2f(400, 0);
	glEnd();

	glBegin(GL_POLYGON); //right blue strip
	glColor3f(0, 0.898, 1);
	glVertex2f(668, 400);
	glVertex2f(700, 400);
	glVertex2f(700, 375);
	glVertex2f(225, -400);
	glVertex2f(172, -400);
	glEnd();

	glBegin(GL_POLYGON); //left to right blue strip
	glColor3f(0, 0.898, 1);
	glVertex2f(-700, 325);
	glVertex2f(-700, 365);
	glVertex2f(300, -240);
	glVertex2f(300, -280);
	glEnd();

	glBegin(GL_POLYGON); //right up grey strip
	glColor3f(0.216, 0.278, 0.31);
	glVertex2f(668, 400);
	glVertex2f(172, -400);
	glVertex2f(-175, -400);
	glVertex2f(350, 400);
	glEnd();


	glBegin(GL_POLYGON); //slim grey strip
	glColor3f(0.149, 0.196, 0.22);
	glVertex2f(350, 400);
	glVertex2f(-175, -400);
	glVertex2f(-190, -400);
	glVertex2f(325, 400);
	glEnd();



	glBegin(GL_POLYGON); //right up grey strip-2
	glColor3f(0.216, 0.278, 0.31);
	glVertex2f(325, 400);
	glVertex2f(-190, -400);
	glVertex2f(-390, -400);
	glVertex2f(125, 400);
	glEnd();




	glBegin(GL_POLYGON); //left bttm tri
	glColor3f(0.329, 0.431, 0.478);
	glVertex2f(-700, 325);
	glVertex2f(500, -400);
	glVertex2f(-700, -400);
	glEnd();

	glBegin(GL_POLYGON); //left bttm2 tri
	glColor3f(0.376, 0.49, 0.545);
	glVertex2f(-700, 250);
	glVertex2f(370, -400);
	glVertex2f(-700, -400);
	glEnd();


	glColor3f(0.878, 0.878, 0.878);
	textPrint(-240, 300, "SRINIVAS INSTITUTE OF TECHNOLOGY");
	textPrint(-150, 270, "Valchil,Mangaluru-574143");
	textPrint(-350, 230, "DEPARTMENT  OF COMPUTERSCIENCE  AND ENGINEERING");
	textPrint(-270, 190, "COMPUTER GRAPHICS AND VISUALIZATION ");
	textPrint(-110, 150, "Mini Project ");
	textPrint(-70, 110, "On");
	textPrint(-180, 65, "3D  NATURE  EXPLORER");
	textPrint(-650, -210, "Team Members:");
	textPrint(-650, -250, "DARSHAN AIL");
	textPrint(-400, -250, "4SN14CS006");
	textPrint(-400, -290, "4SN14CS063");
	textPrint(-650, -290, "NISHMITHA ANCHAN");
	textPrint(-650, -330, "Dept of CSE,SEC A");
	textPrint(500, -210, "Project guide :");
	textPrint(500, -250, "Mr.HEMANTH K");
	textPrint(500, -290, "Asst.Professor");
	textPrint(500, -330, "Dept of CSE");
	glColor3f(1.0, 0.0, 0.0);
	textPrint(-100, -360, "Press w for Next:");
}



void keys(unsigned char key, int x, int y)
{
	if (key == 'w')
		mainpage2();
}

void init()
{
	glPointSize(4.0);
	glClearColor(0.149, 0.196, 0.22, 1.0);

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	welcomeScreen();
	glFlush();
	glutSwapBuffers();
}







int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);


	glutInitWindowSize(1550, 795);

	glutInitWindowPosition(0, 0);
	glutCreateWindow("MINI PROJ");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keys);

	glutMainLoop();
	return 0;
}