#include "pch.h"
#include "cgCollisionBounce.h"
#include "cgPentagram.h"
#include "cgRectangle.h"

cgCollisionBounce::cgCollisionBounce()
{
    beta = 0;
    positionX = 200;
    positionY = 300;
    deltaX = 10;
    deltaY = 10;
}

cgCollisionBounce::~cgCollisionBounce()
{
}

void cgCollisionBounce::Init()
{
    auto rect_ptr = std::make_shared<cgRectangle>(0,vec3(300,300,0));
    rect_ptr->Init();
    rect_ptr->CalculateModelMatrix();
    AddElement(rect_ptr);

    auto pentagram_ptr = std::make_shared<cgPentagram>(beta,vec3(positionX,positionY,0));
    pentagram_ptr->SetType(2);
    pentagram_ptr->Init();
    pentagram_ptr->CalculateModelMatrix();
    AddElement(pentagram_ptr);
}

void cgCollisionBounce::Render()
{
	for (auto iterator = elementsArray.begin(); iterator != elementsArray.end(); iterator++)
	{
		(*iterator)->Render(projectionMat);
	}
}

void cgCollisionBounce::Update()
{
    positionX += deltaX;
    positionY += deltaY;
    
    if(positionX>500||positionX<100)deltaX = -deltaX;
    if(positionY>500||positionY<100)deltaY = -deltaY;
    int length = elementsArray.size();
    /* elementsArray.pop_back();
    TRACE("Angle: %d\n", beta);
    auto pentagram_ptr = std::make_shared<cgPentagram>(beta,vec3(positionX,positionY,0));
    pentagram_ptr->SetType(2);
    pentagram_ptr->Init();
    pentagram_ptr->CalculateModelMatrix();
    AddElement(pentagram_ptr);*/

    auto element_ptr = elementsArray[1];
    auto pentagram_ptr = std::dynamic_pointer_cast<cgPentagram>(element_ptr);
    //Todo £¿£¿ ½Ç¶È´æÔÚÌø±ä
    pentagram_ptr->SetPosition((pentagram_ptr->GetAngle()) + 15,vec3(positionX,positionY,0));
    pentagram_ptr->CalculateModelMatrix();
    
}