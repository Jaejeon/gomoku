#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "omok_class.h"
#include <vector>
#include <cstdlib>

using namespace std;


void printLFTP(){ wcout << L"┏"; } void printITTP(){ wcout << L"┳"; } void printRTTP(){ wcout << L"┓"; }
void printLFMD(){ wcout << L"┣"; } void printITMD(){ wcout << L"╋"; } void printRTMD(){ wcout << L"┫"; }
void printLFBT(){ wcout << L"┗"; } void printITBT(){ wcout << L"┻"; } void printRTBT(){ wcout << L"┛"; }
void printBlack(){ wcout << L"○"; } void printWhite(){ wcout << L"●"; }
void printEnd(){ wcout << endl; }
DOL recog(int nextX, int nextY);
DOL recog(DOL who, int nextX, int nextY, vector<Position>* costs);
void input(char* position);
void findIndex(char* position, int* indexX, int* indexY);
void display();
Position nextMove(DOL who, int depth, int x, int y);
int recog_samsam(DOL who, int nextX, int nextY);
void findThreats(DOL who, int x, int y, vector<Position> threats);
void findCost(DOL who, int x, int y, vector<Position> costs);
void findOppoThreats(DOL who, vector<Position>* threats);
int heuristicScore(DOL who, int x, int y);
bool near_my_square(int x, int y, DOL who);

DOL arr[BOARD_SIZE][BOARD_SIZE];

int main(){
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	char position[4]; /* input position */
	int indexX, indexY;
	Position next;
	int axisCount = BOARD_SIZE;
	int diagCount = 2 * BOARD_SIZE - 1;
	int turn = 1;
	int three_count = 0;
	char start[6];
	char forClear;
	DOL stone;

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			arr[i][j] = NONE;
		}
	}

	wcout << "Black: ";
	printBlack();
	wcout << endl << "White: ";
	printWhite();
	wcout << endl;
	
	cin >> start;
	if (start[0] == 'S'){
		do{
			if ((turn % 2)){ /* Computer turn */
				if (turn == 1){
					next.x = BOARD_SIZE / 2;
					next.y = BOARD_SIZE / 2;
				}
				else{
					next = nextMove(BLACK, 0, -1, -1); // next.x, next.y 가 -1 이면 depth가 0
				}
				arr[next.x][next.y] = BLACK;
				wcout << "***********COMPUTER************" << endl;
				wcout << "AI : (" << next.x << ", " << next.y << ")" << endl;

			}
			else{ /* User turn */
				do{
					wcout << "Please input position of white stone: ";
					cin >> position;
					wcout << endl;
					findIndex(position, &indexX, &indexY);
					if (arr[indexX][indexY] != NONE) wcout << "Invalid input... Please input another position" << endl;
					else{
						next.x = indexX;
						next.y = indexY;
						arr[next.x][next.y] = WHITE;
						three_count = recog_samsam(WHITE, indexX, indexY);
						arr[next.x][next.y] = NONE;
						if (three_count >= 2) wcout << "You can not input there" << endl;
					}
				} while (arr[indexX][indexY] != NONE || three_count >= 2);
				arr[next.x][next.y] = WHITE;
				wcout << "***********  USER  ************" << endl;
			}
			turn++;
			display();
		} while (recog(next.x, next.y) == NONE || recog(next.x, next.y) == BLACK_THREE || recog(next.x, next.y) == WHITE_THREE
			|| recog(next.x, next.y) == BLACK_FOUR || recog(next.x, next.y) == WHITE_FOUR);

		if (recog(next.x, next.y) == BLACK_FIVE) wcout << "Black wins";
		else if (recog(next.x, next.y) == WHITE_FIVE) wcout << "White wins";
		else wcout << "Draw";
		wcout << endl;

		//TODO
		//wcout << "Press any key to continue..." << endl;
		//cin >> position;
		return 0;
	}
	
	else{
		
		do{
			if (!(turn % 2)){ /* Computer turn */
				if (turn == 1){
					next.x = BOARD_SIZE / 2;
					next.y = BOARD_SIZE / 2;
				}
				else{
					next = nextMove(WHITE, 0, -1, -1); // next.x, next.y 가 -1 이면 depth가 0
				}
				arr[next.x][next.y] = WHITE;
				wcout << "***********COMPUTER************" << endl;
				wcout << "AI : (" << next.x << ", " << next.y << ")" << endl;

			}
			else{ /* User turn */
				do{
					if (turn == 1){
						position[0] = start[0];
						position[1] = start[1];
						position[2] = start[2];
						position[3] = start[3];
					}
					else{
						wcout << "Please input position of white stone: ";
						cin >> position;
						wcout << endl;
					}
					findIndex(position, &indexX, &indexY);
					if (arr[indexX][indexY] != NONE) wcout << "Invalid input... Please input another position" << endl;
					else{
						next.x = indexX;
						next.y = indexY;
					}
				} while (arr[indexX][indexY] != NONE);
				arr[next.x][next.y] = BLACK;
				wcout << "***********  USER  ************" << endl;
			}
			turn++;
			display();
		} while (recog(next.x, next.y) == NONE || recog(next.x, next.y) == BLACK_THREE || recog(next.x, next.y) == WHITE_THREE
			|| recog(next.x, next.y) == BLACK_FOUR || recog(next.x, next.y) == WHITE_FOUR);

		if (recog(next.x, next.y) == BLACK_FIVE) wcout << "Black wins";
		else if (recog(next.x, next.y) == WHITE_FIVE) wcout << "White wins";
		else wcout << "Draw";
		wcout << endl;

		//TODO
		//wcout << "Press any key to continue..." << endl;
		//cin >> position;
		return 0;
	}
}

