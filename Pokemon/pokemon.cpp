#include "pokemon.h"
const int MIN_ATKI = 10;//设定最低攻击间隔，单位为10^-1s
SKILL::SKILL()
{
}

SKILL::SKILL(string sname, int srank, SKILLKIND skind, int spower, int shit)
{
	SkillName = sname;
	SkillRank = srank;
	SkillKind = skind;
	SkillPower = spower;
	SkillHit = shit;
}

SKILL::SKILL(const SKILL & SK)
{
	SkillName = SK.SkillName;
	SkillRank = SK.SkillRank;
	SkillKind = SK.SkillKind;
	SkillPower = SK.SkillPower;
	SkillHit = SK.SkillHit;
}

//----------------------------------------------------------------------------------------------
//小精灵基类
POKEMON::POKEMON()
{
	//kind，Name没必要赋初值
	Rank = 1;
	Exp = 0;
	// Atk 初值？
	//Def
	//Hp
	//AtkInterval
	//Accuracy
	//Evasiveness
	//wType
	//Skills
	//SkillCnt
	//Nick
}

POKEMON::POKEMON(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
	int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
	WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt)
{
	Kind = xkind;
	Name = xname;
	Rank = xrank;
	Exp = xexp;
	Atk = xatk;
	Def = xdef;
	Hp = xhp;
	AtkInterval = xatki;
	Accuracy = xaccuracy;
	Evasiveness = xevasiveness;
	wType = xtype;
	GotSkillCnt = xskillcnt;
	AllSkillCnt = xallSkillcnt;
	Nick = xnick;
}

POKEMON::POKEMON(const POKEMON & PET)
{
	Kind = PET.Get_Kind();
	Name = PET.Get_Name();
	Rank = PET.Get_Rank();
	Exp = PET.Get_Exp();
	Atk = PET.Get_Atk();
	Def = PET.Get_Def();
	Hp = PET.Get_Hp();
	AtkInterval = PET.Get_AtkI();
	Accuracy = PET.Get_Accuracy();
	Evasiveness = PET.Get_Evasiveness();
	wType = PET.Get_Type();
	AllSkillCnt = PET.Get_ALLSkillCnt();
	GotSkillCnt = PET.Get_GotSkillCnt();
	Nick = PET.Get_Nick();
	for (int i = 0; i < AllSkillCnt; ++i)
	{
		AllSkills[i] = *(PET.Access_AllSkill()+i);
	}
	for (int i = 0; i < GotSkillCnt; ++i)
	{
		GotSkills[i] = PET.Access_GotSkill(i);
	}
}

POKEMON::~POKEMON()
{
}

void POKEMON::Input_Kind(POKEMONKIND xkind)
{
	Kind = xkind;
}

POKEMONKIND POKEMON::Get_Kind()const
{
	return Kind;
}

void POKEMON::Input_Name(string xname)
{
	Name = xname;
}

string POKEMON::Get_Name()const
{
	return Name;
}

void POKEMON::Input_Rank(int xrank)
{
	Rank = xrank;
}

int POKEMON::Get_Rank()const
{
	return Rank;
}

void POKEMON::Input_Exp(int xexp)
{
	Exp = xexp;
}

int POKEMON::Get_Exp()const
{
	return Exp;
}

void POKEMON::Input_Atk(int xatk)
{
	Atk = xatk;
}

int POKEMON::Get_Atk()const
{
	return Atk;
}

void POKEMON::Input_Def(int xdef)
{
	Def = xdef;
}

int POKEMON::Get_Def()const
{
	return Def;
}

void POKEMON::Input_Hp(int xhp)
{
	Hp = xhp;
}

int POKEMON::Get_Hp()const
{
	return Hp;
}

void POKEMON::Input_AtkI(int xatki)
{
	AtkInterval = xatki;
}

int POKEMON::Get_AtkI()const
{
	return AtkInterval;
}

void POKEMON::Input_Accuracy(double xaccuracy)
{
	Accuracy = xaccuracy;
}

double POKEMON::Get_Accuracy()const
{
	return Accuracy;
}

