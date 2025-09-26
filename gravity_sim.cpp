#include <GLFW/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <cmath>
#include <iostream>

static const int screenWidth  = 800;
static const int screenHeight = 600;
using namespace std;

void DrawCircle(float centerX, float centerY, float radius, float res);

GLFWwindow* StartGLFW() {
    if (!glfwInit()) { cerr << "GLFW init failed\n"; exit(1); }
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Circle", 0, 0);
    if (!window) { cerr << "Window create failed\n"; glfwTerminate(); exit(1); }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glClearColor(0.f, 0.f, 0.f, 1.f);
    return window;
}

class Object {
    public:

    vector<float> position;
    vector<float> velocity;
    float radius;
    const int res = 100;
    Object(vector<float> position, vector<float> velocity, float radius){
        this->position = position;
        this->velocity = velocity;
        this->radius = radius;
    }

    void accelerate(float x, float y){
        this->velocity[0] += x;
        this->velocity[1] += y;
    };
    void updatePos(){
        this->position[0] += this->velocity[0];
        this->position[1] += this->velocity[1]; 
    }
    void DrawCircle(){
        glBegin(GL_TRIANGLE_FAN);
        float centerX =this->position[0];
        float centerY =this->position[1];
        
        glVertex2d(centerX, centerY);
        for (int i = 0; i <= res; ++i) {
            const float t = static_cast<float>(i) / this->res;
            const float angle = 2.0f * 3.14159265358979323846f * t;
            const float x = centerX + this->radius * cos(angle);
            const float y = centerY + this->radius * sin(angle);
            glVertex2d(x, y);
        }
        glEnd();
    } 
};

int main() {
    GLFWwindow* window = StartGLFW();
    const float radius = 50.0f;
    vector<Object> objs = {
        Object(vector<float>{400.0f, 500.0f}, vector<float>{0.0f,0.0f}, radius),
        Object(vector<float>{400.0f, 200.0f}, vector<float>{0.0f,0.0f}, radius)
    };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        for(auto& obj : objs){
            obj.accelerate(0, -9.81);
            obj.updatePos();
            obj.DrawCircle();
            if(obj.position[1] < 0 || obj.position[1] > screenHeight) obj.velocity[1] *= -0.95;
            if(obj.position[0] < 0 || obj.position[0] > screenWidth) obj.velocity[0] *= -0.95;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}