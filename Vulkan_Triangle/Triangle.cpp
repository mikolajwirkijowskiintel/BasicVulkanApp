#include "Triangle.h"

Triangle::Triangle(float rotationSpeed, glm::vec2 translationSpeed):rotationSpeed(rotationSpeed), translationSpeed(translationSpeed)
{
	transform2d.translation = { 0.0f,0.0f };
	transform2d.rotation = 0.0f;
}
