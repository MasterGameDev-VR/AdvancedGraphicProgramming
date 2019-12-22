// AdvancedGraphicProgramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Transform.h"

#define FLOAT_PRECISION 0.5f

using namespace MCGD20182019;
using namespace std;

void PrintTransform(Transform T) {
	
	cout <<"\n" << "Tx: " << T.T.x << ", Ty: " << T.T.y << ", Tz: " << T.T.z<< "\n";
	cout << "Rx: " << T.R.toEulerAngles().x << ", Ry: " << T.R.toEulerAngles().y << ", Rz: " << T.R.toEulerAngles().z << "\n";
	cout << "S:" << T.S << "\n\n";
}

bool CompareMatrices(mat4 m1, mat4 m2)
{
	assert(m1._11 == m2._11);
	assert(m1._12 == m2._12);
	assert(m1._13 == m2._13);
	assert(m1._14 == m2._14);
	assert(m1._21 == m2._21);
	assert(m1._22 == m2._22);
	assert(m1._23 == m2._23);
	assert(m1._24 == m2._24);
	assert(m1._31 == m2._31);
	assert(m1._32 == m2._32);
	assert(m1._33 == m2._33);
	assert(m1._34 == m2._34);
	assert(m1._41 == m2._41);
	assert(m1._42 == m2._42);
	assert(m1._43 == m2._43);
	assert(m1._44 == m2._44);

	return true;
}

void UnitTest01() //AKA "PIPPO"
{ 
	/*
		Transform T;
		vec3 p(x, y, z);
		p = T(p);  // sinonimo di p = T.applyToPos( p );
	
		Transform T1, T2, T3;
		T3 = Transform::blend(T1, T2, 0.5);
	*/
}

void UnitTest00()
{
	cout << "UNIT TEST 00 START\n";
	vec3 res = Transform::rotateX(90).applyToPos(vec3(30, 10, 5));
	//assertSamePoint(res, vec3(30, 5, -10));
	cout << "UNIT TEST 00 - END\n";
}

void UnitTest10()
{
	cout << "UNIT TEST 10 - START\n";

	const float values[8] = { 10.f, 20.f, 30.f, 40.f, 50.f, 60.f, 70.f, 80.f };

	{
		cout << "- Scale only: ";

		Transform transform;
		transform.S = values[0];

		mat4 test = transform.toMat();

		mat4 comparison;
		DirectX::XMMATRIX tmp = DirectX::XMMatrixScaling(values[0], values[0], values[0]);
		DirectX::XMStoreFloat4x4(&comparison, tmp);

		bool result = CompareMatrices(test, comparison);
		cout << (result ? "OK" : "FAILED") << endl;
	}

	{
		cout << "- Rotate only: ";

		Transform transform;
		transform.R.imm = { values[1], values[2], values[3] };
		transform.R.real = values[4];

		mat4 test = transform.toMat();

		mat4 comparison;
		DirectX::XMMATRIX tmp = DirectX::XMMatrixRotationQuaternion(DirectX::XMVector4Normalize({ values[1], values[2], values[3], values[4] }));
		DirectX::XMStoreFloat4x4(&comparison, tmp);

		bool result = CompareMatrices(test, comparison);
		cout << (result ? "OK" : "FAILED") << endl;
	}

	{
		cout << "- Translate only: ";

		Transform transform;
		transform.T = { values[5], values[6], values[7] };

		mat4 test = transform.toMat();

		mat4 comparison;
		DirectX::XMMATRIX tmp = DirectX::XMMatrixTranslation(values[5], values[6], values[7]);
		DirectX::XMStoreFloat4x4(&comparison, tmp);

		bool result = CompareMatrices(test, comparison);
		cout << (result ? "OK" : "FAILED") << endl;
	}

	{
		cout << "- Scale, rotate and translate: ";

		Transform transform;
		transform.S = values[0];
		transform.R.imm = { values[1], values[2], values[3] };
		transform.R.real = values[4];
		transform.T = { values[5], values[6], values[7] };

		mat4 test = transform.toMat();

		mat4 comparison;
		DirectX::XMMATRIX tmp = DirectX::XMMatrixAffineTransformation(
			{ values[0], values[0], values[0] },
			{ 0.f, 0.f, 0.f },
			DirectX::XMVector4Normalize({ values[1], values[2], values[3], values[4] }),
			{ values[5], values[6], values[7] }
		);
		DirectX::XMStoreFloat4x4(&comparison, tmp);

		bool result = CompareMatrices(test, comparison);
		cout << (result ? "OK" : "FAILED") << endl;
	}

	cout << "UNIT TEST 10 - END\n";
}

void UnitTest13()
{
	cout << "UNIT TEST 13 START\n";
	Transform T_test = Transform::translate(20, 0, 0);
	PrintTransform(T_test);
	assert(T_test.T.x == 20);
	assert(T_test.T.y == 0);
	assert(T_test.T.z == 0);

	Transform Rx_test = Transform::rotateX(30);
	PrintTransform(Rx_test);
	assert( (Rx_test.R.toEulerAngles().x < 30 + FLOAT_PRECISION && Rx_test.R.toEulerAngles().x >= 30) );

	Transform Ry_test = Transform::rotateY(30);
	PrintTransform(Ry_test);
	assert((Ry_test.R.toEulerAngles().y < 30 + FLOAT_PRECISION && Ry_test.R.toEulerAngles().y >= 30));

	Transform Rz_test = Transform::rotateZ(30);
	PrintTransform(Rz_test);
	assert((Rz_test.R.toEulerAngles().z < 30 + FLOAT_PRECISION && Rz_test.R.toEulerAngles().z >= 30));

	cout << "UNIT TEST 13 END\n";
}

void UnitTest06()
{
	cout << "UNIT TEST 06 START\n";
	Transform test = Transform::rotateX(30);
	PrintTransform(test);
	mat3 matrix = test.R.toMatrix();

	cout << matrix._11 << " " << matrix._12 << " " << matrix._13 << "\r\n";
	cout << matrix._21 << " " << matrix._22 << " " << matrix._23 << "\r\n";
	cout << matrix._31 << " " << matrix._32 << " " << matrix._33 << "\r\n";
	cout << "UNIT TEST 06 - END\n";
}

int main()
{
    cout << "ADVANCED GRAPHIC PROGRAMMING TEST CLASS\n";
	// PASTE YOUR TEST CODE HERE   VVVVVVVVVVVVVVVVVVVVVVVVVVV

	UnitTest00();
	UnitTest01();
	UnitTest06();
	UnitTest10();
	UnitTest13();


}