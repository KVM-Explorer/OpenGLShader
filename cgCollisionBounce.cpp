#include "pch.h"
#include "cgCollisionBounce.h"
#include "cgPentagram.h"
#include "cgRectangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

cgCollisionBounce::cgCollisionBounce()
{
    beta = 0;
    positionX = 100;
    positionY = 100;
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
    
    
    if (positionX <= 500 && positionY == 500) positionX += deltaX;
    if (positionX == 500 && positionY >= 100) positionY -= deltaY;
    if (positionX > 100 && positionY == 100) positionX -= deltaX;
    if (positionX == 100 && positionY <= 500) positionY += deltaY;
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
    
    pentagram_ptr->SetPosition((pentagram_ptr->GetAngle()) + 15,vec3(positionX,positionY,0));
    pentagram_ptr->CalculateModelMatrix();
    
}

void cgCollisionBounce::SetProjection(int width, int height)
{
    //auto projection = glm::ortho(0.0f, (float)600, 0.0f, (float)600);//?û????귶Χ????ά?ü??ռ䣩

}

void cgCollisionBounce::SetProjection(mat4 projection)
{
    projectionMat = projection;
}
