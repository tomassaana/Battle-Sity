#include "ResourceManager.h"
#include "../Renderer/shaderProgram.h"
#include "../Renderer/Texture2d.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#define STB_IMAGE_STATIC
#define STBI_ONLY_PNG




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

std::shared_ptr<Renderer::Texture2d> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0, width = 0, height = 0;
	stbi_set_flip_vertically_on_load(true);
	// Load image

	unsigned char* pixels = stbi_load(std::string(m_executablePath + "/" + texturePath).c_str(), &width, &height, &channels, 0);
	if (!pixels) {
		std::cout << "Error load texture: " << texturePath << std::endl;
		return nullptr;
	}	

//	std::shared_ptr<Renderer::Texture2d>& newtexture = 
//		m_textures.emplace(textureName, std::make_shared<Renderer::Texture2d>(width, height, pixels, channels)).first->second;
	std::shared_ptr<Renderer::Texture2d> newtexture2d = 
		m_textures.emplace(textureName, std::make_shared<Renderer::Texture2d>
				(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;


	
	stbi_image_free(pixels);
	return newtexture2d;

}

std::shared_ptr<Renderer::Texture2d> ResourceManager::getTexture(const std::string& textureName) const
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	else {
		std::cout << "Error get textures: not found texture with name:" << textureName << std::endl;
		return nullptr;
	}



	//return std::shared_ptr<Renderer::Texture2d>();
}
