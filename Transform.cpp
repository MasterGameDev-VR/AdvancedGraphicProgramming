#include "pch.h"
#include "Transform.h"


Rotation Rotation::identity()
{
	return Rotation();
}

Transform Rotation::aroundX(scalar degrees)
{
	return Transform();
}

Transform Rotation::aroundY(scalar degrees)
{
	return Transform();
}

Transform Rotation::aroundZ(scalar degrees)
{
	return Transform();
}

vec3 Rotation::apply(vec3 p) const
{
	return vec3();
}

void Rotation::combine(Rotation R)
{
}

void Rotation::invert()
{
}

Rotation Rotation::blend(Rotation a, Rotation b, scalar t)
{
	return Rotation();
}

void Rotation::fromMatrix(mat3 m)
{
}

mat3 Rotation::toMatrix() const
{
	return mat3();
}

void Rotation::fromAxisAngle(vec3 axis)
{
}

vec3 Rotation::toAxisAngle() const
{
	return vec3();
}

void Rotation::fromEulerAngles(vec3 angles)
{
}

vec3 Rotation::toEulerAngles() const
{
	return vec3();
}

Rotation Rotation::inverse() const
{
	return Rotation();
}

Rotation Rotation::operator*(Rotation R)
{
	return Rotation();
}

void Transform::lookAt(vec3 worldPos, vec3 worldTarget, vec3 worldUpvec)
{
}

mat4 Transform::toMat() const
{
	return mat4();
}

void Transform::fromMat(mat4 M)
{
}

void Transform::combine(const Transform & b)
{
}

void Transform::invert()
{
}

void Transform::setIdentity()
{
}

Transform Transform::identity()
{
	return Transform();
}

Transform Transform::translate(scalar dx, scalar dy, scalar dz)
{
	return Transform();
}

Transform Transform::translate(vec3 v)
{
	return Transform();
}

Transform Transform::scale(scalar ss)
{
	return Transform();
}

Transform Transform::rotateX(scalar degrees)
{
	return Transform();
}

Transform Transform::rotateY(scalar degrees)
{
	return Transform();
}

Transform Transform::rotateZ(scalar degrees)
{
	return Transform();
}

vec3 Transform::applyToPos(vec3 p) const
{
	return vec3();
}

vec3 Transform::applyToVec(vec3 v) const
{
	return vec3();
}

vec3 Transform::applyToDir(vec3 d) const
{
	return vec3();
}

Transform Transform::blend(const Transform & a, const Transform & b, scalar t)
{
	return Transform();
}

Transform Scene::globalTr(int nodeId) const
{
	return Transform();
}

void Scene::render()
{
}

int Scene::newNode()
{
	return 0;
}

void Scene::init()
{
}

void Scene::reattachUnder(int newParent)
{
}

void Scene::transformGlobal(int nodeI, Transform T)
{
}

void Scene::transformLocal(int nodeI, Transform T)
{
}
