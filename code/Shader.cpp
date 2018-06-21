#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>
#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>
using namespace std;

Shader::Shader(const char* vetexPath, const char* fragmentPath)
{
	ifstream vertexFile;//vertex shader代码文件
	ifstream fragmentFile;//fragment shader代码文件

	stringstream vertexSStream;   //vertex字符串流缓存
	stringstream fragmentSStream;	//fragment字符串流缓存

	vertexFile.open(vetexPath);  //打开shader代码文件
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::badbit || ifstream::failbit);
	fragmentFile.exceptions(ifstream::badbit || ifstream::failbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) //打开失败
		{
			throw exception("open file error");
		}
		vertexSStream << vertexFile.rdbuf();   //读入缓存
		fragmentSStream << fragmentFile.rdbuf();
		vertexString = vertexSStream.str();    //转为字符串
		fragmentString = fragmentSStream.str();

		//cout << vertexString << endl;          //打印
		//cout << fragmentString << endl;

		vertexSource = vertexString.c_str();   //转为C字符串
		fragementSource = fragmentString.c_str();

		unsigned int vertexShader;   //顶点着色器
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);//编译
		checkCompileErrors(vertexShader, "VERTEX");


		unsigned int fragmentShader;   //片元着色器
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragementSource, NULL);
		glCompileShader(fragmentShader);//编译
		checkCompileErrors(vertexShader, "FRAGMENT");
										//连接成Program
		//unsigned int shaderProgram;
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		checkCompileErrors(vertexShader, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);



	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[512];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
