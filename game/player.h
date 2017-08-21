#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>

using namespace std;

#include "skill.h"

#define SKILL_NUM 3

class Player
{
public:
	Player(string name, int blood);
	void initSkill();
	const string &getName();
	int getBlood();
	void beAttacked(const Player &p);
	bool isLost();
	void showWin();
	void showLost();

private:
	string m_strName;
	int m_iBlood;
	Skill *m_pSkill[SKILL_NUM];
};

#endif
