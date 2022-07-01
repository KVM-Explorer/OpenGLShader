#include "pch.h"
#include "cgRayTraceScene.h"
#include "pch.h"
#include "cgRayTraceScene.h"
#include "RayTrace.h"

cgRayTraceScene::cgRayTraceScene()
{
}

cgRayTraceScene::~cgRayTraceScene()
{
}
void cgRayTraceScene::Init()
{
	computerShader.CompileShader("Shader/computer/raytrace.comp");
	computerShader.Link();

	
	glGenTextures(1, &tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexStorage2D(GL_TEXTURE_2D, 8, GL_RGBA32F, 512, 256);
}

void cgRayTraceScene::Render()
{
	computerShader.Use();
	glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	glDispatchCompute(W, H, 1);
	computerShader.Unuse();

	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	for (auto iterator = elementsArray.begin(); iterator != elementsArray.end(); iterator++)
	{
		(*iterator)->Render(projectionMat);
	}
	
}

void cgRayTraceScene::Update()
{
}

void cgRayTraceScene::SetProjection(mat4 projection)
{
	projectionMat = projection;
}

void cgRayTraceScene::SetProjection(int width, int height)
{
}

void cgRayTraceScene::AddElement(std::shared_ptr<cgElement> element)
{
	elementsArray.push_back(element);
}

