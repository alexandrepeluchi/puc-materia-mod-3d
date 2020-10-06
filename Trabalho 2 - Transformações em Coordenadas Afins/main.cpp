#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <cmath>

GLfloat escala = 1;
GLfloat rotacao = 0;
GLfloat translacao = 0;

void DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments)
{
	float theta = arc_angle / float(num_segments - 1);
	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);

	float x = r * cosf(start_angle);
	float y = r * sinf(start_angle);

	glBegin(GL_LINE_STRIP);
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

void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

		float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component

		glVertex2f(x + cx, y + cy);//output vertex

	}
	glEnd();
}

void desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20, 20, -20, 20);

    // Escala
    glScalef(escala, escala, 0);

    // Rotacao
    glRotatef(rotacao, 1, 1, 1);

    // Translacao
    glTranslatef(translacao, translacao, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub( 255, 255, 255 );

    DrawCircle(3, 3, 1, 50);

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
            glVertex2f(-2.6, 0.0);
    glEnd();

    // Letra E
    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 2.0);
            glVertex2f(-2.5, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 2.0);
            glVertex2f(-1.6, 2.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 1.0);
            glVertex2f(-2.0, 1.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(-2.5, 0.0);
            glVertex2f(-1.6, 0.0);
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

    // Letra D
    //DrawArc(0.89, 1, 1.17, -45, 2.048, 50);
    DrawArc(1.57, 1.2, 0.8, -44.0, 2.0, 50);
    DrawArc(1.57, 0.8, 0.8, -45.96, 2.0, 50);

    // Letra R
    glBegin(GL_LINE_STRIP);
            glVertex2f(2.5, 2.0);
            glVertex2f(2.5, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(2.5, 1.0);
            glVertex2f(3.5, 0.0);
    glEnd();

    // DrawArc(2.2, 1.49, 0.6, -45, 2.048, 50);
    DrawArc(2.8, 1.48, 0.6, -43.94, 2.048, 50);
    DrawArc(2.8, 1.51, 0.6, -46, 2.048, 50);

    glBegin(GL_LINE_STRIP);
            glVertex2f(2.38, 1.2);
            glVertex2f(2.38, 0.8);
    glEnd();

    // Letra E
    glBegin(GL_LINE_STRIP);
            glVertex2f(3.5, 2.0);
            glVertex2f(3.5, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(3.5, 2.0);
            glVertex2f(4.4, 2.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(3.5, 1.0);
            glVertex2f(4.0, 1.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
            glVertex2f(3.5, 0.0);
            glVertex2f(4.4, 0.0);
    glEnd();

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

        case 'q':
            rotacao--;
        break;

        case 'e':
            rotacao++;
        break;

        case 'a':
            translacao--;
        break;

        case 'd':
            translacao++;
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

    printf("\n\nTrabalho 2 - Implementacao sobre Transformacoes Afins em Open GL\n\n");
    printf("Comandos:\n\n");
    printf("Rotacao     - [Q] [E]\n");
    printf("Escalamento - [-] [+]\n");
    printf("Translacao  - [A] [D]\n");

    //glClearColor(1,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
