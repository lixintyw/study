#include "skill.h"

Skill::Skill(string name, int attack)
{
	m_strName = name;
	m_iAttack = attack;
	cout << "Skill(string, int)\n";
}

const string & Skill::getName()
{
	return m_strName;
}

int Skill::getAttack()
{
	return m_iAttack;
}
