#ifdef WIN32
    #include <windows.h>
#endif

#include "base.h"
#include <iostream>

using namespace std;

GLint width     = 400,
      height    = 400;

GLfloat ortho2D_minX = -400.0f,
        ortho2D_maxX =  400.0f,
        ortho2D_minY = -400.0f,
        ortho2D_maxY =  400.0f;

int ZOOM = 100;

void display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Eixo X e Y.
    DrawXYAxes();

    // Circulo de pontos.
    glColor3f(0.0, 0.0, 0.0);
    DrawCircle(0, 0, 100, 72, GL_POINTS);

    glutSwapBuffers();
}

void initialize () 
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_LIGHTING);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void zoom_in()
{
    ZOOM = ZOOM + 5 * 100 / 400;
}

void zoom_out()
{
    ZOOM = ZOOM - 5 * 100 / 400;
}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
    switch (key)
    {
        case KEY_ESCAPE:
            exit(0);
        break;

        case 'I':
        case 'i':
            if (ZOOM < 180) // Inverte
            {
                ortho2D_minX += 5.0f;
                ortho2D_maxX -= 5.0f;
                ortho2D_minY += 5.0f;
                ortho2D_maxY -= 5.0f;
                zoom_in();
                cout << "ZOOM: " << ZOOM << "%%\n";
                glutPostRedisplay();
            }
        break;

        case 'O':
        case 'o':
            if (ZOOM > 0)
            {
                ortho2D_minX -= 5.0f;
                ortho2D_maxX += 5.0f;
                ortho2D_minY -= 5.0f;
                ortho2D_maxY += 5.0f;
                zoom_out();
                cout << "ZOOM: " << ZOOM << "%%\n";
                glutPostRedisplay();
            }
        break;

        case 'E':
        case 'e':
            ortho2D_minX += 5.0f;
            ortho2D_maxX += 5.0f;
            glutPostRedisplay();
        break;

        case 'D':
        case 'd':
            ortho2D_minX -= 5.0f;
            ortho2D_maxX -= 5.0f;
            glutPostRedisplay();
        break;

        case 'C':
        case 'c':
            ortho2D_minY -= 5.0f;
            ortho2D_maxY -= 5.0f;
            glutPostRedisplay();
        break;

        case 'B':
        case 'b':
            ortho2D_minY += 5.0f;
            ortho2D_maxY += 5.0f;
            glutPostRedisplay();
        break;

        default:
            cout << "Invalid key pressed: " << key << "\n";
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(300, 250);
    glutInitWindowSize(width, height);

    glutCreateWindow("N2 - Exercicio 2");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    initialize();
    glutMainLoop();

    return 0;
}