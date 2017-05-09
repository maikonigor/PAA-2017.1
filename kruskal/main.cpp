/* Código para a criação de projeções
 * perspectivas e ortonais no OpenGL.
 * É mostrado como especificar uma câmera
 * e desenhar primitivas 3D do opengl */
//#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <list>
#include <fstream>
#include <vector>
#include "tgaload.h"
#include "kruskal.cpp"


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
int value[8] = {1,2,3,4,5,6,7,8};
vector<double> valorAresta;
vector<double> eixoX;
vector<double> eixoY;
vector<double> eixoZ;
vector<double> aleatorio;
vector<int> color;
vector<int> colorP;
int countColor=0;
int contador=0;
int contadorColor=0;
int nPoints=0;
Grafo g(1);

int arestas=1;
vector<double> vet1;
vector<double> vet2;
char cam[1024];

void criarCubo(int x,int y, int val)
{

    glBindTexture ( GL_TEXTURE_2D, texture_id[val] );

    glPushMatrix();
    glScalef(ex, ey, 1.0f);
    glTranslated(x,y,0);

    glColor3f(0.5,0.5, 0.5);
    glBegin(GL_QUADS);

	// top

    glVertex3f(-1.5f, 1.5f, 1.5f);
	glVertex3f(1.5f, 1.5f, 1.5f);
	glVertex3f(1.5f, 1.5f, -1.5f);
	glVertex3f(-1.5f, 1.5f, -1.5f);

    //front
    glVertex3f(1.5f, -1.5f, 1.5f);
    glVertex3f(1.5f, 1.5f, 1.5f);
    glVertex3f(-1.5f, 1.5f, 1.5f);
    glVertex3f(-1.5f, -1.5f, 1.5f);

    //right
    glVertex3f(1.5f, 1.5f, -1.5f);
	glVertex3f(1.5f, 1.5f, 1.5f);
	glVertex3f(1.5f, -1.5f, 1.5f);
	glVertex3f(1.5f, -1.5f, -1.5f);

    //left
    glVertex3f(-1.5f, 1.5f, 1.5f);
	glVertex3f(-1.5f, 1.5f, -1.5f);
	glVertex3f(-1.5f, -1.5f, -1.5f);
	glVertex3f(-1.5f, -1.5f, 1.5f);

	//under
    glVertex3f(-1.5f, -1.5f, 1.5f);
	glVertex3f(1.5f, -1.5f, 1.5f);
	glVertex3f(1.5f, -1.5f, -1.5f);
	glVertex3f(-1.5f, -1.5f, -1.5f);

    //back
    glVertex3f(1.5f, -1.5f, -1.5f);
    glVertex3f(1.5f, 1.5f, -1.5f);
    glVertex3f(-1.5f, 1.5f, -1.5f);
    glVertex3f(-1.5f, -1.5f, -1.5f);

	glEnd();
    glPopMatrix();

}

void drawStrokeText(char str,int x,int y,int z, double scala1,double scala2)
{
	  glPushMatrix();
	  glTranslatef(x, y,z);
	  glScalef(scala1,scala2,z);
     glutStrokeCharacter(GLUT_STROKE_ROMAN , str);
	  glPopMatrix();
}

void criarLinha(int x,int y, int z,int w, int color,int value){

    glColor3f(0.0,color, 0.0);

    char cBuffer[5] = {0};
    //itoa(value,cBuffer, 10);
   snprintf(cBuffer, sizeof(cBuffer), "%d", value);

    drawStrokeText(cBuffer[0],((x +y)/2)-2,((z+w)/2)+1,0,0.018,0.015);
    glLineWidth(5);
    glScalef(ex, ey, 1.0f);
    glBegin(GL_LINES);
	glVertex2i(x, z);
	glVertex2i(y, w);
    glEnd();

}

void criarLinha(int x,int z,int y, int w,int color, int value, float scala1, float scala2){

    glColor3f(0.0,color, 0.0);

    char cBuffer[5] = {0};
    //itoa(value,cBuffer, 10);
    snprintf(cBuffer, sizeof(cBuffer), "%d", value);
    drawStrokeText(cBuffer[0],((x +y)/2),((z+w)/2),0,scala1,scala2);
    glLineWidth(1);
    glScalef(ex, ey, 1.0f);
    glBegin(GL_LINES);
	glVertex2i(x, z);
	glVertex2i(y, w);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);

}

void criarEsfera(double x,double y){

    glPushMatrix();
    glScalef(ex, ey, 1.0f);
    glTranslated(x,y,0);

    glColor3f(0.0,0.0, 0.0);
    glutSolidSphere(0.2,15,15);
    glPopMatrix();

}

