
#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "shader.hpp"
#include "objectEnv.hpp"
#include "glm/glm.hpp"
GLFWwindow* window;
GLuint vertexbuffer;
const int WINDOW_WITH = 1024;
const int WINDOW_HEIGHT = 728;
void glfwWindowInit(){
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

void ft_glewInit(){
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if (glewInit() != GLEW_OK){
        throw std::runtime_error("GLEW 초기화 실패");
    }
}

void vaoInit(){
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    //buffer
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}
std::vector<glm::vec3> loadOBJ(std::string path, std::vector<glm::vec3>& buffer, std::string& objName, std::string& metal){
	std::ifstream objStream(path, std::ios::in);
	std::stringstream ss;

	std::vector<
	ss << objStream.rdbuf();
	std::string line;
	while (std::getline(ss, line)){
		std::stringstream tmpSS(line);
		glm::vec3 
		if (line[0] == 'o'){

		} else if (line[0] == 'v'){

		} else {
			continue;
		}
	}
}

void bufferInit(std::string path){
	glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	std::vector<glm::vec3> v_vertex_buffer_data;
	std::string objName;
	std::string metal;
	loadOBJ(path,v_vertex_buffer_data, objName, metal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*v_vertex_buffer_data.size(), &v_vertex_buffer_data[0], GL_STATIC_DRAW);
}

int main(int ac , char* av){

    try
    {
        glfwWindowInit();
        ft_glewInit();
        vaoInit();
				bufferInit(av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    glClearColor(0,0,1,0);
    GLuint programID = LoadShaders( "/Users/schoe/Desktop/scope/shaderSource/VertexShader", "/Users/schoe/Desktop/scope/shaderSource/FragmentShader");
    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
        glDrawArrays(GL_TRIANGLES,0,3);
        glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && 
                glfwWindowShouldClose(window) == 0 );
}