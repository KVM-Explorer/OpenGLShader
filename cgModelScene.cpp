#include "pch.h"
#include "cgModelScene.h"
#include "cgCube.h"
#include "cgSphere.h"
#include "cgLightCube.h"
#include "cgCylinder.h"

cgModelScene::cgModelScene():ourModel("models/Rabbit/Rabbit.obj")
{
	viewPos = vec3(0.f, 1.f, 6.f);

	alpha = 180.f;
	beta = 0.f;
	viewHead.y = 0.f;
	viewHead.x = sin(alpha / 180.f * PI);	//0
	viewHead.z = cos(alpha / 180.f * PI);	//-1

	lightPos = vec3(0, 1, 2);

	drawMode = 0;
	
}

cgModelScene::~cgModelScene()
{

}

void cgModelScene::Init()
{
	viewMat = glm::lookAt(viewPos, viewPos + viewHead, glm::vec3(0.0f, 1.0f, 0.0f));
	projectionMat = glm::perspective(glm::radians(60.f), 1.f, 1.f, 60.f);

	prog.CompileShader("Shader/cg3DScene/3d.vert");
	prog.CompileShader("Shader/cg3DScene/3d.frag");
	prog.Link();

	textureProg.CompileShader("Shader/cgLight/texture.vert");
	textureProg.CompileShader("Shader/cgLight/texture.frag");
	textureProg.Link();

	texture.LoadTexture("texture/40km.bmp");
	earthTexture.LoadTexture("texture/earth.jpg");

	std::vector<float> angles;
	std::vector<vec3> roller;

	auto cylinder_ptr = std::make_shared<cgCylinder>(4, 1);
	cylinder_ptr->Init();
	cylinder_ptr->SetPosition(vec3(0.f, 14.f, 0.f));
	angles.push_back(180.f);
	angles.push_back(180.f);
	roller.push_back(vec3(0.f, 0.f, 1.f));
	roller.push_back(vec3(0.f, 1.f, 0.f));
	cylinder_ptr->SetRotateInfo(angles, roller);
	cylinder_ptr->CalcuteModelMatrix();
	cylinder_ptr->SetName("texture");
	cylinder_ptr->SetTextureID(texture.GetID());
	AddElement(cylinder_ptr);

	angles.clear(); roller.clear();
	cylinder_ptr = std::make_shared<cgCylinder>(0.5f, 10.f);
	cylinder_ptr->Init();
	cylinder_ptr->SetPosition(vec3(0, 5, 0));
	angles.push_back(90.f);
	roller.push_back(vec3(1.f, 0.f, 0.f));
	cylinder_ptr->SetRotateInfo(angles, roller);
	cylinder_ptr->CalcuteModelMatrix();
	cylinder_ptr->SetName("pillar");
	AddElement(cylinder_ptr);

	auto cube_ptr = std::make_shared<cgLightCube>();
	cube_ptr->Init();
	cube_ptr->SetPosition(vec3(0.f, 0.f, 0.f));
	cube_ptr->SetScaleRatio(vec3(10.f, 0.1f, 10.f));
	cube_ptr->CalculateModelMatrix();
	cube_ptr->SetName("texture");
	cube_ptr->SetTextureID(texture.GetID());
	AddElement(cube_ptr);

	auto sphere_ptr = std::make_shared<cgSphere>(1);
	sphere_ptr->Init();
	sphere_ptr->SetName("sun");
	sphere_ptr->SetPosition(vec3(0, 10, 2));
	sphere_ptr->CalculateModelMatrix();
	//sphere_ptr->SetTextureID(earthTexture.GetID());
	elementsArray.push_back(sphere_ptr);


	ourShader.compileShader("Shader/cgModel/model_loading_light.vert");
	ourShader.compileShader("Shader/cgModel/model_loading_light.frag");
	ourShader.link();

}

void cgModelScene::Render()
{
	//启用需要的shader，可以动态切换不同的shader
	if (!drawMode)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Todo  Use prog
	textureProg.Use();
	for (auto iter = elementsArray.begin(); iter != elementsArray.end(); ++iter)
	{
		unsigned int iTexture;
		/*if ((*iter)->GetName() == "Ground")
			iTexture = texture.GetID();*/
		//else  if ((*iter)->GetName() == "Sphere")
		//	iTexture = earthTexture.GetID();

		if ((*iter)->GetName() == "sun")
		{
			auto sun_ptr = std::dynamic_pointer_cast<cgSphere>((*iter));
			sun_ptr->SetPosition(lightPos);
			sun_ptr->CalculateModelMatrix();
		}

		mat4 model = (*iter)->GetModelMatrix();

		textureProg.SetUniform("ProjectionMatrix", projectionMat);
		textureProg.SetUniform("ViewMatrix", viewMat);
		textureProg.SetUniform("ModelMatrix", model);

		textureProg.SetUniform("lightColor", vec3(1, 1, 1));
		textureProg.SetUniform("lightPos", lightPos);
		textureProg.SetUniform("viewPos", viewPos);
		textureProg.SetUniform("ambientColor", vec3(0.5, 0.5, 0.5));
		textureProg.SetUniform("shiness", 10);

		(*iter)->Render();
	}

	textureProg.Unuse();

	ourShader.use();
	ourShader.setUniform("projection", projectionMat);
	ourShader.setUniform("view", viewMat);

	//模型渲染
	glm::mat4 model;
	model = glm::translate(glm::vec3(5.0f, 5.f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(2.f, 2.f, 2.f));	// it's a bit too big for our scene, so scale it down
	ourShader.setUniform("model", model);
	ourShader.setUniform("lightColor", vec3(1.f, 1.f, 1.f));
	ourShader.setUniform("lightPos", lightPos);
	ourShader.setUniform("viewPos", viewPos);
	ourShader.setUniform("ambientColor", vec3(0.5, 0.5, 0.5));
	ourShader.setUniform("shiness", 10);
	ourModel.Draw(ourShader);
	
}

void cgModelScene::SetProjection(int width, int height)
{
	projectionMat = glm::perspective(glm::radians(60.f), float(width) / float(height), 1.0f, 300.f);
}

void cgModelScene::Input(const unsigned int& key)
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
	//TRACE("look: (%d %d %d)\n", viewPos.x + viewHead.x, viewPos.y + viewHead.y, viewPos.z + viewHead.z);
	auto tmp = viewHead + viewPos;
	TRACE("eye: (%.2lf %.2lf %.2lf)\n", tmp.x, tmp.y, tmp.z);
}

void cgModelScene::Update()
{
}
