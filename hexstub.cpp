#include <iostream>
#include <SOIL.h>
#include <math.h>
#include <freeglut.h>

using namespace std;

GLuint texture[8];

const float PI = 3.14159;

float move_x = -3.0f, move_y = 8.0f;
bool rot[6] = { 0 };
int rotate_tank = 0;
bool drawTank = false;
bool drawTank_one = false;
bool drawTank_two = false;
bool drawTank_three = false;
bool drawTank_four = false;
bool drawTank_five = false;

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

void drawHexWater()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(4.5f, 1.5f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(4.5f, 14.5f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(-10.5f, 14.5f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(-10.5f, 1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
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
	drawHexWater();
	if (rot[3] == 1 || drawTank_one == false)
	{
		drawTankEast();
		rot[3] = 0;
		drawTank_one = true;
	}
	if (rot[2] == 1 || drawTank_two == false)
	{
		drawTankNorthEast();
		rot[2] = 0;
		drawTank_two = true;
	}
	if (rot[1] == 1 || drawTank_three == false)
	{
		drawTankNorthWest();
		rot[1] = 0;
		drawTank_three = true;
	}
	if (rot[4] == 1 || drawTank_four == false)
	{
		drawTankSouthEast();
		rot[4] = 0;
		drawTank_four = true;
	}
	if (rot[5] == 1 || drawTank_five == false)
	{
		drawTankSouthWest();
		rot[5] = 0;
		drawTank_five = true;
	}
	if (rot[0] == 1 || drawTank==false)
	{
	drawTankWest();
	rot[0] = 0;
	drawTank = true;
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
	texture[1] = loadTex("C:\\Users\\Owner\\Desktop\\tileWater.png");
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

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		cout << ox << "  " << oy << endl;
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
		rot[rotate_tank] = 1;
		break;
	case GLUT_KEY_RIGHT:
		if (rotate_tank >= 5)
		{
			rotate_tank = 0;
		}
		rotate_tank++;
		rot[rotate_tank] = 1;
		break;
	case GLUT_KEY_UP:
		if(rotate_tank==3)
		{
		drawTank_one = false;
		move_x += 15.0f;
		}
		if (rotate_tank == 0)
		{
		drawTank = false;
		move_x -= 15.0f;
		}
		if (rotate_tank == 2)
		{
			drawTank_two = false;
			move_x += 8.0f;
			move_y += 13.5f;
		}
		if (rotate_tank == 1)
		{
			drawTank_three = false;
			move_x -= 8.0f;
			move_y += 13.5f;
		}
		if (rotate_tank == 4)
		{
			drawTank_four = false;
			move_x += 8.0f;
			move_y -= 13.5f;
		}
		if (rotate_tank == 5)
		{
			drawTank_five = false;
			move_x -= 8.0f;
			move_y -= 13.5f;
		}
		break;
	case GLUT_KEY_DOWN:
		if (rotate_tank == 3)
		{
			drawTank_one = false;
			move_x -= 15.0f;
		}
		if (rotate_tank == 0)
		{
			drawTank = false;
			move_x += 15.0f;
		}
		if (rotate_tank == 2)
		{
			drawTank_two = false;
			move_x -= 8.0f;
			move_y -= 13.5f;
		}
		if (rotate_tank == 1)
		{
			drawTank_three = false;
			move_x += 8.0f;
			move_y -= 13.5f;
		}
		if (rotate_tank == 4)
		{
			drawTank_four = false;
			move_x -= 8.0f;
			move_y += 13.5f;
		}
		if (rotate_tank == 5)
		{
			drawTank_five = false;
			move_x += 8.0f;
			move_y += 13.5f;
		}
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