void Desenha(void)
{
	/* Limpa a janela de visualização com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(eye[0], eye[1], eye[2], /* eye */
    		  0.0, 5.0, 0.0,		/* look */
    		  0.0, 1.0, 0.0);		/* up */

    /* Rotaciona os objetos para visualizar a 3 dimensão */
	glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */

    criarCubo(pos[0],10,value[0]-1);
    criarCubo(pos[1],10,value[1]-1);
    criarCubo(pos[2],10,value[2]-1);
    criarCubo(pos[3],10,value[3]-1);

    criarCubo(pos[0],0,value[4]-1);
    criarCubo(pos[1],0,value[5]-1);
    criarCubo(pos[2],0,value[6]-1);
    criarCubo(pos[3],0,value[7]-1);

    criarLinha(pos[0],pos[1],10,10,color[0],valorAresta[0]);
    criarLinha(pos[1],pos[2],10,10,color[1],valorAresta[1]);
    criarLinha(pos[2],pos[3],10,10,color[2],valorAresta[2]);

    criarLinha(pos[0],pos[1],0,0,color[3],valorAresta[3]);
    criarLinha(pos[1],pos[2],0,0,color[4],valorAresta[4]);
    criarLinha(pos[2],pos[3],0,0,color[5],valorAresta[5]);

    criarLinha(pos[0],pos[0],10,0,color[6],valorAresta[6]);
    criarLinha(pos[1],pos[1],10,0,color[7],valorAresta[7]);
    criarLinha(pos[2],pos[2],10,0,color[8],valorAresta[8]);
    criarLinha(pos[3],pos[3],10,0,color[9],valorAresta[9]);

    criarLinha(pos[1],pos[0],10,0,color[10],valorAresta[10]);
    criarLinha(pos[2],pos[1],10,0,color[11],valorAresta[11]);
    criarLinha(pos[3],pos[2],10,0,color[12],valorAresta[12]);

	/* Executa os comandos OpenGL */
	glFlush();

}

void Desenha2(void)
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

    srand(time(NULL));
    for(int i=0; i<nPoints;i++){
        if(i+1!=nPoints){
            criarLinha(eixoX[i],eixoY[i],eixoX[i+1],eixoY[i+1],color[i],valorAresta[i],0.010f,0.008f);
        }else{
         criarLinha(eixoX[0],eixoY[0],eixoX[nPoints-1],eixoY[nPoints-1],color[nPoints-1],valorAresta[nPoints-1],0.010f,0.008f);
        }

    }

    for(int i=nPoints; i<nPoints*2;i++){
        criarLinha(eixoX[i-nPoints],eixoY[i-nPoints],eixoX[aleatorio[i-nPoints]],eixoY[aleatorio[i-nPoints]],color[i],valorAresta[i],0.010f,0.008f);
    }

	glFlush();

}

void Desenha3(void)
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

    for(int i=0; i<arestas;i++){
        criarLinha(eixoX[vet1[i]-1],eixoY[vet1[i]-1],eixoX[vet2[i]-1],eixoY[vet2[i]-1],color[i],valorAresta[i],0.010f,0.008f);
    }

	glFlush();

}

void DesenhaInit(void)
{
	/* Limpa a janela de visualização com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(eye[0], eye[1], eye[2], /* eye */
    		  0.0, 5.0, 0.0,		/* look */
    		  0.0, 1.0, 0.0);		/* up */

    /* Rotaciona os objetos para visualizar a 3 dimensão */
	glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */

	/* Executa os comandos OpenGL */
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

void Inicializa1 (void)
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

	valorAresta = vector<double>(13);
	colorP = vector<int>(13);

    srand(time(NULL));
    for(int i=0; i<valorAresta.size();i++){
        int t = rand() % 8 + 1;
        valorAresta[i] = t;
        colorP[i]=-1;
    }

    g = Grafo(13); // grafo

	// adiciona as arestas
	g.adicionarAresta(1, 2, valorAresta[0],0);
	g.adicionarAresta(2, 3, valorAresta[1],1);
	g.adicionarAresta(3, 4, valorAresta[2],2);

	g.adicionarAresta(5, 6, valorAresta[3],3);
	g.adicionarAresta(6, 7, valorAresta[4],4);
	g.adicionarAresta(7, 8, valorAresta[5],5);

	g.adicionarAresta(1, 5, valorAresta[6],6);
	g.adicionarAresta(2, 6, valorAresta[7],7);
	g.adicionarAresta(3, 7, valorAresta[8],8);
	g.adicionarAresta(4, 8, valorAresta[9],9);

	g.adicionarAresta(2, 5, valorAresta[10],10);
	g.adicionarAresta(3, 6, valorAresta[11],11);
	g.adicionarAresta(4, 7, valorAresta[12],12);

    colorP = g.kruskal(colorP); // roda o algoritmo de Kruskal

}

