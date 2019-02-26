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
	

	int GameStatus;   //Game状态，-1表示未开始，0表示准备，1表示正在进行，2表示结束
	double timer;	//计时器
	clock_t start, finish; //开始时间和结束时间
	int gamecount;   //过关人数
	int player_rank, finish_player;	//玩家游戏排名,以及完成游戏的人数
	void GetRank(std::vector<Car> nowstatu, vector<Load> loads);
	std::vector<int> rank;	//排行榜
private:
	GameManager();
	~GameManager();
	void StartGame();
	void EndGame();
	void ReadyGame();
	static GameManager* instance;
};
//GetRank在Main函数里调用，GetRnak(allcar,mytrack.loads);调用方式如上，allcar是存所有小车的vector，mytrack.loads是指道路信息中的路段信息，不用改此参数。

