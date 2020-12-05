#pragma once

#include <glm/glm.hpp>
#include "Controllers/AssetController.h"

class Transform
{
public:
	Transform() {}
	Transform(glm::vec3 pos);
	Transform(glm::vec3 pos, glm::vec3 scale);
	~Transform() {}

	void move(const glm::vec3& offset);
	void rotate(const glm::vec3& angles);
	void scale(const glm::vec3& factor);
	void move(float dx, float dy, float dz);
	void rotate(float ax, float ay, float az);
	void scale(float fx, float fy, float fz);
	void setPosition(const glm::vec3& pos);
	void setRotation(const glm::vec3& newAngles);
	void setScale(const glm::vec3& scale);
	void setPosition(float x, float y, float z);
	void setRotation(float ax, float ay, float az);
	void setScale(float sx, float sy, float sz);
	glm::mat4 convertToMat4() const;

private:
	glm::vec3 pos = glm::vec3(0);
	glm::vec3 eulerRotation = glm::vec3(0);
	glm::vec3 size = glm::vec3(1);
};