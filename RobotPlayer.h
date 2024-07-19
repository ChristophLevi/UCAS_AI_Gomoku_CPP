#include"SustainFunctions.h" 
#include"GamePlayer.h" 
#include"GameCondition.h" 
#include"GameScore.h" 

class RobotPlayer : public GamePlayer                      // RobotPlayer类继承自GamePlayer类，表示机器玩家
{
private:
	int chequer_score[Size][Size] = { 0 };                 // 棋盘评分
	int search_depth = 2;                                  // 搜索深度
	int board_evaluate(int chequer);                        // 对整个棋盘局势进行评估，得到评分
	GameCondition line_situation(const vector<int>& line, int chequer); // 计算一条线上的局势情况
	GameCondition single_situation(Position p, int chequer);   // 计算一个位置的局势情况
	int calculateTotalScore(int chequer);
	void countMatches(const vector<int>& shape, const vector<int>& line, int start, int chequer, int& counter);
	void updateChequerScore(Position p);
	int calculateTotalScore();
	GameCondition lineSituation(const vector<int>& line, int chequer);
	int calculateLineScore(const GameCondition& my_situation, const GameCondition& enemy_situation);
	//void get_line(vector<int>& line, Position start, int len, Position dir);
	//void get_line(std::vector<int>& line, Position start, int len, Position dir);
	bool is_board_empty();
	Position get_next_position(Position p, Position dir);
	void get_neighbor(std::vector<Position>& ps, Position p);
	bool is_valid_position(Position p);
	//bool is_valid_position(Position p);
	//GameCondition single_situation(Position p, int player);
	//int change_player(int player);
	void update_positions(vector<Position>& ps, const vector<Position>& v);
	bool is_higher_situation(const vector<Position>& v_win5, const vector<Position>& v_live4, const vector<Position>& v_dead4, const vector<Position>& v_jump4, const vector<Position>& v_live3);
	bool is_lower_situation(const vector<Position>& v_dead3, const vector<Position>& v_jump3, const vector<Position>& v_live2, const vector<Position>& v_dead2, const vector<Position>& v_jump2);
	void insert_positions(vector<Position>& ps, const vector<Position>& v);
    void get_horizontal_line_situation(Position p, int chequer, GameCondition& situation, vector<int>& line);
	void get_vertical_line_situation(Position p, int chequer, GameCondition& situation, vector<int>& line);
	void get_main_diagonal_line_situation(Position p, int chequer, GameCondition& situation, vector<int>& line);
	void get_secondary_diagonal_line_situation(Position p, int chequer, GameCondition& situation, vector<int>& line);
	int board_situation_evaluate(int chequer);             // 对棋盘局势进行评估，得到评分
	int evaluate_line_around(Position p, Position direction);
	int evaluate_diagonal_lines_around(Position p);
	void single_score_update(Position p);                   // 更新一个位置的评分
	void put_chequer(Position p, int chequer);               // 下棋，同时更新棋盘评分
	void remove_chequer(Position p, int chequer);            // 移除棋子，同时更新评分
	int get_board_score();                                   // 获取棋盘上所有棋子的总分
	int line_evaluate(const vector<int>& line, int chequer); // 对一条线的评估
	int single_evaluate(Position p, int chequer);            // 对某一个位置的评估
	void get_line(vector<int>& line, Position start, int len, Position orientation); // 获取一条线上的棋子情况
	//void get_neighbor(vector<Position>& ps, Position p);
	void effect_pos_gen(vector<Position>& ps);           // 生成有效点集
	void clearVisitArray();
	void checkNeighborSituations(const vector<Position>& neighbor, int i, int j, vector<vector<Position>>& situationVectors);
	void checkAndAddSituation(const Position& pos, vector<vector<Position>>& situationVectors);
	void addPositionToSituationVector(const GameCondition& s1, const GameCondition& s2, const Position& pos, vector<vector<Position>>& situationVectors);
	bool hasHigherSituation(const vector<vector<Position>>& situationVectors);
	bool hasLowerSituation(const vector<vector<Position>>& situationVectors);
	void addPositionsToResult(vector<Position>& ps, const vector<vector<Position>>& situationVectors, bool higher_situation, bool lower_situation);
public:
	bool inline checkMatch(const vector<int>& shape, const vector<int>& line, int start, int chequer);
	vector<int> inline reverseShape(const vector<int>& shape);
	bool is_board_empty() const;
	RobotPlayer() {}
	RobotPlayer(int c, int _board[Size][Size]) { chequer = c; board = _board; } // 带参数的构造函数，用于初始化棋子和棋盘
	int min_max_search(int chequer, Position step, int beta, int alpha, int deep, bool maxl); // 极大极小搜索算法
	virtual Position get_position();                         // 重写父类的虚函数，获取玩家下棋的位置
	void TEST();
};