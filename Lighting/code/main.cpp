#include <iostream>    //导入系统的头文件
#include "Shader.h"     //导入本项目的头文件
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
//摄像机位置参数
glm::vec3 cameraPos = glm::vec3(0, 0, 5);
glm::vec3 cameraFront = glm::vec3(0, 0, -1);
glm::vec3 cameraUp = glm::vec3(0, 1, 0);
//时间记录
float deltaTime = 0;//时间间隔
float lastTime = 0;//上一帧时间
				   //鼠标移动视角有关
bool firstMouse = true;
float yaw = 0;
float pitch = 0;
float lastX = screenWidth / 2;
float lastY = screenHeight / 2;
//滚动相关
float fov = 45;  //视野

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	//float cameraSpeed = 2.5f*deltaTime;//一帧距离变化量
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) //鼠标时间回调函数
{
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;//屏幕是左上0,0
	lastX = xpos;
	lastY = ypos;
	//float sensitivity = 0.05f;//灵敏度
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
	//front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));  //z轴正方向为初始方向
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
	glfwInit();   //初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//高版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//低版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//配置

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "My openGL game", NULL, NULL);
	if (window == NULL) {
		printf("open window failed");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//初始化 GLFW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("init GLEW failed");
		glfwTerminate();
		return -1;
	}

	//open viewpoint
	glViewport(0, 0, 800, 600);

	//设置OpenGL参数
	//glEnable(GL_CULL_FACE);//开启面剔除，默认不剔除
	//glCullFace(GL_BACK);    //剔除背面
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式
	glEnable(GL_DEPTH_TEST);//开启深度测试
							//配置鼠标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//关闭光标
	glfwSetCursorPosCallback(window, mouse_callback);//配置鼠标回调函数
	glfwSetScrollCallback(window, scroll_callback);//设置滚轮回调



	unsigned int VAO;   //VAO ID
	glGenVertexArrays(1, &VAO);   //产生1个VAO
	glBindVertexArray(VAO);       //绑定
	unsigned int VBO;   //VBO ID
	glGenBuffers(1, &VBO);  //产生一个VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设置BufferData
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));//参数0，顶点的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(0);//使能参数0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));//参数0，顶点的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(1);//使能参数0


	unsigned int lightVAO;//光源立方体VAO
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);///绑定VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0 * sizeof(float)));//参数0，顶点的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(0);//使能参数0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));//参数0，顶点的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(1);//使能参数0

	//着色器
	Shader *lightShader = new Shader("../resource/1_color_vertexShader.txt","../resource/1_color_fragmentShader.txt");
	Shader *cubeShader = new Shader("../resource/1_lamp_vertexShader.txt", "../resource/1_lamp_fragmentShader.txt");

	////矩阵计算测试
	////移动测试
	glm::mat4 trans = glm::mat4(1);  //构建单位矩阵												//空间变换
	glm::mat4 model = glm::mat4(1.0f);//构建单位阵,模型到世界
	glm::mat4 view = glm::mat4(1);//世界到相机
	glm::mat4 projection = glm::mat4(1);//投影矩阵

	//位置设置
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);//光源位置
	
	
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

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影


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
		lightShader->setVec3("light.diffuse", diffuseColor); // 将光照调暗了一些以搭配场景
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





