#pragma once
#include <string>
//#include <iostream>
#include <memory>	
#include <map>	
 


namespace Renderer
{
	class ShaderProgram;
	class Texture2d;
	class Sprite;
}



	class ResourceManager
	{
	public:
		ResourceManager(const std::string& executablepath);
		~ResourceManager() = default;


		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string& shaderName) const;
		std::shared_ptr<Renderer::Texture2d> loadTexture(const std::string& textureName, const std::string& texturePath);
		std::shared_ptr<Renderer::Texture2d> getTexture(const std::string& textureName) const;

		
		std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName,
													const std::string& textureName,
													const std::string&  shaderName,
													const unsigned int  spriteWidth,
													const unsigned int  spriteHight ) ;
		

		std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName) const;


	private:
		std::string getFileString(const std::string& relativePath) const;

		typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
		ShaderProgramsMap m_shaderPrograms;

		typedef std::map<std::string, std::shared_ptr<Renderer::Texture2d>> TexturesMap;
		TexturesMap m_textures;

		typedef std::map<std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
		SpritesMap m_sprites;


		std::string m_executablePath;
		
		




	};

