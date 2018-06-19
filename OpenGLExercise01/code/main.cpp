#include <iostream>    //导入系统的头文件
#include "Shader.h"     //导入本项目的头文件
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

	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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


int main() 
{
	glfwInit();   //初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//高版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//低版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//配置

	GLFWwindow* window = glfwCreateWindow(800, 600, "My openGL game", NULL, NULL);
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

	Shader* shader = new Shader("resource/vertexShader.txt","resource/fragmentShader.txt");//创建shader

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
	unsigned char* data1 = stbi_load("resource/container.jpg",&width1,&height1,&nrChannels1,0);//处理纹理
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
	unsigned char* data2 = stbi_load("resource/awesomeface.png", &width2, &height2, &nrChannels2, 0);//处理纹理
	
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






	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0*sizeof(float)));//参数0，顶点的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(0);//使能参数0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));//参数1，颜色的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(1);//使能参数1
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));//参数2，颜色的参数个数，float类型，不归一化，间隔，偏移
	glEnableVertexAttribArray(2);//使能参数2


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//从cup获取时间，修改shader输出的颜色
		/*float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);*/
		
		//画图	
		shader->use();
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/*
		第一个参数指定了我们绘制的模式，这个和glDrawArrays的一样。第二个参数是我们打算绘制顶点的个数，这里填6，也就是说我们一共需要绘制6个顶点。第三个参数是索引的类型，这里是GL_UNSIGNED_INT。最后一个参数里我们可以指定EBO中的偏移量（或者传递一个索引数组，但是这是当你不在使用索引缓冲对象的时候），但是我们会在这里填写0。
		*/
		//导入纹理
		//glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 6);//第一个顶点，一共6个顶点


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
	
} 





