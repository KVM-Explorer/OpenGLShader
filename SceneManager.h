#pragma once
#include "Camera.h"
#include "MeshManager.h"
#include "ColorPatch.h"
#include "Indicator3D.h"
#include "DataLoader.h"
using std::string;
using ViewMode = Camera::ViewMode;

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
	mat4 orthoMatrix;
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
	void setColorType(int type);
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
	//void setScaleRatio(float ratio);
	void selectShowData(int index);
	void setProperty(string property_name);
	bool showNext();
	bool showPre();
	/**
	 * @brief 获得当前属性下的帧数目
	 * @return 
	*/
	int getFrameNum() const;
	void setShowRange(int dimension,int st);
	int getStRange(int dimension) const;
	/**
	 * @brief 设置视角模式
	 * @param type 0-XY 1-XZ 2-YZ 3-3D
	*/
	void setViewMode(int type);
	void setBlockNum(int num);
};