void POKEMON::Input_Evasiveness(double xevasiveness)
{
	Evasiveness = xevasiveness;
}

double POKEMON::Get_Evasiveness()const
{
	return Evasiveness;
}

void POKEMON::Input_Type(WUXINGTYPE xtype)
{
	wType = xtype;
}

WUXINGTYPE POKEMON::Get_Type()const
{
	return wType;
}

void POKEMON::Input_GotSkillCnt(int xskillcnt)
{
	GotSkillCnt = xskillcnt;
}

int POKEMON::Get_GotSkillCnt()const
{
	return GotSkillCnt;
}

void POKEMON::Input_ALLSkillCnt(int xskillcnt)
{
	AllSkillCnt = xskillcnt;
}

int POKEMON::Get_ALLSkillCnt() const
{
	return AllSkillCnt;
}

void POKEMON::Input_Nick(string xnick)
{
	Nick = xnick;
}

string POKEMON::Get_Nick() const
{
	return Nick;
}

const SKILL * POKEMON::Access_AllSkill() const
{
	const SKILL *firstSkillPtr = AllSkills;
	return firstSkillPtr;
}

SKILL * POKEMON::Write_AllSkill() 
{
	SKILL *firstSkillPtr = AllSkills;
	return firstSkillPtr;
}

PSKILL POKEMON::Access_GotSkill(int pos) const
{
	return GotSkills[pos];
}

PSKILL * POKEMON::Write_GotSkill(int pos)
{
	return &GotSkills[pos];
}

void POKEMON::RefershRank()
{
	if (Exp >= 0 && Exp < 100)
		Rank = 1;
	else if (Exp >= 100 && Exp < 200)
		Rank = 2;
	else if (Exp >= 200 && Exp < 300)
		Rank = 3;
	else if (Exp >= 300 && Exp < 400)
		Rank = 4;
	else if (Exp >= 400 && Exp < 500)
		Rank = 5;
	else if (Exp >= 500 && Exp < 650)
		Rank = 6;
	else if (Exp >= 650 && Exp < 800)
		Rank = 7;
	else if (Exp >= 800 && Exp < 950)
		Rank = 8;
	else if (Exp >= 950 && Exp < 1100)
		Rank = 9;
	else if (Exp >= 1100 && Exp < 1300)
		Rank = 10;
	else if (Exp >= 1300 && Exp < 1500)
		Rank = 11;
	else if (Exp >= 1500 && Exp < 1700)
		Rank = 12;
	else if (Exp >= 1700 && Exp < 2000)
		Rank = 13;
	else if (Exp >= 2000 && Exp < 2500)
		Rank = 14;
	else if (Exp >= 2500)
		Rank = 15;
}

void POKEMON::PrintPetInfo()
{
	cout << Name << "   Nick:" << Nick << endl;
	cout << "Kind:" << Kind;
	cout << " , Type:" << wType;
	cout << " , Rank:" << Rank;
	cout << " , Exp:" << Exp << endl;
	cout << " , Atk:" << Atk;
	cout << " , Def:" << Def;
	cout << " , Hp:" << Hp;
	cout << " , AtkI:" << AtkInterval << endl;
	cout << " , Accuracy:" << Accuracy;
	cout << " , Evasiveness:" << Evasiveness << endl;
	cout << "习得技能：" << endl;
	for (int i = 0; i < GotSkillCnt; ++i)
	{
		cout << GotSkills[i]->SkillName;
		cout << "   ";
	}
	cout << endl;
}

void POKEMON::Upgrade()
{
}

/*void POKEMON::SkillAll()
{
}*/

//--------------------------------------------------------------------------------------------------------

POWERPET::POWERPET():POKEMON()
{
	Input_Kind(POWER);
}

POWERPET::POWERPET(POKEMONKIND xkind, string xname, int xrank, int xexp,
	int xatk, int xdef, int xhp, int xatki, double xaccuracy,
	double xevasiveness, WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt)
	:POKEMON(xkind, xname, xrank, xexp, xatk, xdef, xhp, xatki, xaccuracy, xevasiveness, xtype, xskillcnt, xnick, xallSkillcnt)
{
}

