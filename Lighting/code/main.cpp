#include <iostream>    //����ϵͳ��ͷ�ļ�
#include "Shader.h"     //���뱾��Ŀ��ͷ�ļ�
#include "stb_image.h"
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"



float vertices[] = {
	// first triangle

	//     ---- λ�� ----       ---- ��ɫ ----     - ��������(�������ϵ�����) -
	//0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
	//0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
	//-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
	//-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f

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

int screenWidth = 800;
int screenHeight = 600;
//�����λ�ò���
glm::vec3 cameraPos = glm::vec3(0, 0, 5);
glm::vec3 cameraFront = glm::vec3(0, 0, -1);
glm::vec3 cameraUp = glm::vec3(0, 1, 0);
//ʱ���¼
float deltaTime = 0;//ʱ����
float lastTime = 0;//��һ֡ʱ��
				   //����ƶ��ӽ��й�
bool firstMouse = true;
float yaw = 0;
float pitch = 0;
float lastX = screenWidth / 2;
float lastY = screenHeight / 2;
//�������
float fov = 45;  //��Ұ

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = 2.5f*deltaTime;//һ֡����仯��
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) //���ʱ��ص�����
{
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;//��Ļ������0,0
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.05f;//������
	xOffset *= sensitivity;
	yOffset *= sensitivity;
	yaw += xOffset;
	pitch += yOffset;
	if (pitch > 89) {
		pitch = 89;
	}
	if (pitch < -89) {
		pitch = -89;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));  //z��������Ϊ��ʼ����
	cameraFront = glm::normalize(front);


}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	if (fov >= 1 && fov <= 45) {
		fov -= yoffset;
	}
	if (fov <= 1) {
		fov = 1;
	}
	if (fov >= 45) {
		fov = 45;
	}
}


int main()
{
	glfwInit();   //��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//�߰汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�Ͱ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "My openGL game", NULL, NULL);
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
	glEnable(GL_DEPTH_TEST);//������Ȳ���
							//�������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//�رչ��
	glfwSetCursorPosCallback(window, mouse_callback);//�������ص�����
	glfwSetScrollCallback(window, scroll_callback);//���ù��ֻص�



	Shader* shader = new Shader("../resource/vertexShader.txt", "../resource/fragmentShader.txt");//����shader  //resource/vertexShader.txt�Ǵ���Ŀ�ĸ�Ŀ¼

	unsigned int VAO;   //VAO ID

	glGenVertexArrays(1, &VAO);   //����1��VAO

	glBindVertexArray(VAO);       //��

	unsigned int VBO;   //VBO ID

	glGenBuffers(1, &VBO);  //����һ��VBO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//����BufferData

	unsigned int EBO;     //����EBO
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	stbi_set_flip_vertically_on_load(true);//��תͼƬ�����⵹ת
										   //���ɵ�һ��������
	int width1, height1, nrChannels1;//������ߣ�ͨ����
	unsigned char* data1 = stbi_load("../resource/container.jpg", &width1, &height1, &nrChannels1, 0);//��������
																																		  //��������
	unsigned int texture1;
	glGenTextures(1, &texture1);
	//������Ϊ2D
	glBindTexture(GL_TEXTURE_2D, texture1);
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
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture1"), 0);//��������Ԫ0����ӦGL_TEXTURE0


																	//���ɵڶ�������
	int width2, height2, nrChannels2;//������ߣ�ͨ����
	unsigned char* data2 = stbi_load("../resource/awesomeface.png", &width2, &height2, &nrChannels2, 0);//��������

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


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0 * sizeof(float)));//����0������Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(0);//ʹ�ܲ���0
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));//����1����ͼ�Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(1);//ʹ�ܲ���1


								 ////����������
								 ////�ƶ�����
	glm::vec4 vec(1, 0, 0, 1);//����x,y,z,w
	glm::mat4 trans = glm::mat4(1);  //������λ����
	trans = glm::translate(trans, glm::vec3(1, 1, 0));//�ƶ�1,1,0,���ر任����
	vec = trans * vec;  //�任
	std::cout << vec.x << vec.y << vec.z << vec.w << std::endl;
	//��ת����
	trans = glm::mat4(1);  //������λ����
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 0, 1));//��z��ת90��
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));//����0.5


														//�ռ�任
	glm::mat4 model = glm::mat4(1.0f);//������λ��,ģ�͵�����
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1, 0, 0));//�ֲ����������꣨ԭ��0,0,0����������x��ת-55��
	glm::mat4 view = glm::mat4(1);//���絽���
	view = glm::translate(view, glm::vec3(0, 0, -3));

	glm::mat4 projection = glm::mat4(1);//ͶӰ����
	projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);//fov����߱ȣ������룬Զ����

																											 //����10��������λ�ã�����10��λ�û�
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastTime;
		lastTime = currentFrameTime;
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//��cup��ȡʱ�䣬�޸�shader�������ɫ
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);*/

		//��ͼ	
		shader->use();
		glBindVertexArray(VAO);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/*
		��һ������ָ�������ǻ��Ƶ�ģʽ�������glDrawArrays��һ�����ڶ������������Ǵ�����ƶ���ĸ�����������6��Ҳ����˵����һ����Ҫ����6�����㡣���������������������ͣ�������GL_UNSIGNED_INT�����һ�����������ǿ���ָ��EBO�е�ƫ���������ߴ���һ���������飬�������ǵ��㲻��ʹ��������������ʱ�򣩣��������ǻ���������д0��
		*/
		//��������
		//glBindTexture(GL_TEXTURE_2D, texture1);
		for (unsigned int i = 0; i < 10; i++)
		{

			// calculate the model matrix for each object and pass it to shader before drawing
			trans = glm::mat4(1);  //������λ����
								   //�任
			trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));//����0.5
			trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 1, 1));//��z��ת90��

			model = glm::mat4(1);
			//����˳����д�ĺ�ִ��
			//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));//������������ת
			model = glm::translate(model, cubePositions[i]);//�����������ƶ�
															//�۲��ռ䣬�������0��0,0��ת
			view = glm::mat4(1);
			//float radius = 10.0f;//��ת�뾶
			//float camX = sin(glfwGetTime())*radius;//xλ��
			//float camZ = cos(glfwGetTime())*radius;//zλ��
			//view = glm::lookAt(glm::vec3(camX, 0, camZ), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));//�����λ�ã��������ע�㣬�Ϸ���
			view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);//�����λ�ã��������ע�㣬�Ϸ���

			projection = glm::mat4(1);//ͶӰ����
			projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);//fov����߱ȣ������룬Զ����


			int transformLoc = glGetUniformLocation(shader->ID, "transform");//��ȡ���Ų���id
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));//�������Ų���
			int modelLoc = glGetUniformLocation(shader->ID, "model");//��ȡģ�͵�����任����id
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));//����ģ�͵�����任����
			int viewLoc = glGetUniformLocation(shader->ID, "view");//��ȡ���絽�������id
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));//�������絽�������
			int projectionLoc = glGetUniformLocation(shader->ID, "projection");//��ȡ�����ͶӰ����id
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));//���������ͶӰ����
																					   //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);//��һ�����㣬һ��36������	
		}



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}





