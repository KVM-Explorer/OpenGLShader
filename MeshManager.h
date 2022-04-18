#pragma once
#include "Unit.h"
#include "cgProgram.h"
#include "DataLoader.h"
#include "cgCube.h"
#include <vector>

using ModeType = Unit::Mode;
using DS = DataLoader::DataStructure;
using PS = DataLoader::PropertyStructure;
class MeshManager
{
private:
	DS dataStructure;
	int stX;
	int stY;
	int stZ;
	vec3 centerPos;
	[[maybe_unused]]bool refineFlag;
protected:
	std::vector<std::shared_ptr<Unit>> units;
	ModeType renderMode;

public:
	MeshManager();
	~MeshManager();

	void init(DS data_struct);
	/**
	 * @brief ����ϸ��
	 * @param data_struct 
	 * @param multiple ����ά������Ϊ2^multiple
	*/
	void initRefineMesh(DS data_struct, int multiple);


	void render();
	void setProperty(PS property_struct);
	/**
	 * @brief ��������ֵϸ��
	 * @param property_struct 
	*/
	void setRefineProperty(PS property_struct);

	void selectViewRange(int dimension,int st);// չʾx-xmax y-ymax z-zmax �����ڵ�����
	void setRenderMode(ModeType type);
	ModeType getRenderMode() const;
	mat4 getModelMat();
};

