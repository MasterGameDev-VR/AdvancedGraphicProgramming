// AdvancedGraphicProgramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Transform.h"

using namespace MCGD20182019;
using namespace std;

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