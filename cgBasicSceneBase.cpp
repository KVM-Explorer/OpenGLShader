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
	auto pTriagnle = std::make_shared<cgTriangle>();
	pTriagnle->Init();
	pTriagnle->CalculateModelMatrix();
	AddElement(pTriagnle);
}

void cgBasicSceneBase::Render()
{
	for (auto iterator = elementsArray.begin(); iterator != elementsArray.end(); iterator++)
	{
		(*iterator)->Render(mat4Projection);
	}
}
