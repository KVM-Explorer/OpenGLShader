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
	mat4 viewMatrix;
	mat4 projection;
	mat4 modelMatrix;	// Todo update position
	DS dataStructure;
	int stX, stY, stZ;
	vec3 centerPos;

protected:
	cgProgram shader;
	cgProgram cubeShader;
	std::shared_ptr<cgCube> cube;
	std::vector<std::shared_ptr<Unit>> units;
	ModeType renderMode;

public:
	MeshManager();
	~MeshManager();

	void init(DS data_struct);


	void render();
	//void setScaleRatio(float ratio);	// 模型变换缩放
	void setProperty(PS property_struct);
	void setProjection(mat4 proj);
	void setViewMatrix(mat4 view_matrix);
	void selectViewRange(int dimension,int st);// 展示x-xmax y-ymax z-zmax 区间内的网格
	void setRenderMode(ModeType type);
	ModeType getRenderMode() const;
	mat4 getModelMat();
};

