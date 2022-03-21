#pragma once
#include "Unit.h"
#include "cgProgram.h"
#include "DataLoader.h"
#include <vector>
using DS = DataLoader::DataStructure;
class MeshManager
{
private:
	mat4 viewMatrix;
	mat4 projection;
	DS dataStructure;
	int stX, stY, stZ;
protected:
	cgProgram shader;
	std::vector<std::shared_ptr<Unit>> units;
public:
	MeshManager();
	~MeshManager();

	void init(DS data_struct);

	void render();
	//void setScaleRatio(float ratio);	// 模型变换缩放
	void setProjection(mat4 proj);
	void setViewMatrix(mat4 view_matrix);
	void selectViewRange(int x, int y, int z); // 展示x-xmax y-ymax z-zmax 区间内的网格

};

