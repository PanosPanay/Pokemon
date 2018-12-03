#include"pokemon.h"
#include"fight.h"

int main()
{
	GYARADOS gyarados1;
	//gyarados1.SkillAll();
	HAPPINY happiny1;
	SQUIRTLE squirtle1;
	MEWTWO mewtwo1;
	INCINEROAR incineroar1;
	WOBBUFFET wobbufffet1;
	STEELIX steelix1;
	ALAKAZAM alakazam1;
	//输出宠物信息
	cout << "1、";
	gyarados1.PrintPetInfo();
	cout << endl << "2、";
	happiny1.PrintPetInfo();
	cout << endl << "3、";
	squirtle1.PrintPetInfo();
	cout << endl << "4、";
	mewtwo1.PrintPetInfo();
	cout << endl << "5、";
	incineroar1.PrintPetInfo();
	cout << endl << "6、";
	wobbufffet1.PrintPetInfo();
	cout << endl << "7、";
	steelix1.PrintPetInfo();
	cout << endl << "8、";
	alakazam1.PrintPetInfo();
	int A=1;
	int B=1;
	while (A != 0)
	{
		cout << endl << "输入你想要进行战斗的第1只宠物(键入0退出）：" << endl;
		int A;
		int B;
		POKEMON *pet1=nullptr;
		POKEMON *pet2=nullptr;
		cin >> A;
		while (A < 0 || A>8)
		{
			cout << "错误输入！请重新输入：";
			cin >> A;
		}
		if (A != 0)
		{
			switch (A)
			{
			case 1:
				pet1 = &gyarados1;
				break;
			case 2:
				pet1 = &happiny1;
				break;
			case 3:
				pet1 = &squirtle1;
				break;
			case 4:
				pet1 = &mewtwo1;
				break;
			case 5:
				pet1 = &incineroar1;
				break;
			case 6:
				pet1 = &wobbufffet1;
				break;
			case 7:
				pet1 = &steelix1;
				break;
			case 8:
				pet1 = &alakazam1;
				break;
			}
			cout << endl << "输入你想要进行战斗的第2只宠物：" << endl;
			cin >> B;
			while (B < 1 || B > 8)
			{
				cout << "错误输入！请重新输入：";
				cin >> B;
			}
			switch (B)
			{
			case 1:
				pet2 = &gyarados1;
				break;
			case 2:
				pet2 = &happiny1;
				break;
			case 3:
				pet2 = &squirtle1;
				break;
			case 4:
				pet2 = &mewtwo1;
				break;
			case 5:
				pet2 = &incineroar1;
				break;
			case 6:
				pet2 = &wobbufffet1;
				break;
			case 7:
				pet2 = &steelix1;
				break;
			case 8:
				pet2 = &alakazam1;
				break;
			}
			FIGHT fight1(pet1, pet2);
			fight1.A_VS_B();
		}
	}	

	system("pause");
	return 0;
}