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

class player : public randomNumGen{
private:
    float bulletCoordinateX, bulletCoordinateY;
    float velocityX, velocityY;
public:
    int counter;
    player(){
        bulletCoordinateX = mouseX;
        bulletCoordinateY = mouseY;
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

    void shoot(){
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(10.0);
        glBegin(GL_POINTS);
            glColor3f(1.0 ,0.0, 0.0);
            glVertex2f(bulletCoordinateX, bulletCoordinateY);
        glEnd();
        bulletCoordinateX += velocityX;   
        bulletCoordinateY += velocityY;

        if (counter == 50){  //higher counter = less frequent shot
            bulletCoordinateX = mouseX;
            bulletCoordinateY = mouseY;
            float t = randomDegree();
            velocityX = 0.05 * cos(t); 
            velocityY = 0.05 * sin(t);
            counter = 0;
        }
        glutSwapBuffers();
    }
};
class enemy{
public:
    virtual void spawn() = 0;
};
class squareEnemy : public enemy, public randomNumGen{
private:
    float x, y;
    float velocityX, velocityY;
public:
    int counter;
    squareEnemy(){
        x = randomCustom(-1.0f, 1.0f);
        y = randomCustom(-1.0f, 1.0f);
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
            glVertex2f(x - 0.1, y - 0.1); 
            glVertex2f(x + 0.1, y - 0.1);
            glVertex2f(x + 0.1, y + 0.1);
            glVertex2f(x - 0.1, y + 0.1);
        glEnd();
        x += velocityX;
        y += velocityY;
        if (x > 1.0 || x < -1.0 || y > 1.0 || y < -1.0){
            counter = 0;
        }
        if (y > 1.0) {
            velocityY = -1 * velocityY;
        }
        if (y < -1.0){
            velocityY = -1 * velocityY;
        }
        if (x > 1.0){
            velocityX = -1 * velocityX;
        }
        if (x < -1.0){
            velocityX = -1 * velocityX;
        }
        glutSwapBuffers();
    }
};

squareEnemy dot;
squareEnemy dot2;
player Player;

void display(){
    dot2.spawn();
    dot.spawn();
    Player.triangle();
    Player.shoot();
}

void timer(int x){
    dot.counter += 1;
    Player.counter += 1;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("OpenGL Window");
    glutPassiveMotionFunc(passiveMotion);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}

