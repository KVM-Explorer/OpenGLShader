#pragma once
#include "Camera.h"
#include "MeshManager.h"
#include "ColorPatch.h"
#include "Indicator3D.h"
#include "DataLoader.h"
using std::string;

enum class InputType
{
	Keyboard,
	Mouse
};

class SceneManager
{
private:
	mat4 projectMatrix;
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
	void setProjection(int width,int height);
	void setInputSignal(const unsigned char& key, InputType type,int value = 0);

};

