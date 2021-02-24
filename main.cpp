#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime> //rand
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define WIDTH 14
#define HEIGHT 20

#define NUMBER_OF_BLOCKS 3

using namespace std;

const int block1[4][4][4]{
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 1,1,1,1 }
	},
	{
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 }
	},
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 1,1,1,1 }
	},
	{
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 }
	}
};
const int block2[4][4][4]{
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,1,1,0 },
		{ 0,1,1,0 }
	},
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,1,1,0 },
		{ 0,1,1,0 }
	},
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,1,1,0 },
		{ 0,1,1,0 }
	},
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,1,1,0 },
		{ 0,1,1,0 }
	}
};
const int block3[4][4][4]{
	{
		{ 0,0,0,0 },
		{ 0,1,1,0 },
		{ 0,0,1,0 },
		{ 0,0,1,0 }
	},
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,1,0 },
		{ 1,1,1,0 }
	},
	{
		{ 0,0,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,1,0 }
	},
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,1,1,1 },
		{ 0,1,0,0 }
	}
};

void gotoxy(int, int);
void CursorView(char);

class Block
{
protected:
	int x;
	int y;
	int rotate_idx;
	int shape[4][4][4];
public:
	const int getX()
	{
		return x;
	}
	const int getY()
	{
		return y;
	}
	const int getShape(int rotate_idx, int y, int x)
	{
		return shape[rotate_idx][y][x];
	}
	const int getRotateIdx()
	{
		return rotate_idx;
	}
	void initialize()
	{
		x = WIDTH / 2 - 2;
		y = -1;
		rotate_idx = 0;
	}
	void down()
	{
		y++;
	}
	void left()
	{
		x--;
	}
	void right()
	{
		x++;
	}
	void rotate()
	{
		rotate_idx = (rotate_idx + 1) % 4;
	}
};
class Block1 : public Block
{
public:
	Block1()
	{
		initialize(); //x,y에 처음 블럭위치 할당

					  //블럭 모양 복사
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					shape[i][j][k] = block1[i][j][k];
				}
			}
		}

	}
};
class Block2 : public Block
{
public:
	Block2()
	{
		initialize(); //x,y에 처음 블럭위치 할당

					  //블럭 모양 복사
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					shape[i][j][k] = block2[i][j][k];
				}
			}
		}

	}
};
class Block3 : public Block
{
public:
	Block3()
	{
		initialize(); //x,y에 처음 블럭위치 할당

					  //블럭 모양 복사
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					shape[i][j][k] = block3[i][j][k];
				}
			}
		}

	}
};

class Table
{
private:
	int table[HEIGHT + 2][WIDTH + 2]{ 0 };
	Block* blockPtr;

public:
	

	Table()
	{
		newBlock();
	}
	~Table()
	{
		delete blockPtr;
	}
	int GetTableValue(int i,int j)
	{
		return table[i][j];
	}
	void drawBackground()
	{
		//table에 테두리값 저장
		for (int j = 0; j < WIDTH + 2; j++)
		{
			table[0][j] = 2; // 왼쪽
			table[HEIGHT + 1][j] = 4; // 밑바닥
			table[2][j] = 5; //블럭이 선에 닿으면 게임 종료
		}
		for (int i = 1; i < HEIGHT + 1; i++)
		{
			table[i][0] = 2; // 위쪽
			table[i][WIDTH + 1] = 2; //오른쪽
		}
		
	}

	void printTable()
	{
		int temp = -1;
		gotoxy(0, 0);
		for (int i = 0; i < HEIGHT + 2; i++)
		{
			for (int j = 0; j < WIDTH + 2; j++)
			{
				temp = table[i][j];
				if (temp == 1)
				{
					cout << "■";
				}
				else if (temp == 3) //3: 쌓인 블럭
				{
					cout << "▦";
				}
				else if (temp == 2 || temp == 4) //2:좌우상 벽
				{
					cout << "□";
				}
				else if (temp == 5)
				{
					cout << "◎";
				}
				else if (temp == 0)
				{
					cout << "  ";
				}
			}
			cout << endl;
		}
	}

