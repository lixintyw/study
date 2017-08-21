#include "player.h"
#include <unistd.h>


class Game
{
public:
	Game()
	{
		string strName;
		int iBlood = 0;
		cout << "请输入游戏人物名字:";
		cin >> strName;
		cout << "请输入游戏人物血值:";
		cin >> iBlood;
		m_pPlayer1 = new Player(strName, iBlood);
	
		cout << "请输入游戏人物名字:";
		cin >> strName;
		cout << "请输入游戏人物血值:";
		cin >> iBlood;
		m_pPlayer2 = new Player(strName, iBlood);
	}

	void run()
	{
		bool bAttack = false;
		while (1)
		{
			if (bAttack)
			{
				m_pPlayer1->beAttacked(*m_pPlayer2);
				if (m_pPlayer1->isLost())
				{
					m_pPlayer2->showWin();
					m_pPlayer1->showLost();
					break;
				}
				bAttack = false;
			}
			else
			{
				m_pPlayer2->beAttacked(*m_pPlayer1);
				if (m_pPlayer2->isLost())
				{
					m_pPlayer1->showWin();
					m_pPlayer2->showLost();
					break;
				}
				bAttack = true;
			}
			sleep(1);
		}
	}

private:
	Player *m_pPlayer1;
	Player *m_pPlayer2;
};

int main(void)
{
	Game game;
	game.run();

	return 0;
}
