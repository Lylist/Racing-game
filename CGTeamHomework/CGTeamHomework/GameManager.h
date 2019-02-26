#pragma once
#include <vector>
#include <time.h>
#include "Track.h"
#include "Car.h"
class Car;
class GameManager
{
public:
	static GameManager* GetInstance();
	

	int GameStatus;   //Game״̬��-1��ʾδ��ʼ��0��ʾ׼����1��ʾ���ڽ��У�2��ʾ����
	double timer;	//��ʱ��
	clock_t start, finish; //��ʼʱ��ͽ���ʱ��
	int gamecount;   //��������
	int player_rank, finish_player;	//�����Ϸ����,�Լ������Ϸ������
	void GetRank(std::vector<Car> nowstatu, vector<Load> loads);
	std::vector<int> rank;	//���а�
private:
	GameManager();
	~GameManager();
	void StartGame();
	void EndGame();
	void ReadyGame();
	static GameManager* instance;
};
//GetRank��Main��������ã�GetRnak(allcar,mytrack.loads);���÷�ʽ���ϣ�allcar�Ǵ�����С����vector��mytrack.loads��ָ��·��Ϣ�е�·����Ϣ�����øĴ˲�����

