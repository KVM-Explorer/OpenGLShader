#include "pch.h"
#include "cgBasicSceneBase.h"
#include "cgTriangle.h"

cgBasicSceneBase::cgBasicSceneBase()
{
}

cgBasicSceneBase::~cgBasicSceneBase()
{
}
void cgBasicSceneBase::Init()
{

}

void cgBasicSceneBase::Render()
{
	for (auto iterator = elementsArray.begin(); iterator != elementsArray.end(); iterator++)
	{
		(*iterator)->Render(projectionMat);
	}
}

void cgBasicSceneBase::Update()
{
}

void cgBasicSceneBase::SetProjection(mat4 projection)
{
	projectionMat = projection;
}

void cgBasicSceneBase::SetProjection(int width, int height)
{
}

void cgBasicSceneBase::AddElement(std::shared_ptr<cgElement> element)
{
	elementsArray.push_back(element);
}

