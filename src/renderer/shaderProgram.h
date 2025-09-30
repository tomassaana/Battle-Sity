#pragma	once
#include <string>
#include <glad/glad.h>
#include <iostream>
#include <mat4x4.hpp>	



namespace Renderer
{

	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& frameShader );
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& SP)  noexcept;
		ShaderProgram(ShaderProgram&& SP)  noexcept;

		void SetMatrix4(const std::string& name, const glm::mat4& matrix ) const;




		~ShaderProgram();
		bool isCompiled() const { return m_iscompiled; }
		void use() const;	
		void setInt(const std::string& name, const int value) const;
		
	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_iscompiled = false;
		GLuint m_ID = 0 ;
	};



}