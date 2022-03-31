#include "pch.h"
#include "MeshManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

MeshManager::MeshManager()
{
	stX = stY = stZ = 0;
	renderMode = ModeType::smooth;
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
			}

}


void MeshManager::render()
{
	if(renderMode==ModeType::mesh)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for(int z= stZ;z<dataStructure.z;z++)
		for(int y=stY;y<dataStructure.y;y++)
			for (int x = stX; x < dataStructure.x; x++)
			{
				int index = x + y*dataStructure.x+ z * dataStructure.x * dataStructure.y;
				units[index]->render();
			}
}

void MeshManager::setProperty(PS property_struct)
{
	auto getSmoothValue = [this,property_struct](int u)
	{
		using namespace std;
		float tmp = property_struct.buffer[u];
		int z = u / (dataStructure.x * dataStructure.y);	u -= z * dataStructure.x * dataStructure.y;
		int y = u / dataStructure.x;						u -= y * dataStructure.x;
		int x = u;

		vector<float> result;
		const int fx[][8] = {	{0,0,-1,-1,0,0,-1,-1}, 
								{0,1,1,0,0,1,1,0}};
		const int fy[][8] = {	{0,-1,0,-1,0,-1,0,-1}, 
								{0,0,1,1,0,0,1,1} };
		const int fz[][8] = {	{0,0,0,0,-1,-1,-1,-1}, 
								{0,0,0,0,1,1,1,1}};
		for (int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++)
				{
					int tot = 8;
					float averg = 0.f;
					for (int u = 0; u < 8; u++)
					{
						int dx = x + fx[k][u];
						int dy = y + fy[j][u];
						int dz = z + fz[i][u];
						if (dx < 0 || dy < 0 || dz < 0
							||dx>=dataStructure.x||dy>=dataStructure.y||dz>=dataStructure.z)
						{
							tot--;
							continue;
						}
						int pos = dz * dataStructure.x * dataStructure.y + dy * dataStructure.x + dx;
						averg = averg + property_struct.buffer[pos];
					}
					if(tot!=0)averg = averg / (float)tot;
					result.push_back(averg);
				}
			}
		}
		return result;
	};

	int index = 0;
	for (auto& x : units)
	{
		switch (renderMode)
		{
		case ModeType::single:
			x->setValue(property_struct.buffer[index]);
			break;
		case ModeType::smooth:
			x->setValue(getSmoothValue(index));
			break;
		default:
			x->setValue(property_struct.buffer[index]);
			break;
		}	
		index++;
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

ModeType MeshManager::getRenderMode() const
{
	return renderMode;
}