int recog_samsam(DOL who, int nextX, int nextY){
	Line lineHor, lineVer, lineUp, lineDown;
	int count = 0;
	lineHor.setType(1);
	lineVer.setType(2);
	lineUp.setType(3);
	lineDown.setType(4);
	lineHor.setStartPosition(0, nextY);
	lineVer.setStartPosition(nextX, 0);
	if (nextX > nextY) lineUp.setStartPosition(nextX - nextY, 0);
	else lineUp.setStartPosition(0, nextY - nextX);
	if (nextX + nextY >= BOARD_SIZE) lineDown.setStartPosition(nextX + nextY - BOARD_SIZE + 1, BOARD_SIZE - 1);
	else lineDown.setStartPosition(0, nextX + nextY);
	
	if (lineHor.recog(arr, who, THREE)) count++;
	if (lineUp.recog(arr, who, THREE)) count++;
	if (lineVer.recog(arr, who, THREE)) count++;
	if (lineDown.recog(arr, who, THREE)) count++;
	
	return count;
}

DOL recog(int nextX, int nextY){
	
	Line lineHor, lineVer, lineUp, lineDown;
	lineHor.setStartPosition(0, nextY);
	lineHor.setType(1);
	lineVer.setStartPosition(nextX, 0);
	lineVer.setType(2);

	if (nextX > nextY) lineUp.setStartPosition(nextX - nextY, 0);
	else lineUp.setStartPosition(0, nextY - nextX);
	lineUp.setType(3);

	if (nextX + nextY >= BOARD_SIZE) lineDown.setStartPosition(nextX + nextY - BOARD_SIZE + 1, BOARD_SIZE - 1);
	else lineDown.setStartPosition(0, nextX + nextY);
	lineDown.setType(4);

	if (lineUp.recog(arr, BLACK, WIN_STATE) || lineDown.recog(arr, BLACK, WIN_STATE) || lineHor.recog(arr, BLACK, WIN_STATE) || lineVer.recog(arr, BLACK, WIN_STATE)) return BLACK_FIVE;
	else if (lineUp.recog(arr, WHITE, WIN_STATE) || lineDown.recog(arr, WHITE, WIN_STATE) || lineHor.recog(arr, WHITE, WIN_STATE) || lineVer.recog(arr, WHITE, WIN_STATE)) return WHITE_FIVE;

	if (lineUp.recog(arr, BLACK, FOUR) || lineDown.recog(arr, BLACK, FOUR) || lineHor.recog(arr, BLACK, FOUR) || lineVer.recog(arr, BLACK, FOUR)) return BLACK_FOUR;
	else if (lineUp.recog(arr, WHITE, FOUR) || lineDown.recog(arr, WHITE, FOUR) || lineHor.recog(arr, WHITE, FOUR) || lineVer.recog(arr, WHITE, FOUR)) return WHITE_FOUR;
	
	if (lineUp.recog(arr, BLACK, THREE) || lineDown.recog(arr, BLACK, THREE) || lineHor.recog(arr, BLACK, THREE) || lineVer.recog(arr, BLACK, THREE)) return BLACK_THREE;
	else if (lineUp.recog(arr, WHITE, THREE) || lineDown.recog(arr, WHITE, THREE) || lineHor.recog(arr, WHITE, THREE) || lineVer.recog(arr, WHITE, THREE)) return WHITE_THREE;

	int count = 0;

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (arr[i][j] == NONE) count++;
		}
	}

	if (!count) return DRAW;
	return NONE;

}

