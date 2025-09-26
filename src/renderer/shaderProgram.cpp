#include "shaderProgram.h"
#include <iostream>

namespace Renderer
{


	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& frameShader)
	{
		GLuint vertexShaderID ;
		if( !createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cout << "Error create vertex shader" << std::endl;	
			return;
		}
		
		GLuint fragmentShaderID ;
		if( !createShader(frameShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cout << "Error create fragment shader" << std::endl;	
			glDeleteShader(vertexShaderID);
			return;
		}

		
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if(!success)
		{
			
			std::cout << "Error link program:"  << std::endl;
			glDeleteProgram(m_ID);
			
		}
		else {	m_iscompiled = true;	}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);


	

		


	}

	bool ShaderProgram::createShader(const std::string& source,	const GLenum shaderType, GLuint& shaderID) 
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);
		
		GLint success ;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			GLint maxLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
			std::string errorLog(maxLength, ' ');
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
			std::cout << "Error compile shader:" << errorLog << std::endl;
			glDeleteShader(shaderID);
			return false;
		}
			return true;
	}
	
	ShaderProgram::~ShaderProgram()
	{
		if(m_ID)
			glDeleteProgram(m_ID);
	}

	void ShaderProgram::use() const
	{
		
		glUseProgram(m_ID);
		
	}
	void ShaderProgram::setInt(const std::string& name, const int value) const
	{

		glUniform1d(glGetUniformLocation(m_ID, name.c_str()), value);
	}




	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& SP) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = SP.m_ID;
		m_iscompiled = SP.m_iscompiled;
		SP.m_ID = 0;
		SP.m_iscompiled = false;
		return *this;

	}
	ShaderProgram::ShaderProgram(ShaderProgram&& SP) noexcept
	{ 
		glDeleteProgram(m_ID);
		m_ID = SP.m_ID;
		m_iscompiled = SP.m_iscompiled;


		SP.m_ID = 0;
		SP.m_iscompiled = false;
	}
	
			




	



}


