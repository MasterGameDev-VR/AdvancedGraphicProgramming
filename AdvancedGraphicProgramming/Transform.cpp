#include "pch.h"
#include "Transform.h"
#include <math.h>

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
		float num2 = (((imm.x * imm.x) + (imm.y * imm.y)) + (imm.z * imm.z)) + (real * real);
		float num = 1.f / num2;
		imm.x = -imm.x * num;
		imm.y = -imm.y * num;
		imm.z = -imm.z * num;
		real = real * num;
	}

	Rotation Rotation::blend(Rotation a, Rotation b, scalar t)
	{
		float num = t;
		float num2 = 1.f - t;
		Rotation result;
		float num3 = (((a.imm.x * b.imm.x) + (a.imm.y * b.imm.y)) + (a.imm.z * b.imm.z)) + (a.real * b.real);
		if (num3 >= 0.f)
		{
			result.imm.x = (num2 * a.imm.x) + (num * b.imm.x);
			result.imm.y = (num2 * a.imm.y) + (num * b.imm.y);
			result.imm.z = (num2 * a.imm.z) + (num * b.imm.z);
			result.real = (num2 * a.real) + (num * b.real);
		}
		else
		{
			result.imm.x = (num2 * a.imm.x) - (num * b.imm.x);
			result.imm.y = (num2 * a.imm.y) - (num * b.imm.y);
			result.imm.z = (num2 * a.imm.z) - (num * b.imm.z);
			result.real = (num2 * a.real) - (num * b.real);
		}
		float num4 = (((result.imm.x * result.imm.x) + (result.imm.y * result.imm.y)) + (result.imm.z * result.imm.z)) + (result.real * result.real);
		float num5 = 1.f / sqrt(num4);
		result.imm.x *= num5;
		result.imm.y *= num5;
		result.imm.z *= num5;
		result.real *= num5;
		return result;
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
		Rotation result = *this;
		result.invert();

		return result;
	}

	Rotation Rotation::operator*(Rotation R)
	{
		return Rotation();
	}

	Transform::Transform()
		: S{ 1.f }
		, T{ 0.f, 0.f, 0.f }
		, R{ { 0.f, 0.f, 0.f }, 1.f }
	{ }

	Transform::Transform(scalar scale, const vec3& position, const Rotation& rotation)
	{
		S = scale;
		T = position;
		R = rotation;
	}


	void Transform::lookAt(vec3 worldPos, vec3 worldTarget, vec3 worldUpvec)
	{
		using namespace DirectX;

		XMVECTOR position = XMLoadFloat3(&worldPos);
		XMVECTOR target = XMLoadFloat3(&worldTarget);
		XMVECTOR up = XMLoadFloat3(&worldUpvec);

		XMVECTOR direction = XMVectorSubtract(target, position);

		XMVECTOR dotVec = XMVector3Dot(up, direction);

		float dot;
		XMStoreFloat(&dot, dotVec);

		float angle = acosf(dot);

		XMVECTOR crossVec = XMVector3Normalize( XMVector3Cross(direction, up) ) * angle;
		vec3 cross;
		DirectX::XMStoreFloat3(&cross, crossVec);
	
		R.fromAxisAngle(cross);
	}

	mat4 Transform::toMat() const
	{
		DirectX::XMMATRIX scaling =
		{
			S,   0.f, 0.f, 0.f,
			0.f, S,   0.f, 0.f,
			0.f, 0.f, S,   0.f,
			0.f, 0.f, 0.f, 1.f
		};

		mat3 tmp = R.toMatrix();
		DirectX::XMMATRIX rotation =
		{
			tmp._11, tmp._21, tmp._31, 0.f,
			tmp._12, tmp._22, tmp._32, 0.f,
			tmp._13, tmp._23, tmp._33, 0.f,
			0.f,     0.f,     0.f,     1.f
		};

		DirectX::XMMATRIX translation =
		{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			T.x, T.y, T.z, 1
		};

		mat4 result;
		DirectX::XMMATRIX transform = scaling * rotation * translation;
		DirectX::XMStoreFloat4x4(&result, transform);

		return result;
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

	void Scene::reattachUnder(int nodeI, int newParent)
	{
		nodes[nodeI].parent = newParent;
		nodes[newParent].children.push_back(nodeI);
	}

	void Scene::transformGlobal(int nodeI, Transform T)
	{
	}

	void Scene::transformLocal(int nodeI, Transform T)
	{
	}
}