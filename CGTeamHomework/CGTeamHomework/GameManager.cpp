#include "GameManager.h"



GameManager::GameManager()
{
	timer = 0;
	GameStatus = 0;
	gamecount = 0;
}
GameManager* GameManager::instance = new GameManager();
GameManager* GameManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new GameManager();
	}
	return instance;
}

GameManager::~GameManager()
{
}

void GameManager::StartGame()
{
	start = clock();
	GameStatus = 1;
}

void GameManager::EndGame()
{
	finish = clock();
	GameStatus = 2;
	player_rank = finish_player + 1;
}

void GameManager::ReadyGame()
{
	GameStatus = 0;
}


//��ȡ���а��ȱȽ����ĸ�·�Σ�Ȼ��Ƚ���ͬһ·�εĳ��Ⱥ�
void GameManager::GetRank(std::vector<Car> nowstatu, vector<Load> loads)
{
	//����ѡ������ǰ�������θߵ�
	for (int i = 0; i < nowstatu.size(); i++)
	{
		for (int j = i + 1; j < nowstatu.size(); j++)
		{
			if (nowstatu[i].now_load < nowstatu[j].now_load)
			{
				std::swap(nowstatu[i], nowstatu[j]);
			}
			else if (nowstatu[i].now_load == nowstatu[j].now_load)
			{
				if (loads[nowstatu[i].now_load].type == 1)
				{
					if (nowstatu[j].pos.z > nowstatu[i].pos.z)
					{
						std::swap(nowstatu[i], nowstatu[j]);
					}
				}
				else if (loads[nowstatu[i].now_load].type == 2)
				{
					if (nowstatu[j].pos.z < nowstatu[i].pos.z)
					{
						std::swap(nowstatu[i], nowstatu[j]);
					}
				}
				else if (loads[nowstatu[i].now_load].type == 3
					|| loads[nowstatu[i].now_load].type == 13
					|| loads[nowstatu[i].now_load].type == 32
					|| loads[nowstatu[i].now_load].type == 23
					|| loads[nowstatu[i].now_load].type == 42)
				{
					if (nowstatu[j].pos.x > nowstatu[i].pos.x)
					{
						std::swap(nowstatu[i], nowstatu[j]);
					}
				}
				else if (loads[nowstatu[i].now_load].type == 4
					|| loads[nowstatu[i].now_load].type == 24
					|| loads[nowstatu[i].now_load].type == 13)
				{
					if (nowstatu[j].pos.x < nowstatu[i].pos.x)
					{
						std::swap(nowstatu[i], nowstatu[j]);
					}
				}
			}
		}
	}
}