POWERPET::POWERPET(const POWERPET & PET):POKEMON(PET)
{
}

//----------------------------------------------------------------------------------------------------------------

TANKPET::TANKPET():POKEMON()
{
	Input_Kind(TANK);
}

TANKPET::TANKPET(POKEMONKIND xkind, string xname, int xrank, int xexp,
	int xatk, int xdef, int xhp, int xatki, double xaccuracy,
	double xevasiveness, WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt)
	: POKEMON(xkind, xname, xrank, xexp, xatk, xdef, xhp, xatki, xaccuracy, xevasiveness, xtype, xskillcnt, xnick, xallSkillcnt)
{
}

TANKPET::TANKPET(const TANKPET & PET) : POKEMON(PET)
{
}

//----------------------------------------------------------------------------------------------------------------

DEFENSIVEPET::DEFENSIVEPET() :POKEMON()
{
	Input_Kind(DEFENSIVE);
}

DEFENSIVEPET::DEFENSIVEPET(POKEMONKIND xkind, string xname, int xrank, int xexp,
	int xatk, int xdef, int xhp, int xatki, double xaccuracy,
	double xevasiveness, WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt)
	: POKEMON(xkind, xname, xrank, xexp, xatk, xdef, xhp, xatki, xaccuracy, xevasiveness, xtype, xskillcnt, xnick, xallSkillcnt)
{
}

DEFENSIVEPET::DEFENSIVEPET(const DEFENSIVEPET & PET) : POKEMON(PET)
{
}

AGILEPET::AGILEPET() :POKEMON()
{
	Input_Kind(AGILE);
}

AGILEPET::AGILEPET(POKEMONKIND xkind, string xname, int xrank, int xexp,
	int xatk, int xdef, int xhp, int xatki, double xaccuracy,
	double xevasiveness, WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt)
	: POKEMON(xkind, xname, xrank, xexp, xatk, xdef, xhp, xatki, xaccuracy, xevasiveness, xtype, xskillcnt, xnick, xallSkillcnt)
{
}

AGILEPET::AGILEPET(const AGILEPET & PET) : POKEMON(PET)
{
}

//----------------------------------------------------------------------------------------------------------------
//鲤鱼王Magikarp（1-5）->暴鲤龙Gyarados（6-10）->超级暴鲤龙Super Gyarados（11-15）,高攻击
GYARADOS::GYARADOS() : POWERPET()
{
	Input_Name("鲤鱼王Magikarp");//鲤鱼王
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(95);
	//Input_AtkI(81);
	Input_AtkI(40);
	Input_Atk(125);
	Input_Def(79);
	Input_Accuracy(1);
	Input_Evasiveness(0.2);
	Input_Type(SHUI);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;	
	Input_GotSkillCnt(1);
}

GYARADOS::GYARADOS(const GYARADOS & PET) : POWERPET(PET)
{
	//SkillAll();//存入所有技能
}

void GYARADOS::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 6)
	{
		Input_Name("暴鲤龙Gyarados");
		cout << "进化为" << "暴鲤龙Gyarados !" << endl;
	}
	else if (currentRank >= 11)
	{
		Input_Name("超级暴鲤龙Super Gyarados");
		cout << "进化为" << "超级暴鲤龙Super Gyarados !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 1;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 5 + 1;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;		
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 6;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 1;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void GYARADOS::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr = Write_AllSkill();
	//第0个技能：龙卷风，攻击型技能
	theSkillPtr->SkillName = "龙卷风Twister";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 40;
	theSkillPtr->SkillHit = 100;
	//第1个技能：龙之舞，提升自身攻击力
	++theSkillPtr;
	theSkillPtr->SkillName = "龙之舞Dragon Dance";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：求雨，恢复部分生命值
	theSkillPtr->SkillName = "求雨Rain Dance";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 50;
	++AllSkillCnt;
	//第0个技能：龙之怒，攻击型技能
	theSkillPtr->SkillName = "龙之怒Dragon Rage";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 120;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第4个技能：瞪眼，降低对手防御力
	theSkillPtr->SkillName = "瞪眼Leer";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第5个技能：水炮，攻击型技能
	theSkillPtr->SkillName = "水炮Hydro Pump";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 110;
	theSkillPtr->SkillHit = 80;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}

