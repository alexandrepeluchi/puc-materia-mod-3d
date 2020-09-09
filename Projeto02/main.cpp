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

    glBegin(GL_TRIANGLES);
        glColor3f(0, 1, 0);
        glVertex2f(-2, 0);
        glVertex2f(2, 0);
        glColor3f(1, 0, 0);
        glVertex2f(0, 2);
    glEnd();

    glFlush();
}

void listeningKey(unsigned char tecla, GLint x, GLint y) {
    switch(tecla) {
        case '+':
            escala++;
        break;

        case '-':
            escala--;
        break;
    }
    desenha();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Ola Glut");

    glutKeyboardFunc(listeningKey);

    glutDisplayFunc(desenha);

    //glClearColor(1,1,1,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
