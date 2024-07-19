#include "MainOperations.h"
#include<cstdio>

int main() {                      
	MainOperations mo = MainOperations(); // 创建游戏控制对象
	mo.maingame();                        // 运行游戏主循环
	return 0; 
}