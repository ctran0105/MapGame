#include<windows.h>
#include<iostream>
#include<chrono>
#include<thread>
#include<string>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;

enum Move { LEFT, RIGHT, UP, DOWN, NONE, QUIT };

const int Rows = 20;
const int Cols = 40;

struct Location {
	int x;
	int y;
};

struct Player {
	Location location;
	char symbol = '+';
	Move move = NONE;
	Location lastLocation;
	char last_map_symbol;
};

struct Deer {
	Location location;
	const int numDeer = 12;
	char symbol = '$';
	Move move = NONE;
	Location lastLocation;
	char last_map_symbol;
};

void setCursor(Location loc);
void hideCursor();
bool keyPressed(int key);
void sleep(int ms);
bool isPressed(int key);
Move getMove();
void readMap(char map[][Cols], const string& filename);
void printMap(const char map[][Cols]);
bool isWall(const Location& loc, const char map[][Cols]);
void processMove(Player& p, const char map[][Cols]);

int main()
{
	// game data
	char map[Rows][Cols];
	Player p;

	// hide the cursor
	hideCursor();

	// initialize player location
	p.location = { 4, 4 };

	// load and display map 1
	readMap(map, "map1.txt");
	printMap(map);

	// print player initial position
	setCursor(p.location);
	cout << p.symbol;

	// game loop
	bool gameOver = false;
	while (!gameOver)
	{
		// timing
		sleep(50);

		// get the move
		p.move = getMove();

		// process move
		processMove(p, map);

		// display player
		if (p.move != NONE)
		{
			setCursor(p.lastLocation);
			cout << p.last_map_symbol;
			setCursor(p.location);
			cout << p.symbol;
		}

		// quit?
		if (p.move == QUIT)
		{
			gameOver = true;
		}
	}
}

void setCursor(Location loc)
{
	COORD c;
	c.X = loc.x;
	c.Y = loc.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void hideCursor()
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;

	SetConsoleCursorInfo(hOut, &ConCurInf);
}

bool keyPressed(int key)
{
	return GetAsyncKeyState(key) < 0;
}

void sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool isPressed(int key)
{
	return GetAsyncKeyState(key) < 0;
}

Move getMove()
{
	Move m = NONE;
	if (isPressed(VK_LEFT)) m = LEFT;
	if (isPressed(VK_RIGHT)) m = RIGHT;
	if (isPressed(VK_UP)) m = UP;
	if (isPressed(VK_DOWN)) m = DOWN;
	if (isPressed('Q')) m = QUIT;

	return m;
}

void readMap(char map[][Cols], const string& filename)
{
	ifstream inFile;
	inFile.open(filename);

	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			map[i][j] = inFile.get();
		}
		inFile.get();
	}

	inFile.close();
}

void printMap(const char map[][Cols])
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

bool isWall(const Location& loc, const char map[][Cols])
{
	if (map[loc.y][loc.x] == '*')
		return true;
	else
		return false;
}

void processMove(Player& p, const char map[][Cols])
{
	p.lastLocation = p.location;
	p.last_map_symbol = map[p.lastLocation.y][p.lastLocation.x];

	if (p.move == RIGHT)
	{
		if (p.location.x < Cols && !isWall({ p.location.x + 1, p.location.y }, map))
			p.location.x = p.location.x + 1;
	}

	if (p.move == LEFT)
	{
		if (p.location.x > 0 && !isWall({ p.location.x - 1, p.location.y }, map))
			p.location.x--;
	}

	if (p.move == UP)
	{
		if (p.location.y > 0 && !isWall({ p.location.x, p.location.y - 1 }, map))
			p.location.y--;
	}

	if (p.move == DOWN)
	{
		if (p.location.y < Rows && !isWall({ p.location.x, p.location.y + 1 }, map))
			p.location.y++;
	}

}