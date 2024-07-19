#include "MainOperations.h"
void MainOperations::maingame()        // 游戏主循环
{
	GamePlayer *p1, *p2;
	p1 = new HumanityPlayer(black_chequer, board);
	p2 = new RobotPlayer(white_chequer, board);
	int status= 1;
	board_display();
    // p1
while (status>= 0)            
	{
	if (status == 1) {                    // 如果状态为1（玩家回合）
		Position p = p1->get_position();  // 获取玩家位置
		last_pos = p;                     // 记录上次位置
		if (steps.empty())                // 如果步骤为空
		{
			steps.push_back(Step(1, 1, p));                     // 添加第一步
		}
		else
		{
			steps.push_back(Step(1, steps.back().hand + 1, p));  // 添加后续步骤
		}
		board_display();              // 显示棋盘
		int result = victory_sense(p);  // 检测是否获胜
		if (result == 1) {           // 如果玩家获胜
			cout << "你打败了人工智能..." << endl;                  // 输出获胜信息
			status = -1;             // 设置状态为-1（游戏结束）
		}
		else if (result == 2) {       // 如果AI获胜
			cout << "你被人工智能打败了..." << endl;               // 输出失败信息
			status = -2;             // 设置状态为-2（游戏结束）
		}
		else {
			status = 2;             // 设置状态为2（AI回合）
			continue;               // 继续下一次循环
		}
	}
		if (status== 2) {
			Position p = p2->get_position();
			last_pos = p;
			if (steps.empty()) {
				steps.push_back(Step(1, 1, p));
			}
			else {
				steps.push_back(Step(1, steps.back().hand + 1, p));
			}
			board_display();
			int result = victory_sense(p);
			if (result == 1) {
				cout << "你                " << endl;
				cout << "  打              " << endl;
				cout << "    败            " << endl;
				cout << "      了          " << endl;
				cout << "        人        " << endl;
				cout << "          工      " << endl;
				cout << "            智    " << endl;
				cout << "              能  " << endl;
				cout << "                ！" << endl;
				status= -1;
			}
			else if (result == 2) {
				cout << "你                " << endl;
				cout << "  被              " << endl;
				cout << "    人            " << endl;
				cout << "      工          " << endl;
				cout << "        智        "<< endl;
				cout << "          能      " << endl;
				cout << "            打    " << endl;
				cout << "              败  " << endl;
				cout << "                了" << endl;
				status= -2;
			}
			else status= 1;
			continue;
		}
	}
	save_steps();
	system("pause");
}
void MainOperations::board_display()
{
	system("cls");
	cout << "   ";
	for (int i = 0; i < Size; i++) 
	{
		cout << char('A' + i) << " ";  //横行为ABCD..等字母
	}
	cout << endl;
	for (int i = 0; i < Size; i++) 
	{
		for (int j = 0; j < Size; j++) 
		{
			if (j == 0) {
				printf("%*d", 3, 13 - i);
			}
			if (board[i][j]>0) 
			{
				if (board[i][j] == black_chequer) cout << "●";
				else if (board[i][j] == white_chequer) cout << "○";
				if (j == Size - 1)cout << endl;
			}
			else {
				if (i == 0 && j == 0)                   cout << "┏-";
				else if (i == 0 && j == Size - 1)       cout << "┓" << endl;
				else if (i == 0)                        cout << "┳-";
				else if (i == Size - 1 && j == 0)       cout << "┗-";
				else if (i == Size - 1 && j == Size - 1)cout << "┛" << endl;
				else if (j == 0)                        cout << "┣-";
				else if (i == Size - 1)                 cout << "┻-";
				else if (j == Size - 1)                 cout << "┫" << endl;
				else                                    cout << "╋-";
			}
		}
	}
}
bool MainOperations::five_lian(Position p0, Position orientation) {
	// 计算五个位置
	Position p1 = p0 + orientation;
	Position p2 = p1 + orientation;
	Position p3 = p2 + orientation;
	Position p4 = p3 + orientation;
    // 检查这五个位置是否在棋盘内，以及是否具有相同的棋子
	if (is_in(p0) && is_in(p1) && is_in(p2) && is_in(p3) && is_in(p4) &&
		board[p1.r][p1.c] == board[p0.r][p0.c] && board[p2.r][p2.c] == board[p0.r][p0.c] &&
		board[p3.r][p3.c] == board[p0.r][p0.c] && board[p4.r][p4.c] == board[p0.r][p0.c]) {
		return true;  // 如果满足五连条件，返回true
	}
	return false;      
}
bool MainOperations::six_lian(Position p0, Position orientation) {
	// 计算六个位置
	Position p1 = p0 + orientation;
	Position p2 = p1 + orientation;
	Position p3 = p2 + orientation;
	Position p4 = p3 + orientation;
	Position p5 = p4 + orientation;
	// 检查这六个位置是否在棋盘内，以及是否具有相同的棋子
	if (is_in(p0) && is_in(p1) && is_in(p2) && is_in(p3) && is_in(p4) && is_in(p5) &&
		board[p1.r][p1.c] == board[p0.r][p0.c] && board[p2.r][p2.c] == board[p0.r][p0.c] &&
		board[p3.r][p3.c] == board[p0.r][p0.c] && board[p4.r][p4.c] == board[p0.r][p0.c] &&
		board[p5.r][p5.c] == board[p0.r][p0.c])
	{
		return true;  // 如果满足六连条件，返回true
	}
	    return false;
}
Position MainOperations::find_edge(Position p0, Position orientation) {
	Position p1 = p0 + orientation;
	while (is_in(p1) && board[p1.r][p1.c] == board[p0.r][p0.c]) {
		p0 = p1;
		p1 = p1 + orientation;
	}
	return p0;
}
int MainOperations::victory_sense(Position p)
{
	// 从p开始的检测五连
	char chequer = board[p.r][p.c];
	// 找到最左、上、左上、左下端
	Position p_left = find_edge(p, Position(0, -1));
	Position p_up = find_edge(p, Position(-1, 0));
	Position p_upleft = find_edge(p, Position(-1, -1));
	Position p_downleft = find_edge(p, Position(1, -1));
	// p位置的棋子胜利标志	
	bool win_flag = five_lian(p_left, Position(0, 1)) || five_lian(p_up, Position(1, 0)) ||
		five_lian(p_upleft, Position(1, 1)) || five_lian(p_downleft, Position(-1, 1));
	if (chequer == this->black_chequer) {
		// 如果玩家1胜利，返回1
		if (win_flag) return 1;
	}
	else {
		// 如果玩家2胜利，返回2
		if (win_flag) return 2;
	}
	return 0;
}
void MainOperations::forward() 
{
}
string MainOperations::save_steps()
{
	return string();
}

