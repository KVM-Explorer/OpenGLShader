#include "pch.h"
#include "cg3DScene.h"
#include "cgCube.h"
#include "cgTriangle.h"

cg3DScene::cg3DScene()
{
	viewPos = vec3(0.f, 1.f, 6.f);

	alphaf = 180.f;
	viewHead.y = 0.f;
	viewHead.x = sin(alphaf / 180.f * PI);
	viewHead.z = cos(alphaf / 180.f * PI);

	mode = 0;
}

cg3DScene::~cg3DScene()
{

}

void cg3DScene::Init()
{
	viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
	projectionMat = glm::perspective(60.f, 1.f, 1.f, 200.f);
	//projectionMat = glm::ortho(0.0f, (float)600, 0.0f, (float)600);

	prog.CompileShader("Shader/cg3DScene/3d.vert");
	prog.CompileShader("Shader/cg3DScene/3d.frag");
	prog.Link();

	// Todo  添加元素
	auto cube_ptr = std::make_shared<cgCube>();
	cube_ptr->Init();
	cube_ptr->SetPosition(vec3(0, -5, -10));
	cube_ptr->CalculateModelMatrix();
	elementsArray.push_back(cube_ptr);


	auto triangle_ptr = std::make_shared<cgTriangle>();
	triangle_ptr->Init();
	triangle_ptr->SetPosition(vec3(300, 300, 0));
	triangle_ptr->CalculateModelMatrix();
	elementsArray.push_back(triangle_ptr);

}

void cg3DScene::Render()
{
	if (!mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	cgProgram* program_ptr = nullptr;
	for (auto iter = elementsArray.begin(); iter != elementsArray.end(); iter++)
	{
		// Todo Select shader program  Render Element texture

		prog.Use();
		program_ptr = &prog;
		/*auto cube_ptr = std::dynamic_pointer_cast<cgCube>(*iter);
		auto cube_pos = cube_ptr->GetPosition();
		TRACE("cube Position: (%.2f,%.2f,%.2f)\n", cube_pos.x, cube_pos.y, cube_pos.z);*/

		mat4 model = (*iter)->GetModelMatrix();
		vec3 color = vec3(1, 0, 0);


		
		program_ptr->SetUniform("ProjectionMatrix", projectionMat);
		program_ptr->SetUniform("ViewMatrix", viewMat);
		program_ptr->SetUniform("ModelMatrix", model);
		program_ptr->SetUniform("ObjectColor", color);

		(*iter)->Render();
		program_ptr->Unuse();
	}

}


void cg3DScene::SetProjection(int width, int height)
{
	projectionMat = glm::perspective(60.f, float(width) / float(height), 1.0f, 3000.f);
	
}

void cg3DScene::Input(const unsigned int& key)
{
	float step = 0.2f;
	switch (key)
	{
	case 'w':
	case 'W':
	case VK_UP:
		viewPos += step * viewHead;
		viewMat= glm::lookAt(viewPos, viewPos + viewHead, vec3(0.f, 1.f, 0.f));
		break;
	case 's':
	case 'S':
	case VK_DOWN:
		viewPos -= step * viewHead;
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, vec3(0.f, 1.f, 0.f));
	case 'a':
	case 'A':
	case VK_LEFT:
		alphaf += 1.0f;
		viewHead.x = sin(alphaf / 180.0f * PI);	// Y不变，逆时针为正
		viewHead.z = cos(alphaf / 180.0f * PI);	// 
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'd':
	case 'D':
	case VK_RIGHT:
		alphaf -= 1.0f;
		viewHead.x = sin(alphaf / 180.0f * PI);	// Todo X Z 是否反了？？？？
		viewHead.z = cos(alphaf / 180.0f * PI);
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'z':
	case 'Z'://抬高相机
		viewPos.y += 1.1f;
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'x':
	case 'X'://降低相机
		viewPos.y -= 1.1f;
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'f':
	case 'F':
		mode++;
		mode = mode % 2;
		break;
	default:
		break;

	}
	TRACE("Position :(%.2lf,%.2lf,%.2lf) Angle: %.2lf\n", viewPos.x, viewPos.y, viewPos.z, alphaf);
}

void cg3DScene::Update()
{
}

