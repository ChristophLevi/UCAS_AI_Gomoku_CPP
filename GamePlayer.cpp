#include"HumanityPlayer.h" 
#include"RobotPlayer.h" 

const vector<int> win5 = { 1,1,1,1,1 };
const vector<int> live4 = { 0,1,1,1,1,0 };
const vector<int> jump4 = { 1,1,1,0,1 };
const vector<int> dead4 = { 1,1,1,1,0 };
const vector<int> live3 = { 0,1,1,1,0 };
const vector<int> jump3 = { 0,1,1,0,1,0 };
const vector<int> dead3 = { 1,1,1,0 };
const vector<int> live2 = { 0,1,1,0 };
const vector<int> jump2 = {0,1,0,1,0};
void GamePlayer::change_chequer(int _chequer){this->chequer = chequer;}
int ab_cut = 0;
bool visit[Size][Size];

Position HumanityPlayer::get_position()
{
	int r, c;	
	char temp;  
	cout << "[友情提示：您可以按住crtl+鼠标滚轮实现放大]"<<endl ;
	cout << "请输入坐标(形如 1B) 并按下回车键 来与AI对战:" ;
	while (true) {
		cin >> r;
		cin >> temp;
		r = 13 - r; c = temp - 'A';
		if (!is_in(Position(r, c))) {
			cout << "你所下的格子是无效位置 (请注意使用大写字母):" ;
			continue;
		}
		if (board[r][c]) {
			cout << "你所下的格子被占用了 (请重新选择落点）：" ;
			continue;
		}
		break;
	}
	board[r][c] = chequer;
	return Position(r, c);
}

int RobotPlayer::board_evaluate(int chequer) {
	vector<int> line;
	int total_score = 0;
	total_score = calculateTotalScore(chequer);
	return total_score;
}

int RobotPlayer::calculateTotalScore(int chequer) {
	int total = 0;
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (board[i][j] == chequer) {
				total += single_evaluate(Position(i, j), chequer);
			}
			else if (board[i][j] == change_player(chequer)) {
				total -= single_evaluate(Position(i, j), change_player(chequer));
			}
		}
	}
	return total;
}