DOL recog(DOL who, int nextX, int nextY, vector<Position>* costs){

	Line lineHor, lineVer, lineUp, lineDown;
	lineHor.setStartPosition(0, nextY);
	lineHor.setType(1);
	lineVer.setStartPosition(nextX, 0);
	lineVer.setType(2);

	if (nextX > nextY) lineUp.setStartPosition(nextX - nextY, 0);
	else lineUp.setStartPosition(0, nextY - nextX);
	lineUp.setType(3);

	if (nextX + nextY >= BOARD_SIZE) lineDown.setStartPosition(nextX + nextY - BOARD_SIZE + 1, BOARD_SIZE - 1);
	else lineDown.setStartPosition(0, nextX + nextY);
	lineDown.setType(4);

	if (who == WHITE && (lineUp.recog(arr, BLACK, WIN_STATE) || lineDown.recog(arr, BLACK, WIN_STATE) || lineHor.recog(arr, BLACK, WIN_STATE) || lineVer.recog(arr, BLACK, WIN_STATE))) return BLACK_FIVE;
	else if (who == BLACK && (lineUp.recog(arr, WHITE, WIN_STATE) || lineDown.recog(arr, WHITE, WIN_STATE) || lineHor.recog(arr, WHITE, WIN_STATE) || lineVer.recog(arr, WHITE, WIN_STATE))) return WHITE_FIVE;

	if (who == WHITE && (lineUp.recog(arr, BLACK, FOUR, costs) || lineDown.recog(arr, BLACK, FOUR, costs) || lineHor.recog(arr, BLACK, FOUR, costs) || lineVer.recog(arr, BLACK, FOUR, costs))) return BLACK_FOUR;
	else if (who == BLACK && (lineUp.recog(arr, WHITE, FOUR, costs) || lineDown.recog(arr, WHITE, FOUR, costs) || lineHor.recog(arr, WHITE, FOUR, costs) || lineVer.recog(arr, WHITE, FOUR, costs))) return WHITE_FOUR;

	if (who == WHITE && (lineUp.recog(arr, BLACK, THREE, costs) || lineDown.recog(arr, BLACK, THREE, costs) || lineHor.recog(arr, BLACK, THREE, costs) || lineVer.recog(arr, BLACK, THREE, costs))) return BLACK_THREE;
	else if (who == BLACK && (lineUp.recog(arr, WHITE, THREE, costs) || lineDown.recog(arr, WHITE, THREE, costs) || lineHor.recog(arr, WHITE, THREE, costs) || lineVer.recog(arr, WHITE, THREE, costs))) return WHITE_THREE;

}

void findIndex(char* position, int* indexX, int* indexY){

	int index = 0;
	index = index + (*position - 64) * 100;

	// 3-length input
	if (*(position + 2) >= 48 && *(position + 2) <= 57){
		index = index + (*(position + sizeof(char)) - 48) * 10 + (*(position + 2*sizeof(char)) - 48);
	}

	// 2-length input
	else{
		index = index + (*(position + 1) - 48);
	}

	*indexX = index / 100 - 1;
	*indexY = index % 100 - 1;
}

