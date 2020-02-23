#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>

#define AMMO 20
#define AMMO2 20
#define MOVEACCELERATION 0.02
#define FIRESPEED 0.11
#define REFRESH 20

double speed = 0, speed2 = 0, xbat = -0.1, ybat = -0.8, xfire[AMMO], powercom =
		0.4, powercom2 = 0.4, yfire[AMMO], xdist = 0.008, ydist = 0.007, x, y,
		x1 = -0.98, x2 = 0.71, xcomfire[AMMO2], ycomfire[AMMO2];
int i, j, numoffire = 0, fireVisible[AMMO], twobatvisible = 1, numofcomfire = 0,
		comfirevisible[AMMO2], REFRESH2 = 0;

char xd = 'r', yd = 'u';

void keyboard(unsigned char Key, int x, int y) {
	switch (Key) {
	case 27:
		exit(0);
	case 'd':
		speed = speed + MOVEACCELERATION;
		x1 = -0.95;
		x2 = 0.60;
		break;
	case 'a':
		speed = speed - MOVEACCELERATION;
		x1 = -0.72;
		x2 = 0.38;
		break;
	case 'w':
		speed2 = speed2 + MOVEACCELERATION;
		x1 = -0.58;
		x2 = 0.22;
		break;
	case 's':
		speed2 = speed2 - MOVEACCELERATION;
		x1 = -0.42;
		x2 = 0.14;
		break;
	case 32:
		xfire[numoffire % 10] = xbat;
		yfire[numoffire % 10] = ybat;
		fireVisible[numoffire % 10] = 1;
		x1 = -0.19;
		numoffire++;
		x2 = 0.1;
		break;
	}
}

void Timer(int Value) {

	for (i = 0; i < AMMO; i++) {
		yfire[i] += FIRESPEED;
	}
	for (i = 0; i < AMMO2; i++) {
		ycomfire[i] -= FIRESPEED;
	}
	if (xbat < -0.96) {
		xbat = -0.96;
		speed = 0;
	}
	if (xbat > 0.69) {
		xbat = 0.69;
		speed = 0;
	}
	if (ybat > 0.9) {
		ybat = 0.9;
		speed2 = 0;
	}
	if (ybat < -1.0) {
		ybat = -1.0;
		speed2 = 0;
	}
	
	xbat = xbat + speed;
	ybat = ybat + speed2;
	
	if (speed >= 0.0004) {
		speed = speed - 0.002;
	} else if (speed <= (-0.0004)) {
		speed = speed + 0.002;
	} else
		speed = 0;
	if (speed2 >= 0.0004) {
		speed2 = speed2 - 0.002;
	} else if (speed2 <= (-0.0004)) {
		speed2 = speed2 + 0.002;
	} else
		speed2 = 0;
	glutPostRedisplay();
	glutTimerFunc(REFRESH, Timer, 0);
	REFRESH2 += REFRESH;
	if (xbat + 0.2 >= x && xbat - 0.2 <= x) {
		if (REFRESH2 >= 30) {
			xcomfire[numofcomfire % 10] = x;
			ycomfire[numofcomfire % 10] = y;
			comfirevisible[numofcomfire % 10] = 1;
			numofcomfire++;
			REFRESH2 = 0;
		}
	}
}

void Display() {
	
	if (xd == 'r')
		x = x + xdist;
	else if (xd == 'l')
		x = x - xdist;
	if (yd == 'd')
		y = y - ydist;
	else if (yd == 'u')
		y = y + ydist;
	if (x < x1)
		xd = 'r';
	else if (x > x2) {
		xd = 'l';
	}
	
	if (y > 0.2)
		yd = 'd';
	else if (y < -0.5)
		yd = 'u';
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(xbat, ybat, 0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2d(-0.04, 0.025);
	glVertex2d(-0.04, -0.025);
	glVertex2d(0.09, -0.025);
	glVertex2d(0.09, 0.025);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2d(0.02, 0.20);
	glVertex2d(-0.01, 0.0);
	glVertex2d(0.06, 0.0);
	glEnd();
	
	if (twobatvisible == 1) {
		glLoadIdentity();
		glTranslatef(x, y, 0);
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.04, 0.8);
		glVertex2f(-0.04, 0.75);
		glVertex2f(0.09, 0.75);
		glVertex2f(0.09, 0.8);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2d(0.02, 0.55);
		glVertex2d(-0.01, 0.8);
		glVertex2d(0.06, 0.8);
		glEnd();
	}
	
	glLoadIdentity();
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2f(0.8, -1.0);
	glVertex2f(0.8, 1.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0.0);
	glVertex2f(1.0, 0.0);
	glEnd();
	glLoadIdentity();
	glTranslatef(0.9, 0.5, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.08, powercom);
	glVertex2f(-0.08, -0.4);
	glVertex2f(0.08, -0.4);
	glVertex2f(0.08, powercom);
	glEnd();
	glLoadIdentity();
	glTranslatef(0.9, -0.5, 0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.08, powercom2);
	glVertex2f(-0.08, -0.4);
	glVertex2f(0.08, -0.4);
	glVertex2f(0.08, powercom2);
	glEnd();
	
	for (i = 0; i < AMMO; i++) {
		if (fireVisible[i] == 1) {
			glLoadIdentity();
			glColor3f(0.0f, 1.0f, 0.0f);
			glTranslatef(xfire[i] + 0.02, yfire[i] + 0.09, 0);
			glutSolidSphere(0.01, 10, 10);
		}
	}
	
	for (i = 0; i < AMMO2; i++) {
		if (comfirevisible[i] == 1) {
			glLoadIdentity();
			glColor3f(0.0f, 1.0f, 0.0f);
			glTranslatef(xcomfire[i] + 0.025, ycomfire[i] + 0.55, 0);
			glutSolidSphere(0.01, 10, 10);
		}
	}
	
	for (i = 0; i < AMMO; i++) {
		if (fireVisible[i] == 1 && (x < xfire[i] + 0.09 && x > xfire[i] - 0.09)
				&& y > yfire[i]) {
			if (powercom > -0.4)
				powercom = powercom - 0.001;
		}
	}
	
	for (i = 0; i < AMMO2; i++) {
		if (comfirevisible[i] == 1
				&& (xbat < xcomfire[i] + 0.09 && xbat > xcomfire[i] - 0.09)
				&& ybat < ycomfire[i]) {
			if (powercom2 > -0.4)
				powercom2 = powercom2 - 0.001;
		}
	}
	
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	
	for (j = 0; j < AMMO; j++) {
		fireVisible[j] = 0;
	}
	
	for (j = 0; j < AMMO2; j++) {
		comfirevisible[j] = 0;
	}
	
	glutInit(&argc, argv);
	glutInitWindowSize(1440, 920);
	glutInitWindowPosition(200, 300);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutCreateWindow("Space Ship Game Created by Ankush");
	glutFullScreen();
	glutDisplayFunc(Display);
	glutTimerFunc(0, Timer, 0);
	glutKeyboardFunc(keyboard);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutMainLoop();
	return 0;
	
}