/*
 * main.cpp
 *
 *  Created on: 29 de abr de 2017
 *      Author: maikon
 */

//#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <list>
#include "convex-hull.h"

#define LARGURA  600		/* Width */
#define ALTURA   600		/* Heigth */


// Qtd m�xima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 9

#define CUBE_TEXTURE 0


using namespace std;
void Desenha(void);

// vetor com os n�meros das texturas
GLuint texture_id[MAX_NO_TEXTURES];

double rotationX = 10.0;
double rotationY = 0.0;
GLfloat ex=1.0, ey=1.0;
int last_press_x = 0;
int last_press_y = 0;
double eye[3] = {10.0, 10.0, 50.0};
double pos[4] = {-15,-5,5,15};

vector<double> eixoX;
vector<double> eixoY;
vector<Point> solution;
vector<Point> contatenated;
list< vector<Point> > listSolution;
int contador=-1;
int contadorColor=0;
int nPoints=50;

int event=1;

int color [100][3];

int colors[9][3] = {
		{0.6, 0.8, 1.0}, //white
		{0.0,0.0,0.0}, //black
		{1.0, 0.0, 0.0}, //red
		{1.0, 1.0, 0.0}, //yellow
		{0.0, 1.0, 0.0}, //green
		{0.0, 1.0, 1.0}, //cyan
		{0.0, 0.0, 1.0}, //blue
		{1.0, 0.0, 1.0}, //magenta
		{0.5, 0.5, 0.5} // Gray
};

void criarEsfera(double x,double y, int colorNumer){

    glPushMatrix();
    glScalef(ex, ey, 1.0f);
    glTranslated(x,y,0);

    glColor3f(colors[colorNumer][0], colors[colorNumer][1], colors[colorNumer][2]);
    glutSolidSphere(0.2,15,15);
    glPopMatrix();

}

void criarLinha(double x,double y, double z, double w, int colorNumer){

    glColor3f(colors[colorNumer][0], colors[colorNumer][1], colors[colorNumer][2]);
//	glColor3f(1.0,color,1.0);
    glLineWidth(1);
    glScalef(ex, ey, 1.0f);
    glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(z, w);
    glEnd();

//    glColor3f(1.0, 1.0, 1.0);

}

void Desenha_Eixos_Coordenados()
{
	/* Desenha Eixo +Y */
	glColor3f(1.0, 0.0, 0.0); /* RED */
	glBegin(GL_LINES);
		glVertex3i(-25, -ALTURA, 0);
		glVertex3i(0, ALTURA, 0);
	glEnd();

	/* Desenha Eixo +X */
	glColor3f(0.0, 0.0, 1.0); /* BLUE */
	glBegin(GL_LINES);
		glVertex3i(-LARGURA, -25, 0);
		glVertex3i(LARGURA, 0, 0);
	glEnd();
}

void Desenha_solucao_concatenada(){
	/* Limpa a janela de visualiza��o com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);
	glClear (GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(eye[0], eye[1], eye[2], /* eye */
			  0.0, 5.0, 0.0,		/* look */
			  0.0, 1.0, 0.0);		/* up */

	/* Rotaciona os objetos para visualizar a 3 dimens�o */
	glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */

	contadorColor = 1;
	for(int i=0; i<contatenated.size() -1;i++){
	printf("pontos %f, %f\n", contatenated[i].x,contatenated[i].y);
		criarEsfera(contatenated[i].x,contatenated[i].y, contadorColor);
		criarEsfera(contatenated[i+1].x,contatenated[i+1].y, contadorColor);
		criarLinha(contatenated[i].x,contatenated[i].y,contatenated[i+1].x,contatenated[i+1].y, contadorColor);
	}
	criarLinha(contatenated[contatenated.size()-1].x,contatenated[contatenated.size()-1].y,contatenated[0].x,contatenated[0].y, contadorColor);

	Desenha_Eixos_Coordenados();
	glFlush();
}