void Inicializa2 (void)
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
    aleatorio = vector<double>(nPoints);
    valorAresta = vector<double>(nPoints*2);
    colorP = vector<int>(nPoints*2);
    color = vector<int>(nPoints*2);
    g = Grafo(nPoints*2); // grafo
    eixoX = vector<double>(nPoints);
    eixoY = vector<double>(nPoints);

    srand(time(NULL));
    for(int i=0; i<nPoints;i++){
        eixoX[i]= (rand() % 27) - 15;
        eixoY[i]= (rand() % 30) - 10;
    }


    for(int i=0; i<nPoints;i++){
        int t;

        do{
        t =  rand() % nPoints;

        if(i==0){
            t=rand() % 2+2;
        }

        if(i==nPoints){
            t=rand() % 2+2;
        }

        }while( t==i || t==i+1 || t==i-1 );
        aleatorio[i] = t;

	}

	for(int i=0; i<nPoints*2;i++){
        valorAresta[i] = rand() % 8 + 1;
        color[i]=0;
        colorP[i]=-1;
	}

	for(int i=0; i<nPoints;i++){
        if(i+1!=nPoints){
           g.adicionarAresta(i,i+1, valorAresta[i],i);
        }else{
            g.adicionarAresta(0,nPoints-1,valorAresta[i],i);
        }
    }

    for(int i=nPoints; i<nPoints*2;i++){
        g.adicionarAresta(i-nPoints,aleatorio[i-nPoints],valorAresta[i],i);
    }

    colorP = g.kruskal(colorP); // roda o algoritmo de Kruskal

}

void Teclado(unsigned char key, int x, int y)
{
    switch (key) {

        case 'Z':
        case 'z':
        glClear (GL_DEPTH_BUFFER_BIT );
        if(countColor<colorP.size()){
            if(colorP[countColor]!=-1){
                color[colorP[countColor]]=1;
            }
            countColor++;
        }else{
        cout<<"finish"<<endl;
        }
        break;


    }
    glutPostRedisplay();
}

void Inicializa3(void)
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


  ifstream file(cam);

  if (!file) {
    cout<<"erro leitura"<<endl;
  }

  file >> nPoints;
  file >> arestas;

  g = Grafo(arestas); // grafo
  valorAresta = vector<double>(arestas);
  colorP = vector<int>(arestas);
  color = vector<int>(arestas);
  vet1 = vector<double>(arestas);
  vet2 = vector<double>(arestas);
  eixoX = vector<double>(nPoints);
  eixoY = vector<double>(nPoints);

  int cont=0;
  int value;
  int value2;
  int value3;

  	for(int i=0; i<arestas;i++){
        valorAresta[i] = rand() % 8 + 1;
        color[i]=0;
        colorP[i]=-1;
	}


  while (true) {
    if (!(file >> vet1[cont])) {
      break;
    }
    file >> vet2[cont];
    file >> valorAresta[cont];
    g.adicionarAresta(vet1[cont],vet2[cont],valorAresta[cont],cont);
    cont++;
  }

    colorP = g.kruskal(colorP); // roda o algoritmo de Kruskal

    srand(time(NULL));
    for(int i=0; i<nPoints;i++){
        eixoX[i]= (rand() % 27) - 15;
        eixoY[i]= (rand() % 30) - 10;
    }

}

void Janela(int opcao)
{
	switch(opcao){

		case 0:
        countColor=0;
        color = vector<int>(13);
        Inicializa1();
        glutDisplayFunc(Desenha);
        break;

        case 1:
        cout<<"Digite o numero de vertices:"<<endl;
        cin>>nPoints;
        countColor=0;
        Inicializa2();
        glutDisplayFunc(Desenha2);
        break;

        case 2:

        string caminho;

        cout<<"Digite o caminho do arquivo:"<<endl;
        cin>>caminho;
        strcpy(cam, caminho.c_str());
        countColor=0;
        Inicializa3();
        glutDisplayFunc(Desenha3);
        break;


	}
	glutPostRedisplay();
}

void CriarMenu()
{
	/* Cria um menu cujas as opções serão gerenciadas pela funcao "Janela" */
	glutCreateMenu(Janela);

	/* Cria entradas nesse menu */
	glutAddMenuEntry("Usar estrutura", 0);
	glutAddMenuEntry("Aleatorio", 1);
	glutAddMenuEntry("Ler Arquivo", 2);

	/* Indica qual o botao que acionará o menu */
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/* Programa Principal */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Trabalho PAA");
	glutDisplayFunc(DesenhaInit);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
	glutKeyboardFunc(Teclado);
	CriarMenu();
	glutMainLoop();
}
