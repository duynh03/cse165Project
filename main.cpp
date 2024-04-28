#include <GL/gl.h>
#include <iostream>
#include <random>
#include <GL/freeglut.h>
#include <cmath>
using namespace std;

//g++ -o run main.cpp -lGL -lglut
//------------------------------------------------------------------------------
int mouseX = 0;
int mouseY = 0;
class randomNumGen{
public:
    float randomCoord(){
        random_device rd;
        mt19937 eng(rd());
        uniform_real_distribution<> distr(-1.0, 1.0);
        float random_num = distr(eng);
        return random_num;   
    }
    float randomDegree(){
        random_device rd;
        mt19937 eng(rd());
        uniform_real_distribution<> distr(0.0, 360.0);
        float random_num = distr(eng);
        return random_num;          
    }
};

class enemySpawn{

};
void passiveMotion(int x, int y) {
    // Update mouse coordinates
    mouseX = x;
    mouseY = y;

    // Print mouse coordinates to console
    std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;
    cout << "Mousex: " << (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1 << endl;
    cout << "MouseY: " << -(mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1 << endl;

    //Redraw the window
    glutPostRedisplay(); //refresh where the cursor is so it can be redrawn in the window
}

class dotPosition : public randomNumGen{
public:
    float x;
    float y;
    dotPosition(){
        x = randomCoord();
        y = randomCoord();
    }
    ~dotPosition(){};
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
        glutSwapBuffers();
    }
};
class player : public randomNumGen{
public:
    float bulletCoordinateX, bulletCoordinateY;
    float mouseCoordinateX, mouseCoordinateY;
    float speedX, speedY;
    int seed;
    player(){
        bulletCoordinateX = mouseX;
        bulletCoordinateY = mouseY;
        speedX = 0.05;
        speedY = 0.05;
        seed = 0;
    }
    ~player(){};

    void triangle() {
        glClear(GL_COLOR_BUFFER_BIT);
        mouseCoordinateX = (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
        mouseCoordinateY = -(mouseY /  (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1;
        glEnable(GL_TRIANGLES);
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0); // Green Color
            glVertex2f(mouseCoordinateX, mouseCoordinateY + 0.05);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(mouseCoordinateX - 0.05, mouseCoordinateY - 0.05);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(mouseCoordinateX + 0.05, mouseCoordinateY - 0.05);
        glEnd();
        glutSwapBuffers();
    }
    void shoot(){
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_POINT);
        glPointSize(10.0);
        glBegin(GL_POINTS);
            glColor3f(1.0 ,0.0, 0.0);
            glVertex2f(bulletCoordinateX, bulletCoordinateY);
        glEnd();
        bulletCoordinateX += speedX;   
        bulletCoordinateY += speedY;

        if (seed == 100){  //higher seed = less frequent shot
            bulletCoordinateX = (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
            bulletCoordinateY = -(mouseY /  (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1;
            speedX = 0.05 * cos(randomDegree()); 
            speedY = 0.05 * sin(randomDegree());

            cout << "SpeedX: " << speedX << endl;
            cout << "SpeedY: " << speedY << endl << endl;
            seed = 0;
        }
        glutSwapBuffers();
    }
};

dotPosition dot;
player Projectile;
void display(){
    Projectile.triangle();
    Projectile.shoot();
}

void timer(int x){
    Projectile.seed += 1;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OpenGL Window");
    glutPassiveMotionFunc(passiveMotion); // Register passive motion callback
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

