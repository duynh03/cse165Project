#include <GL/gl.h>
#include <iostream>
#include <random>
#include <GL/freeglut.h>
#include <cmath>
using namespace std;

//g++ -o run main.cpp -lGL -lglut
//------------------------------------------------------------------------------
float mouseX = 0.0;
float mouseY = 0.0;
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
        float random_degree = distr(eng);
        return random_degree;          
    }
    float randomCustom(float x, float y){
        random_device rd;
        mt19937 eng(rd());
        uniform_real_distribution<> distr(x, y);
        float random_degree = distr(eng);
        return random_degree;          
    }
};

void passiveMotion(int x, int y) {
    mouseX = (x / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
    mouseY = -(y / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1;

    std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;
    cout << "Mousex: " << (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1 << endl;
    cout << "MouseY: " << -(mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1 << endl;
}
class gameObject{
public:
    float xCoordinate, yCoordinate;
    virtual void spawn() = 0;
};
class player : public randomNumGen, public gameObject{
private:
    float velocityX, velocityY;
public:
    int counter;
    player(){
        xCoordinate = mouseX;
        yCoordinate = mouseY;
        velocityX = 0.05;
        velocityY = 0.05;
        counter = 0;
        glEnable(GL_TRIANGLES);
        glEnable(GL_POINTS);        
    }
    ~player(){};
    void triangle() {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0); 
            glVertex2f(mouseX, mouseY + 0.05);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(mouseX - 0.05, mouseY - 0.05);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(mouseX + 0.05, mouseY - 0.05);
        glEnd();
        glutSwapBuffers();
    }

    void spawn() override{
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(10.0);
        glBegin(GL_POINTS);
            glColor3f(1.0 ,0.0, 0.0);
            glVertex2f(xCoordinate, yCoordinate);
        glEnd();
        xCoordinate += velocityX;   
        yCoordinate += velocityY;

        if (counter == 50){  //higher counter = less frequent shot
            xCoordinate = mouseX;
            yCoordinate = mouseY;
            float t = randomDegree();
            velocityX = 0.05 * cos(t); 
            velocityY = 0.05 * sin(t);
            counter = 0;
        }
        glutSwapBuffers();
    }
};

class squareEnemy : public gameObject, public randomNumGen{
private:
    float velocityX, velocityY;
public:
    int counter;
    squareEnemy(){
        xCoordinate = randomCustom(-1.0f, 1.0f);
        yCoordinate = randomCustom(-1.0f, 1.0f);
        velocityX = 0.03;
        velocityY = 0.03;
        counter = 0;
        glEnable(GL_QUADS);        
    }
    ~squareEnemy(){};

    void spawn() override{
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
            glColor3f(0.0, 0.0, 1.0); // Blue Color
            glVertex2f(xCoordinate - 0.1, yCoordinate - 0.1); 
            glVertex2f(xCoordinate + 0.1, yCoordinate - 0.1);
            glVertex2f(xCoordinate + 0.1, yCoordinate + 0.1);
            glVertex2f(xCoordinate - 0.1, yCoordinate + 0.1);
        glEnd();
        xCoordinate += velocityX;
        yCoordinate += velocityY;
        if (xCoordinate > 1.0 || xCoordinate < -1.0 || yCoordinate > 1.0 || yCoordinate < -1.0){
            counter = 0;
        }
        if (yCoordinate > 1.0) {
            velocityY = -1 * velocityY;
        }
        if (yCoordinate < -1.0){
            velocityY = -1 * velocityY;
        }
        if (xCoordinate > 1.0){
            velocityX = -1 * velocityX;
        }
        if (xCoordinate < -1.0){
            velocityX = -1 * velocityX;
        }
        glutSwapBuffers();
    }
};

bool collision(gameObject* objA, gameObject* objB){
    if (objA->xCoordinate > 0.5){
    cout <<"trueA" << endl;
    }
    if (objB->xCoordinate > 0.5){
        cout << "trueB" << endl;
    }
    return false;
}

squareEnemy dot;
squareEnemy dot2;
player Player;

void display(){
    dot2.spawn();
    dot.spawn();
    Player.triangle();
    Player.spawn();
    collision(&dot, &dot2);
}

void timer(int x){
    dot.counter += 1;
    Player.counter += 1;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Window");
    glutPassiveMotionFunc(passiveMotion);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
