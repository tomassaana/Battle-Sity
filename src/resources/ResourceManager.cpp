#include "ResourceManager.h"
#include "../Renderer/shaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>



ResourceManager::ResourceManager(const std::string& executablepath)
{

	size_t lastSlash = executablepath.find_last_of("/\\");
	m_executablePath = executablepath.substr(0, lastSlash + 1);




}

std::string ResourceManager::getFileString(const std::string& relativePath) const 
{
	std::ifstream file;
	file.open(m_executablePath + "/" +  relativePath.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Error open file:" << relativePath << std::endl;
		return std::string();
	}
	std::stringstream fbuffer;
	fbuffer << file.rdbuf();
	file.close();
	return fbuffer.str();

}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::loadShader(const std::string& shaderName, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{

	std::string vertexShaderStr = getFileString(vertexShaderPath);
	if (vertexShaderStr.empty())
	{
		std::cout << "Error load vertex shader: Empty file or not file" << std::endl;
		return nullptr;
	}
	std::string fragmentShaderStr = getFileString(fragmentShaderPath);
	if (fragmentShaderStr.empty())
	{
		std::cout << "Error load vertex shader: Empty file or not file" << std::endl;
		return nullptr;
	}


	std::shared_ptr<Renderer::ShaderProgram>& newshader = m_shaderPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexShaderStr, fragmentShaderStr)).first->second;
	if (newshader->isCompiled()) {
		return newshader;
	}
	else {
		m_shaderPrograms.erase(shaderName);
		std::cout << "Error compile shader program" << std::endl;
		return nullptr;


	}
}



std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShader(const std::string& shaderName) const	
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if(it!= m_shaderPrograms.end())
	{
		return it->second;
	}
	else {
		std::cout << "Error get shader: not found shader with name:" << shaderName << std::endl;
		return nullptr;
	}
}