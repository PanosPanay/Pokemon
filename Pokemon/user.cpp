#include "user.h"

USER::USER()
{
	//userName=
	//passWord=
	petNum = 0;
	/////////////注册成功后再随机发放3只精灵
}

string USER::Get_UserName() const
{
	return userName;
}

void USER::Input_UserName(string uname)
{
	userName = uname;
}

string USER::Get_PassWord() const
{
	return passWord;
}

void USER::Input_PassWord(string upw)
{
	passWord = upw;
}

int USER::Get_PetNum() const
{
	return petNum;
}

void USER::Input_PetNum(int pnum)
{
	petNum = pnum;
}

const POKEMON * USER::ReadPets(int order) const
{
	const POKEMON* aPet = pets + order;
	return aPet;
}

POKEMON * USER::WritePets(int order)
{
	POKEMON* aPet = pets + order;
	return aPet;
}

void USER::InitialPets()//初始送出3只精灵，未完成
{
	for (int i = 0; i < 3; ++i)
	{
		srand((unsigned)time(NULL));
		int random = rand() % PETMAX;
		/*switch (random) 
		{
		case 0:
			GYARADOS gyarados1;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		}*/
	}
}
