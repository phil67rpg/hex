#include <iostream>
#include <SOIL.h>
#include <math.h>
#include <freeglut.h>

using namespace std;

GLuint texture[8];

const float PI = 3.14159;

float move_x = -3.25f, move_y = 8.35f;

void drawHex()
{
	const float hexagon_r = 10.0;
	const float hexagon_dx = hexagon_r * cos(30.0*PI / 180.0);
	const float hexagon_dy = hexagon_r * sin(30.0*PI / 180.0);
	const float hexagon_gx = 2.0*hexagon_dx;
	const float hexagon_gy = 2.0*hexagon_dx*sin(60.0*PI / 180.0);
	float x = 1.0f, y = 1.0f, z = 0.0f;
	int ni = 22, nj = 22;
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

void drawTankNorth()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f + move_x, -5.0f + move_y);
	
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(5.0f + move_x, 0.0f + move_y);
	
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.0f + move_x, 5.0f + move_y);
	
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-5.0f + move_x, 0.0f + move_y);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawHex();
	drawTankNorth();
	glFlush();
}

GLuint loadTex(const char* texname)
{
	/* load an image file directly as a new OpenGL texture */
	GLuint texture = SOIL_load_OGL_texture
	(
		texname,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);
	return texture;
}

void init()
{
	texture[0] = loadTex("C:\\Users\\Owner\\Desktop\\tanknorth.png");
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

void OnMouseClick(int button, int state, int x, int y)
{
	float mx = x;
	float my = y;
	float ox = ((mx / (4.0f))-100.0f);
	float oy = -((my / (3.0f))-100.0f);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cout << ox << "  " << oy << endl;
		move_x = ox;
		move_y = oy;
	}
	glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	}
	glutPostRedisplay();
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
	glutSpecialFunc(handleSpecialKeypress);
	init();
	glutMouseFunc(OnMouseClick);
	glutMainLoop();
	return 0;
}
