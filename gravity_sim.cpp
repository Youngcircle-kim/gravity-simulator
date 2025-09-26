// main.cpp
#include <GLFW/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>  // macOS에서 즉시 모드 사용 시
#else
#include <GL/gl.h>
#endif
#include <cmath>
#include <iostream>

static const int screenWidth  = 800;
static const int screenHeight = 600;

GLFWwindow* StartGLFW() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        std::exit(1);
    }

#ifdef __APPLE__
    // macOS에서 glBegin 등 즉시 모드 쓰려면 2.1 컨텍스트가 편합니다.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Circle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Window create failed\n";
        glfwTerminate();
        std::exit(1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // 뷰포트 & 직교 투영: 좌하(0,0) ~ 우상(screenWidth, screenHeight)
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenWidth, 0, screenHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 배경색 (검정)
    glClearColor(0.f, 0.f, 0.f, 1.f);

    return window;
}

int main() {
    GLFWwindow* window = StartGLFW();

    const float centerX = screenWidth  * 0.5f;
    const float centerY = screenHeight * 0.5f; // ← 수정
    const float radius  = 50.0f;
    const int   res     = 100;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();

        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(centerX, centerY); // 중심
        for (int i = 0; i <= res; ++i) {
            const float t = static_cast<float>(i) / res;
            const float angle = 2.0f * 3.14159265358979323846f * t;
            const float x = centerX + radius * std::cos(angle);
            const float y = centerY + radius * std::sin(angle); // ← sin으로 수정
            glVertex2d(x, y);
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}