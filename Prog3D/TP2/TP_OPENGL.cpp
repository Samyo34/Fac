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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "point.h"
#include "vector.h"
#include "oGl.h"

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


// Entêtes de fonctions
void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height);
GLvoid window_key(unsigned char key, int x, int y);


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
  // la gestion des événements clavier
  glutKeyboardFunc(&window_key);

  // la boucle prinicipale de gestion des événements utilisateur
  glutMainLoop();

  return 1;
}

// initialisation du fond de la fenêtre graphique : noir opaque
GLvoid initGL()
{
  glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir à stocker des variables de votre programme
// à initialiser
void init_scene()
{
}

// fonction de call-back pour l´affichage dans la fenêtre

GLvoid window_display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glLoadIdentity();

  // C'est l'endroit où l'on peut dessiner. On peut aussi faire appel
  // à une fonction (render_scene() ici) qui contient les informations
  // que l'on veut dessiner
  render_scene();

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
  glOrtho(-2.0, 5.0, -2.0, 5.0, -2.0, 5.0);

  // toutes les transformations suivantes s´appliquent au modèle de vue
  glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des événements clavier

GLvoid window_key(unsigned char key, int x, int y)
{
  switch (key) {
  case KEY_ESC:
    exit(1);
    break;

  default:
    printf ("La touche %d n´est pas active.\n", key);
    break;
  }
}



//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene()
{
//Définition de la couleur
 glColor3f(0, 0, 0);

  //  Nous créons ici un polygone. Nous pourrions aussi créer un triangle ou des lignes. Voir ci-dessous les parties
  // en commentaires (il faut commenter le bloc qui ne vous intéresse pas et décommenter celui que vous voulez tester.

    Point a(3,1,1);
    Point b(4,3,1);
    Point c(4.5,3.5,1);
    Point c2;
    c2 = c.projectOnLine(a,b);

   // Création de deux lignes
    glLineWidth(4);
    glBegin(GL_LINES);
        glVertex3f(a.getX(), a.getY(), a.getZ());
        glVertex3f(b.getX(), b.getY(), b.getZ());
    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
        glColor3f(1.0,0.6,0);
        glVertex3f(c.getX(),c.getY(),c.getZ());
        glColor3f(0.5,0.4,0.84);
        glVertex3f(c2.getX(),c2.getY(),c2.getZ());
    glEnd();




    Point *p0 = new Point(0,0,0);
    Point *p1 = new Point(2,0,0);
    Vector *v0 = new Vector(1,1,0);
    Vector *v1 = new Vector(1,-1,0);
    Point ** pts = HermiteCubicCurve(p0,p1,v0,v1,50);
    //drawCurve(pts,50);

    Point** pts2 = new Point*[4];
    pts2[0]=new Point(0,0,0);
    pts2[1]=new Point(1,2,0);
    pts2[2]=new Point(3,3,0);
    pts2[3]=new Point(2,2,0);

    Point** pts3 = BezierCurveByBernstein(pts2, 4, 10);
    drawCurve(pts3,10);


    Point** pts4 = new Point*[5];
    pts4[0]=new Point(1,1,0);
    pts4[1]=new Point(1,2,0);
    pts4[2]=new Point(3,0,0);
    pts4[3]=new Point(3,2,0);
    pts4[4]=new Point(3,3,0);
    Point** pts5= BezierCurveByCasteljau(pts4,5,11);
    glColor3f(0.8,1.0,0.4);
    drawCurve(pts5,11);
    glColor3f(0.0,0.0,0.0);
    drawCurve(pts4,5);
 
  





 // création d'un polygone
/*	glBegin(GL_POLYGON);
        glVertex3f(-1, -1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(1, 1, 0);
        glVertex3f(-1, 1, 0);
    glEnd();
*/


/*
// création d'un triangle
    glBegin(GL_TRIANGLES);
        glVertex3f(-1, -1, 0);
        glVertex3f(1, -1, 0);
        glVertex3f(1, 1, 0);
    glEnd();
*/



}
