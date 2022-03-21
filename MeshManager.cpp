#include "pch.h"
#include "MeshManager.h"

MeshManager::MeshManager()
{
	stX = stY = stZ = 0;
}

MeshManager::~MeshManager()
{
}

void MeshManager::init(DS data_struct)
{
	shader.CompileShader("Shader/project/basic.vert");
	shader.CompileShader("Shader/project/basic.frag");
	shader.Link();

	dataStructure = data_struct;

	for(int x=0;x<dataStructure.x;x++)
		for(int y=0;y<dataStructure.y;y++)
			for (int z = 0; z < dataStructure.z; z++)
			{
				auto st = &dataStructure.buffer.get()[x * y * z * 6];
				auto unit = std::make_shared<Unit>();
				unit->init(std::shared_ptr<float[]>(st));
				units.emplace_back(unit);
			}
}

void MeshManager::render()
{
	shader.Use();
	for (auto& x : units)
	{
		x->render();
	}
	shader.Unuse();
}

void MeshManager::setProjection(mat4 proj)
{
	projection = proj;
}

void MeshManager::setViewMatrix(mat4 view_matrix)
{
	viewMatrix = view_matrix;
}

void MeshManager::selectViewRange(int x, int y, int z)
{
	stX = x;
	stY = y;
	stZ = z;
}