//小福蛋Happiny->吉利蛋Chansey->幸福蛋Blissey,肉盾型
HAPPINY::HAPPINY() : TANKPET()
{
	Input_Name("小福蛋Happiny");
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(255);
	//Input_AtkI(55);
	Input_AtkI(60);
	Input_Atk(10);
	Input_Def(10);
	Input_Accuracy(1);
	Input_Evasiveness(0.1);
	Input_Type(TU);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;
	Input_GotSkillCnt(1);
}

HAPPINY::HAPPINY(const HAPPINY & PET) : TANKPET(PET)
{
	//SkillAll();//存入所有技能
}

void HAPPINY::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 6)
	{
		Input_Name("吉利蛋Chansey");
		cout << "进化为" << "吉利蛋Chansey !" << endl;
	}
	else if (currentRank >= 11)
	{
		Input_Name("幸福蛋Blissey");
		cout << "进化为" << "幸福蛋Blissey !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 6;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 5 + 1;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 1;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 1;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void HAPPINY::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr = Write_AllSkill();
	//第0个技能：炸蛋，攻击型技能
	theSkillPtr->SkillName = "炸蛋Egg Bomb";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 100;
	theSkillPtr->SkillHit = 90;
	++AllSkillCnt;
	//第1个技能：变圆，提高自己的防御力
	++theSkillPtr;
	theSkillPtr->SkillName = "变圆Defense Curl";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 10;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：生蛋，恢复部分生命值
	theSkillPtr->SkillName = "生蛋Soft-Boiled";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 100;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第3个技能：猛撞，攻击型技能
	theSkillPtr->SkillName = "猛撞Take Down";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 90;
	theSkillPtr->SkillHit = 85;
	++AllSkillCnt;
	//第4个技能：天使之吻，降低对手防御力
	theSkillPtr->SkillName = "天使之吻Sweet Kiss";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 80;
	++AllSkillCnt;
	//第5个技能：连环巴掌，攻击型技能
	theSkillPtr->SkillName = "连环巴掌Double Slap";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 15;
	theSkillPtr->SkillHit = 85;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}

//杰尼龟Squirtle(1-5级）->卡咪龟Wartortle(6-10级）->水箭龟Blastoise(11-15级），高防御
SQUIRTLE::SQUIRTLE():DEFENSIVEPET()
{
	Input_Name("杰尼龟Squirtle");
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(79);
	//Input_AtkI(78);
	Input_AtkI(45);
	Input_Atk(83);
	Input_Def(100);
	Input_Accuracy(1);
	Input_Evasiveness(0.2);
	Input_Type(SHUI);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;
	Input_GotSkillCnt(1);
}

SQUIRTLE::SQUIRTLE(const SQUIRTLE & PET) : DEFENSIVEPET(PET)
{
	//SkillAll();//存入所有技能
}

