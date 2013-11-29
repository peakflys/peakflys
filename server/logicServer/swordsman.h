#include "player.h"
class Swordsman:public Player//剑士类，继承人物类
{
public:
	Swordsman(int i,char *cptr);//构造函数
	void isLevelUp();
	bool attack(Player &p);
	bool specialatt(Player &p);
	void AI(Player &p);//电脑AI
};
Swordsman::Swordsman(int i,char *cptr)//构造函数
{
	role=sw;
	for (int j=0;j<10;j++)
		name[j]=cptr[j];
	HP=150+8*(i-1);
	HPmax=150+8*(i-1);
	MP=75+2*(i-1);
	MPmax=75+2*(i-1);
	AP=25+4*(i-1);
	DP=25+4*(i-1);
	speed=25+2*(i-1);
	LV=i;
	death=0;
	EXP=LV*LV*75;
	bag.set(i*5,i*5);
}
void Swordsman::isLevelUp()
{
	if (EXP>=LV*LV*75)
	{
		LV++;
		AP=AP+4;
		DP=DP+4;
		HPmax=HPmax+8;
		MPmax=MPmax+2;
		speed=speed+2;
		cout <<name <<"升级了！" <<endl;
		cout <<"生命值增加了" <<8 <<"点" <<endl;
		cout <<"魔法值增加了" <<2 <<"点" <<endl;
		cout <<"速度增加了" <<2 <<"点" <<endl;
		cout <<"攻击力增加了" <<4 <<"点" <<endl;
		cout <<"防御力增加了" <<4 <<"点" <<endl;
		isLevelUp();//递归调用，如果一次获得经验值太多可能发生剩多级的可能
	}
}
bool Swordsman::attack(Player &p)
{
	double HPtemp=0,EXPtemp=0;//敌方伤血和玩家经验值
	double hit=1;//攻击因子，可能产生重击
	srand(time(NULL));//产生随机因子
	if ((speed>p.speed) && (rand()%100<(speed-p.speed)))//两次攻击
	{
		HPtemp=(int)((1.0*AP/p.DP)*AP*5/(rand()%4+10));
		cout <<name <<"先发制人，飞剑出鞘，击中" <<p.name <<"的脑门，" <<p.name <<"生命值减少了" <<HPtemp <<endl;
		p.HP=(int)(p.HP-HPtemp);
		EXPtemp=(int)(HPtemp*1.2);
	}
	if ((speed<=p.speed) && (rand()%50<1))//敌方躲避
	{
		cout <<name <<"拔出利剑，一阵乱砍，" <<p.name <<"顺势躲开了。" <<endl;
		system("pause");
		return 1;
	}
	if (rand()%100<=10)//10%概率发生重击
	{
		hit=1.5;//攻击因子变为1.5
		cout <<name <<"力量剧增，发出会心一击。";
	}
	HPtemp=(int)(hit*(1.0*AP/p.DP)*AP*30/(rand()%8+32));
	cout <<name <<"猛然挥剑，一道银光略过眼前，" <<p.name <<"被一道剑气穿膛而过，生命值减少了" <<HPtemp <<endl;
	EXPtemp=(int)(EXPtemp+HPtemp*1.2);//没有int可能会有警告
	p.HP=(int)(p.HP-HPtemp);
	cout <<name <<"获得了" <<EXPtemp <<"点经验值。" <<endl;
	EXP=(int)(EXP+EXPtemp);
	system("pause");
	return 1;//攻击操作成功
}
bool Swordsman::specialatt(Player &p)
{
	if (MP<40)
	{
		cout <<"您的魔法值不够！" <<endl;
		system("pause");
		return 0;//魔法不够，特殊攻击操作失败
	}
	else
	{
		MP=MP-40;
		if (rand()%100<=10)//10%敌方躲避
		{
			cout <<name <<"刚刚使出重剑斩，" <<p.name <<"就来了个鹞子翻身，跳开了。" <<endl;
			system("pause");
			return 1;
		}
		double HPtemp=0,EXPtemp=0;
		double hit=1;
		srand(time(NULL));
		HPtemp=(int)(AP*1.2+20);
		EXPtemp=(int)(HPtemp*1.5);
		cout <<name <<"使出浑身解数，大叫一声“重~~~~剑~~~~斩~~~~！”拿起宝剑就向" <<p.name <<"砸去，顿时间鲜血四溅……" <<endl;
		cout <<p.name <<"生命值减少了" <<HPtemp <<"，" <<name <<"获得了" <<EXPtemp <<"点经验值。" <<endl;
		p.HP=(int)(p.HP-HPtemp);
		EXP=(int)(EXP+EXPtemp);
		system("pause");
	}
	return 1;//特殊攻击操作成功
}
void Swordsman::AI(Player &p)//电脑AI
{
	if ((HP<=(int)((1.0*p.AP/DP)*p.AP*1.5)) && (HP+100<=1.1*HPmax) && (bag.nOfHeal()>0) && (p.HP>int((1.0*p.AP/DP)*p.AP*0.6)))
	//电脑玩家的生命值经不起人类玩家打击且使用回复剂不算太浪费且有回复剂可以使用且人类玩家不可能被电脑玩家直接杀死
	{
		useHeal();//则使用回复剂
	}
	else
	{
		if (MP>=40 && HP>0.5*HPmax && rand()%10>7)//魔法值足够且电脑的HP足够且30%概率
		{
			specialatt(p);//使用特殊攻击
			p.isDead();//判断人类玩家是否死亡了
		}
		else
		{
			if (MP<40 && HP>0.5*HPmax && !bag.nOfMW())//魔法值不够且电脑的HP足够安全
			{
				useMW();//使用魔法水
			}
			else//其他情况
			{
				attack(p);//使用普通攻击
				p.isDead();//判断人类玩家是否死亡了
			}
		}
	}
}
