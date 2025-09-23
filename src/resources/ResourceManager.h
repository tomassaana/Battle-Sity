#pragma once
#include <string>
#include <iostream>
#include <memory>	
#include <map>	
 


namespace Renderer
{
	class ShaderProgram;
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


private:

	typedef std::map<std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;
	std::string m_executablePath;
	std::string getFileString(const std::string& relativePath) const;


};

