#ifndef _MAINOPERATIONS
#define _MAINOPERATIONS
#include"SustainFunctions.h"
#include"HumanityPlayer.h" 
#include"RobotPlayer.h" 
#include"GameCondition.h" 
#include"GameScore.h" 

class MainOperations {
public:
	int board[Size][Size];            
	static const int black_chequer = 1;  // 黑棋为1
	static const int white_chequer = 2;  // 白棋为2
	static const int nothing = 0;        // 空格为0
	MainOperations() {memset(this->board, 0, sizeof(this->board));}       // 初始化棋盘数组为0
	vector<Step> steps;    
	Position last_pos;         
	void maingame();      
	void board_display(); 
	bool five_lian(Position p0, Position orientation);      // 判断从p0位置开始，按照orientation方向是否形成5连
	bool six_lian(Position p0, Position orientation);      // 判断从p0位置开始，按照orientation方向是否形成6连
	Position find_edge(Position p0, Position orientation);  // 从p0位置开始，按照orientation方向找到边界位置
	int victory_sense(Position p);                         // 从p位置检测是否形成5连、6连，若有人胜利，返回玩家编号，否则返回0
	void forward();                                        // 前进
	string save_steps();            
};
#endif 