	 #pragma once
#include <string>
#include <glad/glad.h>
#include <vec2.hpp>
#include <map>





namespace Renderer
{

	class Texture2d
	{
	public:

		struct SubTexture2d
		{
			glm::vec2 leftBottomUV;
			glm::vec2 righttTopUV;
			SubTexture2d(const glm::vec2& _leftBottomUV ,	const glm::vec2& _righttTopUV ) 
				: leftBottomUV(_leftBottomUV),
					righttTopUV(_righttTopUV) 
			{}

			SubTexture2d()
				: leftBottomUV(0.f),
				righttTopUV(1.f) 
			{}



		};




		Texture2d(const GLuint width, 
				const GLuint height, 
				const unsigned char* data, 
				const unsigned int channels, 
				const GLenum filter , const GLenum wrapmode); //конструктор

		
		Texture2d() = delete;
		Texture2d(const Texture2d&) = delete;	
		Texture2d& operator=(const Texture2d&) = delete;	
		Texture2d& operator=(Texture2d&&) ;	
		Texture2d(Texture2d&&) ;

		~Texture2d(); //деструктор

	
		
		void addSubTexture( std::string& name, const glm::vec2& leftBottomUV, const glm::vec2& righttTopUV); //добавление субтекстуры
		const SubTexture2d& getSubTexture(const std::string& name) const; //получение субтекстуры по имени 
		void bind() const; //привязка текстуры к текстурному блоку
		
	private:
			
		GLint m_ID; //идентификатор текстуры
		unsigned int m_width; //ширина текстуры
		unsigned int m_height; //высота текстуры
		GLenum m_mode; //внутренний формат текстуры

		std::map<std::string, SubTexture2d> m_subTextures; //карта субтекстур 

	};




}

