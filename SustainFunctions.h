#pragma once
#define Size 13
#define INF 100000000
#include<set>
#include<cstring>
#include<random>
#include<time.h> 
#include<assert.h>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<vector>
#include<map>
using namespace std;

struct Position {
public:
	int r;
	int c;
	Position() {}
	Position(int _r, int _c) { r = _r; c = _c; }
	Position operator+(const Position &p)const { return Position(r + p.r, c + p.c); }
};
struct Step {
	int player;	     // 玩家
	int hand;	     // 手数
	Position p;		 // 落子位置
	Step() {}
	Step(int _player, int _hand, Position _p) {
		player = _player;
		hand = _hand;
		p = _p;
	}
};

bool is_in(Position p);
void print_board(int board[][Size]);
string position_trans(Position p);
int change_player(int role);



