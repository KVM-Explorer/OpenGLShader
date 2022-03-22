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
				auto st = x * y * z;
				auto unit = std::make_shared<Unit>();
				unit->init(dataStructure.buffer,st);
				units.push_back(unit);
			}
	
	auto p = dataStructure.buffer.use_count();	// ptr 引用数为3 loader 1 Meshmanager 2 data_struct 3
}

void MeshManager::render()
{
	shader.Use();

	shader.SetUniform("ProjectionMatrix",projection);
	shader.SetUniform("ViewMatrix",viewMatrix);
	//shader.SetUniform("ModelMatrix", modelMatrix);
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
