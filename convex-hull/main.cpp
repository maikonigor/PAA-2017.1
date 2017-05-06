/*
 * main.cpp
 *
 *  Created on: 29 de abr de 2017
 *      Author: maikon
 */

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <list>
#include "convex-hull.h"

#define LARGURA  600		/* Width */
#define ALTURA   600		/* Heigth */


// Qtd máxima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 9

#define CUBE_TEXTURE 0


using namespace std;

// vetor com os números das texturas
GLuint texture_id[MAX_NO_TEXTURES];

double rotationX = 10.0;
double rotationY = 0.0;
GLfloat ex=1.0, ey=1.0;
int last_press_x = 0;
int last_press_y = 0;
double eye[3] = {10.0, 10.0, 50.0};
double pos[4] = {-15,-5,5,15};
vector<int> color;
vector<double> eixoX;
vector<double> eixoY;
vector<Point> solution;
list< vector<Point> > listSolution;
int contador=0;
int contadorColor=0;
int nPoints=50;

void criarEsfera(double x,double y){

    glPushMatrix();
    glScalef(ex, ey, 1.0f);
    glTranslated(x,y,0);

    glColor3f(0.0,0.0, 0.0);
    glutSolidSphere(0.2,15,15);
    glPopMatrix();

}

void criarLinha(double x,double y, double z,double w,int color){

    glColor3f(1.0,color, 1.0);

    glLineWidth(1);
    glScalef(ex, ey, 1.0f);
    glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(z, w);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);

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

void Desenha(void)
{
	/* Limpa a janela de visualização com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);
	glClear (GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(eye[0], eye[1], eye[2], /* eye */
    		  0.0, 5.0, 0.0,		/* look */
    		  0.0, 1.0, 0.0);		/* up */

    /* Rotaciona os objetos para visualizar a 3 dimensão */
	glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */

    for(int i=0; i<nPoints;i++){
        criarEsfera(eixoX[i],eixoY[i]);
    }

    contadorColor=0;
    for(list< vector<Point> >::iterator list_iter = listSolution.begin(); list_iter != listSolution.end(); list_iter++){
      vector<Point> solution = *list_iter;

        for(int i=0; i<solution.size()-1;i++){
                criarLinha(solution[i].x,solution[i].y,solution[i+1].x,solution[i+1].y,color[contadorColor]);
                contadorColor++;
        }
        criarLinha(solution[solution.size()-1].x,solution[solution.size()-1].y,solution[0].x,solution[0].y,color[contadorColor]);
        contadorColor++;
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
		/* Pega a posição atua do mouse */
		last_press_x = x;
		last_press_y = y;
	}

}


void Inicializa (void)
{
    /* Define a cor de fundo da janela de visualização como branca */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* Modo de projecao ortogonal (Default) */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-10, 10, -10, 10, -50, 50);
    gluPerspective(40.0f, ((GLfloat)LARGURA/(GLfloat)ALTURA), 1, 100.0f);


	/* Habilita o depth-buffering para remoção de faces escondidas */
    glEnable(GL_DEPTH_TEST);
    glClear (GL_DEPTH_BUFFER_BIT );


	/* Modelos de Iluminação Defaut */
	glShadeModel(GL_SMOOTH); 		/* Gouraud */

	glEnable(GL_BLEND);

    vector<Point> points(nPoints);
    color = vector<int>(nPoints+100);
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

	for(int i = 0; i < nPoints; i++){
        vector<Point> differences(nPoints);
        vector<Point> solution = convex_hull(points, &differences);
        listSolution.push_back(solution);
        points = differences;
	}

    for(int i = 0; i < color.size(); i++){
        color[i]=1;
    }

	printf("****************************\n");
}

void Teclado(unsigned char key, int x, int y)
{
    switch (key) {

        case 'Z':
        case 'z':
        glClear (GL_DEPTH_BUFFER_BIT );
        color[contador]=0;
        contador++;
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
	glutDisplayFunc(Desenha);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
	glutKeyboardFunc(Teclado);
	glutMainLoop();
}





