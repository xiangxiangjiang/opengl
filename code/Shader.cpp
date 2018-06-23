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
void Shader::setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}