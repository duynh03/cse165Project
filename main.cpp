#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//g++ -o run main.cpp -lGL -lglut
//------------------------------------------------------------------------------
int mouseX = 0;
int mouseY = 0;

void passiveMotion(int x, int y) {
    // Update mouse coordinates
    mouseX = x;
    mouseY = y;
    
    // Print mouse coordinates to console
    std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;
    cout << "Window width: "  << glutGet(GLUT_WINDOW_WIDTH) << endl;
    cout << "window Height: " << glutGet(GLUT_WINDOW_HEIGHT) << endl;
    cout << "Mousex: " << (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1 << endl;
    cout << "MouseY: " << -(mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1 << endl;
    glutPostRedisplay(); //refresh where the cursor is so it can be redrawn in the window
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    float xCoordinate = (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
    float yCoordinate = -(mouseY /  (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1;
 
    glEnable(GL_TRIANGLES);
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0); // Green Color
        glVertex2f(xCoordinate, yCoordinate + 0.05);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(xCoordinate - 0.05, yCoordinate - 0.05);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(xCoordinate + 0.05, yCoordinate - 0.05);
    glEnd();
    
    glutSwapBuffers();
}

void testpoint(){
    // glClear(GL_COLOR_BUFFER_BIT);  //if this isnt here, then the dots dont get cleared
    glEnable(GL_POINT);
    glPointSize(5.0); //set size THEN begin, otherwise nothing show on screen
    float xCoordinate = (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
    float yCoordinate = -(mouseY /  (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1;
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);
    // glVertex2f(0.5, 0.5);
    glVertex2d(xCoordinate, yCoordinate);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OpenGL Window");
    
    glutPassiveMotionFunc(passiveMotion); // Register passive motion callback
    // glutDisplayFunc(render);
    glutDisplayFunc(testpoint);
    glutMainLoop();
    return 0;
}

