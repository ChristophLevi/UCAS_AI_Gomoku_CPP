#include"SustainFunctions.h" 
#include"GamePlayer.h" 
#include"GameCondition.h" 
#include"GameScore.h" 

class HumanityPlayer : public GamePlayer {
public:
	HumanityPlayer() {}                                                                // 默认构造函数
	HumanityPlayer(int c, int _board[Size][Size]) { chequer = c; board = _board; }      // 带参数的构造函数，用于初始化棋子和棋盘
	virtual Position get_position();         // 重写父类的虚函数，获取玩家下棋的位置
	void print_error(string message);
	void put_chess(int r, int c);
};