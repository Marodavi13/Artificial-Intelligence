#include "Steering.h"

using namespace std;

CSteering::CSteering()
{
	cout << "CSteering constructor" << endl;
}

CSteering::CSteering(Character * character,const float& weight)
{
	mCharacter = character;
	mWeight = weight;
}

CSteering::~CSteering()
{
	cout << "CSteering destructor" << endl;
}