void SQUIRTLE::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 6)
	{
		Input_Name("卡咪龟Wartortle");
		cout << "进化为" << "卡咪龟Wartortle !" << endl;
	}
	else if (currentRank >= 11)
	{
		Input_Name("水箭龟Blastoise");
		cout << "进化为" << "水箭龟Blastoise !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 1;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 5 + 1;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 1;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 6;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void SQUIRTLE::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr= Write_AllSkill();
	//第0个技能：高速旋转，攻击型技能
	theSkillPtr->SkillName = "高速旋转Rapid Spin";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第1个技能：缩入壳中，提高自己的防御力
	++theSkillPtr;
	theSkillPtr->SkillName = "缩入壳中Withdraw";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：睡觉，恢复部分生命值
	theSkillPtr->SkillName = "睡觉Rest";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 30;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第3个技能：泰山压顶，攻击型技能
	theSkillPtr->SkillName = "泰山压顶Body Slam";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 90;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第4个技能：冰冻光束，降低对手防御力
	theSkillPtr->SkillName = "冰冻光束Ice Beam";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 30;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第5个技能：打鼾，攻击型技能(打鼾噪声攻击）
	theSkillPtr->SkillName = "打鼾Snore";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 60;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}

//超梦xMewtwoX->超梦Mewtwo->超级超梦yMewtwoY，敏捷型
MEWTWO::MEWTWO() : AGILEPET()
{
	Input_Name("超梦x MewtwoX");
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(106);
	//Input_AtkI(130);
	Input_AtkI(20);
	Input_Atk(110);
	Input_Def(90);
	Input_Accuracy(1);
	Input_Evasiveness(0.4);
	Input_Type(TU);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;
	Input_GotSkillCnt(1);
}

MEWTWO::MEWTWO(const MEWTWO & PET) : AGILEPET(PET)
{
	//Input_GotSkillCnt(1);
}

void MEWTWO::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 6)
	{
		Input_Name("超梦Mewtwo");
		cout << "进化为" << "超梦Mewtwo !" << endl;
	}
	else if (currentRank >= 11)
	{
		Input_Name("超级超梦y MewtwoY");
		cout << "进化为" << "超级超梦y MewtwoY !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 1;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 2 + 3;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 1;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 1;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void MEWTWO::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr = Write_AllSkill();
	//第0个技能：精神利刃，攻击型技能
	theSkillPtr->SkillName = "精神利刃Psycho Cut";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第1个技能：屏障，提高自己的防御力
	++theSkillPtr;
	theSkillPtr->SkillName = "屏障Barrier";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 50;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：自我再生，恢复部分生命值
	theSkillPtr->SkillName = "自我再生Recover";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 60;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第3个技能：精神强念，攻击型技能
	theSkillPtr->SkillName = "精神强念Psychic";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 90;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第4个技能：白雾，降低对手防御力
	theSkillPtr->SkillName = "白雾";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 40;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第5个技能：精神击破，攻击型技能
	theSkillPtr->SkillName = "精神击破Psystrike";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 100;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}

//火斑喵Litten->炎热喵Torracat->炽焰咆啸虎Incineroar，力量型
INCINEROAR::INCINEROAR() : POWERPET()
{
	Input_Name("火斑喵Litten");
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(95);
	//Input_AtkI(60);
	Input_AtkI(50);
	Input_Atk(115);
	Input_Def(90);
	Input_Accuracy(1);
	Input_Evasiveness(0.2);
	Input_Type(HUO);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;
	Input_GotSkillCnt(1);
}

INCINEROAR::INCINEROAR(const INCINEROAR & PET) : POWERPET(PET)
{
	//SkillAll();//存入所有技能
}

void INCINEROAR::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 6)
	{
		Input_Name("炎热喵Torracat");
		cout << "进化为" << "炎热喵Torracat !" << endl;
	}
	else if (currentRank >= 11)
	{
		Input_Name("炽焰咆啸虎Incineroar");
		cout << "进化为" << "炽焰咆啸虎Incineroar !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 1;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 5 + 1;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 6;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 1;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void INCINEROAR::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr = Write_AllSkill();
	//第0个技能：喷射火焰，攻击型技能
	theSkillPtr->SkillName = "喷射火焰Flamethrower";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 90;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第1个技能：健美，提高自己的防御力
	++theSkillPtr;
	theSkillPtr->SkillName = "健美Bulk Up";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 40;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：火花，攻击型技能
	theSkillPtr->SkillName = "火花Ember";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 40;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第3个技能：DD金勾臂，攻击型技能
	theSkillPtr->SkillName = "DD金勾臂Darkest Lariat";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 85;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第4个技能：舌舔，降低对手防御力
	theSkillPtr->SkillName = "舌舔Lick";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 30;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第5个技能：闪焰冲锋，攻击型技能
	theSkillPtr->SkillName = "闪焰冲锋Flare Blitz";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 120;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}

//小果然Wynaut->果然翁Wobbuffet，肉盾型
WOBBUFFET::WOBBUFFET() : TANKPET()
{
	Input_Name("小果然Wynaut");
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(190);
	//Input_AtkI(33);
	Input_AtkI(90);
	Input_Atk(33);
	Input_Def(58);
	Input_Accuracy(1);
	Input_Evasiveness(0.1);
	Input_Type(MU);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;
	Input_GotSkillCnt(1);
}

