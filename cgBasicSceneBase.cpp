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
		(*iterator)->Render(mat4Projection);
	}
}

void cgBasicSceneBase::Update()
{
}

void cgBasicSceneBase::AddElement(std::shared_ptr<cgElement> element)
{
	elementsArray.push_back(element);
}
