// AdvancedGraphicProgramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Transform.h"

using namespace MCGD20182019;
using namespace std;

void PrintTransform(Transform T) {
	
	cout <<"\n" << "Tx: " << T.T.x << ", Ty: " << T.T.y << ", Tz: " << T.T.z<< "\n";
	cout << "Rx: " << T.R.toEulerAngles().x << ", Ry: " << T.R.toEulerAngles().y << ", Rz: " << T.R.toEulerAngles().z << "\n";
	cout << "S:" << T.S << "\n\n";
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
	vec3 res = Transform::rotateX(90).applyToPos(vec3(30, 10, 5));
	//assertSamePoint(res, vec3(30, 5, -10));
}

void UnitTest13()
{
	cout << "UNIT TEST 13 START\n";
	Transform test = Transform::rotateX(30) * Transform::translate(20, 0, 0) * Transform::scale(10);
	PrintTransform(test);
	assert(test.T.x == 20);
	assert(test.T.y == 0);
	assert(test.T.z == 0);

	assert(test.S == 10);
	assert(test.R.toEulerAngles().x == 30);

	cout << "UNIT TEST 13 END\n";
}

int main()
{
    cout << "ADVANCED GRAPHIC PROGRAMMING TEST CLASS\n";
	// PASTE YOUR TEST CODE HERE   VVVVVVVVVVVVVVVVVVVVVVVVVVV

	UnitTest00();
	UnitTest01();
	UnitTest13();
}