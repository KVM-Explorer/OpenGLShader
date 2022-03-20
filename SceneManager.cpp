#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::SetFileDirectory(string dir)
{
	dataLoader.getFiles(dir);
	dataLoader.initFiles();
}
