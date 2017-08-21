#ifndef SKILL_H
#define SKILL_H

#include <iostream>
#include <string>
using namespace std;

class Skill
{
public:
	Skill(string name, int attack);
	const string &getName();
	int getAttack();

private:
	string m_strName;
	int m_iAttack;
};

#endif
