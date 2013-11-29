class Archer:public Player//弓箭手类和剑士类差不多，就是数值设定不同
{
public:
	Archer(int i,char *cptr);
	void isLevelUp();
	bool attack(Player &p);
	bool specialatt(Player &p);
};
Archer::Archer(int i,char *cptr)
{
	role=ar;
	for (int j=0;j<10;j++)
		name[j]=cptr[j];
	HP=180+6*(i-1);
	HPmax=180+6*(i-1);
	MP=75+8*(i-1);
	MPmax=75+8*(i-1);
	AP=30+3*(i-1);
	DP=24+3*(i-1);
	speed=30+10*(i-1);
	LV=i;
	death=0;
	EXP=(LV-1)*(LV-1)*70;
	bag.set(i*8,i*8);
}
void Archer::isLevelUp()
{
	if (EXP>=LV*LV*70)
	{
		LV++;
		AP=AP+3;
		DP=DP+3;
		HPmax=HPmax+6;
		MPmax=MPmax+8;
		speed=speed+10;
		cout <<name <<"升级了！" <<endl;
		cout <<"生命值增加了" <<6 <<"点" <<endl;
		cout <<"魔法值增加了" <<8 <<"点" <<endl;
		cout <<"速度增加了" <<10 <<"点" <<endl;
		cout <<"攻击力增加了" <<3 <<"点" <<endl;
		cout <<"防御力增加了" <<3 <<"点" <<endl;
		isLevelUp();
	}
}
bool Archer::attack(Player &p)
{
	double HPtemp=0,EXPtemp=0;
	double hit=1;
	srand(time(NULL));
	if ((speed>p.speed) && (rand()%100<(speed-p.speed)))//Double Hit
	{
		HPtemp=(int)((1.0*AP/p.DP)*AP*2/(rand()%4+10));
		cout <<name <<"先暗放一箭，不偏不倚正好打在" <<p.name <<"的胸口，" <<p.name <<"生命值减少了" <<HPtemp <<endl;
		p.HP=(int)(p.HP-HPtemp);
		EXPtemp=(int)(HPtemp*1.2);
	}
	if (rand()%100<1)
	{
		cout <<name <<"射出一支歪歪扭扭的箭，" <<p.name <<"很轻松地避开了。" <<endl;
		system("pause");
		return 1;
	}
	if (rand()%100<=10)
	{
		hit=1.5;
		cout <<name <<"拉足了弓，发出会心一击。";
	}
	HPtemp=(int)(hit*(1.0*AP/p.DP)*AP*30/(rand()%8+32));
	cout <<name <<"射出一支长箭，“嗖”地一声，插入了" <<p.name <<"的" <<(rand()%2==1?"胸膛，":"大腿，") <<p.name <<"生命值减少了" <<HPtemp <<endl;
	EXPtemp=(int)(EXPtemp+HPtemp*1.2);
	p.HP=(int)(p.HP-HPtemp);
	cout <<name <<"获得了" <<EXPtemp <<"点经验值。" <<endl;
	EXP=(int)(EXP+EXPtemp);
	system("pause");
	return 1;
}
bool Archer::specialatt(Player &p)
{
	if (MP<40)
	{
		cout <<"您的魔法值不够！" <<endl;
		system("pause");
		return 0;
	}
	else
	{
		MP=MP-40;
		double HPtemp=0,EXPtemp=0;
		srand(time(NULL));
		HPtemp=(int)(AP*1.4+18);
		EXPtemp=(int)(HPtemp*1.5);
		cout <<name <<"拿出三把长箭，大叫一声“流~~~~星~~~~箭~~~~！”三把长箭径直向" <<p.name <<"飞去，" <<p.name <<"无处闪躲……" <<endl;
		cout <<p.name <<"生命值减少了" <<HPtemp <<"，" <<name <<"获得了" <<EXPtemp <<"点经验值。" <<endl;
		p.HP=(int)(p.HP-HPtemp);
		EXP=(int)(EXP+EXPtemp);
		system("pause");
	}
	return 1;
}