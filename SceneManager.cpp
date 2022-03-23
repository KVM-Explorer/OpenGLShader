#include "pch.h"
#include "SceneManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

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
}

void SceneManager::render()
{
	meshManager.setViewMatrix(camera.getViewMatrix());
	meshManager.setProjection(projectMatrix);
	meshManager.render();
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
