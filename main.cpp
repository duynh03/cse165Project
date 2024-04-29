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

    // std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;
    // cout << "Mousex: " << (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1 << endl;
    // cout << "MouseY: " << -(mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1 << endl;
}
class gameObject{
public:
    float xCoordinate, yCoordinate;
    virtual void spawn() = 0;
};
class player : public gameObject{
public:
    player(){
        xCoordinate = mouseX;
        yCoordinate = mouseY;
        glEnable(GL_TRIANGLES);
    }
    void spawn() {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0); 
            glVertex2f(xCoordinate, yCoordinate + 0.05);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(xCoordinate - 0.05, yCoordinate - 0.05);
            glColor3f(1.0, 0.0, 0.0);
            glVertex2f(xCoordinate + 0.05, yCoordinate - 0.05);
        glEnd();
        xCoordinate = mouseX;
        yCoordinate = mouseY;
        glutSwapBuffers();
    }
};
class bullet : public randomNumGen, public gameObject{
private:
    float velocityX, velocityY;
public:
    int counter;
    bullet(){
        xCoordinate = mouseX;
        yCoordinate = mouseY;
        velocityX = 0.05;
        velocityY = 0.05;
        counter = 0;
        glEnable(GL_POINTS);        
    }
    ~bullet(){};
    void spawn() override{
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(10.0);
        glBegin(GL_POINTS);
            glColor3f(1.0 ,0.0, 0.0);
            glVertex2f(xCoordinate, yCoordinate);
        glEnd();
        xCoordinate += velocityX;   
        yCoordinate += velocityY;

        if (counter >= 50 || xCoordinate > 1.0 || xCoordinate < -1.0 || yCoordinate > 1.0 || yCoordinate < -1.0){  //higher counter = less frequent shot
            xCoordinate = mouseX;
            yCoordinate = mouseY;
            float t = randomDegree();
            velocityX = 0.1 * cos(t); 
            velocityY = 0.1 * sin(t);
            counter = 0;
        }
        glutSwapBuffers();
    }
};

class squareEnemy : public gameObject, public randomNumGen{
private:
    float velocityX, velocityY;
public:
    squareEnemy(){
        xCoordinate = randomCustom(-1.0f, 1.0f);
        yCoordinate = randomCustom(-1.0f, 1.0f);
        velocityX = 0.03;
        velocityY = 0.03;
        glEnable(GL_QUADS);        
    }
    ~squareEnemy(){};
    void randomSpawn(){
        xCoordinate = randomCustom(-1.0f, 1.0f);
        yCoordinate = randomCustom(-1.0f, 1.0f); 
    }
    void spawn() override{
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
            glColor3f(0.0, 0.0, 1.0); // Blue Color
            glVertex2f(xCoordinate - 0.1, yCoordinate - 0.1); //bottom left
            glVertex2f(xCoordinate + 0.1, yCoordinate - 0.1); //bottom right
            glVertex2f(xCoordinate + 0.1, yCoordinate + 0.1); //top right
            glVertex2f(xCoordinate - 0.1, yCoordinate + 0.1); //top left
        glEnd();
        xCoordinate += velocityX;
        yCoordinate += velocityY;
        // if (xCoordinate > 1.0 || xCoordinate < -1.0 || yCoordinate > 1.0 || yCoordinate < -1.0){
        // }
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
    bool x = false;
    bool y = false;
    if (objA->yCoordinate - 0.1 <= objB->yCoordinate + 0.1 && objB->yCoordinate - 0.1 <= objA->yCoordinate + 0.1){
        y = true;
    }
    if (objA->xCoordinate + 0.1 >= objB->xCoordinate - 0.1 && objB->xCoordinate + 0.1 >= objA->xCoordinate - 0.1){
        x = true;
    }
    return x && y;
}
//Game objects
squareEnemy dot1;
squareEnemy dot2;
bullet Bullet;
player Player;

void display(){
    dot2.spawn();
    dot1.spawn();
    Player.spawn();
    Bullet.spawn();
    if (collision(&Player, &dot1) == true || collision(&Player, &dot2) == true){
        cout << "You lose" << endl;
    }
    if (collision(&Bullet, &dot1) == true){
        dot1.randomSpawn();
        Bullet.counter = 50;
    }
    if (collision(&Bullet, &dot2) == true){
        dot2.randomSpawn();
        Bullet.counter = 50;
    }
    
}

void timer(int x){
    Bullet.counter += 1;
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
