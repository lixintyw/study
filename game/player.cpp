#include "player.h"
#include <stdlib.h>  //srand  rand
#include <time.h>  //用于产生随机种子

Player::Player(string name, int blood)
{
	//给成员变量赋值
	m_strName = name;
	m_iBlood = blood;
	//初始化游戏技能
	initSkill();
}
void Player::initSkill()
{
	string strName = "";
	int iAttack = 0;
	for (int i = 0; i < SKILL_NUM; i++)
	{
		cout << "请输入技能的名字:\n";
		cin >> strName;
		cout << "请输入技能的攻击值:\n";
		cin >> iAttack;
		m_pSkill[i] = new Skill(strName, iAttack);
	}
}
const string & Player::getName()
{
	return m_strName;
}
int Player::getBlood()
{
	return m_iBlood;
}
void Player::beAttacked(const Player &p)
{
	//获得攻击的技能
	int num = 0;
	srand((unsigned int)time(NULL));
	num = rand() % SKILL_NUM;

	//掉血
	int iDropBlood = 0;
	if (m_iBlood > p.m_pSkill[num]->getAttack())
	{
		iDropBlood = p.m_pSkill[num]->getAttack();
		m_iBlood -= iDropBlood;
	}
	else
	{
		iDropBlood = m_iBlood;
		m_iBlood -= iDropBlood;
	}

	//显示
	cout << m_strName << "受到" << p.m_strName
		 << "使用" << p.m_pSkill[num]->getName()
		 << "攻击,掉了" << iDropBlood 
		 << "点血,剩余血量值为:" << m_iBlood 
		 << endl;
}
bool Player::isLost()
{
	bool bLost = false;
	if (0 == m_iBlood)
	{
		bLost = true;
	}
	return bLost;
}
void Player::showWin()
{
	cout << m_strName << ":使用蔑视的眼光看着对方说:我是第二，谁是第一...\n";
}
void Player::showLost()
{
	cout << m_strName<< ":你等着，我会骑驴再回来的\n";
}
