	 #pragma once
#include <string>
#include <glad/glad.h>
#include <iostream>	



namespace Renderer
{

	class Texture2d
	{
	public:
		Texture2d(const GLuint width, const GLuint height, const unsigned char* data, const unsigned int channels, const GLenum filter , const GLenum wrapmode); //�����������

		
		Texture2d() = delete;
		Texture2d(const Texture2d&) = delete;	
		Texture2d& operator=(const Texture2d&) = delete;	
		Texture2d& operator=(Texture2d&&) ;	
		Texture2d(Texture2d&&) ;

		~Texture2d(); //����������

		void bind() const; //�������� �������� � ����������� �����

	//	void bind(const GLuint textureUnit = 0) const; //�������� �������� � ����������� �����




	private:
			
		GLint m_ID; //������������� ��������
		unsigned int m_width; //������ ��������
		unsigned int m_height; //������ ��������
		//unsigned int m_channels; //���������� �������
		//glenum m_filter; //������ ��������
		//glenum m_wrapmode; //����� ������� ��������
		//bool m_isloaded; //���� �������� ��������
		GLenum m_mode; //���������� ������ ��������



	};




}

