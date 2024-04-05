#include <GL/gl.h>
#include <GL/freeglut.h>
#include <iostream>
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
    // Render OpenGL scene here
    
    // Example: Draw a point at the current mouse position
    glEnable(GL_POINT);
    glColor3f(1.0, 0.0, 0.0); // Red color
    glPointSize(1.0); // Set point size
    glBegin(GL_POINTS);
    glVertex2f((mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1, -(mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1); // Normalize mouse coordinates
    glVertex2f(.5, .5);
    glEnd();
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OpenGL Window");
    
    glutPassiveMotionFunc(passiveMotion); // Register passive motion callback
    glutDisplayFunc(render);
    glutMainLoop();
    //aasddadafas
    return 0;
}

