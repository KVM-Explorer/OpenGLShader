#include "pch.h"
#include "cgLightScene.h"
#include "cgCube.h"
#include "cgCylinder.h"
#include "cgSphere.h"
#include "cgLightCube.h"

cgLightScene::cgLightScene()
{
	viewPos = vec3(0, 0, 0);
	alpha = 180.f;
	beta = 0.f;
	viewHead.y = 0.f;
	viewHead.x = sin(alpha / 180.f * PI);
	viewHead.z = cos(alpha / 180.f * PI);

	drawMode = 0;
	lightPos = vec3(0, 1, 2);
}

cgLightScene::~cgLightScene()
{
}

void cgLightScene::Init()
{
	viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
	projectionMat = glm::perspective(glm::radians(60.0f), 1.0f, 1.0f, 200.0f);

	prog.CompileShader("Shader/cgLight/light.vert");
	prog.CompileShader("Shader/cgLight/light.frag");
	prog.Link();

	textureProg.CompileShader("Shader/cgLight/texture.vert");
	textureProg.CompileShader("Shader/cgLight/texture.frag");
	textureProg.Link();


	texture.LoadTexture("texture/40km.bmp");

	// 添加图元
	
	
}

void cgLightScene::Render()
{
	if (!drawMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	cgProgram* shader = nullptr;
	for (auto iter = elementsArray.begin(); iter != elementsArray.end(); ++iter)
	{
		if ((*iter)->GetName() == "sun")
		{
			shader = &prog;
			shader->Use();
			auto sun_ptr = std::dynamic_pointer_cast<cgSphere>((*iter));
			sun_ptr->SetPosition(lightPos);
			sun_ptr->CalculateModelMatrix();
			shader->SetUniform("objectColor", vec3(1, 1, 1));
			shader->SetUniform("ProjectionMatrix", projectionMat);
			shader->SetUniform("ViewMatrix", viewMat);
			shader->SetUniform("lightColor", vec3(1, 1, 1));
			shader->SetUniform("lightPos", lightPos);
			shader->SetUniform("viewPos", viewPos);
			
		}
		if ((*iter)->GetName() == "texture")
		{
			shader = &textureProg;
			shader->Use();

			// Texture
			shader->SetUniform("ProjectionMatrix", projectionMat);
			shader->SetUniform("ViewMatrix", viewMat);
			shader->SetUniform("lightColor", vec3(1, 1, 1));
			shader->SetUniform("lightPos", lightPos);
			shader->SetUniform("viewPos", viewPos);
			shader->SetUniform("ambientColor", vec3(0.5, 0.5, 0.5));
			shader->SetUniform("shiness", 10);
			shader->SetUniform("objectColor", vec3(0, 1, 0));
		
		}
		if ((*iter)->GetName() != "sun" && (*iter)->GetName() != "texture")
		{
			shader = &prog;
			shader->Use();
			shader->SetUniform("objectColor", vec3(0, 0, 1));
			shader->SetUniform("ProjectionMatrix", projectionMat);
			shader->SetUniform("ViewMatrix", viewMat);
			shader->SetUniform("lightColor", vec3(1, 1, 1));
			shader->SetUniform("lightPos", lightPos);
			shader->SetUniform("viewPos", viewPos);
		}

		
		mat4 model = (*iter)->GetModelMatrix();
		shader->SetUniform("ModelMatrix", model);
		(*iter)->Render();
		shader->Unuse();
	}



	//关闭所用的shader
	prog.Unuse();
}


void cgLightScene::SetProjection(int width, int height)
{
	projectionMat = glm::perspective(glm::radians(60.0f), float(width) / height, 1.0f, 300.0f);
}

void cgLightScene::Input(const unsigned int& key)
{
	float step = 0.2f;
	float r = 0;
	switch (key)
	{
	case 'w':
	case 'W':
	case VK_UP:
		viewPos += step * viewHead;
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, vec3(0.f, 1.f, 0.f));
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

		viewPos -= step * glm::normalize(glm::cross(viewHead, vec3(0.f, 1.f, 0.f)));
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
		break;
	case 'd':
	case 'D':
	case VK_RIGHT:

		viewPos += step * glm::normalize(glm::cross(viewHead, vec3(0.f, 1.f, 0.f)));
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.f, 1.f, 0.f));
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
		drawMode++;
		drawMode = drawMode % 2;
		break;
	case 'U':
	case 'u':
		if (beta < 90)beta += 1.0f;
		viewHead.y = sin(beta / 180.f * PI);
		r = cos(beta / 180.f * PI);
		viewHead.x = r * sin(alpha / 180.0f * PI);	// origin is right
		viewHead.z = r * cos(alpha / 180.0f * PI);
		viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));

		break;
	case 'V':
	case 'v':
		if (beta > -90)beta -= 1.0f;
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

	case '1':
		lightPos.x -= step;
		break;
	case '2':
		lightPos.x += step;
		break;
	case '3':
		lightPos.y -= step;
		break;
	case '4':
		lightPos.y += step;
		break;
	case '5':
		lightPos.z -= step;
		break;
	case '6':
		lightPos.z += step;
		break;
	default:
		break;

	}
	TRACE("Light Pos %.2f %.2f %.2f\n", lightPos.x, lightPos.y, lightPos.z);
}

void cgLightScene::Update()
{
}
