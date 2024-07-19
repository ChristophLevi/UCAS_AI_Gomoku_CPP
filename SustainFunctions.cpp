#include"SustainFunctions.h"
#include"GameCondition.h" 

// 反转角色
int change_player(int role) {
	if (role == 1)
		return 2;
	return 1;
}
// 检查位置是否在棋盘内
bool is_in(Position p) {
	if (p.r >= 0 && p.r < Size && p.c >= 0 && p.c < Size)
		return true;
	else return false;
}
// 将位置转换为字符串表示
string position_trans(Position p) {
	string s = "";
	s = "(" + to_string(13 - p.r) + ", " + char(p.c + 'A') + ")";  // 将行号和列号转换为字符串
	return s;
}
// 打印棋盘
void print_board(int board[][Size])
{
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			cout << board[i][j] << " ";  // 输出棋盘上每个位置的值
		}
		cout << endl; 
	}
}
