#include "pch.h"
#include "SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/color_space.hpp>

SceneManager::SceneManager()
{
	camera.init();

	projectMatrix = glm::perspective(glm::radians(60.f), 1.f, 1.f, 300.f);
}

SceneManager::~SceneManager()
{
}

void SceneManager::setFileDirectory(string dir)
{
	// Files
	dataLoader.getFiles(dir);
	dataLoader.initFiles();

	// MeshManager
	meshManager.init(dataLoader.getDataStructure());
	auto data_property = dataLoader.getPropertyDataText("pressure.pro");
	meshManager.setProperty(data_property);

	
	// ColorPatch
	//colorPatch.setRange();
	//colorPatch.init();
}

void SceneManager::render()
{
	/// Mesh
	meshManager.setViewMatrix(camera.getViewMatrix());
	meshManager.setProjection(projectMatrix);
	meshManager.render();

	/// Color Patch
	// Todo update the content
	//colorPatch.setPosition(camera.getPosition());
	colorPatch.setProjection(projectMatrix);
	colorPatch.setViewMatrix(camera.getViewMatrix());
	colorPatch.render();

}

void SceneManager::setProjection(int width, int height)
{
	projectMatrix = glm::perspective(glm::radians(60.f), float(width) / float(height), 1.0f, 3000.f);
}

void SceneManager::setInputSignal(const unsigned char& key, InputType type,int value)
{
	if (type == InputType::Keyboard) camera.inputKeyboard(key);
	if (type == InputType::Mouse) camera.inputMouse(key, value);

}

void SceneManager::setColorMin(unsigned char r, unsigned char g, unsigned char b)
{
	auto hsv = glm::hsvColor(vec3(float(r / 255.f), float(g / 255.f), float(b / 255.f)));
	colorPatch.setColorMin(hsv);
}

/**
 * @brief 设置颜色上界
 * @param r 0-255
 * @param g 0-255
 * @param b 0-255
*/
void SceneManager::setColorMax(unsigned char r, unsigned char g, unsigned char b)
{
	auto hsv = glm::hsvColor(vec3(float(r/255.f),float( g/255.f), float(b/255.f)));
	colorPatch.setColorMax(hsv);
}