	void newBlock()
	{
		//blockPtr = nullptr;
		srand((unsigned int)time(0));
		switch (rand() % NUMBER_OF_BLOCKS)
		{
		case 0:
			blockPtr = new Block1;
			break;
		case 1:
			blockPtr = new Block2;
			break;
		case 2:
			blockPtr = new Block3;
			break;
		default:
			break;
		}
	}
	void stackBlock()
	{
		int xStart = blockPtr->getX();
		int yStart = blockPtr->getY();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (table[yStart + i][xStart + j] == 1 && (table[yStart + i + 1][xStart + j] == 3 || table[yStart + i + 1][xStart + j] == 4))
				{
					for (int i = yStart; i < yStart + 4; i++)
					{
						for (int j = xStart; j < xStart + 4; j++)
						{
							if (table[i][j] == 1)
								table[i][j] = 3;
						}
					}
					newBlock();
					return;
				}
			}
		}

	}
	void eraseBlock()
	{
		for (int i = HEIGHT; i > 2; i--)
		{
			int rowSum = 0;

			for (int j = 1; j < WIDTH + 1; j++)
			{
				rowSum += table[i][j];
			}

			if (rowSum == 3 * WIDTH)
			{
				for (int i_ = i; i_ > 3; i_--)
				{
					for (int j = 1; j < WIDTH + 1; j++)
					{
						table[i_][j] = table[i_ - 1][j];
					}
				}

				eraseBlock();
			}
			
		}
	}
	void initializeBlock()
	{
		int X = blockPtr->getX();
		int Y = blockPtr->getY();
		for (int i = Y; i < Y + 4; i++)
		{
			for (int j = X; j < X + 4; j++)
			{
				//초기화
				if (table[i][j] == 1)
					table[i][j] = 0;
			}
		}
	}
	void allocateBlock()
	{
		int xStart = blockPtr->getX();
		int yStart = blockPtr->getY();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (table[yStart + i][xStart + j] == 0)
				{
					table[yStart + i][xStart + j] = blockPtr->getShape(blockPtr->getRotateIdx(), i, j);
				}
			}
		}
	}
	void moveBlock(int key)
	{
		int X = blockPtr->getX();
		int Y = blockPtr->getY();

		bool isLeft = false;
		bool isRight = false;
		bool isStackBlockOnLeft = false;
		bool isStackBlockOnRight = false;
		bool isOverlap = false;

		//왼쪽 벽에 붙어있는지 검사
		for (int i = 1; i < HEIGHT + 1; i++)
		{
			if (table[i][1] == 1)
			{
				isLeft = true;
				break;
			}
		}
		//오른쪽 벽에 붙어있는지 검사
		for (int i = 1; i < HEIGHT + 1; i++)
		{
			if (table[i][WIDTH] == 1)
			{
				isRight = true;
				break;
			}
		}
		//왼쪽에 쌓인 블럭이 있는지 확인 
		if (X > 0)
		{
			for (int i = Y; i < Y + 4; i++)
			{
				for (int j = X; j < X + 4; j++)
				{
					if (table[i][j] == 1 && table[i][j - 1] == 3)
					{
						isStackBlockOnLeft = true;
					}
				}
			}
		}
		//오른쪽에 쌓인 블럭이 있는지 확인 
		if (X < WIDTH+ 1)
		{
			for (int i = Y; i < Y + 4; i++)
			{
				for (int j = X; j < X + 4; j++)
				{
					if (table[i][j] == 1 && table[i][j + 1]  == 3)
					{
						isStackBlockOnRight = true;
					}
				}
			}
		}

		initializeBlock();

		int nextRotateIdx = (blockPtr->getRotateIdx() + 1) % 4;
		//회전 했을 때 다른 블럭과 겹치는 지 확인
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (blockPtr->getShape(nextRotateIdx, i, j) == 1 && table[Y + i][X + j] != 0)
				{
					isOverlap = true;
				}

			}
		}

		switch (key)
		{
		case UP:
			
			if(isOverlap == false)
			{
				blockPtr->rotate();
			}
			break;
		case DOWN:
			blockPtr->down();
			break;
		case LEFT:			
			if (isLeft == false &&  isStackBlockOnLeft == false)
			{
				blockPtr->left();
			}
			break;
		case RIGHT:
			if (isRight == false && isStackBlockOnRight == false)
			{
				blockPtr->right();
			}
			break;
		default:
			break;
		}

		allocateBlock();

	}
	void InitializeTable()
	{
		for (int i = 0; i < HEIGHT + 2; i++)
		{
			for (int j = 0; j < WIDTH + 2; j++)
			{
				table[i][j] = 0;
			}
		}
	}

};

class Play
{
private:
	Table* tablePtr;
public:

	Play()
	{
		tablePtr = new Table;
		tablePtr->drawBackground();

		int loop_per_drop = 10;
		int drop_idx = 0;

		while (true)
		{
			clock_t start_ = clock();

			drop_idx = (drop_idx + 1) % loop_per_drop;
			if (drop_idx == 0)
			{
				tablePtr->moveBlock(DOWN); //블럭 내려오기    
			}

			tablePtr->stackBlock();
			tablePtr->eraseBlock();
			if (_kbhit())
			{
				int keyVal = _getch();
				if (keyVal == 224)
				{
					keyVal = _getch();
					switch (keyVal)
					{
					case UP:
						tablePtr->moveBlock(UP);
						break;
					case DOWN:
						tablePtr->moveBlock(DOWN);
						break;
					case LEFT:
						tablePtr->moveBlock(LEFT);
						break;
					case RIGHT:
						tablePtr->moveBlock(RIGHT);
						break;
					default:
						break;
					}
				}
			}

			tablePtr->printTable();

			if (IsGameEnd() == true)
			{
				break;
			}

			clock_t end_ = clock();
			cout << end_ - start_ << endl;
		}
		GameEnd();
	}
	bool IsGameEnd()
	{
		bool isGameEnd(false);
		int tblVal(-1);

		for (int j = 1; j < WIDTH + 1; j++)
		{
			tblVal = tablePtr->GetTableValue(3, j);
			if (tblVal == 3)
			{
				isGameEnd = true;
			}
		}

		return isGameEnd;
	}
	void GameEnd()
	{
		tablePtr->InitializeTable();
		tablePtr->drawBackground();
		tablePtr->printTable();

		HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hand, 12);

		gotoxy(10, 10);
		cout << "game end" << endl;
		
	}
	~Play()
	{
		delete tablePtr;
	}

};

int main()
{
	CursorView(0);

	Play newGame;

	return 0;
}

void gotoxy(int x, int y)
{
	COORD pos{ x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

//,main loop 수정
//게임 종료 내려오는 거 수정