#include <GL/gl.h>
#include <iostream>
#include <random>
using namespace std;
#include <GL/freeglut.h>
//g++ -o run main.cpp -lGL -lglut
//------------------------------------------------------------------------------
int mouseX = 0;
int mouseY = 0;
int test = 0;
float randomGen(){
    random_device rd;
    mt19937 eng(rd());
    uniform_real_distribution<> distr(-1.0, 1.0);
    float random_num = distr(eng);
    return random_num;   
}

void passiveMotion(int x, int y) {
    // Update mouse coordinates
    mouseX = x;
    mouseY = y;
    if (test >= 500){
        test = 0;
    }
    else{
        test++;
    }

    // Print mouse coordinates to console
    std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;
    cout << "Mousex: " << (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1 << endl;
    cout << "MouseY: " << -(mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1 << endl;

    //Redraw the window
    glutPostRedisplay(); //refresh where the cursor is so it can be redrawn in the window
}

class dotPosition{
public:
    float x;
    float y;

    void triangle() {
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

        if (test < 50){
            glEnable(GL_POINT);
            glPointSize(20.0);
            glBegin(GL_POINTS);
                glColor3f(1.0 ,0.0, 0.0);
                glVertex2f(x, y);
            glEnd();        
        }


        glutSwapBuffers();
    }
};
dotPosition dot;
void display(){
    dot.triangle();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OpenGL Window");
    glutPassiveMotionFunc(passiveMotion); // Register passive motion callback
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

