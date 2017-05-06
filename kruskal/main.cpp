/* Código para a criação de projeções
 * perspectivas e ortonais no OpenGL.
 * É mostrado como especificar uma câmera
 * e desenhar primitivas 3D do opengl */


#include <windows.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
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
int valorAresta[13] = {6,5,6,1,3,3,1,2,4,7,2,5,5};


int color[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
int colorP[13] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int countColor=0;
int z=2;
int n=8;
int p=2;
int orden =0;
int movi =1;

double y=10;


void initTexture (void)
{

	// Habilita o uso de textura
	glEnable ( GL_TEXTURE_2D );

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

	// Define quantas texturas serão usadas no programa
	glGenTextures (9, texture_id);  // 1 = uma textura;
									// texture_id = vetor que guardas os números das texturas

	// Define o número da textura do cubo.
	texture_id[CUBE_TEXTURE] = 1001;

	// Define que tipo de textura será usada
	// GL_TEXTURE_2D ==> define que será usada uma textura 2D (bitmaps)
	// texture_id[CUBE_TEXTURE]  ==> define o número da textura


    image_t temp_image;
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/1.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/2.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/3.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

	glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/4.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

	glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/5.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

	glBindTexture ( GL_TEXTURE_2D, texture_id[5] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/6.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

	glBindTexture ( GL_TEXTURE_2D, texture_id[6] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/7.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );

    glBindTexture ( GL_TEXTURE_2D, texture_id[7] );
	tgaLoad  ( "C:/Users/Raphael/Desktop/trabalho PAA - 1/imagens/8.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY );


}

void criarCubo(int x,int y, int val)
{

    glBindTexture ( GL_TEXTURE_2D, texture_id[val] );

    glPushMatrix();
    glScalef(ex, ey, 1.0f);
    glTranslated(x,y,0);

    glBegin(GL_QUADS);

	// top
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, -1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, -1.5f);

    //front
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);

    //right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, -1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, -1.5f);

    //left
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, -1.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, -1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);

	//under
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, -1.5f, -1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.5f, -1.5f);

    //back
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, -1.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, -1.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, -1.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, -1.5f);

	glEnd();
    glPopMatrix();

}

void drawStrokeText(char str,int x,int y,int z)
{
	  glPushMatrix();
	  glTranslatef(x, y,z);
	  glScalef(0.018f,0.015f,z);
     glutStrokeCharacter(GLUT_STROKE_ROMAN , str);
	  glPopMatrix();
}


void criarLinha(int x,int y, int z,int w, int color,int value){

    glColor3f(0.0,color, 0.0);

    char cBuffer[5] = {0};
    itoa(value,cBuffer, 10);

    drawStrokeText(cBuffer[0],((x +y)/2)-2,((z+w)/2)+1,0);
    glLineWidth(5);
    glScalef(ex, ey, 1.0f);
    glBegin(GL_LINES);
	glVertex2i(x, z);
	glVertex2i(y, w);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);

}

void Desenha(void)
{
	/* Limpa a janela de visualização com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    /* Especifica uma Câmera com:
     * olho = (0, 0, 30)
     * olhar = (0, 0, 0)
     * up = (0, 1, 0) */
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

void Janela(int opcao)
{
	switch(opcao){
		case 0:
        break;
        case 1:
        break;
	}
	glutPostRedisplay();
}

void CriarMenu()
{
	/* Cria um menu cujas as opções serão gerenciadas pela funcao "Janela" */
	glutCreateMenu(Janela);

	/* Cria entradas nesse menu */
	glutAddMenuEntry("Ler Arquivo", 0);
	glutAddMenuEntry("Aleatorio", 1);

	/* Indica qual o botao que acionará o menu */
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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

    /*************** Parâmetros de Iluminação ***************/

	/* Habilita o uso de iluminação */
	//glEnable(GL_LIGHTING);

	/* Habilita a luz de número 0 */
	//glEnable(GL_LIGHT0);


	/* Habilita o depth-buffering para remoção de faces escondidas */
    glEnable(GL_DEPTH_TEST);
    glClear (GL_DEPTH_BUFFER_BIT );

	/* Modelos de Iluminação Defaut */
	glShadeModel(GL_SMOOTH); 		/* Gouraud */

    srand(time(NULL));
    for(int i=0; i<8;i++){
        int t = rand() % 8 + 1;
        valorAresta[i] = t;
    }

    Grafo g(13); // grafo

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

    g.kruskal(colorP); // roda o algoritmo de Kruskal

}

void Teclado(unsigned char key, int x, int y)
{
    switch (key) {

        case 'Z':
        case 'z':
        glClear (GL_DEPTH_BUFFER_BIT );
        if(countColor<13){
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

/* Programa Principal */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Trabalho PAA");
	glutDisplayFunc(Desenha);
	glutMouseFunc(Mouse_Press);
	glutMotionFunc(Mouse_Motion);
	glutKeyboardFunc(Teclado);
    initTexture ();
	Inicializa();
	CriarMenu();
	glutMainLoop();
}
