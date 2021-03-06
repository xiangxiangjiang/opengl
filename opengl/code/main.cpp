#include <iostream>    //导入系统的头文件
#include "Shader.h"     //导入本项目的头文件
#include "stb_image.h"
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"



float vertices[] = {
	// first triangle

	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标(在纹理上的坐标) -
	//0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	//0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	//-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	//-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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
	0,1,3,//第一个三角形顶点位置
	1,2,3  //第二个三角形
};


////shader源代码
//const char* vertexShaderSource= 
//"#version 330 core									 \n"
//"layout(location = 0) in vec3 aPos;					 \n"   //读入参数0
//"layout(location = 1) in vec3 aColor;					 \n"   //读入参数1
//"out vec4 vertexColor;     \n"   //定义一个颜色输出
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
//"uniform vec4 ourColor; // 在OpenGL程序代码中设定这个变量\n"
//"											  \n"
//"void main()								  \n"
//"{											  \n"
//"	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"	FragColor = vertexColor;\n"
//"	//FragColor = ourColor;\n"
//"}\n";

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
float lastX = screenWidth/2;
float lastY = screenHeight/2;
//滚动相关
float fov = 45;  //视野

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = 2.5f*deltaTime;//一帧距离变化量
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraUp,cameraFront));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraFront, cameraUp));
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
	float sensitivity = 0.05f;//灵敏度
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
	front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));  //z轴正方向为初始方向
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
	glfwInit();   //初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//高版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//低版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//配置

	GLFWwindow* window = glfwCreateWindow(screenWidth,screenHeight, "My openGL game", NULL, NULL);
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



	Shader* shader = new Shader("F:/数学/opengl/work/CPP/OpenGLExercise02/resource/vertexShader.txt","F:/数学/opengl/work/CPP/OpenGLExercise02/resource/fragmentShader.txt");//创建shader

	unsigned int VAO;   //VAO ID

	glGenVertexArrays(1,&VAO);   //产生1个VAO

	glBindVertexArray(VAO);       //绑定

	unsigned int VBO;   //VBO ID

	glGenBuffers(1, &VBO);  //产生一个VBO

	glBindBuffer(GL_ARRAY_BUFFER,VBO);//绑定VBO

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设置BufferData

	unsigned int EBO;     //产生EBO
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	stbi_set_flip_vertically_on_load(true);//翻转图片，避免倒转
	//生成第一章张纹理
	int width1, height1, nrChannels1;//纹理，宽高，通道数
	unsigned char* data1 = stbi_load("F:/数学/opengl/work/CPP/OpenGLExercise02/resource/container.jpg",&width1,&height1,&nrChannels1,0);//处理纹理
	//生成纹理
	unsigned int texture1;
	glGenTextures(1, &texture1);
	//绑定纹理为2D
	glBindTexture(GL_TEXTURE_2D,texture1);
	//设置配置纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//生成纹理
	if (data1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);//glGenerateMipmap。这会为当前绑定的纹理自动生成所有需要的多级渐远纹理。
	}
	
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//释放内存
	stbi_image_free(data1);

	shader->use();
	glUniform1i(glGetUniformLocation(shader->ID,"ourTexture1"),0);//分配纹理单元0，对应GL_TEXTURE0


	//生成第二张纹理
	int width2, height2, nrChannels2;//纹理，宽高，通道数
	unsigned char* data2 = stbi_load("F:/数学/opengl/work/CPP/OpenGLExercise02/resource/awesomeface.png", &width2, &height2, &nrChannels2, 0);//处理纹理
	
	//生成纹理
	unsigned int texture2;
	glGenTextures(1, &texture2);
	//绑定纹理为2D
	glBindTexture(GL_TEXTURE_2D, texture2);
	//设置配置纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//生成纹理
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);//glGenerateMipmap。这会为当前绑定的纹理自动生成所有需要的多级渐远纹理。
	}

	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//释放内存
	stbi_image_free(data2);
	shader->use();
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture2"), 1);//分配纹理单元1 对应GL_TEXTURE1


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(0*sizeof(float)));//参数0，顶点的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(0);//使能参数0
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));//参数1，贴图的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(1);//使能参数1
	

	////矩阵计算测试
	////移动测试
	glm::vec4 vec(1, 0, 0, 1);//向量x,y,z,w
	glm::mat4 trans = glm::mat4(1);  //构建单位矩阵
	trans = glm::translate(trans, glm::vec3(1, 1, 0));//移动1,1,0,返回变换矩阵
	vec = trans * vec;  //变换
	std::cout << vec.x << vec.y << vec.z << vec.w << std::endl;
	//旋转测试
	trans = glm::mat4(1);  //构建单位矩阵
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 0, 1));//绕z旋转90°
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));//缩放0.5


	//空间变换
	glm::mat4 model = glm::mat4(1.0f);//构建单位阵,模型到世界
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1, 0, 0));//局部到世界坐标（原点0,0,0），并且绕x旋转-55度
	glm::mat4 view = glm::mat4(1);//世界到相机
	view = glm::translate(view, glm::vec3(0, 0, -3));

	glm::mat4 projection = glm::mat4(1);//投影矩阵
	projection = glm::perspective(glm::radians(fov),(float)screenWidth/(float)screenHeight,0.1f,100.0f);//fov，宽高比，近距离，远距离

	//定义10个立方体位置，在这10个位置画
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
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		//从cup获取时间，修改shader输出的颜色
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);*/
		
		//画图	
		shader->use();
		glBindVertexArray(VAO);


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/*
		第一个参数指定了我们绘制的模式，这个和glDrawArrays的一样。第二个参数是我们打算绘制顶点的个数，这里填6，也就是说我们一共需要绘制6个顶点。第三个参数是索引的类型，这里是GL_UNSIGNED_INT。最后一个参数里我们可以指定EBO中的偏移量（或者传递一个索引数组，但是这是当你不在使用索引缓冲对象的时候），但是我们会在这里填写0。
		*/
		//导入纹理
		//glBindTexture(GL_TEXTURE_2D, texture1);
		for (unsigned int i = 0; i < 10; i++)
		{

			// calculate the model matrix for each object and pass it to shader before drawing
			trans = glm::mat4(1);  //构建单位矩阵
			//变换
			trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));//缩放0.5
			trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 1, 1));//绕z旋转90°

			model = glm::mat4(1);
			//运算顺序，先写的后执行
			//model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));//世界坐标下旋转
			model = glm::translate(model, cubePositions[i]);//世界坐标下移动
			//观擦空间，摄像机绕0，0,0旋转
			view = glm::mat4(1);
			//float radius = 10.0f;//旋转半径
			//float camX = sin(glfwGetTime())*radius;//x位置
			//float camZ = cos(glfwGetTime())*radius;//z位置
			//view = glm::lookAt(glm::vec3(camX, 0, camZ), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));//摄像机位置，摄像机关注点，上方向
			view = glm::lookAt(cameraPos,cameraFront+cameraPos, cameraUp);//摄像机位置，摄像机关注点，上方向
			
			projection = glm::mat4(1);//投影矩阵
			projection = glm::perspective(glm::radians(fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);//fov，宽高比，近距离，远距离


			int transformLoc = glGetUniformLocation(shader->ID, "transform");//获取缩放参数id
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));//设置缩放参数
			int modelLoc = glGetUniformLocation(shader->ID, "model");//获取模型到世界变换参数id
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));//设置模型到世界变换参数
			int viewLoc = glGetUniformLocation(shader->ID, "view");//获取世界到相机参数id
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));//设置世界到相机参数
			int projectionLoc = glGetUniformLocation(shader->ID, "projection");//获取相机到投影参数id
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));//设置相机到投影参数
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);//第一个顶点，一共36个顶点	
		}
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
	
} 





