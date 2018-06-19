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
	ifstream vertexFile;//vertex shader�����ļ�
	ifstream fragmentFile;//fragment shader�����ļ�

	stringstream vertexSStream;   //vertex�ַ���������
	stringstream fragmentSStream;	//fragment�ַ���������

	vertexFile.open(vetexPath);  //��shader�����ļ�
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::badbit || ifstream::failbit);
	fragmentFile.exceptions(ifstream::badbit || ifstream::failbit);

	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open()) //��ʧ��
		{
			throw exception("open file error");
		}
		vertexSStream << vertexFile.rdbuf();   //���뻺��
		fragmentSStream << fragmentFile.rdbuf();
		vertexString = vertexSStream.str();    //תΪ�ַ���
		fragmentString = fragmentSStream.str();

		//cout << vertexString << endl;          //��ӡ
		//cout << fragmentString << endl;

		vertexSource = vertexString.c_str();   //תΪC�ַ���
		fragementSource = fragmentString.c_str();

		unsigned int vertexShader;   //������ɫ��
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);//����
		checkCompileErrors(vertexShader, "VERTEX");


		unsigned int fragmentShader;   //ƬԪ��ɫ��
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragementSource, NULL);
		glCompileShader(fragmentShader);//����
		checkCompileErrors(vertexShader, "FRAGMENT");
										//���ӳ�Program
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
