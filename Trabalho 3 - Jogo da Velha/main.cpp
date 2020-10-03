#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int matriz[3][3];
int playerturn;
int result;
bool gameover;

void IniciaJogo()
{
	playerturn = 1;

	// Limpa a matriz
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
		    Sleep(50);
			matriz[i][j] = 0;
		}
	}
}

void TeclaPressionada(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		if (gameover == true)
		{
			gameover = false;
			IniciaJogo();
		}
		break;
	case 'n':
		if (gameover == true)
			exit(0);
		break;
	case 27:
		exit(0);
	}
}

//This function is called when the mouse button is pressed and this function puts the x or o on the blank box
void DesenhaSimboloLocalCorreto(int button, int state, int x, int y)
{
	if (gameover == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (playerturn == 1)
		{
			if (matriz[(y - 100) / 200][x / 200] == 0)
			{
				matriz[(y - 100) / 200][x / 200] = 1;
				playerturn = 2;
			}
		}
		else
		{
			if (matriz[(y - 100) / 200][x / 200] == 0)
			{
				matriz[(y - 100) / 200][x / 200] = 2;
				playerturn = 1;
			}
		}
	}
}

void DesenhaTexto(void *font, char *s, float x, float y)
{
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);
}

void DesenhaCirculo(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);

	float radial_factor = cosf(theta);

	float x = r;

	float y = 0;

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
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

void DesenhaLinhas()
{
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);

	// Desenha duas linhas verticais
	glVertex2f(200, 100);
	glVertex2f(200, 680);
	glVertex2f(400, 680);
	glVertex2f(400, 100);

	// Desenha duas linhas horizontais
	glVertex2f(0, 300);
	glVertex2f(600, 300);
	glVertex2f(0, 500);
	glVertex2f(600, 500);
	glEnd();
}

void DesenhaXeO()
{
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			// Desenha X
			if (matriz[i][j] == 1)
			{
				glBegin(GL_LINES);
				glVertex2f(100 + j * 200 - 50, 200 + i * 200 - 50);
				glVertex2f(100 + j * 200 + 50, 200 + i * 200 + 50);
				glVertex2f(100 + j * 200 - 50, 200 + i * 200 + 50);
				glVertex2f(100 + j * 200 + 50, 200 + i * 200 - 50);
				glEnd();
			}
			// Desenha O
			else if (matriz[i][j] == 2)
			{
				glColor3ub(255, 255, 255);
				DesenhaCirculo(100 + j * 200, 200 + i * 200, 70, 50);
			}
		}
	}
}

bool VerificaVitoria()
{
	int i, j;
    int contadorX = 0, contadorO = 0;

	for (i = 0; i <= 2; i++)
	{
		for (j = 1; j <= 2; j++)
		{
			if (matriz[i][0] != 0 && matriz[i][0] == matriz[i][j])
			{
				if (j == 2)
					return true;
			}
			else
				break;
		}
	}

	for (i = 0; i <= 2; i++)
	{
		for (j = 1; j <= 2; j++)
		{
			if (matriz[0][i] != 0 && matriz[0][i] == matriz[j][i])
			{
				if (j == 2)
					return true;
			}
			else
				break;
		}
	}

	for (i = 1; i <= 2; i++)
	{
		if (matriz[0][0] != 0 && matriz[0][0] == matriz[i][i])
		{
			if (i == 2)
				return true;
		}
		else
			break;
	}
	for (i = 1; i <= 2; i++)
	{
		if (matriz[2][0] != 0 && matriz[2][0] == matriz[2 - i][i])
		{
			if (i == 2)
				return true;
		}
		else
			break;
	}
}

bool VerificaEmpate()
{
	int i, j;
	bool draw;
	int contador;

    contador = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (matriz[i][j] != 0) {
                Sleep(10);
                contador++;
			}
		}
	}

	if (contador == 9) {
        return true;
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glColor3ub(255, 255, 255);
	if (playerturn == 1)
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Vez do Jogador 1", 230, 60);
	else
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Vez do Jogador 2", 230, 60);

	DesenhaLinhas();
	DesenhaXeO();

	if (VerificaVitoria() == true)
	{
		// O Jogador que fez o último movimento vence
		if (playerturn == 1)
		{
			// Jogador 2 vence
			gameover = true;
			result = 2;
		}
		else
		{
			// Jogador 1 vence
			gameover = true;
			result = 1;
		}
	}
	else if (VerificaEmpate() == true)
	{
		gameover = true;
		result = 0;
	}

	if (gameover == true)
	{
		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Fim de Jogo", 250, 330);

		if (result == 0)
			DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Ocorreu um Empate!", 220, 405);

		if (result == 1)
			DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Jogador 1 Venceu!!!", 215, 405);

		if (result == 2)
			DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Jogador 2 Venceu!!!", 215, 405);

		DesenhaTexto(GLUT_BITMAP_HELVETICA_18, "Continuar? (s/n)", 235, 480);
	}

	glutSwapBuffers();
}

void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
	IniciaJogo();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 700);
	glutCreateWindow("Trabalho 3 - Jogo da Velha");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(TeclaPressionada);
	glutMouseFunc(DesenhaSimboloLocalCorreto);
	glutIdleFunc(display);
	glutMainLoop();
}
