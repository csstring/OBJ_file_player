#include "GLFW/glfw3.h"
#include <iostream>
#include <stdexcept>
GLFWwindow* window;
const int WINDOW_WITH = 1024;
const int WINDOW_HEIGHT = 728;
void glfWindowInit(){
    if (!glfwInit()){
        throw std::runtime_error("GLFW 초기화 실패");
    }
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 을 쓸 겁니다
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS 가 기분 좋아짐; 꼭 필요한 부분은 아님
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //옛날 OpenGL은 원하지 않아요
    window = glfwCreateWindow(WINDOW_WITH,WINDOW_HEIGHT, "Scope", NULL,NULL);
    if (!window){
        glfwTerminate();
        throw std::runtime_error("GLFW 윈도우 창 여는데 실패");
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
}

int main(){

    try
    {
        glfWindowInit();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    do{
        // 아무것도 그리지 않습니다. 두번째 튜토리얼에서 만나도록 하죠!

        // 버퍼들을 교체
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
                glfwWindowShouldClose(window) == 0 );
}