void display(){
	
	wcout << L"  ";
	for (int i = 0; i < BOARD_SIZE; i++){
		wcout << char('A' + i) << L" ";
	}
	wcout << endl;
	for (int i = BOARD_SIZE -1; i >= 0; i--){
		wcout.width(2);
		wcout << (i + 1);
		for (int j = 0 ; j < BOARD_SIZE; j++){
			if (arr[j][i] == BLACK) printBlack();
			else if (arr[j][i] == WHITE) printWhite();
			else{
				switch (i){
				case (BOARD_SIZE - 1) :
					if (j == 0) printLFTP();
					else if (j == BOARD_SIZE - 1) printRTTP();
					else printITTP();
					break;
				case 0:
					if (j == 0) printLFBT();
					else if (j == BOARD_SIZE - 1) printRTBT();
					else printITBT();
					break;
				default:
					if (j == 0) printLFMD();
					else if (j == BOARD_SIZE - 1) printRTMD();
					else printITMD();
					break;
				}
			}
		}
		wcout << (i + 1);
		wcout << endl;
	}
	wcout << L"  ";
	for (int i = 0; i < BOARD_SIZE; i++){
		wcout << char('A' + i) << L" ";
	}
	wcout << endl;
};

void findThreats(DOL who, int x, int y, vector<Position>* threats){
	Position temp;

	if (who == BLACK){
		if (x == -1){
			for (int i = 0; i < BOARD_SIZE; i++){
				for (int j = 0; j < BOARD_SIZE; j++){
					if (arr[i][j] == NONE){
						int pre_result = recog(i, j);
						arr[i][j] = BLACK;
						int recog_result = recog(i, j);
						if (recog_result >= 3 && (recog_result % 2) == 0 && pre_result != recog_result && recog_samsam(BLACK, i, j) < 2){
							temp.x = i;
							temp.y = j;
							temp.score = recog_result;
							(*threats).push_back(temp);
						}
						arr[i][j] = NONE;
					}
				}
			}
		}

		else{
			for (int i = 0; i < BOARD_SIZE; i++){
				for (int j = 0; j < BOARD_SIZE; j++){
					if (arr[i][j] == NONE){
						arr[i][j] = BLACK;
						if (recog(i, j) >= 3 && recog(x, y) == recog(i, j) && (recog(i, j) % 2) == 0){
							temp.x = i;
							temp.y = j;
							temp.score = recog(i, j);
							(*threats).push_back(temp);
						}
						arr[i][j] = NONE;
					}
				}
			}
		}
	}
	
	else if (who == WHITE){
		if (x == -1){
			for (int i = 0; i < BOARD_SIZE; i++){
				for (int j = 0; j < BOARD_SIZE; j++){
					if (arr[i][j] == NONE){
						int pre_result = recog(i, j);
						arr[i][j] = WHITE;
						int recog_result = recog(i, j);
						if (recog_result >= 3 && (recog_result % 2) == 1 && pre_result != recog_result && recog_samsam(WHITE, i, j) < 2){
							temp.x = i;
							temp.y = j;
							temp.score = recog_result;
							(*threats).push_back(temp);
						}
						arr[i][j] = NONE;
					}
				}
			}
		}

		else{
			for (int i = 0; i < BOARD_SIZE; i++){
				for (int j = 0; j < BOARD_SIZE; j++){
					if (arr[i][j] == NONE){
						arr[i][j] = WHITE;
						if (recog(i, j) >= 3 && recog(x, y) == recog(i, j) && (recog(i, j) % 2) == 1){
							temp.x = i;
							temp.y = j;
							temp.score = recog(i, j);
							(*threats).push_back(temp);
						}
						arr[i][j] = NONE;
					}
				}
			}
		}
	}
}

bool near_my_square(int x, int y, DOL who){

	bool result = false;
	for (int i = -1; i < 2; i++){
		for (int j = -1; j < 2; j++){
			if (i != 0 && j != 0){
				if (x + i >= 0 && x + i < BOARD_SIZE && y + j >= 0 && y + j < BOARD_SIZE && arr[x + i][y + j] == who) result = true;
			}
		}
	}

	return result;
}

