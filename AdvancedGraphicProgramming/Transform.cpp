#include "pch.h"
#include "Transform.h"

namespace  MCGD20182019 {

	#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

	MCGD20182019::Rotation Rotation::identity()
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
		scalar n = sqrt(imm.x*imm.x + imm.y*imm.y + imm.z*imm.z + real * real);
		vec3 immNorm;
		immNorm.x = imm.x / n;
		immNorm.y = imm.y / n;
		immNorm.z = imm.z / n;
		scalar realNorm = real / n;
		mat3 mat = { 1.0f - 2.0f * (immNorm.y*immNorm.y) - 2.0f * (immNorm.z*immNorm.z), 2.0f * immNorm.x*immNorm.y - 2.0f * immNorm.z*realNorm, 2.0f * immNorm.x*immNorm.z + 2.0f * immNorm.y*realNorm,
		2.0f * immNorm.x*immNorm.y + 2.0f * immNorm.z*realNorm, 1.0f - 2.0f * (immNorm.x*immNorm.x) - 2.0f * (immNorm.z*immNorm.z), 2.0f * immNorm.y*immNorm.z - 2.0f * immNorm.x*realNorm,
		2.0f * immNorm.x*immNorm.z - 2.0f * immNorm.y *realNorm, 2.0f * immNorm.y*immNorm.z + 2.0f * immNorm.x*realNorm, 1.0f - 2.0f * (immNorm.x*immNorm.x) - 2.0f * (immNorm.y*immNorm.y) };
		return mat;
	}

	void Rotation::fromAxisAngle(vec3 axis)
	{
		float angle = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
		vec3 axisNormalized;
		axisNormalized.x = axis.x / angle;
		axisNormalized.y = axis.y / angle;
		axisNormalized.z = axis.z / angle;

		double s = sin(angle / 2);
		imm.x = axisNormalized.x * s;
		imm.y = axisNormalized.y * s;
		imm.z = axisNormalized.z * s;
		real = cos(angle / 2);
	}

	vec3 Rotation::toAxisAngle() const
	{
		vec3 axis;
		float angle = 2 * acos(real);
		if (angle != 0)
		{
			axis.x = (imm.x / sqrt(1 - real * real))*angle;
			axis.y = (imm.x / sqrt(1 - real * real))*angle;
			axis.z = (imm.x / sqrt(1 - real * real))*angle;
		}
		else
		{
			axis.x = angle;
			axis.y = angle;
			axis.z = angle;
		}
		return axis;
	}

	void Rotation::fromEulerAngles(vec3 angles)
	{
	}

	vec3 Rotation::toEulerAngles() const
	{
		//COPY PASTE FROM WIKI
		vec3 angles;

		// roll (x-axis rotation)
		double sinr_cosp = +2.0f * (real * imm.x + imm.y * imm.z);
		double cosr_cosp = +1.0f - 2.0f * (imm.x * imm.x + imm.y * imm.y);
		angles.x = atan2(sinr_cosp, cosr_cosp);

		// pitch (y-axis rotation)
		double sinp = +2.0f * (real* imm.y - imm.z * imm.x);
		if (fabs(sinp) >= 1.0f)
			angles.y = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
		else
			angles.y = asin(sinp);

		// yaw (z-axis rotation)
		double siny_cosp = +2.0f * (real * imm.z + imm.x * imm.y);
		double cosy_cosp = +1.0f - 2.0f * (imm.y * imm.y + imm.z * imm.z);
		angles.z = atan2(siny_cosp, cosy_cosp);

		return angles;
	}

	Rotation Rotation::inverse() const
	{
		return Rotation();
	}

	Rotation Rotation::operator*(Rotation R)
	{
		return Rotation();
	}

	Transform::Transform()
	{

	}

	Transform::Transform(scalar scale, const vec3& position, const Rotation& rotation)
	{
		S = scale;
		T = position;
		R = rotation;
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
		*this = identity();
	}

	Transform Transform::identity()
	{
		return Transform(scalar{ 1.0f }, vec3{ 0.0f, 0.0f, 0.0f }, Rotation::identity());
	}

	Transform Transform::translate(scalar dx, scalar dy, scalar dz)
	{
		return Transform::translate( vec3{ dx, dy, dz } );
	}

	Transform Transform::translate( vec3 v )
	{
		return Transform(scalar{ 1.0f }, vec3{ v.x,v.y,v.z }, Rotation::identity());
	}

	Transform Transform::scale(scalar ss)
	{
		return Transform(scalar{ ss }, vec3{ 0.0f, 0.0f, 0.0f }, Rotation::identity());
	}

	Transform Transform::rotateX(scalar degrees)
	{
		Rotation R = Rotation::identity();
		R.fromAxisAngle(vec3{ degrees, 0.0f, 0.0f });
		return Transform(scalar{ 1.0f }, vec3{ 0.0f, 0.0f, 0.0f }, R);
	}

	Transform Transform::rotateY(scalar degrees)
	{
		Rotation R = Rotation::identity();
		R.fromAxisAngle(vec3{ 0.0f, degrees, 0.0f });
		return Transform(scalar{ 1.0f }, vec3{ 0.0f, 0.0f, 0.0f }, R);
	}

	Transform Transform::rotateZ(scalar degrees)
	{
		Rotation R = Rotation::identity();
		R.fromAxisAngle(vec3{  0.0f, 0.0f, degrees });
		return Transform(scalar{ 1.0f }, vec3{ 0.0f, 0.0f, 0.0f }, R);
	}

	vec3 Transform::applyToPos(vec3 p) const
	{
		return vec3();
	}

	vec3 Transform::applyToVec(vec3 v) const
	{
		/*DirectX::XMVECTOR vm = DirectX::XMLoadFloat3(v);
		vm *= scalar;
		DirectX::XMStoreFloat4(v, vm);*/
		v.x *= S;
		v.y *= S;
		v.z *= S;
		return R.apply(v);
	}

	vec3 Transform::applyToDir(vec3 d) const
	{
		return R.apply(d);
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
		nodes.push_back(Node());
		return nodes.size() - 1;
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
}