#pragma once
#include<glad/glad.h>
#include<vec2.hpp>
#include<memory> 



namespace Renderer
{

	class ShaderProgram;
	class Texture2d;


	class Sprite
	{


	public:
		Sprite(const std::shared_ptr <Texture2d> pTexture,
				const std::shared_ptr <ShaderProgram> pShaderProgram,
				const glm::vec2& position = glm::vec2(0.f),
				const glm::vec2& size = glm::vec2(1.f),
				const float rotation = 0.f);
		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void render() const;
		void setPosition(const glm::vec2& position);
		void setSize(const glm::vec2& size);
		void setRotation(const float rotation);

	private:
		std::shared_ptr<Texture2d> m_pTexture;
		std::shared_ptr <ShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
		GLuint m_VAO;
		GLuint m_vertexCoordsVBO;
		GLuint m_textureCoordsVBO;
	};

}