bool inline checkMatch(const vector<int>& shape, const vector<int>& line, int start, int chequer) {
	bool flag = true;
	for (int i = 0; i < int(shape.size()); i++) {
		if (line[start + i] != chequer && shape[i] == 1 ||
			line[start + i] != 0 && shape[i] == 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

vector<int> inline reverseShape(const vector<int>& shape) {
	vector<int> shape_rev(shape.size());
	reverse_copy(shape.begin(), shape.end(), shape_rev.begin());
	return shape_rev;
}

bool inline match(const vector<int>& shape, const vector<int>& line, int start, int chequer) {
	if (line.size() - start < shape.size()) return false;
	bool flag1 = checkMatch(shape, line, start, chequer);
	bool flag2 = checkMatch(reverseShape(shape), line, start, chequer);
	return flag1 || flag2;
}

GameCondition RobotPlayer::line_situation(const vector<int>& line, int chequer)
{
	GameCondition situation;
	for (int i = 0; i < int(line.size()); i++) {
		countMatches(win5, line, i, chequer, situation.win5);
		countMatches(live4, line, i, chequer, situation.live4);
		countMatches(jump4, line, i, chequer, situation.jump4);
		countMatches(dead4, line, i, chequer, situation.dead4);
		countMatches(live3, line, i, chequer, situation.live3);
		countMatches(jump3, line, i, chequer, situation.jump3);
		countMatches(dead3, line, i, chequer, situation.dead3);
		countMatches(live2, line, i, chequer, situation.live2);
		countMatches(jump2, line, i, chequer, situation.jump2);
	}
	return situation;
}

void RobotPlayer::countMatches(const vector<int>& shape, const vector<int>& line, int start, int chequer, int& counter) {
	if (match(shape, line, start, chequer)) {
		counter++;
	}
}

GameCondition RobotPlayer::single_situation(Position p, int chequer)
{
	int score = 0;
	int b_left = max(0, p.c - 4);
	int b_right = min(Size, p.c + 4);
	int b_up = max(0, p.r - 4);
	int b_down = min(Size, p.r + 4);
	vector<int>line;
	GameCondition situation;
	get_line(line, Position(p.r, b_left), b_right - b_left + 1, Position(0, 1));
	situation = situation + line_situation(line, chequer);
	get_line(line, Position(b_up, p.c), b_down - b_up + 1, Position(1, 0));
	situation = situation + line_situation(line, chequer);
	int a = min(p.c - b_left, p.r - b_up);
	int b = min(b_right - p.c, p.r - b_up);
	int c = min(b_down - b_up, b_right - b_left);
	get_line(line, Position(p.r - a, p.c - a), c, Position(1, 1));
	situation = situation + line_situation(line, chequer);
	get_line(line, Position(p.r - a, p.c + a), c, Position(1, -1));
	situation = situation + line_situation(line, chequer);
	return situation;
}

void RobotPlayer::single_score_update(Position p)
{
	if (board[p.r][p.c] == 0) {
		chequer_score[p.r][p.c] = 0;
		return;
	}
	updateChequerScore(p);
}
void RobotPlayer::updateChequerScore(Position p)
{
	int score = 0;
	int b_left = max(0, p.c - 4);
	int b_right = min(Size, p.c + 4);
	int b_up = max(0, p.r - 4);
	int b_down = min(Size, p.r + 4);
	vector<int> line;
	get_line(line, Position(p.r, b_left), b_right - b_left + 1, Position(0, 1));
	score += line_evaluate(line, chequer);
	get_line(line, Position(b_up, p.c), b_down - b_up + 1, Position(1, 0));
	score += line_evaluate(line, chequer);
	int a = min(p.c - b_left, p.r - b_up);
	int b = min(b_right - p.c, p.r - b_up);
	int c = min(b_down - b_up, b_right - b_left);
	get_line(line, Position(p.r - a, p.c - a), c, Position(1, 1));
	score += line_evaluate(line, chequer);
	get_line(line, Position(p.r - a, p.c + a), c, Position(1, -1));
	score += line_evaluate(line, chequer);
	if (board[p.r][p.c] == chequer) {
		chequer_score[p.r][p.c] = score;
	}
	else if (board[p.r][p.c] == change_player(chequer)) {
		chequer_score[p.r][p.c] = -score;
	}
	else {
		chequer_score[p.r][p.c] = 0;
	}
}

int RobotPlayer::get_board_score()
{
	return calculateTotalScore();
}
int RobotPlayer::calculateTotalScore()
{
	int total_score = 0;
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			total_score += board[i][j] == chequer ? chequer_score[i][j] : -chequer_score[i][j];
		}
	}
	return total_score;
}


int RobotPlayer::line_evaluate(const vector<int>& line, int chequer)
{
	GameCondition my_situation = lineSituation(line, chequer);
	GameCondition enemy_situation = lineSituation(line, change_player(chequer));
	return calculateLineScore(my_situation, enemy_situation);
}
GameCondition RobotPlayer::lineSituation(const vector<int>& line, int chequer)
{
	GameCondition condition;
	// 实现 lineSituation 函数的代码
	return condition;
}
int RobotPlayer::calculateLineScore(const GameCondition& my_situation, const GameCondition& enemy_situation)
{
	int score = 0;
	score += GameScore::win5 * (my_situation.win5);
	score += -GameScore::win5 / 2 * (enemy_situation.win5);
	score += GameScore::live4 * (my_situation.live4 - enemy_situation.live4);
	score += GameScore::jump4 * (my_situation.jump4 - enemy_situation.jump4);
	score += GameScore::dead4 * (my_situation.dead4 - enemy_situation.dead4);
	score += GameScore::live3 * (my_situation.live3 - enemy_situation.live3);
	score += GameScore::jump3 * (my_situation.jump3 - enemy_situation.jump3);
	score += GameScore::dead3 * (my_situation.dead3 - enemy_situation.dead3);
	score += GameScore::live2 * (my_situation.live2 - enemy_situation.live2);
	return score;
}

int RobotPlayer::single_evaluate(Position p, int chequer)
{
	int score = 0;
	int b_left = max(0, p.c - 4);
	int b_right = min(Size, p.c + 4);
	int b_up = max(0, p.r - 4);
	int b_down = min(Size, p.r + 4);
	vector<int> line;

	get_line(line, Position(p.r, b_left), b_right - b_left + 1, Position(0, 1));
	score += line_evaluate(line, chequer);

	get_line(line, Position(b_up, p.c), b_down - b_up + 1, Position(1, 0));
	score += line_evaluate(line, chequer);

	int a = min(p.c - b_left, p.r - b_up);
	int b = min(b_right - p.c, p.r - b_up);
	int c = min(b_down - b_up, b_right - b_left);

	get_line(line, Position(p.r - a, p.c - a), c, Position(1, 1));
	score += line_evaluate(line, chequer);

	get_line(line, Position(p.r - a, p.c + a), c, Position(1, -1));
	score += line_evaluate(line, chequer);

	return score;
}

int RobotPlayer::min_max_search(int chequer, Position step, int alpha, int beta, int deep, bool maxl)
{
	if (deep <= 1) {
		board[step.r][step.c] = chequer;
		int score = board_evaluate(change_player(chequer));
		board[step.r][step.c] = 0;
		return score;
	}
	board[step.r][step.c] = chequer;
	vector<Position> effect_pos;
	effect_pos_gen(effect_pos);
	int best_score;
	if (maxl) best_score = -INF;
	else	  best_score = INF;
	for (auto iter = effect_pos.begin(); iter != effect_pos.end(); iter++) {
		Position p = *iter;
		int score = min_max_search(change_player(chequer), p, alpha, beta, deep - 1, !maxl);
		best_score = (maxl) ? std::max(best_score, score) : std::min(best_score, score);
	}
	board[step.r][step.c] = 0;
	return best_score;
}
bool RobotPlayer::is_board_empty() {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (board[i][j]) {
				return false;
			}
		}
	}
	return true;
}
Position RobotPlayer::get_position() {
	std::vector<Position> effect_pos;
	effect_pos_gen(effect_pos);
	Position best_pos = Position(0, 0);
	int best_score = -INF; 

	if (is_board_empty()) {
		board[Size / 2][Size / 2] = chequer;
		return Position(Size / 2, Size / 2);
	}

	int alpha = INF;
	int beta = -INF;
	ab_cut = 0;

	for (auto iter = effect_pos.begin(); iter != effect_pos.end(); iter++) {
		int score = min_max_search(chequer, *iter, alpha, beta, search_depth, false);
		if (score > best_score) {
			best_score = score;
			best_pos = *iter;
		}
		if (score > beta) {
			beta = score;
		}
	}

	board[best_pos.r][best_pos.c] = chequer;
	return best_pos;
}

