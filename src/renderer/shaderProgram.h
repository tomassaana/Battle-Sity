#pragma	once
#include <string>
#include <glad/glad.h>
#include <iostream>


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
		



		~ShaderProgram();
		bool isCompiled() const { return m_iscompiled; }
		void use() const;	


	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_iscompiled = false;
		GLuint m_ID = 0 ;
	};




	
	





}//ShaderProgam