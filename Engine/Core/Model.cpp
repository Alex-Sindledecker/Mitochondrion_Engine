#include "mepch.h"
#include "Model.h"

Transform::Transform(glm::vec3 pos)
{
	this->pos = pos;
}

Transform::Transform(glm::vec3 pos, glm::vec3 scale)
{
	this->pos = pos;
	this->size = scale;
}

void Transform::move(const glm::vec3& offset)
{
	pos += offset;
}

void Transform::rotate(const glm::vec3& angles)
{
	eulerRotation += angles;
}

void Transform::scale(const glm::vec3& factor)
{
	size *= factor;
}

void Transform::move(float dx, float dy, float dz)
{
	pos.x += dx;
	pos.y += dy;
	pos.z += dz;
}

void Transform::rotate(float ax, float ay, float az)
{
	eulerRotation.x += ax;
	eulerRotation.y += ay;
	eulerRotation.z += az;
}

void Transform::scale(float fx, float fy, float fz)
{
	size.x *= fx;
	size.y *= fy;
	size.z *= fz;
}

void Transform::setPosition(const glm::vec3& pos)
{
	this->pos = pos;
}

void Transform::setRotation(const glm::vec3& newAngles)
{
	eulerRotation = newAngles;
}

void Transform::setScale(const glm::vec3& scale)
{
	size = scale;
}

void Transform::setPosition(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Transform::setRotation(float ax, float ay, float az)
{
	eulerRotation.x = ax;
	eulerRotation.y = ay;
	eulerRotation.z = az;
}

void Transform::setScale(float sx, float sy, float sz)
{
	size.x = sx;
	size.y = sy;
	size.z = sz;
}

glm::mat4 Transform::convertToMat4() const
{
	glm::mat4 mat = glm::translate(glm::mat4(1.f), pos);
	mat = glm::rotate(mat, eulerRotation.x, glm::vec3(1, 0, 0));
	mat = glm::rotate(mat, eulerRotation.y, glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, eulerRotation.z, glm::vec3(0, 0, 1));
	mat = glm::scale(mat, size);
	return mat;
}
