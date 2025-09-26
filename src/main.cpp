
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "renderer/shaderProgram.h"
#include "resources/resourceManager.h"
#include "renderer/Texture2d.h"





//массив вертексов треугольника
GLfloat point[] = {
     -0.5f, -0.5f, 0.0f, // нижний левый угол
      0.5f, -0.5f, 0.0f, // нижний правый угол
      0.0f,  0.5f, 0.0f  // верхний угол
};
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f, // красный
    0.0f, 1.0f, 0.0f, // зеленый
    0.0f, 0.0f, 1.0f  // синий
};
GLfloat texcord[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.5f, 1.0f 
};


//const char* vertexShader = 
//"#version 460 core\n"
//"layout(location = 0 ) in vec3 vertex_position;"
//"layout(location = 1 ) in vec3 vertex_color;"
//"out vec3 color;"
//"void main(){"
//"   color = vertex_color;"
//"   gl_Position = vec4(vertex_position,1.0);"
//"}";
//
//const char* fragmentShader =    
//"#version 460 core\n"
//"in vec3 color;"
//"out vec4 frag_color;"
//"void main(){"
//"   frag_color = vec4(color,1.0);"
//"}";
//







int g_windowSizeX = 800;
int g_windowSizeY = 600;


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, true);
    }
}


int main(int argc, char** argv)
{





	GLFWwindow* pWindow;

	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}


	/* Create a windowed mode window and its OpenGL context */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle-Sity", nullptr, nullptr);
	if (!pWindow)
	{
		std::cout << "GLFW create window error" << std::endl;

		glfwTerminate();

		return -1;
	}


	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
	glfwSetKeyCallback(pWindow, glfwKeyCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(pWindow);


	if (!gladLoadGL()) {
		std::cout << "error GLAD" << std::endl;
		return -1;
	}

	std::cout << "Renderer" << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGl version:" << glGetString(GL_VERSION) << std::endl;


	glClearColor(1, 1, 0, 1);


	{

		ResourceManager resourceManager(argv[0]);
		auto pDefaultShaderProgram = resourceManager.loadShader("defaultShaders", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
		if (pDefaultShaderProgram == nullptr)
		{
			std::cout << "Error load default shader program" << std::endl;
			return -1;
		}

		auto tex = resourceManager.loadTexture("defaulttextur", "res/textures/map_16x16.png");


	GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);


	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint texcord_vbo = 0;
	glGenBuffers(1, &texcord_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, texcord_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texcord), texcord, GL_STATIC_DRAW);


	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, texcord_vbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);



	pDefaultShaderProgram->use();//установка шейдерной программы
	pDefaultShaderProgram->setInt("tex", 0);





	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(pWindow))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		pDefaultShaderProgram->use();//установка шейдерной программы

		glBindVertexArray(vao);
		tex->bind();

		glDrawArrays(GL_TRIANGLES, 0, 3);




		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow); //переключение буферов

		/* Poll for and process events */
		glfwPollEvents();
		}
	}
    glfwTerminate();
    return 0;
}