#include "Steering.h"

using namespace std;

CSteering::CSteering()
{
	cout << "CSteering constructor" << endl;
}

CSteering::CSteering(Character * character)
{
	mCharacter = character;
}

CSteering::~CSteering()
{
	cout << "CSteering destructor" << endl;
}
