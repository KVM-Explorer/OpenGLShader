#include "pch.h"
#include "MeshManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

MeshManager::MeshManager()
{
	stX = stY = stZ = 0;
	viewMode = ModeType::mesh;
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
				auto st = x * y * z*24 ;
				auto unit = std::make_shared<Unit>();
				unit->init(dataStructure.buffer,st);
				units.push_back(unit);
			}
	
	//auto p = dataStructure.buffer.use_count();	// ptr 引用数为3 loader 1 Meshmanager 2 data_struct 3

	cubeShader.CompileShader("Shader/cg3DScene/3d.vert");
	cubeShader.CompileShader("Shader/cg3DScene/3d.frag");
	cubeShader.Link();

	cube = std::make_shared<cgCube>();
	cube->Init();
	cube->SetPosition(vec3(0.f, 0.f, 0.f));
	cube->CalculateModelMatrix();
	//cube->SetTextureID(0);

}

void MeshManager::render()
{
	if(viewMode==ModeType::mesh)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader.Use();
	modelMatrix = glm::translate(vec3(0.f,0.f,0.f));
	shader.SetUniform("ProjectionMatrix",projection);
	shader.SetUniform("ViewMatrix",viewMatrix);
	shader.SetUniform("ModelMatrix", modelMatrix);
	for (auto& x : units) 
	{
		x->render();
	}
	shader.Unuse();


	cubeShader.Use();
	auto model = cube->GetModelMatrix();
	cubeShader.SetUniform("ProjectionMatrix",projection);
	cubeShader.SetUniform("ModelMatrix",model);
	cubeShader.SetUniform("ViewMatrix", viewMatrix);
	cubeShader.SetUniform("ObjectColor", vec3(1.f, 1.f, 0.f));

	cube->Render();
	cubeShader.Unuse();

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
