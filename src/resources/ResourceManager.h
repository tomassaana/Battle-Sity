#pragma once
#include <string>
#include <iostream>
#include <memory>	
#include <map>	
 


namespace Renderer
{
	class ShaderProgram;
	class Texture2d;

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
	
	std::shared_ptr<Renderer::ShaderProgram> loadShader(const std::string& shaderName, 
													const std::string& vertexShaderPath, 
													const std::string& fragmentShaderPath);
	 
	std::shared_ptr<Renderer::ShaderProgram> getShader(const std::string& shaderName) const;

	//load texture
	std::shared_ptr<Renderer::Texture2d> loadTexture(const std::string& textureName, const std::string& texturePath);

	
	std::shared_ptr<Renderer::Texture2d> getTexture(const std::string& textureName) const;




private:

	typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;
	std::string m_executablePath;
	std::string getFileString(const std::string& relativePath) const;

	typedef std::map<std::string, std::shared_ptr<Renderer::Texture2d>> TexturesMap;
	TexturesMap m_textures;








};

