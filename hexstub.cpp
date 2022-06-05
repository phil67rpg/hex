#include <iostream>
#include <math.h>
#include <glut.h>

using namespace std;

const float PI = 3.14159;

void drawHex()
{
	const float hexagon_r = 15.0;
	const float hexagon_dx = hexagon_r * cos(30.0*PI / 180.0);
	const float hexagon_dy = hexagon_r * sin(30.0*PI / 180.0);
	const float hexagon_gx = 2.0*hexagon_dx;
	const float hexagon_gy = 2.0*hexagon_dx*sin(60.0*PI / 180.0);
	float x = 0.0f, y = 0.0f, z = 0.0f;
	int ni = 5, nj = 5;
			int i, j; float x0;
			x -= float(ni - 1)*hexagon_gx*0.5; // just shift x,y to start position (i=0,j=0)
			x -= float(nj - 1)*hexagon_dx*0.5;
			y -= float(nj - 1)*hexagon_gy*0.5;
			for (x0 = x, j = 0; j < nj; j++, x0 += hexagon_dx, x = x0, y += hexagon_gy)
			{
				for (i = 0; i < ni; i++, x += hexagon_gx)
				{
					glBegin(GL_LINE_LOOP);
					glVertex3f(x - hexagon_dx, y - hexagon_dy, z);
					glVertex3f(x - hexagon_dx, y + hexagon_dy, z);
					glVertex3f(x, y + hexagon_r, z);
					glVertex3f(x + hexagon_dx, y + hexagon_dy, z);
					glVertex3f(x + hexagon_dx, y - hexagon_dy, z);
					glVertex3f(x, y - hexagon_r, z);
					glEnd();
				}
			}
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawHex();
	glFlush();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(400, 300);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hex");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}
