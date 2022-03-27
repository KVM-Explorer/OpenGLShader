#include "pch.h"
#include "MeshManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

MeshManager::MeshManager()
{
	stX = stY = stZ = 0;
	renderMode = ModeType::mesh;
}

MeshManager::~MeshManager()
{
}

void MeshManager::init(DS data_struct)
{
	dataStructure = data_struct;
	int st = 0;
	for(int z=0;z<dataStructure.z;z++)
		for(int y=0;y<dataStructure.y;y++)
			for (int x = 0; x < dataStructure.x; x++)
			{
				auto unit = std::make_shared<Unit>();
				unit->init(dataStructure.buffer,st);
				units.emplace_back(unit);
				st += 24;
				TRACE("st = %d\n", st);
			}

}


void MeshManager::render()
{
	if(renderMode==ModeType::mesh)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (auto& x : units) 
	{
		x->render();
	}
}

void MeshManager::setProperty(PS property_struct)
{
	int index = 0;
	for (auto& x : units)
	{
		//  Todo  ¼ÆËãÑÕÉ«
		 x->setValue(property_struct.buffer[index++]);
	}
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

void MeshManager::setRenderMode(ModeType type)
{
	renderMode = type;
}
