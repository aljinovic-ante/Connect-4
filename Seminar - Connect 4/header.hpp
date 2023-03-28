#include <iostream>
using namespace std;

class Board
{
	int height, length;
	char** map;
public:
	Board();
	void print();
	void clear();
	bool put_char(int column,char player);
	bool check(char player);
	bool is_draw();
	int check_PC(char player);
	int check_columns_free();
};

template <typename T>
class exc
{
public:
	T err;
	exc(T s) : err(s) {}
};

