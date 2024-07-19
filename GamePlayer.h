#pragma once
#include"SustainFunctions.h" 
#include"GameCondition.h" 
#include"GameScore.h" 

class GamePlayer {
public:	
	int chequer;                                       // 棋子标识
	int(*board)[Size];                                // 指向棋盘数组的指针
	virtual Position get_position() = 0;              // 纯虚函数 等着做重写
	void change_chequer(int _chequer);                // 改变玩家的棋子标识


};
