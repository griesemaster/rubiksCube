#include "cubetroller.h"
#include <cube.h>

void Cubetroller::F(bool automated) {
	(*currentCube).rotateZClockwiseFront(automated);
}

void Cubetroller::Fp(bool automated) {
	(*currentCube).rotateZantiClockwiseFront(automated);
}



void Cubetroller::R(bool automated) {
	(*currentCube).rotateXClockwiseFront(automated);
}

void Cubetroller::Rp(bool automated) {
	(*currentCube).rotateXantiClockwiseFront(automated);
}


void Cubetroller::U(bool automated) {
	(*currentCube).rotateYantiClockwiseFront(automated);
}

void Cubetroller::Up(bool automated) {
	(*currentCube).rotateYClockwiseFront(automated);
}


void Cubetroller::D(bool automated) {
	(*currentCube).rotateYClockwiseBack(automated);
}
void Cubetroller::Dp(bool automated) {
	(*currentCube).rotateYantiClockwiseBack(automated);
}


void Cubetroller::L(bool automated) {
	(*currentCube).rotateXantiClockwiseBack(automated);
}

void Cubetroller::Lp(bool automated) {
	(*currentCube).rotateXClockwiseBack(automated);
}


void Cubetroller::B(bool automated) {
	(*currentCube).rotateZantiClockwiseBack(automated);
}

void Cubetroller::Bp(bool automated) {
	(*currentCube).rotateZClockwiseBack(automated);
}

void Cubetroller::superFlip() {
	//U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2 
	if ((*currentCube).checkValidCommand()) {
		U(true);//U
		R(true);//R2
		R(true);
		F(true);//F
		B(true);//B
		R(true);//R
		B(true);//B2
		B(true);
		R(true);//R
		U(true);//U2
		U(true);
		L(true);//L
		B(true);//B2
		B(true);
		R(true);//R
		Up(true);//U'
		Dp(true);//D'
		R(true);//R2
		R(true);
		F(true);//F
		Rp(true);//R'
		L(true);//L
		B(true);//B2
		B(true);
		U(true);//U2
		U(true);
		F(true);//F2
		F(true);
	}
}