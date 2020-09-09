#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat escala = 1;

void desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-6, 6, -6, 6);

    glScalef(escala, escala, 0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub( 255, 255, 255 );

    // Letra A
    glBegin(GL_LINE_STRIP);
            glVertex2f(-0.5, 0.00);
            glVertex2f(0, 2);
            glVertex2f(0, 2);
            glVertex2f(0.5, 0);
    glEnd();

    // Traço da Letra A
    glBegin(GL_LINE_STRIP);
            glVertex2f(-0.3, 0.75);
            glVertex2f(0.3, 0.75);
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