void inline RobotPlayer::get_line(std::vector<int>& line, Position start, int len, Position dir) {
	line.clear();
	Position p = start;
	for (int i = 0; i < len; i++) {
		line.push_back(board[p.r][p.c]);
		p = get_next_position(p, dir);
	}
}
Position RobotPlayer::get_next_position(Position p, Position dir) {
	return Position(p.r + dir.r, p.c + dir.c);
}

void RobotPlayer::get_neighbor(std::vector<Position>& ps, Position p) {
	ps.clear();
	for (int i = max(p.r - 2, 0); i <= min(p.r + 2, Size - 1); i++) {
		for (int j = max(p.c - 2, 0); j <= min(p.c + 2, Size - 1); j++) {
			if (is_valid_position(Position(i, j))) {
				ps.push_back(Position(i, j));
				visit[i][j] = 1;
			}
		}
	}
}
bool RobotPlayer::is_valid_position(Position p) {
	return p.r >= 0 && p.r < Size && p.c >= 0 && p.c < Size && !visit[p.r][p.c];
}

























void RobotPlayer::effect_pos_gen(vector<Position>& ps) {// 生成有效位置
	// 初始化visit数组
	memset(visit, 0, sizeof(visit));
	// 分别存储不同棋型的位置
	vector<Position> v_win5;
	vector<Position> v_live4;
	vector<Position> v_dead4;
	vector<Position> v_jump4;
	vector<Position> v_live3;
	vector<Position> v_dead3;
	vector<Position> v_jump3;
	vector<Position> v_live2;
	vector<Position> v_dead2;
	vector<Position> v_jump2;
	vector<Position> v_others;
	// 存储当前局势
	GameCondition situation;
	// 遍历棋盘
	for (int i = 0; i < Size; i++) {
	for (int j = 0; j < Size; j++) {
		// 如果当前位置有棋子
		if (board[i][j]) {
			// 标记该位置已访问
			visit[i][j] = 1;
			// 获取邻居位置
			vector<Position> neighbor;
			get_neighbor(neighbor, Position(i, j));
			// 遍历邻居位置
			for (auto it = neighbor.begin(); it != neighbor.end(); it++) {
					// 如果邻居位置有棋子，跳过
				if (board[it->r][it->c]) continue;
					// 在邻居位置下子，并得到当前局势
				board[it->r][it->c] = chequer;
				GameCondition s1 = single_situation(Position(it->r, it->c), chequer);
					// 切换玩家，在邻居位置下子，并得到当前局势
				board[it->r][it->c] = change_player(chequer);
				GameCondition s2 = single_situation(Position(it->r, it->c), change_player(chequer));
					// 恢复邻居位置为空
				board[it->r][it->c] = 0;
					// 根据当前局势将位置加入对应的棋型
if (s1.win5 || s2.win5) v_win5.push_back(Position(it->r, it->c));
	else if (s1.live4 || s2.live4) v_live4.push_back(Position(it->r, it->c));
	else if (s1.dead4 || s2.dead4) v_dead4.push_back(Position(it->r, it->c));
	else if (s1.jump4 || s2.jump4) v_jump4.push_back(Position(it->r, it->c));
	else if (s1.live3 || s2.live3) v_live3.push_back(Position(it->r, it->c));
	else if (s1.dead3 || s2.dead3) v_dead3.push_back(Position(it->r, it->c));
	else if (s1.jump3 || s2.jump3) v_jump3.push_back(Position(it->r, it->c));
	else if (s1.live2 || s2.live2) v_live2.push_back(Position(it->r, it->c));
	else if (s1.dead2 || s2.live2) v_dead2.push_back(Position(it->r, it->c));
	else if (s1.jump2 || s2.jump2) v_jump2.push_back(Position(it->r, it->c));
				}
			}
		}
	}
	// 标记不同的局势
	bool higher_situation = false;
	bool lower_situation = false;
	bool mid_situation = false;
	higher_situation = !v_win5.empty() || !v_live4.empty() || !v_dead4.empty() ||
		!v_jump4.empty() || !v_live3.empty();
	lower_situation = !v_dead3.empty() || !v_jump3.empty() || !v_live2.empty() ||
		!v_dead2.empty() || !v_jump2.empty();
	// 根据不同的局势将位置加入到ps中
	if (!v_win5.empty()) {
		ps.insert(ps.end(), v_win5.begin(), v_win5.end());
		return;
	}
	if (!v_live4.empty()) {
		ps.insert(ps.end(), v_live4.begin(), v_live4.end());
		return;
	}
	ps.insert(ps.end(), v_dead4.begin(), v_dead4.end());
	ps.insert(ps.end(), v_jump4.begin(), v_jump4.end());
	ps.insert(ps.end(), v_live3.begin(), v_live3.end());
	if (!higher_situation && lower_situation) {
		ps.insert(ps.end(), v_dead3.begin(), v_dead3.end());
		ps.insert(ps.end(), v_jump3.begin(), v_jump3.end());
		if (v_dead3.empty() && v_jump3.empty()) {
			ps.insert(ps.end(), v_live2.begin(), v_live2.end());
		}
		if (v_dead3.empty() && v_jump3.empty() && v_live2.empty()) {
			ps.insert(ps.end(), v_jump2.begin(), v_jump2.end());
		}
		if (v_dead3.empty() && v_jump3.empty() && v_live2.empty() && v_jump2.empty()) {
			ps.insert(ps.end(), v_dead2.begin(), v_dead2.end());
		}
	}
	else if (!higher_situation && !lower_situation) {
		ps.insert(ps.end(), v_others.begin(), v_others.end());
	}
}
