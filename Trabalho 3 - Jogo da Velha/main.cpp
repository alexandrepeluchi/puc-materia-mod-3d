#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int matrix[3][3];
int playerturn;
int result;
bool gameover;

//initialize the game
void initgame()
{
	playerturn = 1; //x starts first

	//clear the matrix
	for(int i = 0; i <= 2; i++)
	{
		for(int j = 0; j <= 2; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

//this function is called when keyboard button is pressed
void KeyPress(unsigned char key, int x, int y ){
    switch(key){
		case 's':
			if(gameover == true)
			{
				gameover = false;
				initgame();
			}
			break;
		case 'n':
			if(gameover == true)
				exit(0);
			break;
		case 27:
			exit(0);

	}
}

//This function is called when the mouse button is pressed and this function puts the x or o on the blank box
void click(int button, int state, int x, int y)
{
	if(gameover == false && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(playerturn == 1)
		{
			if(matrix[(y - 100) / 200][x / 200] == 0)
			{
				matrix[(y - 100) / 200][x / 200] = 1;
				playerturn = 2;
			}
		}
		else
		{
			if(matrix[(y - 100) / 200][x / 200] == 0)
			{
				matrix[(y - 100) / 200][x / 200] = 2;
				playerturn = 1;
			}
		}
	}
}

//Used to write text in the opengl window
void drawString (void * font, char *s, float x, float y){
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < strlen (s); i++)
        glutBitmapCharacter (font, s[i]);
}



void DrawCircle(float cx, float cy, float r, int num_segments)
{
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	float x = r;//we start at angle = 0

	float y = 0;

	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy);//output vertex

		//calculate the tangential vector
		//remember, the radial vector is (x, y)
		//to get the tangential vector we flip those coordinates and negate one of them

		float tx = -y;
		float ty = x;

		//add the tangential vector

		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		//correct using the radial factor

		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

//This function is used to draw the 4 lines 2 vertical and 2 horizontal
void drawlines()
{
	glBegin(GL_LINES);
    glColor3ub( 255, 255, 255 );
    //2 vertical lines
    glVertex2f(200, 100);
    glVertex2f(200, 680);
    glVertex2f(400, 680);
    glVertex2f(400, 100);
    //2 horizontal lines
    glVertex2f(0, 300);
    glVertex2f(600, 300);
    glVertex2f(0, 500);
    glVertex2f(600, 500);
	glEnd();
}

//This Function Draw the x and o's
void drawxo()
{
	for(int i = 0; i <= 2; i++)
	{
		for(int j = 0; j <= 2; j++)
		{
			if(matrix[i][j] == 1) //if it is 1 then draw x
			{
				glBegin(GL_LINES);
                glVertex2f(100 + j * 200 - 50, 200 + i * 200 - 50);
                glVertex2f(100 + j * 200 + 50, 200 + i * 200 + 50);
                glVertex2f(100 + j * 200 - 50, 200 + i * 200 + 50);
                glVertex2f(100 + j * 200 + 50, 200 + i * 200 - 50);
				glEnd();
			}
			else if(matrix[i][j] == 2) //if it is 2 then draw o
			{
				glColor3ub( 255, 255, 255 );
                DrawCircle(100 + j * 200, 200 + i * 200, 70, 50);
			}
		}
	}
}

//This function checks if there is any winner
bool checkifwin()
{
	int i, j;

	//check if there are horizontal win i.e if there is any row that has same value
	for(i = 0; i <= 2; i++)
	{
		for(j = 1; j <= 2; j++)
		{
			if(matrix[i][0] != 0 && matrix[i][0] == matrix[i][j])
			{
				if(j == 2)
					return true;
			}
			else
				break;
		}
	}

	//check if there are vertical win i.e if there is any column that has same value
	for(i = 0; i <= 2; i++)
	{
		for(j = 1; j <= 2; j++)
		{
			if(matrix[0][i] != 0 && matrix[0][i] == matrix[j][i])
			{
				if(j == 2)
					return true;
			}
			else
				break;
		}
	}

	//check if there is any diagonal win i.e. if there is any diagonals that has same value
	for(i = 1; i <= 2; i++)
	{
		if(matrix[0][0] != 0 && matrix[0][0] == matrix[i][i])
		{
			if(i == 2)
				return true;
		}
		else
            break;
	}
	for(i = 1; i <= 2; i++)
	{
		if(matrix[2][0] != 0 && matrix[2][0] == matrix[2 - i][i])
		{
			if(i == 2)
				return true;
		}
		else
            break;
	}
}

//This function checks if the match is a draw i.e it returns false if there is atleast one empty box else returns true
bool checkifdraw()
{
	int i, j;
	bool draw;

	for(i = 0; i <= 2; i++)
	{
		for(j = 0; j <= 2; j++)
		{
			if(matrix[i][j] == 0)
				return false;
		}
	}
	return true;
}

//This is the idle call back function
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);
	glColor3ub( 255, 255, 255 );
	if(playerturn == 1)
		drawString(GLUT_BITMAP_HELVETICA_18, "Vez do Jogador 1", 230, 60);
	else
		drawString(GLUT_BITMAP_HELVETICA_18, "Vez do Jogador 2", 230, 60);

	drawlines();
	drawxo();

	if(checkifwin() == true)
	{
		//the player who made the previous move is the winner
		if(playerturn == 1)
		{
			gameover = true;
			result = 2; //player2 wins
		}
		else
		{
			gameover = true;
			result = 1; //player1 wins
		}
	}
	else if(checkifdraw() == true)
	{
		gameover = true;
		result = 0;
	}

	if(gameover == true)
	{
		drawString(GLUT_BITMAP_HELVETICA_18, "Fim de Jogo", 250, 330);

		if(result == 0)
			drawString(GLUT_BITMAP_HELVETICA_18, "Ocorreu um Empate!", 220, 405);

		if(result == 1)
			drawString(GLUT_BITMAP_HELVETICA_18, "Jogador 1 Venceu!!!", 215, 405);

		if(result == 2)
			drawString(GLUT_BITMAP_HELVETICA_18, "Jogador 2 Venceu!!!", 215, 405);

		drawString(GLUT_BITMAP_HELVETICA_18, "Continuar? (s/n)", 235, 480);
	}

	glutSwapBuffers();
}

//This function is called on windows resize
void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, x, y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}

//main function of the program
int main(int argc, char **argv)
{
	initgame();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600, 700);
	glutCreateWindow("Trabalho 3 - Jogo da Velha");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyPress);
	glutMouseFunc(click);
	glutIdleFunc(display);
    glutMainLoop();
}
