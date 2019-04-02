
#include <GL/glut.h>
#include <cmath>
#include <iostream>

#define min(x,y) ((x) > (y) ? (y) : (x))

int proof_simulation = 0; // 0 for 'proof A' & 1 for 'proof B', 0 by default.

// values will be entered by the user:
double a; // left open-interval endpoint.
double b; // right open-interval endpoint.
double e; // the epsilon radius of the neighborhood (a - e, a + e).

const double POINT_SIZE = 0.01;
const double SCALE_X = 5.0, SCALE_Y = 5.0;

void proof_A(double t)
{
	// calculate 'x':
	double 	x = min(a + e/2.0, (a + b)/2.0);

	double scaled_a = a / SCALE_X;
	double scaled_b = b / SCALE_X;
	double scaled_e = e / SCALE_X;
	double scaled_x = x / SCALE_X;

	// plot open-interval (a,b) with its endpoints:
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	{
		// plotting the line:
		glVertex2d(scaled_a, 0);
		glVertex2d(scaled_b, 0);

		// plotting the left endpoint 'a':
		glVertex2d(scaled_a - POINT_SIZE, +POINT_SIZE);
		glVertex2d(scaled_a + POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_a - POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_a + POINT_SIZE, +POINT_SIZE);

		// plotting the right endpoint 'b':
		glVertex2d(scaled_b - POINT_SIZE, +POINT_SIZE);
		glVertex2d(scaled_b + POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_b - POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_b + POINT_SIZE, +POINT_SIZE);
	}
	glEnd();

	// plotting the point 'x':
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	{
		glVertex2d(scaled_x - POINT_SIZE, +POINT_SIZE);
		glVertex2d(scaled_x + POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_x - POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_x + POINT_SIZE, +POINT_SIZE);
	}
	glEnd();

	// plotting the epsilon neighborhood around point 'a' (a - e, a + e):
	glColor3f(0, 1, 1);
	glBegin(GL_LINES);
	{
		const double scaled_height = 1 / SCALE_Y;

		// plotting the line:
		glVertex2d(scaled_a - scaled_e, scaled_height);
		glVertex2d(scaled_a + scaled_e, scaled_height);

		// plotting the left endpoint 'a-e':
		glVertex2d(scaled_a - scaled_e - POINT_SIZE, scaled_height +POINT_SIZE);
		glVertex2d(scaled_a - scaled_e + POINT_SIZE, scaled_height -POINT_SIZE);
		glVertex2d(scaled_a - scaled_e - POINT_SIZE, scaled_height -POINT_SIZE);
		glVertex2d(scaled_a - scaled_e + POINT_SIZE, scaled_height +POINT_SIZE);

		// plotting the right endpoint 'a+e':
		glVertex2d(scaled_a + scaled_e - POINT_SIZE, scaled_height +POINT_SIZE);
		glVertex2d(scaled_a + scaled_e + POINT_SIZE, scaled_height -POINT_SIZE);
		glVertex2d(scaled_a + scaled_e - POINT_SIZE, scaled_height -POINT_SIZE);
		glVertex2d(scaled_a + scaled_e + POINT_SIZE, scaled_height +POINT_SIZE);
	}
	glEnd();
	
	static double begin_e = e;
	e = begin_e * (sin(t) + 1)/2.0 + 0.001;
}

void proof_B(double t)
{
	double scaled_a = a / SCALE_X;
	double scaled_b = b / SCALE_X;

	// plot open-interval (a,b) with its endpoints:
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	{
		// plotting the line:
		glVertex2d(scaled_a, 0);
		glVertex2d(scaled_b, 0);

		// plotting the left endpoint 'a':
		glVertex2d(scaled_a - POINT_SIZE, +POINT_SIZE);
		glVertex2d(scaled_a + POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_a - POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_a + POINT_SIZE, +POINT_SIZE);

		// plotting the right endpoint 'b':
		glVertex2d(scaled_b - POINT_SIZE, +POINT_SIZE);
		glVertex2d(scaled_b + POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_b - POINT_SIZE, -POINT_SIZE);
		glVertex2d(scaled_b + POINT_SIZE, +POINT_SIZE);
	}
	glEnd();

	// plotting the sequence points 'x(n)':
	const int COUNT = 100;
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	{
		double fitted_t = fmodf(t, 1);
		fitted_t = pow(fitted_t, 4);
		for(int n = 0; n < COUNT * fitted_t; n++)
		{
			double x = a + (b - a)/2 * (1.0 / n);
			double scaled_x = x / SCALE_Y;

			glVertex2d(scaled_x - POINT_SIZE, +POINT_SIZE);
			glVertex2d(scaled_x + POINT_SIZE, -POINT_SIZE);
			glVertex2d(scaled_x - POINT_SIZE, -POINT_SIZE);
			glVertex2d(scaled_x + POINT_SIZE, +POINT_SIZE);
		}
	}
	glEnd();	
}

void ask_user_for_input_on_entry(void)
{
	std::cout << "Please enter the values for 'a' and 'b' and 'e':\n";

	std::cout << "a = ";
	std::cin >> a;

	std::cout << "b = ";
	std::cin >> b;

	std::cout << "e = ";
	std::cin >> e;
}

void renderer_init(void)
{
	// black
	glClearColor(0, 0, 0, 1);
}

void renderer_display(void)
{
	static double t = 0.0;

	glClear(GL_COLOR_BUFFER_BIT);

	if (proof_simulation == 0)
	{
		proof_A(t);
	}
	else if (proof_simulation == 1)
	{
		proof_B(t);
	}

	glutPostRedisplay();
	glutSwapBuffers();

	t += 0.003;
}

void renderer_keyboard(unsigned char key, int mouse_x, int mouse_y)
{
	if (key == 'a')
		proof_simulation = 0;
	else if (key == 'b')
		proof_simulation = 1;
}

int main(int argc, char* argv[])
{
	ask_user_for_input_on_entry();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MeasureTheory_Volume1_Page41_AdditionalExcerciseAtTheBottom");
	renderer_init();
	glutDisplayFunc(renderer_display);
	glutKeyboardFunc(renderer_keyboard);
	glutMainLoop();

	return 0;
}