void Desenha(void)
{
	printf("Função Desenha\n");
	/* Limpa a janela de visualiza��o com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);
	glClear (GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(eye[0], eye[1], eye[2], /* eye */
    		  0.0, 5.0, 0.0,		/* look */
    		  0.0, 1.0, 0.0);		/* up */

    /* Rotaciona os objetos para visualizar a 3 dimens�o */
	glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */

    int num = 0;
    for(list< vector<Point> >::iterator list_iter = listSolution.begin(); list_iter != listSolution.end(); list_iter++){
    	if(contador < 0 and contador > listSolution.size()){

    		break;
    	}

    	if(num <= contador){
		   vector<Point> solution = *list_iter;

			for(int i=0; i<solution.size() -1;i++){
				criarEsfera(solution[i].x,solution[i].y, contadorColor);
				criarEsfera(solution[i+1].x,solution[i+1].y, contadorColor);
				criarLinha(solution[i].x,solution[i].y,solution[i+1].x,solution[i+1].y, contadorColor);
			}
			criarLinha(solution[solution.size()-1].x,solution[solution.size()-1].y,solution[0].x,solution[0].y, contadorColor);
			contadorColor++;
		}
    	num++;
	}

    contadorColor = 0;

    for(int i=0; i<nPoints;i++){
		criarEsfera(eixoX[i],eixoY[i],1);
	}
    Desenha_Eixos_Coordenados();
	glFlush();


}

void Mouse_Motion(int x, int y)
{
    glClear (GL_DEPTH_BUFFER_BIT );
	 //if(rotationX>-35 && rotationX<60){
    rotationX += (double)(x - last_press_x);
	 //}
	rotationY += (double)(y - last_press_y);

	last_press_x = x;
	last_press_y = y;

	glutPostRedisplay();
}

void Mouse_Press(int button, int state, int x, int y)
{
    glClear (GL_DEPTH_BUFFER_BIT );
	if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		/* Pega a posi��o atua do mouse */
		last_press_x = x;
		last_press_y = y;
	}

}

void print_arrays(vector<Point>  pts, vector<Point>  diff){

	printf("Points\n");

	for(int i = 0; i < pts.size(); i++){
		printf("[%f , %f] ",pts[i].x, pts[i].y);
	}
	printf("\n");

	printf("Difference\n");
	for(int i = 0; i < diff.size(); i++){
		printf("[%f , %f] ",diff[i].x, diff[i].y);
	}

}

void Inicializa (void)
{
    /* Define a cor de fundo da janela de visualiza��o como branca */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* Modo de projecao ortogonal (Default) */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10, 10, -10, 10, -50, 50);
    gluPerspective(40.0f, ((GLfloat)LARGURA/(GLfloat)ALTURA), 1, 100.0f);


	/* Habilita o depth-buffering para remo��o de faces escondidas */
    glEnable(GL_DEPTH_TEST);
    glClear (GL_DEPTH_BUFFER_BIT );


	/* Modelos de Ilumina��o Defaut */
	glShadeModel(GL_SMOOTH); 		/* Gouraud */

	glEnable(GL_BLEND);

    vector<Point> points(nPoints);
//    color = vector<int>(nPoints+100);
    eixoX = vector<double>(nPoints);
    eixoY = vector<double>(nPoints);

    srand(time(NULL));

   Point p;
   eixoX[0]= 0;
   eixoY[0]= 0;
   p.x = 0;
   p.y = 0;
   points[0]=p;

	for(int i=1; i<nPoints;i++){
        eixoX[i]= (rand() % 27) - 10;
        eixoY[i]= (rand() % 30) - 10;
        Point p;
        p.x = eixoX[i];
        p.y = eixoY[i];
        cout<<eixoX[i]<<" ---- "<<eixoY[i]<<endl;
        points[i] = p;

	}


	convex_hull_1(points, &listSolution);
	contatenated = concat_solutions(&listSolution);

	printf("****************************\n");
	Desenha();
}

void teste(){
	printf("Função teste\n");
}
void Teclado(unsigned char key, int x, int y)
{
    switch (key) {

        case 'z':
			glClear (GL_DEPTH_BUFFER_BIT );
			contador++;
			event = 1;
			Desenha();
        break;
        case 'c':
        	event = 2;
        	Desenha_solucao_concatenada();
        	printf("Apertou o c\n");

		break;


    }
    glutPostRedisplay();
}


/* Programa Principal */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Trabalho PAA");
	cout<<"Digite o numero de vertices:"<<endl;
	cin>> nPoints;
    Inicializa();
//    if(event == 1)
//    	glutDisplayFunc(Desenha);
//    else
//    	glutDisplayFunc(Desenha_solucao_concatenada);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
	glutKeyboardFunc(Teclado);
	glutMainLoop();
}





