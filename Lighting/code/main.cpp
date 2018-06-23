#include <iostream>    //����ϵͳ��ͷ�ļ�
#include "Shader.h"     //���뱾��Ŀ��ͷ�ļ�
#include "stb_image.h"
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

#include "Camera.h"
Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f));
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f

};


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
	//float cameraSpeed = 2.5f*deltaTime;//һ֡����仯��
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//cameraPos += cameraSpeed * cameraFront;
		camera->ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//cameraPos -= cameraSpeed * cameraFront;
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraFront));
		camera->ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
		camera->ProcessKeyboard(RIGHT, deltaTime);
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
	//float sensitivity = 0.05f;//������
	//xOffset *= sensitivity;
	//yOffset *= sensitivity;
	//yaw += xOffset;
	//pitch += yOffset;
	//if (pitch > 89) {
	//	pitch = 89;
	//}
	//if (pitch < -89) {
	//	pitch = -89;
	//}

	//glm::vec3 front;
	//front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	//front.y = sin(glm::radians(pitch));
	//front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));  //z��������Ϊ��ʼ����
	//cameraFront = glm::normalize(front);
	camera->ProcessMouseMovement(xOffset,yOffset);

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	/*if (fov >= 1 && fov <= 45) {
		fov -= yoffset;
	}
	if (fov <= 1) {
		fov = 1;
	}
	if (fov >= 45) {
		fov = 45;
	}*/
	camera->ProcessMouseScroll(yoffset);
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



	unsigned int VAO;   //VAO ID
	glGenVertexArrays(1, &VAO);   //����1��VAO
	glBindVertexArray(VAO);       //��
	unsigned int VBO;   //VBO ID
	glGenBuffers(1, &VBO);  //����һ��VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//��VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//����BufferData
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));//����0������Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(0);//ʹ�ܲ���0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));//����0������Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(1);//ʹ�ܲ���0


	unsigned int lightVAO;//��Դ������VAO
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);///��VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));//����0������Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(0);//ʹ�ܲ���0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));//����0������Ĳ���������float���ͣ�����һ���������ƫ��
	glEnableVertexAttribArray(1);//ʹ�ܲ���0

	//��ɫ��
	Shader *lightShader = new Shader("../resource/1_color_vertexShader.txt","../resource/1_color_fragmentShader.txt");
	Shader *cubeShader = new Shader("../resource/1_lamp_vertexShader.txt", "../resource/1_lamp_fragmentShader.txt");

	////����������
	////�ƶ�����
	glm::mat4 trans = glm::mat4(1);  //������λ����												//�ռ�任
	glm::mat4 model = glm::mat4(1.0f);//������λ��,ģ�͵�����
	glm::mat4 view = glm::mat4(1);//���絽���
	glm::mat4 projection = glm::mat4(1);//ͶӰ����

	//λ������
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);//��Դλ��
	
	
	lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
	
		float currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastTime;
		lastTime = currentFrameTime;
		processInput(window);

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // ����Ӱ��
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // �ܵ͵�Ӱ


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		lightShader->use();
		projection = glm::perspective(camera->Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		view = camera->GetViewMatrix();
		model = glm::mat4(1);
		
		//lightShader->setVec3("objectColor", 1, 0.5f, 0.31f);
		//lightShader->setVec3("lightColor", 1, 1, 1);
		lightShader->setMat4("model", model);
		lightShader->setMat4("view", view);
		lightShader->setMat4("projection", projection);
		lightShader->setVec3("light.position",lightPos);
		lightShader->setVec3("viewPos", camera->Position);
		lightShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		lightShader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		lightShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		lightShader->setFloat("material.shininess", 32.0f);
		lightShader->setVec3("light.ambient", ambientColor);
		lightShader->setVec3("light.diffuse", diffuseColor); // �����յ�����һЩ�Դ��䳡��
		lightShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		cubeShader->use();
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		cubeShader->setMat4("projection", projection);
		cubeShader->setMat4("view", view);
		cubeShader->setMat4("model", model);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}





