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
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        std::exit(1);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Circle", nullptr, nullptr);
    if (!window) {
        cerr << "Window create failed\n";
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    return window;
}

int main() {
    GLFWwindow* window = StartGLFW();

    const float centerX = screenWidth  * 0.5f;
    const float centerY = screenHeight * 0.5f;
    const float radius  = 50.0f;
    const int res     = 100;
    vector<float> positions ={centerX, centerY};
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        DrawCircle(positions[0], positions[1], radius, res);
        positions[1] -= 1.0f;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void DrawCircle(float centerX, float centerY, float radius, float res){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(centerX, centerY);
    for (int i = 0; i <= res; ++i) {
        const float t = static_cast<float>(i) / res;
        const float angle = 2.0f * 3.14159265358979323846f * t;
        const float x = centerX + radius * cos(angle);
        const float y = centerY + radius * sin(angle);
        glVertex2d(x, y);
    }
    glEnd();
}