WOBBUFFET::WOBBUFFET(const WOBBUFFET & PET) : TANKPET(PET)
{
	//SkillAll();//存入所有技能
}

void WOBBUFFET::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 8)
	{
		Input_Name("果然翁Wobbuffet");
		cout << "进化为" << "果然翁Wobbuffet !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 1;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 5 + 6;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 1;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 1;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void WOBBUFFET::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr = Write_AllSkill();
	//第0个技能：跃起，攻击型技能
	theSkillPtr->SkillName = "跃起Splash";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 20;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第1个技能：神秘守护，提高自己的防御力
	++theSkillPtr;
	theSkillPtr->SkillName = "神秘守护Safeguard";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 40;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：躺赢，恢复部分HP
	theSkillPtr->SkillName = "躺赢Lie Win";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 80;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第3个技能：镜面反射，攻击型技能
	theSkillPtr->SkillName = "镜面反射Mirror Coat";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 30;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第4个技能：撒娇，降低对手防御力
	theSkillPtr->SkillName = "撒娇Charm";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 30;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第5个技能：抓狂，攻击型技能
	theSkillPtr->SkillName = "抓狂Crazy";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 60;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}

//大岩蛇Onix->大钢蛇Steelix->超级大钢蛇，防御型
STEELIX::STEELIX() : DEFENSIVEPET()
{
	Input_Name("大岩蛇Onix");
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(75);
	//Input_AtkI(30);
	Input_AtkI(100);
	Input_Atk(85);
	Input_Def(200);
	Input_Accuracy(1);
	Input_Evasiveness(0.2);
	Input_Type(TU);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;
	Input_GotSkillCnt(1);
}

STEELIX::STEELIX(const STEELIX & PET) : DEFENSIVEPET(PET)
{
	//SkillAll();//存入所有技能
}

void STEELIX::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 6)
	{
		Input_Name("大钢蛇Steelix");
		cout << "进化为" << "大钢蛇Steelix !" << endl;
	}
	else if (currentRank >= 11)
	{
		Input_Name("超级大钢蛇Super Steelix");
		cout << "进化为" << "超级大钢蛇Super Steelix !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 1;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 5 + 1;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 1;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 6;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void STEELIX::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr = Write_AllSkill();
	//第0个技能：绑紧，攻击型技能
	theSkillPtr->SkillName = "绑紧Bind";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 35;
	theSkillPtr->SkillHit = 85;
	++AllSkillCnt;
	//第1个技能：变硬，提高自己的防御力
	++theSkillPtr;
	theSkillPtr->SkillName = "变硬Harden";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 60;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：玩泥巴，恢复部分HP
	theSkillPtr->SkillName = "玩泥巴Mud Sport";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 40;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第3个技能：落石，攻击型技能
	theSkillPtr->SkillName = "落石Rock Throw";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 50;
	theSkillPtr->SkillHit = 90;
	++AllSkillCnt;
	//第4个技能：诅咒，降低对手防御力
	theSkillPtr->SkillName = "诅咒Curse";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 30;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第5个技能：铁尾，攻击型技能
	theSkillPtr->SkillName = "铁尾Iron Tail";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 100;
	theSkillPtr->SkillHit = 75;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}

//凯西Abra->勇基拉Kadabra->胡地Alakazam，敏捷型
ALAKAZAM::ALAKAZAM() : AGILEPET()
{
	Input_Name("凯西Abra");
	Input_Rank(1);
	Input_Exp(0);////////////经验值初始为0
	Input_Hp(55);
	//Input_AtkI(120);
	Input_AtkI(25);
	Input_Atk(50);
	Input_Def(45);
	Input_Accuracy(1);
	Input_Evasiveness(0.4);
	Input_Type(JIN);
	Input_GotSkillCnt(0);
	SkillAll();//存入所有技能
	//给定初始技能，默认指派第0个技能为初始技能
	PSKILL* newSkill = Write_GotSkill(0);
	*newSkill = Write_AllSkill();
	(*newSkill)->Selected = OWNED;
	Input_GotSkillCnt(1);
}

