
#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

// Fun��o que recebe a fonte e um texto por par�metro para ser exibido na
// tela usando caracteres bitmap
void DesenhaTexto(void *font, char *string)
{
    // Exibe caractere a caractere
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++);
}

// Fun��o que recebe a fonte e um texto por par�metro para ser exibido na
// tela usando fonte de linhas
void DesenhaTextoStroke(void *font, char *string)
{
    // Exibe caractere a caractere
    while(*string)
    glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
// Limpa a janela de visualiza��o com a cor de fundo definida
    glClear(GL_COLOR_BUFFER_BIT); // Define a cor para os textos: preto
    glColor3f(1,0,0); // Posiciona o texto stroke usando transforma��es geom�tricas
    glPushMatrix();
    glTranslatef(-50,0,0);
    glScalef(0.2, 0.2, 0.2); // diminui o tamanho do fonte
    //glRotatef(15, 0,0,1); // rotaciona o texto
    glLineWidth(2); // define a espessura da linha
    DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Teste");
    glPopMatrix(); // Posi��o no universo onde o texto bitmap ser� colocado
    glColor3f(0,0,1);
    //glScalef(0.1, 0.1, 0.1); // diminui o tamanho do fonte
    //glRotatef(15, 0,0,1); // rotaciona o texto
    glRasterPos2f(-20,-20);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,"OpenGl");
    // Exibe o desenha na janela
    glutSwapBuffers();
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
    if (key == 27)
    exit(0);
}

// Inicializa proje��o
void Inicializa(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
    glMatrixMode(GL_MODELVIEW); // Define a cor de fundo de tela como branca
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}// Programa Principal
int main ( int argc, char** argv )
{
    glutInit(&argc,argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Interacao via Mouse"); // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc (Desenha); // Registra a fun��o callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado); // Inicializa��o
    Inicializa(); // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop(); return 0;
}
