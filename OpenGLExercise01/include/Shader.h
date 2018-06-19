#pragma once
#include<string>
class Shader
{
	public:
		Shader(const char* vetexPath,const char* fragmentPath);
		std::string vertexString;
		std::string fragmentString;
		const char* vertexSource;
		const char* fragementSource;
		unsigned int ID;     //shader Program ID
		void use();          // π”√∏√shader
				

	private:
		void checkCompileErrors(unsigned int shader, std::string type);
};