ALAKAZAM::ALAKAZAM(const ALAKAZAM & PET) : AGILEPET(PET)
{
	//SkillAll();//存入所有技能
}

void ALAKAZAM::Upgrade()
{
	string currentName = Get_Name();
	srand((unsigned)time(NULL));
	int currentRank = Get_Rank();
	cout << currentName << "升至" << currentRank << "级：" << endl;
	if (currentRank >= 6)
	{
		Input_Name("勇基拉Kadabra");
		cout << "进化为" << "勇基拉Kadabra !" << endl;
	}
	else if (currentRank >= 11)
	{
		Input_Name("胡地Alakazam");
		cout << "进化为" << "胡地Alakazam !" << endl;
	}
	int currentHp = Get_Hp();
	int currentAtkI = Get_AtkI();
	int currentAtk = Get_Atk();
	int currentDef = Get_Def();
	int addition = rand() % 5 + 1;
	currentHp += addition;
	cout << "HP+" << addition;
	Input_Hp(currentHp);
	addition = rand() % 2 + 3;
	if (currentAtkI - addition > MIN_ATKI)
	{
		currentAtkI -= addition;
		cout << " , ATKI-" << addition;
	}
	else
	{
		cout << " , ATKI-" << currentAtkI - MIN_ATKI << "(降到下限）";
		currentAtkI = MIN_ATKI;
	}
	Input_AtkI(currentAtkI);
	addition = rand() % 5 + 1;
	cout << " , ATK+" << addition;
	currentAtk += addition;
	Input_Atk(currentAtk);
	addition = rand() % 5 + 1;
	cout << " , DEF+" << addition << endl;
	currentDef += addition;
	Input_Def(currentDef);

	//有几率获得技能
	int learnSkill = rand() % 10;
	if (learnSkill >= 5 && Get_GotSkillCnt() < Get_ALLSkillCnt())//学到新技能
	{
		learnSkill = rand() % Get_ALLSkillCnt();
		while ((Access_AllSkill() + learnSkill)->Selected == OWNED)
		{
			learnSkill = rand() % Get_ALLSkillCnt();
		}
		int learnSkillCnt = Get_GotSkillCnt();
		PSKILL* newSkill = Write_GotSkill(learnSkillCnt);
		*newSkill = Write_AllSkill() + learnSkill;
		(*newSkill)->Selected = OWNED;
		++learnSkillCnt;
		Input_GotSkillCnt(learnSkillCnt);
		cout << "获得新技能：" << (*newSkill)->SkillName << endl;
	}
}

void ALAKAZAM::SkillAll()
{
	int therank;
	int AllSkillCnt = 0;
	SKILL *theSkillPtr = Write_AllSkill();
	//第0个技能：幻想光线，攻击型技能
	theSkillPtr->SkillName = "幻想光线Psybeam";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 65;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第1个技能：反射壁，提高自己的防御力
	++theSkillPtr;
	theSkillPtr->SkillName = "反射壁Reflect";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = SELFDEFFENCE;
	theSkillPtr->SkillPower = 30;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第2个技能：自我再生，恢复部分HP
	theSkillPtr->SkillName = "自我再生Recover";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = REHP;
	theSkillPtr->SkillPower = 50;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第3个技能：精神利刃，攻击型技能
	theSkillPtr->SkillName = "精神利刃Psycho Cut";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 80;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第4个技能：定身法，降低对手防御力
	theSkillPtr->SkillName = "定身法Disable";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = OPPDEFEENCE;
	theSkillPtr->SkillPower = 40;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	//第5个技能：预知未来，攻击型技能
	theSkillPtr->SkillName = "预知未来Future Sight";
	theSkillPtr->SkillRank = 1;
	theSkillPtr->SkillKind = ATTACK;
	theSkillPtr->SkillPower = 100;
	theSkillPtr->SkillHit = 100;
	++AllSkillCnt;
	Input_ALLSkillCnt(AllSkillCnt);
}
