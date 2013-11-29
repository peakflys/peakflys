
class Mage:public Player//法师类和剑士类差不多，就是数值设定不同
{
public:
	Mage(int i,char *cptr);
	void isLevelUp();
	bool attack(Player &p);
	bool specialatt(Player &p);
};
Mage::Mage(int i,char *cptr)
{
	role=mg;
	for (int j=0;j<10;j++)
		name[j]=cptr[j];
	HP=120+4*(i-1);
	HPmax=120+4*(i-1);
	MP=200+20*(i-1);
	MPmax=200+20*(i-1);
	AP=50+2*(i-1);
	DP=20+2*(i-1);
	speed=25+3*(i-1);
	LV=i;
	death=0;
	EXP=(LV-1)*(LV-1)*65;
	bag.set(i*5,i*30);
}
void Mage::isLevelUp()
{
	if (EXP>=LV*LV*65)
	{
		LV++;
		AP=AP+2;
		DP=DP+2;
		HPmax=HPmax+4;
		MPmax=MPmax+20;
		speed=speed+3;
		cout <<name <<"升级了！" <<endl;
		cout <<"生命值增加了" <<4 <<"点" <<endl;
		cout <<"魔法值增加了" <<20 <<"点" <<endl;
		cout <<"速度增加了" <<3 <<"点" <<endl;
		cout <<"攻击力增加了" <<2 <<"点" <<endl;
		cout <<"防御力增加了" <<2 <<"点" <<endl;
		isLevelUp();
	}
}
bool Mage::attack(Player &p)
{
	double HPtemp=0,EXPtemp=0;
	double hit=1;
	srand(time(NULL));
	if ((speed>p.speed) && (rand()%100<(speed-p.speed)))//Double Hit
	{
		HPtemp=(int)((1.0*AP/p.DP)*AP*3/(rand()%4+10));
		cout <<name <<"先是一记飞腿,踢向" <<p.name <<"的小腹，" <<p.name <<"生命值减少了" <<HPtemp <<endl;
		p.HP=(int)(p.HP-HPtemp);
		EXPtemp=(int)(HPtemp*1.2);
	}
	if (rand()%100<1)
	{
		cout <<name <<"默念咒语，" <<p.name <<"很轻松地避开了。" <<endl;
		system("pause");
		return 1;
	}
	if (rand()%100<=10)
	{
		hit=1.5;
		cout <<name <<"用足力气，发出会心一击。";
	}
	HPtemp=(int)(hit*(1.0*AP/p.DP)*AP*25/(rand()%8+35));
	cout <<name <<"抡起法仗,砸向" <<p.name <<"的" <<(rand()%2==1?"脑袋，":"肩膀，") <<p.name <<"生命值减少了" <<HPtemp <<endl;
	EXPtemp=(int)(EXPtemp+HPtemp*1.2);
	p.HP=(int)(p.HP-HPtemp);
	cout <<name <<"获得了" <<EXPtemp <<"点经验值。" <<endl;
	EXP=(int)(EXP+EXPtemp);
	system("pause");
	return 1;
}
bool Mage::specialatt(Player &p)
{
	if (MP<20)
	{
		cout <<"您的魔法值不够！" <<endl;
		system("pause");
		return 0;
	}
	else
	{
		MP=MP-20;
		if (rand()%100<=20)
		{
			cout <<name <<"默念“&^%@#$*……”，射出一道绿光，" <<p.name <<"逃得远远的了。" <<endl;
			system("pause");
			return 1;
		}
		double HPtemp=0,EXPtemp=0;
		srand(time(NULL));
		HPtemp=(int)(AP*1.1);
		EXPtemp=(int)(HPtemp*1.3);
		cout <<name <<"默念“&^%@#$*……”，一道绿光射向" <<p.name <<"，" <<name <<"吸取了" <<p.name <<"的" <<HPtemp <<"点生命值。" <<endl;
		cout <<name <<"获得了" <<EXPtemp <<"点经验值。" <<endl;
		p.HP=(int)(p.HP-HPtemp);
		EXP=(int)(EXP+EXPtemp);
		if (HP+HPtemp<=HPmax)
			HP=(int)(HP+HPtemp);
		else
			HP=HPmax;
		system("pause");
	}
	return 1;
}