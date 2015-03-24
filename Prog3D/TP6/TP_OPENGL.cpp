///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synthèse d'images - Modélisation géométrique
// Auteur : Gilles Gesquière
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de créer des formes de bases.
// La forme représentée ici est un polygone blanc dessiné sur un fond rouge
///////////////////////////////////////////////////////////////////////////////

//g++ *.cpp -o gl -lglut -lGL -lGLU
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "point.h"
#include "vector.h"
#include "../TP4/oGl3.h"
#include "../TP4/figureGl.h"
#include "voxel.h"
#include "oGl6.h"

/* Dans les salles de TP, vous avez généralement accès aux glut dans C:\Dev. Si ce n'est pas le cas, téléchargez les .h .lib ...
Vous pouvez ensuite y faire référence en spécifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>.
Si vous mettez glut dans le répertoire courant, on aura alors #include "glut.h"
*/

#include <GL/glut.h>

// Définition de la taille de la fenêtre
#define WIDTH  480
#define HEIGHT 480

// Définition de la couleur de la fenêtre
#define RED   1
#define GREEN 1
#define BLUE  1
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27
#define KEY_PLUS 112
#define KEY_MOINS 109

GLint winWidth=600, winHeight=600;
GLfloat eyeX=0.0, eyeY=0.0, eyeZ=2.0;
GLfloat theta=270.0, phi=180.0;
GLfloat upX=0.0, upY=1.0, upZ=0.0;
GLfloat r=2.0;
static int nbMeri = 8;
static int nbPara = 8;


// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);




// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL()
{
  glClearColor(RED, GREEN, BLUE, ALPHA);
  glEnable(GL_DEPTH_TEST);    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1,1,-1,1,.6,300);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);   // set to Model View before drawing
  glLoadIdentity();
  gluLookAt(eyeX,eyeY,eyeZ,0,0,0,upX, upY, upZ);

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations
  // que l'on veut dessiner
  render_scene();
  glutSwapBuffers();
  // trace la scène grapnique qui vient juste d'être définie
  glFlush();
}

// fonction de call-back pour le redimensionnement de la fenêtre

GLvoid window_reshape(GLsizei width, GLsizei height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
  // possible de changer la taille de l'objet dans la fenêtre. Augmentez ces valeurs si l'objet est
  // de trop grosse taille par rapport à la fenêtre.
  glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue
  glMatrixMode(GL_MODELVIEW);
}

void eyePosition( void ) {
  eyeX = r * sin(theta*0.0174532) * sin(phi*0.0174532);
  eyeY = r * cos(theta*0.0174532);
  eyeZ = r * sin(theta*0.0174532) * cos(phi*0.0174532);
  GLfloat dt=1.0;
  GLfloat eyeXtemp = r * sin(theta*0.0174532-dt) * sin(phi*0.0174532);
  GLfloat eyeYtemp = r * cos(theta*0.0174532-dt);
  GLfloat eyeZtemp = r * sin(theta*0.0174532-dt) * cos(phi*0.0174532); 

  upX=eyeXtemp-eyeX;
  upY=eyeYtemp-eyeY;
  upZ=eyeZtemp-eyeZ;

  glutPostRedisplay();
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
  switch (key) { 
    case KEY_ESC:
    exit(1);
    break;
    case KEY_PLUS:
    nbMeri += 1;
    nbPara += 1;
    glutPostRedisplay();
    break;
    case KEY_MOINS:
    nbMeri -= 1;
    nbPara -= 1;
    glutPostRedisplay();
    break;

    default:
    printf ("La touche %d n est pas active.\n", key);
    break;

  }
}


void onMouseMove(int x, int y) { 
// Mouse point to angle conversion
   theta = (360.0/(double)winHeight)*(double)y*1.0; //3.0 rotations possible
   phi = (360.0/(double)winWidth)*(double)x*1.0; 
// Restrict the angles within 0~360 deg (optional)
   if(theta > 360)theta = fmod((double)theta,360.0);
   if(phi > 360)phi = fmod((double)phi,360.0);
   eyePosition();
}


//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{

  Point* p1 = new Point(0,0,0);
  //displayVoxel(p1,4);
  //Voxel* l = new Voxel(p1,20);
  Point* p2 = new Point(0,15,0);
  Vector* axisVector = new Vector(p2->getX()-p1->getX(),p2->getY()-p1->getY(),p2->getZ()-p1->getZ());
  Point* p3 = new Point(0,7.5,0);

  // Initialisation
  glColor3f(0,0,0);
  glBegin(GL_LINES);
  glVertex3f(0,0,0);
  glVertex3f(30,0,0);
  glVertex3f(0,0,0);
  glVertex3f(0,30,0);
  glVertex3f(0,0,0);
  glVertex3f(0,0,30);
  glEnd();

 




}

int main(int argc, char **argv)
{
  // initialisation  des paramètres de GLUT en fonction
  // des arguments sur la ligne de commande
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);

  // définition et création de la fenêtre graphique, ainsi que son titre
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Premier exemple : carré");

  // initialisation de OpenGL et de la scène
  initGL();
  init_scene();

  // choix des procédures de callback pour
  // le tracé graphique
  glutDisplayFunc(&window_display);
  // le redimensionnement de la fenêtre
  glutReshapeFunc(&window_reshape);
  glutPassiveMotionFunc(onMouseMove);
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();

  return 1;
}