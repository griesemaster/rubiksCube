#include <GLcube.h>

#ifndef CUBETROLLER
#define CUBETROLLER

class Cubetroller {
private:
	Cube* currentCube;

public:
	Cubetroller() { currentCube = NULL; };

	void setCube(Cube* newCube) { currentCube = newCube; };

	//N will be the move N, Np will be the prime move (counterclockwise)
	// ----- base moves ------
	void F(bool automated);
	void Fp(bool automated);

	void R(bool automated);
	void Rp(bool automated);

	void U(bool automated);
	void Up(bool automated);

	void D(bool automated);
	void Dp(bool automated);

	void L(bool automated);
	void Lp(bool automated);

	void B(bool automated);
	void Bp(bool automated);


	//--- sequences ---- 
	void superFlip();
};
#endif // !CUBETROLLER
