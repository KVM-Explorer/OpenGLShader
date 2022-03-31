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
	std::map<std::string, ModeType> keyFromString;
	std::map<ModeType, std::unique_ptr<cgProgram>> shaderFromType;
	string propertyName;
protected:
	mat4 projectMatrix;
	DataLoader	dataLoader;
	ColorPatch	colorPatch;
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
	/**
	 * @brief 设置颜色下界
	 * @param r 0-255
	 * @param g 0-255
	 * @param b 0-255
	*/
	void setColorMin(unsigned char r, unsigned char g, unsigned char b);
	/**
	 * @brief 设置颜色上界
	 * @param r 0-255
	 * @param g 0-255
	 * @param b 0-255
	*/
	void setColorMax(unsigned char r, unsigned char g, unsigned char b);
	void setRenderMode(std::string mode);
	void setScaleRatio(float ratio);
	void setTimeStamp(int time);
	void setProperty(string property_name);


};

