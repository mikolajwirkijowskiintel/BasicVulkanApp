#pragma once
#include <vector>
#include "Vertex.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE // TODO check if other behavior wasn't actually deprecated in my version of GLM
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

struct Transform2dComponent {
	glm::vec2 translation{};
	float rotation;
	glm::mat2 mat2() {
		float sinx = glm::sin(rotation);
		float cosx = glm::cos(rotation);
		glm::mat2 rotationMatrix{ {cosx, sinx},{-sinx, cosx} };
		return rotationMatrix;
	}
};
// Period for rotation change
const float TIME_PERIOD = 2;
// SCALING OF ANIMATION
const float SCALE = 5;

class Triangle
{
public:
	Triangle(float rotationSpeed, glm::vec2 translationSpeed);
	const std::vector<Vertex> getVertices() const { return vertices; }

	Transform2dComponent getTransform2dAndUpdate(float deltaTime) { 
		animationTimer += deltaTime;
		

		transform2d.rotation +=  SCALE*glm::sin(animationTimer/TIME_PERIOD)*deltaTime * rotationSpeed * 6.28;
		transform2d.rotation = glm::mod(transform2d.rotation, glm::two_pi<float>());

		transform2d.translation += glm::vec2{ deltaTime } * translationSpeed;

		rotationSpeed += rotationAcceleration * deltaTime;
		return transform2d; 
	}

private:
	Transform2dComponent transform2d{};
	float rotationAcceleration = 0.0f;
	float rotationSpeed = 1.0f;

	glm::vec2 translationAcceleration; // TODO implement
	glm::vec2 translationSpeed;

	const std::vector<Vertex> vertices = {
	{{0.0f, -0.5f-0.167f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f-0.167f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f-0.167f}, {0.0f, 0.0f, 1.0f}}
	};

	float animationTimer = 0.0f;

};