void findOppoThreats(DOL who, vector<Position>* threats){
	Position temp;

	if (who == BLACK){
		for (int i = 0; i < BOARD_SIZE; i++){
			for (int j = 0; j < BOARD_SIZE; j++){
				if (arr[i][j] == NONE){
					int pre_result = recog(i, j);
					arr[i][j] = WHITE;
					int recog_result = recog(i, j);
					if (recog_result >= 3 && (recog_result % 2) == 1 && pre_result != recog_result){
						temp.x = i;
						temp.y = j;
						temp.score = recog_result;

						if (recog_result == WHITE_THREE){
							if (near_my_square(i, j, WHITE)){
								(*threats).push_back(temp);
							}
						}
						else (*threats).push_back(temp);
					}
					arr[i][j] = NONE;
				}
			}
		}
	}
	
	else if (who == WHITE){
		for (int i = 0; i < BOARD_SIZE; i++){
			for (int j = 0; j < BOARD_SIZE; j++){
				if (arr[i][j] == NONE){
					int pre_result = recog(i, j);
					arr[i][j] = BLACK;
					int recog_result = recog(i, j);
					if (recog_result >= 3 && (recog_result % 2) == 0 && pre_result != recog_result){
						temp.x = i;
						temp.y = j;
						temp.score = recog_result;
						if (recog_result == BLACK_THREE){
							if (near_my_square(i, j, BLACK)){
								(*threats).push_back(temp);
							}
						}
						else (*threats).push_back(temp);
					}
					arr[i][j] = NONE;
				}
			}
		}
	}
}

void findCost(DOL who, int x, int y, vector<Position>* costs){
	Position temp;

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (arr[i][j] == NONE){
				int pre_result = recog(x, y);
				arr[i][j] = who; //검은 돌을 한 수 추가해서 더 나은 threat이 생긴다면 그 부분이 costs
				if (recog(x, y) > pre_result){ 
					temp.x = i;
					temp.y = j;
					temp.score = recog(i, j);
					(*costs).push_back(temp);
				}
				arr[i][j] = NONE;
			}
		}
	}
}

int heuristicScore(DOL who, int x, int y){
	Line lineHor, lineVer, lineUp, lineDown;
	lineHor.setStartPosition(0, x);
	lineHor.setType(1);
	lineVer.setStartPosition(x, 0);
	lineVer.setType(2);

	if (x > y) lineUp.setStartPosition(x - y, 0);
	else lineUp.setStartPosition(0, y - x);
	lineUp.setType(3);

	if (x + y >= BOARD_SIZE) lineDown.setStartPosition(x + y - BOARD_SIZE + 1, BOARD_SIZE - 1);
	else lineDown.setStartPosition(0, x + y);
	lineDown.setType(4);

	arr[x][y] = who;
	int count = 0;
	if (lineHor.recog(arr, who, TWO)) count = count + 2;
	if (lineVer.recog(arr, who, TWO)) count = count + 2;
	if (lineUp.recog(arr, who, TWO)) count = count + 2;
	if (lineDown.recog(arr, who, TWO)) count = count + 2;

	for (int i = -1; i < 2; i++){
		for (int j = -1; j < 2; j++){
			if (x + i >= 0 && x + i < BOARD_SIZE && y + j >= 0 && y + j < BOARD_SIZE && arr[x + i][y + j] == who) count++;
		}
	}

	arr[x][y] = NONE;

	return count;
}

