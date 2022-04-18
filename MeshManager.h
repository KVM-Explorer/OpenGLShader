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
	 * @brief 网格细化
	 * @param data_struct 
	 * @param multiple 但各维度扩充为2^multiple
	*/
	void initRefineMesh(DS data_struct, int multiple);


	void render();
	void setProperty(PS property_struct);
	/**
	 * @brief 网格属性值细化
	 * @param property_struct 
	*/
	void setRefineProperty(PS property_struct);

	void selectViewRange(int dimension,int st);// 展示x-xmax y-ymax z-zmax 区间内的网格
	void setRenderMode(ModeType type);
	ModeType getRenderMode() const;
	mat4 getModelMat();
};

