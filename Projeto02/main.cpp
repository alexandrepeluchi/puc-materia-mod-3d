#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cmath>

GLfloat escala = 1;

#define STEPS 5

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
	float i;
	int lineAmount = 100; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 3.14;

	glBegin(GL_LINE_LOOP);
		for(i = 0; i <= lineAmount;i+= 0.001) {
			glVertex2f(
			    x + (radius * cos(i *  twicePi / lineAmount)),
			    y + (radius* sin(i * twicePi / lineAmount))
			);
		}
	glEnd();
}

void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments)
{
	float theta = arc_angle / float(num_segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);


	float x = r * cosf(start_angle);//we now start at the start angle
	float y = r * sinf(start_angle);

	glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);

		float tx = -y;
		float ty = x;

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

void desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-6, 6, -6, 6);

    glScalef(escala, escala, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub( 255, 255, 255 );

    /*
     * Desenhar nome utilizando Linhas
     *
     * A L E X A N D R E
     *
     * Começar pela letra A do meio
     */

    // Letra A
    glBegin(GL_LINE_STRIP);
            glVertex2f(-4.5, 0.00);
            glVertex2f(-4.0, 2.0);
            glVertex2f(-4.0, 2.0);
            glVertex2f(-3.5, 0.0);
    glEnd();

    // Traço da Letra A
    glBegin(GL_LINE_STRIP);
            glVertex2f(-4.3, 0.75);
            glVertex2f(-3.7, 0.75);
    glEnd();

    // Letra L
    glBegin(GL_LINE_STRIP);
            glVertex2f(-3.5, 2.0);
            glVertex2f(-3.5, 0.0);
            glVertex2f(-2.5, 0.0);
    glEnd();

    // Letra E
    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 2.0);
            glVertex2f(-2.5, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 2.0);
            glVertex2f(-1.5, 2.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 1.0);
            glVertex2f(-1.5, 1.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 0.0);
            glVertex2f(-1.5, 0.0);
    glEnd();

    // Letra X
    glBegin(GL_LINE_STRIP);
            glVertex2f(-1.5, 2.0);
            glVertex2f(-0.5, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(-1.5, 0.0);
            glVertex2f(-0.5, 2.0);
    glEnd();

    // Letra A
    glBegin(GL_LINE_STRIP);
            glVertex2f(-0.5, 0.00);
            glVertex2f(0.0, 2.0);
            glVertex2f(0.0, 2.0);
            glVertex2f(0.5, 0.0);
    glEnd();

    // Traço da Letra A
    glBegin(GL_LINE_STRIP);
            glVertex2f(-0.3, 0.75);
            glVertex2f(0.3, 0.75);
    glEnd();

    // Letra N
    glBegin(GL_LINE_STRIP);
            glVertex2f(0.5, 0.0);
            glVertex2f(0.5, 2.0);
            glVertex2f(1.5, 0.0);
            glVertex2f(1.5, 2.0);
    glEnd();

    //drawHollowCircle(3, 2, 1);

    DrawArc(1, 1, 1, 90, 180, 20);

    glFlush();
}

void listeningKey(unsigned char tecla, GLint x, GLint y)
{
    switch(tecla) {
        case '+':
            escala++;
        break;

        case '-':
            if (escala > 0)
                escala--;
        break;
    }
    desenha();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Ola Glut");

    glutKeyboardFunc(listeningKey);

    glutDisplayFunc(desenha);

    //glClearColor(1,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
