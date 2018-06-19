#include <iostream>    //����ϵͳ��ͷ�ļ�
#include "Shader.h"     //���뱾��Ŀ��ͷ�ļ�
#include "stb_image.h"
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

float vertices[] = {
	// first triangle

	//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
};

unsigned int indices[] = {
	0,1,3,//��һ�������ζ���λ��
	1,2,3  //�ڶ���������
};


////shaderԴ����
//const char* vertexShaderSource= 
//"#version 330 core									 \n"
//"layout(location = 0) in vec3 aPos;					 \n"   //�������0
//"layout(location = 1) in vec3 aColor;					 \n"   //�������1
//"out vec4 vertexColor;     \n"   //����һ����ɫ���
//"void main(){										\n "													
//"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"//   vertexColor = vec4(0.5,0.0,0.0,1.0);\n"
//"   vertexColor = vec4(aColor,1.0);\n"
//"}\n";
//
//const char* fragmentShaderSource =
//"#version 330 core							  \n"
//"out vec4 FragColor;						  \n"
//"in vec4 vertexColor;\n"
//"uniform vec4 ourColor; // ��OpenGL����������趨�������\n"
//"											  \n"
//"void main()								  \n"
//"{											  \n"
//"	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"	FragColor = vertexColor;\n"
//"	//FragColor = ourColor;\n"
//"}\n";


int main() 
{
	glfwInit();   //��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//�߰汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�Ͱ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����

	GLFWwindow* window = glfwCreateWindow(800, 600, "My openGL game", NULL, NULL);
	if (window == NULL) {
		printf("open window failed");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//��ʼ�� GLFW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("init GLEW failed");
		glfwTerminate();
		return -1;
	}

	//open viewpoint
	glViewport(0, 0, 800, 600);

	//����OpenGL����
	//glEnable(GL_CULL_FACE);//�������޳���Ĭ�ϲ��޳�
	//glCullFace(GL_BACK);    //�޳�����

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ

	Shader* shader = new Shader("resource/vertexShader.txt","resource/fragmentShader.txt");//����shader

	unsigned int VAO;   //VAO ID

	glGenVertexArrays(1,&VAO);   //����1��VAO

	glBindVertexArray(VAO);       //��

	unsigned int VBO;   //VBO ID

	glGenBuffers(1, &VBO);  //����һ��VBO

	glBindBuffer(GL_ARRAY_BUFFER,VBO);//��VBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//����BufferData

	unsigned int EBO;     //����EBO
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	stbi_set_flip_vertically_on_load(true);//��תͼƬ�����⵹ת
	//���ɵ�һ��������
	int width1, height1, nrChannels1;//������ߣ�ͨ����
	unsigned char* data1 = stbi_load("resource/container.jpg",&width1,&height1,&nrChannels1,0);//��������
	//��������
	unsigned int texture1;
	glGenTextures(1, &texture1);
	//������Ϊ2D
	glBindTexture(GL_TEXTURE_2D,texture1);
	//������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//��������
	if (data1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);//glGenerateMipmap�����Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	}
	
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//�ͷ��ڴ�
	stbi_image_free(data1);

	shader->use();
	glUniform1i(glGetUniformLocation(shader->ID,"ourTexture1"),0);//��������Ԫ0����ӦGL_TEXTURE0


	//���ɵڶ�������
	int width2, height2, nrChannels2;//������ߣ�ͨ����
	unsigned char* data2 = stbi_load("resource/awesomeface.png", &width2, &height2, &nrChannels2, 0);//��������
	
	//��������
	unsigned int texture2;
	glGenTextures(1, &texture2);
	//������Ϊ2D
	glBindTexture(GL_TEXTURE_2D, texture2);
	//������������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//��������
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);//glGenerateMipmap�����Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
	}

	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//�ͷ��ڴ�
	stbi_image_free(data2);
	shader->use();
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture2"), 1);//��������Ԫ1 ��ӦGL_TEXTURE1






	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0*sizeof(float)));//����0������Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(0);//ʹ�ܲ���0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));//����1����ɫ�Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(1);//ʹ�ܲ���1
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));//����2����ɫ�Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(2);//ʹ�ܲ���2


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//��cup��ȡʱ�䣬�޸�shader�������ɫ
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);*/
		
		//��ͼ	
		shader->use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/*
		��һ������ָ�������ǻ��Ƶ�ģʽ�������glDrawArrays��һ�����ڶ������������Ǵ�����ƶ���ĸ�����������6��Ҳ����˵����һ����Ҫ����6�����㡣���������������������ͣ�������GL_UNSIGNED_INT�����һ�����������ǿ���ָ��EBO�е�ƫ���������ߴ���һ���������飬�������ǵ��㲻��ʹ��������������ʱ�򣩣��������ǻ���������д0��
		*/
		//��������
		//glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);//��һ�����㣬һ��6������


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
	
} 





