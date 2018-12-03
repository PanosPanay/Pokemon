#include"allPets.h"

ALLPETS::ALLPETS()
{
	petsCnt = 8;
}

POKEMON * ALLPETS::GetAPet(int order)
{
	POKEMON* aPet = nullptr;
	switch (order)
	{
	case 0:
		aPet = &gyarados1;
		break;
	case 1:
		aPet = &happiny1;
		break;
	case 2:
		aPet = &squirtle1;
		break;
	case 3:
		aPet = &mewtwo1;
		break;
	case 4:
		aPet = &incineroar1;
		break;
	case 5:
		aPet = &wobbufffet1;
		break;
	case 6:
		aPet = &steelix1;
		break;
	case 7:
		aPet = &alakazam1;
		break;
	default:
		break;
	}
	return aPet;
}
