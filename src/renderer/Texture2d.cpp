#include "Texture2d.h"



namespace Renderer
{


	Renderer::Texture2d::Texture2d(const GLuint width, const GLuint height,
					const unsigned char* data,
					const unsigned int channels,
					const GLenum filter,
					const GLenum wrapmode) 
		:m_width(width), m_height(height)

	{
		//glGenTextures(1, (GLuint*)&m_ID);
		//glTexImage2D(GL_TEXTURE_2D, 0, (channels == 4) ? GL_RGBA : GL_RGB, width, height, 0, (channels == 4) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);  
		switch (channels)
		{
		case 1:
			m_mode = GL_RED;
			break;
		case 2:
			m_mode = GL_RG;
			break;
		case 3:
			m_mode = GL_RGB;
			break;
		case 4:
			m_mode = GL_RGBA;
			break;
		default:
			m_mode = GL_RGB;
			break;
		}
		
		
		glGenTextures(1, (GLuint*)&m_ID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapmode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapmode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);




	}

	
	Texture2d& Texture2d::operator=(Texture2d&&  texture2d)
	{
		// TODO: insert return statement here
		glDeleteTextures(1, (GLuint*)&m_ID);
		m_ID = texture2d.m_ID;
		texture2d.m_ID = 0;
		m_width = texture2d.m_width;
		m_height = texture2d.m_height;
		m_mode = texture2d.m_mode;

		return* this;


	}

	Texture2d::Texture2d(Texture2d&& texture2d)
	{
		m_ID = texture2d.m_ID;
		texture2d.m_ID = 0;
		m_width = texture2d.m_width;
		m_height = texture2d.m_height;
		m_mode = texture2d.m_mode;

	}

	Texture2d::~Texture2d()
	{
		//glDeleteTextures(1, &m_ID);
		glDeleteTextures(1, (GLuint*)&m_ID);
	}

	void Renderer::Texture2d::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}




}


 