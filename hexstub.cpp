#include <iostream>
#include <SOIL.h>
#include <math.h>
#include <freeglut.h>

using namespace std;

GLuint texture[8];

const float PI = 3.14159;

float move_x = 0.0f, move_y = 0.0f;
bool rot[6] = { 0 };
int rotate_tank = 6;
bool drawTank = false;
float zoom = 9.0f;

void drawHex()
{
	bool drawTank = false;
	float hexagon_r = zoom;
	float hexagon_dx = hexagon_r * cos(30.0*PI / 180.0);
	float hexagon_dy = hexagon_r * sin(30.0*PI / 180.0);
	float hexagon_gx = 2.0*hexagon_dx;
	float hexagon_gy = 2.0*hexagon_dx*sin(60.0*PI / 180.0);
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

void drawTankNorthWest()
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

void drawTankNorthEast()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f + move_x, -5.0f + move_y);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(-5.0f + move_x, 0.0f + move_y);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.0f + move_x, 5.0f + move_y);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(5.0f + move_x, 0.0f + move_y);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTankSouthEast()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f + move_x, 5.0f + move_y);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(-5.0f + move_x, 0.0f + move_y);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.0f + move_x, -5.0f + move_y);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(5.0f + move_x, 0.0f + move_y);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTankSouthWest()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(0.0f + move_x, 5.0f + move_y);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(5.0f + move_x, 0.0f + move_y);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(0.0f + move_x, -5.0f + move_y);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-5.0f + move_x, 0.0f + move_y);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTankWest()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(5.0f + move_x, -5.0f + move_y);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(5.0f + move_x, 5.0f + move_y);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(-5.0f + move_x, 5.0f + move_y);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-5.0f + move_x, -5.0f + move_y);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawTankEast()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(-5.0f + move_x, 5.0f + move_y);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(-5.0f + move_x, -5.0f + move_y);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(5.0f + move_x, -5.0f + move_y);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(5.0f + move_x, 5.0f + move_y);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawHex();
	if (rot[0] == 1 || drawTank==false)
	{
	drawTankWest();
	rot[0] = 0;
	drawTank = true;
	}
	if (rot[1] == 1)
	{
	drawTankNorthWest();
	rot[1] = 0;
	}
	if (rot[2] == 1)
	{
	drawTankNorthEast();
	rot[2] = 0;
	}
	if (rot[3] == 1)
	{
	drawTankEast();
	rot[3] = 0;
	}
	if (rot[4] == 1)
	{
	drawTankSouthEast();
	rot[4] = 0;
	}
	if (rot[5] == 1)
	{
	drawTankSouthWest();
	rot[5] = 0;
	}
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
		glOrtho(-100.0, 100.0, -100.0, 100.0, 1.0, -1.0);
	else
	glOrtho(-100.0, 100.0, -100.0, 100.0, 1.0, -1.0);
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
		rot[0] = 1;
//		cout << ox << "  " << oy << endl;
		move_x = ox;
		move_y = oy;
	}
}

void mouseWheel(int wheel, int direction, int x, int y)
{
	(direction > 0) ? zoom += 0.5f : zoom -= 0.5f;
	glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (rotate_tank <= 0)
		{
			rotate_tank = 6;
		}
		rotate_tank--;
//		cout << rotate_tank << endl;
		rot[rotate_tank] = 1;
		break;
	case GLUT_KEY_RIGHT:
		if (rotate_tank >= 5)
		{
			rotate_tank = -1;
		}
		rotate_tank++;
		rot[rotate_tank] = 1;
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
	glutMouseWheelFunc(mouseWheel);
	glutMouseFunc(OnMouseClick);
	glutDisplayFunc(renderScene);
	glutSpecialFunc(handleSpecialKeypress);
	init();
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}
