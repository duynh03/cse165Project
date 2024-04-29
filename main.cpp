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
    mouseX = x;
    mouseY = y;

    std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;
    cout << "Mousex: " << (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1 << endl;
    cout << "MouseY: " << -(mouseY / (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1 << endl;

    // glutPostRedisplay(); //refresh where the cursor is so it can be redrawn in the window
}

class Enemy : public randomNumGen{
private:
    float x, y;
    float speedX, speedY;
    
public:
    int counter;
    Enemy(){
        x = randomCustom(-0.05f, 0.05f);
        y = randomCustom(-0.05f, 0.05f);
        speedX = 0.05;
        speedY = 0.05;
        counter = 0;
        glEnable(GL_QUADS);        
    }
    ~Enemy(){};
    void spawnEnemy(){
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);
            glColor3f(0.0, 0.0, 1.0); // Blue Color
            glVertex2f(x - 0.1, y - 0.1); 
            glVertex2f(x + 0.1, y - 0.1);
            glVertex2f(x + 0.1, y + 0.1);
            glVertex2f(x - 0.1, y + 0.1);
        glEnd();
        x += speedX;
        y += speedY;
        if (x > 1.0 || x < -1.0 || y > 1.0 || y < -1.0){
            x = randomCustom(-0.05f, 0.05f);
            y = randomCustom(-0.05f, 0.05f);
            float t = randomDegree();
            speedX = 0.03 * cos(t); 
            speedY = 0.03 * sin(t);
            counter = 0;
        }
        glutSwapBuffers();

    }
};
class player : public randomNumGen{
private:
    float bulletCoordinateX, bulletCoordinateY;
    float mouseCoordinateX, mouseCoordinateY;
    float speedX, speedY;
public:
    int counter;
    player(){
        bulletCoordinateX = mouseX;
        bulletCoordinateY = mouseY;
        speedX = 0.05;
        speedY = 0.05;
        counter = 0;
        glEnable(GL_TRIANGLES);
        glEnable(GL_POINTS);        
    }
    ~player(){};
    void triangle() {
        glClear(GL_COLOR_BUFFER_BIT);
        mouseCoordinateX = (mouseX / (float)glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
        mouseCoordinateY = -(mouseY /  (float)glutGet(GLUT_WINDOW_HEIGHT)) * 2 + 1;
        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0); 
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
        glPointSize(10.0);
        glBegin(GL_POINTS);
            glColor3f(1.0 ,0.0, 0.0);
            glVertex2f(bulletCoordinateX, bulletCoordinateY);
        glEnd();
        bulletCoordinateX += speedX;   
        bulletCoordinateY += speedY;

        if (counter == 100){  //higher counter = less frequent shot
            bulletCoordinateX = mouseCoordinateX;
            bulletCoordinateY = mouseCoordinateY;
            float t = randomDegree();
            speedX = 0.05 * cos(t); 
            speedY = 0.05 * sin(t);

            cout << "SpeedX: " << speedX << endl;
            cout << "SpeedY: " << speedY << endl << endl;
            counter = 0;
        }
        glutSwapBuffers();
    }
};

Enemy dot;
player Player;

void display(){
    dot.spawnEnemy();
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

