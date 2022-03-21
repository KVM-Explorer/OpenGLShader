#pragma once
#include "Camera.h"
#include "MeshManager.h"
#include "ColorPatch.h"
#include "Indicator3D.h"
#include "DataLoader.h"
using std::string;

class SceneManager
{
protected:
	DataLoader	dataLoader;
	//ColorPatch	colorPatch;
	//Indicator3D indicator3D;
	MeshManager meshManager;
	Camera		camera;
public:
	SceneManager();
	~SceneManager();
	void setFileDirectory(string dir);
	void render();

};

