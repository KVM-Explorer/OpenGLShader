#include "pch.h"
#include "cg3DScene.h"
#include "cgCube.h"
#include "cgTriangle.h"
#include "cgSphere.h"
#include "cgCylinder.h"


cg3DScene::cg3DScene()
{
	viewPos = vec3(0.f, 1.f, 6.f);
	
	alpha = 180.f;
	beta = 0.f;
	viewHead.y = 0.f;
	viewHead.x = sin(alpha / 180.f * PI);	//0
	viewHead.z = cos(alpha / 180.f * PI);	//-1
	
	yaw = -90.f;
	pitch = 0;

	drawMode = 0;
	sceneType = 0;
}


cg3DScene::~cg3DScene()
{

}

void cg3DScene::Init()
{
	viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
	projectionMat = glm::perspective(glm::radians(60.f), 1.f, 1.f, 60.f);

	prog.CompileShader("Shader/cg3DScene/3d.vert");
	prog.CompileShader("Shader/cg3DScene/3d.frag");
	prog.Link();

	textureProg.CompileShader("Shader/cgTexture/basic.vs");
	textureProg.CompileShader("Shader/cgTexture/basic.frag");
	textureProg.Link();

	texture.LoadTexture("texture/40km.bmp");

	auto cube_ptr = std::make_shared<cgCube>();
	cube_ptr->Init();
	cube_ptr->SetPosition(vec3(0.f, 0.f, 0.f));
	cube_ptr->CalculateModelMatrix();
	cube_ptr->SetName("cube");
	cube_ptr->SetTextureID(texture.GetID());
	elementsArray.push_back(cube_ptr);


	auto sphere_ptr = std::make_shared<cgSphere>(5);
	sphere_ptr->Init();
	sphere_ptr->SetPosition(vec3(30, 10, 0));
	sphere_ptr->CalculateModelMatrix();
	elementsArray.push_back(sphere_ptr);

	std::vector<float> angles;
	std::vector<vec3> roller;

	auto cylinder_ptr = std::make_shared<cgCylinder>(4, 1);
	cylinder_ptr->Init();
	cylinder_ptr->SetPosition(vec3(0.f, 14.f, 0.f));
	angles.push_back(180.f);
	angles.push_back(180.f);
	roller.push_back(vec3(0.f, 0.f, 1.f));
	roller.push_back(vec3(0.f,1.f,0.f));
	cylinder_ptr->SetRotateInfo(angles, roller);
	cylinder_ptr->CalcuteModelMatrix();
	cylinder_ptr->SetName("cylinder");
	cylinder_ptr->SetTextureID(texture.GetID());
	elementsArray.push_back(cylinder_ptr);

	angles.clear(); roller.clear();
	cylinder_ptr = std::make_shared<cgCylinder>(0.5f, 10.f);
	cylinder_ptr->Init();
	cylinder_ptr->SetPosition(vec3(0,5, 0));
	angles.push_back(90.f);
	roller.push_back(vec3(1.f, 0.f, 0.f));
	cylinder_ptr->SetRotateInfo(angles, roller);
	cylinder_ptr->CalcuteModelMatrix();
	cylinder_ptr->SetName("pillar");
	cylinder_ptr->SetTextureID(texture.GetID());
	elementsArray.push_back(cylinder_ptr);


}

void cg3DScene::Render()
{
	if (!drawMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	cgProgram* program_ptr = nullptr;
	vec3 color = vec3(1.f, 0.f, 0.f);
	for (auto iter = elementsArray.begin(); iter != elementsArray.end(); iter++)
	{
		// Todo Select shader program  Render Element texture
		if (sceneType != 0)
		{
			if ((*iter)->GetName() == "cube")
			{
				program_ptr = &textureProg;
				textureProg.Use();
			}
			
			if ((*iter)->GetName() == "cylinder")
			{
				program_ptr = &textureProg;
				textureProg.Use();
			}
			if((*iter)->GetName()!="cube" && (*iter)->GetName()!="cylinder")
			{
				prog.Use();
				program_ptr = &prog;
				prog.SetUniform("ObjectColor", color);
			}
			
		}
		else
		{
			prog.Use();
			program_ptr = &prog;
			prog.SetUniform("ObjectColor", color);
		}
		

		mat4 model = (*iter)->GetModelMatrix();
	
		
		program_ptr->SetUniform("ProjectionMatrix", projectionMat);
		program_ptr->SetUniform("ViewMatrix", viewMat);
		program_ptr->SetUniform("ModelMatrix", model);
		

		
		(*iter)->Render();
		program_ptr->Unuse();
	}

}


void cg3DScene::SetProjection(int width, int height)
{
	projectionMat = glm::perspective(glm::radians(60.f), float(width) / float(height), 1.0f, 300.f);
	
}

void cg3DScene::Input(const unsigned int& key)
{
	float step = 0.2f;
	float r = 0;
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
		break;
	case 'a':
	case 'A':
	case VK_LEFT:

		viewPos -= step * glm::normalize(glm::cross(viewHead,vec3(0.f,1.f,0.f)));
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
		break;
	case 'd':
	case 'D':
	case VK_RIGHT:

		viewPos += step * glm::normalize(glm::cross(viewHead, vec3(0.f, 1.f, 0.f)));
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
		break;
	case 'z':
	case 'Z'://????????
		viewPos.y += 1.1f;
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'x':
	case 'X'://????????
		viewPos.y -= 1.1f;
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case 'f':
	case 'F':
		drawMode++;
		drawMode = drawMode % 2;
		break;
	case 'U':
	case 'u':
		if(beta<90)beta += 1.0f;
		viewHead.y = sin(beta / 180.f * PI);
		r = cos(beta / 180.f * PI);
		viewHead.x = r * sin(alpha / 180.0f * PI);	// origin is right
		viewHead.z = r * cos(alpha / 180.0f * PI);
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));

		break;
	case 'V':
	case 'v':
		if(beta>-90)beta -= 1.0f;
		viewHead.y = sin(beta / 180.f * PI);
		r = cos(beta / 180.f * PI);
		viewHead.x = r * sin(alpha / 180.0f * PI);	// origin is right
		viewHead.z = r * cos(alpha / 180.0f * PI);
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;

	case ']':
		alpha -= 1.0f;
		viewHead.y = sin(beta / 180.f * PI);
		r = cos(beta / 180.f * PI);
		viewHead.x = r * sin(alpha / 180.0f * PI);	// origin is right
		viewHead.z = r * cos(alpha / 180.0f * PI);
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case '[':
		alpha += 1.f;
		viewHead.y = sin(beta / 180.f * PI);
		r = cos(beta / 180.f * PI);
		viewHead.x = r * sin(alpha / 180.0f * PI);	// origin is right
		viewHead.z = r * cos(alpha / 180.0f * PI);
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));

		break;
	default:
		break;

	}
	//TRACE("look: (%d %d %d)\n", viewPos.x + viewHead.x, viewPos.y + viewHead.y, viewPos.z + viewHead.z);
	auto tmp = viewHead + viewPos;
	TRACE("eye: (%.2lf %.2lf %.2lf)\n", tmp.x, tmp.y, tmp.z);
}

void cg3DScene::Update()
{
}

void cg3DScene::SetScene(int type)
{
	sceneType = type;
}