Position nextMove(DOL who, int depth, int x, int y){
	
	Position next;
	vector<Position> moves;
	vector<Position> temp;
	vector<Position> threats;
	vector<Position> costs;
	vector<Position> opposite_threats;
	DOL winning_state;
	DOL enemy;
	if (who == BLACK) { winning_state = BLACK_FIVE; enemy = WHITE; }
	else if (who == WHITE){ winning_state = WHITE_FIVE; enemy = BLACK; }
	/* 
	*	Module: Find threat squares
	*/
	findThreats(who, x, y, &threats);

	if (depth == 0){ //상대방이 나보다 먼저 이긴다면 막아야함
		findOppoThreats(who, &opposite_threats);
		if (opposite_threats.size() && threats.size()){
			int oppo_threats_max = -100;
			int ai_threats_max = -100;
			int index_oppo_max = -1;
			int index_ai_max = -1;
			for (int i = 0; i < opposite_threats.size(); i++){
				if (opposite_threats[i].score > oppo_threats_max){
					oppo_threats_max = opposite_threats[i].score;
					index_oppo_max = i;
				}
			}
			for (int i = 0; i < threats.size(); i++){
				if (threats[i].score > ai_threats_max){
					ai_threats_max = threats[i].score;
					index_ai_max = i;
				}
			}
			if (ai_threats_max < oppo_threats_max){
				next.x = opposite_threats[index_oppo_max].x;
				next.y = opposite_threats[index_oppo_max].y;
				return next;
			}
		}
		else if (opposite_threats.size() && !threats.size()){
			int oppo_threats_max = -100;
			int index_oppo_max = -1;
			for (int i = 0; i < opposite_threats.size(); i++){
				if (opposite_threats[i].score > oppo_threats_max){
					oppo_threats_max = opposite_threats[i].score;
					index_oppo_max = i;
				}
			}
			next.x = opposite_threats[index_oppo_max].x;
			next.y = opposite_threats[index_oppo_max].y;
			return next;
		}
	}

	for (int i = 0; i < threats.size(); i++){
		arr[threats[i].x][threats[i].y] = who;
		if (recog(threats[i].x, threats[i].y) == winning_state && depth > 0){
			arr[threats[i].x][threats[i].y] = NONE;
			next.x = x;
			next.y = y;
			next.score = 60;
			return next;
		}
		arr[threats[i].x][threats[i].y] = NONE;
	}
	
	if (depth > 0 && (threats.size() >= 2)){
		next.x = x;
		next.y = y;
		next.score = 50;
		return next;
	}
	
	if (depth > 0 && threats.size() == 0){
		next.x = x;
		next.y = y;
		next.score = -50;
		return next;
	}
	
	for (int i = 0; i < threats.size(); i++){
		arr[threats[i].x][threats[i].y] = who;

		if (recog(threats[i].x, threats[i].y) == winning_state){
			arr[threats[i].x][threats[i].y] = NONE;
			next.x = threats[i].x;
			next.y = threats[i].y;
			next.score = 50-depth;
			return next;
		}
		/*
		*	Module: findCost
		*/
		findCost(who, threats[i].x, threats[i].y, &costs);
		
		for (int j = 0; j < costs.size(); j++){

			arr[costs[j].x][costs[j].y] = enemy;
			next = nextMove(who, depth + 1, threats[i].x, threats[i].y);
			temp.push_back(next);

			arr[costs[j].x][costs[j].y] = NONE;
		}

		if (costs.size() == 0){
			int max = -100;
			for (int i = 0; i < BOARD_SIZE; i++){
				for (int j = 0; j < BOARD_SIZE; j++){
					if (arr[i][j] == NONE){//error 방지
						int heuristic_result = heuristicScore(who, i, j);
						if (heuristic_result > max){
							max = heuristic_result;
							next.x = i;
							next.y = j;
						}
					}
				}
			}
			next.score = -1;
			return next;
		}
		int index = -1;
		int min = 100;
		for (int k = 0; k < temp.size(); k++){
			if (temp[k].score < min){
				min = temp[k].score;
				index = k;
			}
		}
		arr[threats[i].x][threats[i].y] = NONE;
		moves.push_back(temp[index]);
	}

	if (depth == 0 && threats.size() == 0){
		int max = -100;
		for (int i = 0; i < BOARD_SIZE; i++){
			for (int j = 0; j < BOARD_SIZE; j++){
				if (arr[i][j] == NONE){
					int heuristic_result = heuristicScore(who, i, j) + heuristicScore(enemy, i, j);
					if (heuristic_result > max){
						max = heuristic_result;
						next.x = i;
						next.y = j;
					}
				}
			}
		}
		return next;
	}

	int index = -1;
	int max = -100;
	for (int i = 0; i < temp.size(); i++){
		if (temp[i].score > max){
			max = temp[i].score;
			index = i;
		}
	}
	next.x = temp[index].x;
	next.y = temp[index].y;
	next.score = temp[index].score;
	return next;
}
