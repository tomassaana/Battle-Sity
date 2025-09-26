	 #pragma once
#include <string>
#include <glad/glad.h>
#include <iostream>	



namespace Renderer
{

	class Texture2d
	{
	public:
		Texture2d(const GLuint width, const GLuint height, const unsigned char* data, const unsigned int channels, const GLenum filter , const GLenum wrapmode); //конструктор

		
		Texture2d() = delete;
		Texture2d(const Texture2d&) = delete;	
		Texture2d& operator=(const Texture2d&) = delete;	
		Texture2d& operator=(Texture2d&&) ;	
		Texture2d(Texture2d&&) ;

		~Texture2d(); //деструктор

		void bind() const; //привязка текстуры к текстурному блоку

	//	void bind(const GLuint textureUnit = 0) const; //привязка текстуры к текстурному блоку




	private:
			
		GLint m_ID; //идентификатор текстуры
		unsigned int m_width; //ширина текстуры
		unsigned int m_height; //высота текстуры
		//unsigned int m_channels; //количество каналов
		//glenum m_filter; //фильтр текстуры
		//glenum m_wrapmode; //режим обертки текстуры
		//bool m_isloaded; //флаг загрузки текстуры
		GLenum m_mode; //внутренний формат текстуры



	};




}

