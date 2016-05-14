#include <vector>
#define BOARD_SIZE 15
#define WIN_STATE 5
#define FIVE 5
#define FOUR 4
#define THREE 3
#define TWO 2
#define DEPTH_MAX 4

enum DOL { BLACK = -1, NONE, WHITE, DRAW, WHITE_THREE, BLACK_THREE,WHITE_FOUR, BLACK_FOUR,WHITE_FIVE, BLACK_FIVE };

struct Position{
	int x;
	int y;
	int score;
};

class Line{
private:
	int startX = 0;
	int startY = 0;
	int type = 0;
public:
	int getStartX(){
		return startX;
	}
	int getStartY(){
		return startY;
	}
	int getType(){
		return type;
	}

	void setStartPosition(int x, int y){
		startX = x;
		startY = y;
	}
	void setType(int t){
		type = t;
	}
	bool recog(DOL arr[BOARD_SIZE][BOARD_SIZE], DOL who, int num){
		int count = 0;
		int x = startX;
		int y = startY;
		int none_count = 0;

		if (num == TWO){
			switch (type){
			case 1:
				for (int i = 0; i < BOARD_SIZE - 3; i++, x++){
					if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == NONE){
						return true;
					}
				}
				return false;
			case 2:
				for (int i = 0; i < BOARD_SIZE - 3; i++, y++){
					if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == NONE){
						return true;
					}
				}
				return false;
			case 3:
				for (int i = 0; i < BOARD_SIZE - 3 && x + 3 < BOARD_SIZE && y+3 < BOARD_SIZE; i++, x++, y++){
					if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == NONE){
						return true;
					}
				}
				return false;
			case 4:
				for (int i = 0; i < BOARD_SIZE - 3 && x + 3 < BOARD_SIZE && y - 3 > -1; i++, x++, y--){
					if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == NONE){
						return true;
					}
				}
				return false;
			}
		}

		if (num == THREE){
			switch (type){
			case 1:
				for (int i = 0; i < BOARD_SIZE - 5; i++,x++){
					if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x+1][y] == who && arr[x+2][y] == who && arr[x+3][y] == NONE && arr[x+4][y] == who && arr[x+5][y] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == NONE && arr[x + 3][y] == who && arr[x + 4][y] == who && arr[x + 5][y] == NONE){
						return true;
					}
					
				}
				if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == NONE){
					return true;
				}
				break;
			case 2:
				for (int i = 0; i < BOARD_SIZE - 5; i++,y++){
					if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == NONE && arr[x][y + 4] == who && arr[x][y + 5] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == NONE && arr[x][y + 3] == who && arr[x][y + 4] == who && arr[x][y + 5] == NONE){
						return true;
					}
				}
				if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == NONE){
					return true;
				}
				break;
			case 3:
				for (int i = 0; i < BOARD_SIZE - 5 && x + 5 < BOARD_SIZE && y + 5 < BOARD_SIZE; i++,x++,y++){
					if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == NONE && arr[x + 4][y + 4] == who && arr[x + 5][y + 5] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == NONE && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who && arr[x + 5][y + 5] == NONE){
						return true;
					}
					
				}
				if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == NONE){
					return true;
				}
				break;
			case 4:
				for (int i = 0; i < BOARD_SIZE && x + 5 < BOARD_SIZE && y - 5 > -1; i++,x++,y--){
					if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == NONE && arr[x + 4][y - 4] == who && arr[x + 5][y - 5] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == NONE && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == who && arr[x + 5][y - 5] == NONE){
						return true;
					}
					
				}
				if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == NONE){
					return true;
				}
				break;
			}
			return false;
		}

		if (num == FOUR){
			switch (type){
			case 1:
				for (int i = 0; i < BOARD_SIZE - 5; i++, x++){
					if (arr[x][y] == NONE && arr[x+1][y] == who && arr[x+2][y] == who && arr[x+3][y] == who && arr[x+4][y] == who && arr[x+5][y] == NONE){
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4; i++, x++){
					if (arr[x][y] == who && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y] == NONE && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y] == who && arr[x + 2][y] == NONE && arr[x + 3][y] == who && arr[x + 4][y] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == NONE && arr[x + 4][y] == who){
						return true;
					}
				}
				return false;
			case 2:
				for (int i = 0; i < BOARD_SIZE - 5; i++, y++){
					if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == who && arr[x][y + 5] == NONE){
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4; i++, y++){
					if (arr[x][y] == who && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x][y + 1] == NONE && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x][y + 1] == who && arr[x][y + 2] == NONE && arr[x][y + 3] == who && arr[x][y + 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == NONE && arr[x][y + 4] == who){
						return true;
					}
				}
				return false;
			case 3:
				for (int i = 0; i < BOARD_SIZE - 5 && x + 5 < BOARD_SIZE && y + 5 < BOARD_SIZE; i++, x++, y++){
					if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who && arr[x + 5][y + 5] == NONE){
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4 && x + 4 < BOARD_SIZE && y + 4 < BOARD_SIZE; i++, x++, y++){
					if (arr[x][y] == who && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y + 1] == NONE && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == NONE && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == NONE && arr[x + 4][y + 4] == who){
						return true;
					}
				}
				return false;
			case 4:
				for (int i = 0; i < BOARD_SIZE - 5 && x + 5 < BOARD_SIZE && y - 5 > -1; i++, x++, y--){
					if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == who && arr[x + 5][y - 5] == NONE){
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4 && x + 4 < BOARD_SIZE && y - 4 > -1; i++, x++, y--){
					if (arr[x][y] == who && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == NONE){
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y - 1] == NONE && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == NONE && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == who){
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == NONE && arr[x + 4][y - 4] == who){
						return true;
					}
				}
				return false;
			}
		}

		if (num == WIN_STATE){
			switch (type){
			case 1:
				while (x < BOARD_SIZE){
					if (count == 0){
						if (arr[x][startY] == who){
							count++;
						}
					}
					else{
						if (arr[x][startY] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					x++;
					if (count == num) return true;
				}
				return false;
				break;
			case 2:
				while (y < BOARD_SIZE){
					if (count == 0){
						if (arr[startX][y] == who){
							count++;
						}
					}
					else{
						if (arr[startX][y] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					y++;
					if (count == num) {
						return true;
					}
				}
				return false;
				break;
			case 3:
				while (x < BOARD_SIZE && y < BOARD_SIZE){
					if (count == 0){
						if (arr[x][y] == who){
							count++;
						}
					}
					else{
						if (arr[x][y] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					x++;
					y++;
					if (count == num) return true;
				}
				return false;
				break;
			case 4:
				while (x < BOARD_SIZE && y >= 0){
					if (count == 0){
						if (arr[x][y] == who){
							count++;
						}
					}
					else{
						if (arr[x][y] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					x++;
					y--;
					if (count == num) return true;
				}
				return false;
				break;
			}
		}
	}

	bool recog(DOL arr[BOARD_SIZE][BOARD_SIZE], DOL who, int num, std::vector<Position>* costs){
		int count = 0;
		int x = startX;
		int y = startY;
		int none_count = 0;
		Position temp;

		if (num == THREE){
			switch (type){
			case 1:
				for (int i = 0; i < BOARD_SIZE - 5; i++, x++){
					if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 4;
						temp.y = y;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == NONE && arr[x + 4][y] == who && arr[x + 5][y] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 3;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == NONE && arr[x + 3][y] == who && arr[x + 4][y] == who && arr[x + 5][y] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 2;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y;
						(*costs).push_back(temp);
						return true;
					}
					
				}
				if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == NONE){
					temp.x = x;
					temp.y = y;
					(*costs).push_back(temp);

					temp.x = x + 4;
					temp.y = y;
					(*costs).push_back(temp);
					return true;
				}
				break;
			case 2:
				for (int i = 0; i < BOARD_SIZE - 5; i++, y++){
					if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x;
						temp.y = y + 4;
						(*costs).push_back(temp);

						return true;
					}
					else if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == NONE && arr[x][y + 4] == who && arr[x][y + 5] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x;
						temp.y = y+3;
						(*costs).push_back(temp);

						temp.x = x;
						temp.y = y+5;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == NONE && arr[x][y + 3] == who && arr[x][y + 4] == who && arr[x][y + 5] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x;
						temp.y = y + 2;
						(*costs).push_back(temp);

						temp.x = x;
						temp.y = y + 5;
						(*costs).push_back(temp);
						return true;
					}
					
				}
				if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == NONE){
					temp.x = x;
					temp.y = y;
					(*costs).push_back(temp);

					temp.x = x;
					temp.y = y + 4;
					(*costs).push_back(temp);
					return true;
				}
				break;
			case 3:
				for (int i = 0; i < BOARD_SIZE - 5 && x + 5 < BOARD_SIZE && y + 5 < BOARD_SIZE; i++, x++, y++){
					if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 4;
						temp.y = y + 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == NONE && arr[x + 4][y + 4] == who && arr[x + 5][y + 5] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 3;
						temp.y = y + 3;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y + 5;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == NONE && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who && arr[x + 5][y + 5] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 2;
						temp.y = y + 2;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y + 5;
						(*costs).push_back(temp);
						return true;
					}
					
				}
				if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == NONE){
					temp.x = x;
					temp.y = y;
					(*costs).push_back(temp);

					temp.x = x + 4;
					temp.y = y + 4;
					(*costs).push_back(temp);
					return true;
				}
				break;
			case 4:
				for (int i = 0; i < BOARD_SIZE && x + 5 < BOARD_SIZE && y - 5 > -1; i++, x++, y--){
					if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 4;
						temp.y = y - 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == NONE && arr[x + 4][y - 4] == who && arr[x + 5][y - 5] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 3;
						temp.y = y - 3;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y - 5;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == NONE && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == who && arr[x + 5][y - 5] == NONE){
						temp.x = x;
						temp.y = y;
						(*costs).push_back(temp);

						temp.x = x + 2;
						temp.y = y - 2;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y - 5;
						(*costs).push_back(temp);
						return true;
					}
					
				}
				if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == NONE){
					temp.x = x;
					temp.y = y;
					(*costs).push_back(temp);

					temp.x = x + 4;
					temp.y = y - 4;
					(*costs).push_back(temp);
					return true;
				}
				break;
			}
			return false;
		}

		if (num == FOUR){
			switch (type){
			case 1:
				for (int i = 0; i < BOARD_SIZE - 5; i++, x++){
					if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == who && arr[x + 5][y] == NONE){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4; i++, x++){
					if (arr[x][y] == who && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == NONE){
						temp.x = x + 4;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == who){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y] == NONE && arr[x + 2][y] == who && arr[x + 3][y] == who && arr[x + 4][y] == who){
						temp.x = x + 1;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y] == who && arr[x + 2][y] == NONE && arr[x + 3][y] == who && arr[x + 4][y] == who){
						temp.x = x + 2;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y] == who && arr[x + 2][y] == who && arr[x + 3][y] == NONE && arr[x + 4][y] == who){
						temp.x = x + 3;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				return false;
			case 2:
				for (int i = 0; i < BOARD_SIZE - 5; i++, y++){
					if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == who && arr[x][y + 5] == NONE){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);

						temp.x = x;
						temp.y = y + 5;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4; i++, y++){
					if (arr[x][y] == who && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == NONE){
						temp.x = x;
						temp.y = y+4;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == who){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x][y + 1] == NONE && arr[x][y + 2] == who && arr[x][y + 3] == who && arr[x][y + 4] == who){
						temp.x = x;
						temp.y = y + 1;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x][y + 1] == who && arr[x][y + 2] == NONE && arr[x][y + 3] == who && arr[x][y + 4] == who){
						temp.x = x;
						temp.y = y + 2;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x][y + 1] == who && arr[x][y + 2] == who && arr[x][y + 3] == NONE && arr[x][y + 4] == who){
						temp.x = x;
						temp.y = y + 3;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				return false;
			case 3:
				for (int i = 0; i < BOARD_SIZE - 5 && x + 5 < BOARD_SIZE && y + 5 < BOARD_SIZE; i++, x++, y++){
					if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who && arr[x + 5][y + 5] == NONE){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y + 5;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4 && x + 4 < BOARD_SIZE && y + 4 < BOARD_SIZE; i++, x++, y++){
					if (arr[x][y] == who && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == NONE){
						temp.x = x + 4;
						temp.y = y + 4;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y + 1] == NONE && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who){
						temp.x = x + 1;
						temp.y = y + 1;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == NONE && arr[x + 3][y + 3] == who && arr[x + 4][y + 4] == who){
						temp.x = x + 2;
						temp.y = y + 2;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y + 1] == who && arr[x + 2][y + 2] == who && arr[x + 3][y + 3] == NONE && arr[x + 4][y + 4] == who){
						temp.x = x + 3;
						temp.y = y + 3;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				return false;
			case 4:
				for (int i = 0; i < BOARD_SIZE - 5 && x + 5 < BOARD_SIZE && y - 5 > -1; i++, x++, y--){
					if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 3] == who && arr[x + 4][y - 4] == who && arr[x + 5][y - 5] == NONE){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);

						temp.x = x + 5;
						temp.y = y - 5;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				for (int i = 0; i < BOARD_SIZE - 4 && x + 4 < BOARD_SIZE && y - 4 > -1; i++, x++, y--){
					if (arr[x][y] == who && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 4] == who && arr[x + 4][y - 4] == NONE){
						temp.x = x + 4;
						temp.y = y - 4;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == NONE && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 4] == who && arr[x + 4][y - 4] == who){
						temp.x = x;
						temp.y = y;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y - 1] == NONE && arr[x + 2][y - 2] == who && arr[x + 3][y - 4] == who && arr[x + 4][y - 4] == who){
						temp.x = x + 1;
						temp.y = y - 1;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == NONE && arr[x + 3][y - 4] == who && arr[x + 4][y - 4] == who){
						temp.x = x + 2;
						temp.y = y - 2;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
					else if (arr[x][y] == who && arr[x + 1][y - 1] == who && arr[x + 2][y - 2] == who && arr[x + 3][y - 4] == NONE && arr[x + 4][y - 4] == who){
						temp.x = x + 3;
						temp.y = y - 3;
						temp.score = 4;
						(*costs).push_back(temp);
						return true;
					}
				}
				return false;
			}
		}

		if (num == WIN_STATE){
			switch (type){
			case 1:
				while (x < BOARD_SIZE){
					if (count == 0){
						if (arr[x][startY] == who){
							count++;
						}
					}
					else{
						if (arr[x][startY] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					x++;
					if (count == num) return true;
				}
				return false;
				break;
			case 2:
				while (y < BOARD_SIZE){
					if (count == 0){
						if (arr[startX][y] == who){
							count++;
						}
					}
					else{
						if (arr[startX][y] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					y++;
					if (count == num) {
						return true;
					}
				}
				return false;
				break;
			case 3:
				while (x < BOARD_SIZE && y < BOARD_SIZE){
					if (count == 0){
						if (arr[x][y] == who){
							count++;
						}
					}
					else{
						if (arr[x][y] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					x++;
					y++;
					if (count == num) return true;
				}
				return false;
				break;
			case 4:
				while (x < BOARD_SIZE && y >= 0){
					if (count == 0){
						if (arr[x][y] == who){
							count++;
						}
					}
					else{
						if (arr[x][y] == who){
							count++;
						}
						else{
							count = 0;
						}
					}
					x++;
					y--;
					if (count == num) return true;
				}
				return false;
				break;
			}
		}
	}
};