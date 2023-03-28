#include <iostream>
#include "header.hpp"
using namespace std;

Board::Board()
{
	height = 7;
	length = 9;
	map = new char* [height];
	for (int i = 0; i < height; i++)
		map[i] = new char[length];

	for(int i=0;i<height;i++)
		for (int j = 0; j < length; j++)
		{
			if (i==(height - 1))
				map[i][j] = '-';
			else if (j == 0 || j == (length - 1))
				map[i][j] = '|';
			else
				map[i][j] = ' ';
		}
}

void Board::print()
{
	cout << " 1234567" << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	cout << " 1234567" << endl;
	cout << endl;


}

void Board::clear()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (map[i][j] == 'X' || map[i][j] == 'O' || map[i][j] == 'W')
				map[i][j] = ' ';
		}
	}
}

bool Board::put_char(int column, char player)
{

	//put char on the lowest possible place
	for(int i=height-1;i>=0;i--)
		if (map[i][column] == ' ')
		{
			map[i][column] = player;
			return true;
		}

	return false;
}

bool Board::check(char player)
{
	//check horizontal
	for (int i = 0; i < height-1; i++)
		for (int j = 1; j < length - 4; j++)
			if (map[i][j] == player && map[i][j + 1] == player && map[i][j + 2] == player && map[i][j + 3] == player)
			{
				map[i][j] = map[i][j + 1] = map[i][j + 2] = map[i][j + 3] = 'W';
				return true;
			}

	//check vertical
	for(int i=0;i<height-4;i++)
		for (int j = 1; j < length - 1; j++)
			if (map[i][j] == player && map[i + 1][j] == player && map[i + 2][j] == player && map[i + 3][j] == player)
			{
				map[i][j] = map[i+1][j] = map[i+2][j] = map[i+3][j] = 'W';
				return true;
			}
			
	//check diagonal left->right
	for (int i = 0; i < height - 4; i++)
		for (int j = 1; j < length - 4; j++)
			if (map[i][j] == player && map[i+1][j+1] == player && map[i+2][j+2] == player && map[i+3][j+3] == player)
			{
				map[i][j] = map[i + 1][j + 1] = map[i + 2][j + 2] = map[i + 3][j + 3] = 'W';
				return true;
			}

	//check diagonal right->left
	for (int i = 0; i < height - 4; i++)
		for (int j = length-2; j >3; j--)
			if (map[i][j] == player && map[i + 1][j - 1] == player && map[i + 2][j - 2] == player && map[i + 3][j - 3] == player)
			{
				map[i][j] = map[i + 1][j - 1] = map[i + 2][j - 2] = map[i + 3][j - 3]= 'W';
				return true;
			}
	return false;

}

bool Board::is_draw()
{
	for (int i = 0; i < height - 1; i++)
		for (int j = 1; j < length - 1; j++)
			if (map[i][j] == ' ')
				return false;
	return true;
}

int Board::check_columns_free()
{
	int brojac = 0;
	for (int j = 1; j <= 7; j++)
		if (map[0][j]==' ')
			brojac++;

	//cout << "Slobodno je: " << brojac << " stupaca" << endl;
	return brojac;
}


int Board::check_PC(char player)
{
	//horizonal xxx_
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i][j + 1] == player && map[i][j + 2] == player && map[i][j + 3] == ' ' && map[i + 1][j + 3] != ' ')
			{
				// cout << endl << "//horizonal xxx_" << endl;
				return j + 3;
			}
	
	//horizonal _xxx
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i][j + 1] == player && map[i][j + 2] == player && map[i][j + 3] == player && map[i + 1][j] != ' ')
			{
				// cout << endl << "//horizonal _xxx" << endl;
				return j;
			}

	//horizonal xx_x
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i][j + 1] == player && map[i][j + 2] == ' ' && map[i][j + 3] == player && map[i + 1][j + 2] != ' ')
			{
				// cout << endl << "//horizonal xx_x" << endl;
				return j + 2;
			}

	//horizonal x_xx
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i][j + 1] == ' ' && map[i][j + 2] == player && map[i][j + 3] == player && map[i + 1][j + 1] != ' ')
			{
				// cout << endl << "//horizonal x_xx" << endl;
				return j + 1;
			}

	//vertical
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 8; j++)
			if (map[i][j] == player && map[i-1][j] == player && map[i-2][j] == player && map[i-3][j] == ' ')
			{
				// cout << endl << "//vertical" << endl;
				return j;
			}

	//diagonal xxx_ l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i - 1][j+1] == player && map[i - 2][j+2] == player && map[i - 3][j+3] == ' ' && map[i - 2][j + 3] != ' ')
			{
				// cout << endl << "//diagonal xxx_ l->r" << endl;
				return j + 3;
			}

	//diagonal _xxx l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i - 1][j + 1] == player && map[i - 2][j + 2] == player && map[i - 3][j + 3] == player && map[i +1][j] != ' ')
			{
				// cout << endl << "//diagonal _xxx l->r" << endl;
				return j;
			}

	//diagonal xxx_ r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length-2; j > 3; j--)
			if (map[i-3][j-3] == player && map[i - 2][j -2] == player && map[i - 1][j -1] == player && map[i][j] == ' ' && map[i + 1][j] != ' ')
			{
				// cout << endl << "//diagonal xxx_ r->l" << endl;
				return j;
			}

	//diagonal _xxx r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i][j] == player && map[i - 1][j -1] == player && map[i - 2][j - 2] == player && map[i - 3][j - 3] == ' ' && map[i - 2][j - 3] != ' ')
			{
				// cout << endl << "//diagonal _xxx r->l" << endl;
				return j -3;
			}

	//diagonal xx_x l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i - 1][j + 1] == player && map[i - 2][j + 2] == ' ' && map[i - 3][j + 3] == player && map[i - 1][j + 2] != ' ')
			{
				// cout << endl << "//diagonal xx_x l->r" << endl;
				return j + 2;
			}

	//diagonal x_xx l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i - 1][j + 1] == ' ' && map[i - 2][j + 2] == player && map[i - 3][j + 3] == player && map[i][j+1] != ' ')
			{
				// cout << endl << "//diagonal x_xx l->r" << endl;
				return j + 1;
			}

	//diagonal x_xx r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i - 3][j - 3] == player && map[i - 2][j - 2] == ' ' && map[i - 1][j - 1] == player && map[i][j] == player && map[i - 1][j-2] != ' ')
			{
				// cout << endl << "//diagonal x_xx r->l" << endl;
				return j - 2;
			}

	//diagonal xx_x r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i][j] == player && map[i - 1][j - 1] == ' ' && map[i - 2][j - 2] == player && map[i - 3][j - 3] == player && map[i][j - 1] != ' ')
			{
				// cout << endl << "//diagonal xx_x r->l" << endl;
				return j - 1;
			}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

	char rival = 'X';

	//horizonal xxx_
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i][j + 1] == rival && map[i][j + 2] == rival && map[i][j + 3] == ' ' && map[i + 1][j + 3] != ' ')
			{
				// cout << endl << "//horizonal xxx_" << endl;
				return j + 3;
			}

	//horizonal _xxx
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i][j + 1] == rival && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i + 1][j] != ' ')
			{
				// cout << endl << "//horizonal _xxx" << endl;
				return j;
			}

	//horizonal xx_x
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i][j + 1] == rival && map[i][j + 2] == ' ' && map[i][j + 3] == rival && map[i + 1][j + 2] != ' ')
			{
				// cout << endl << "//horizonal xx_x" << endl;
				return j + 2;
			}

	//horizonal x_xx
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i][j + 1] == ' ' && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i + 1][j + 1] != ' ')
			{
				// cout << endl << "//horizonal x_xx" << endl;
				return j + 1;
			}

	//vertical
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 8; j++)
			if (map[i][j] == rival && map[i - 1][j] == rival && map[i - 2][j] == rival && map[i - 3][j] == ' ')
			{
				// cout << endl << "//vertical" << endl;
				return j;
			}

	//diagonal xxx_ l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == ' ' && map[i - 2][j + 3] != ' ')
			{
				// cout << endl << "//diagonal xxx_ l->r" << endl;
				return j + 3;
			}

	//diagonal _xxx l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i + 1][j] != ' ')
			{
				// cout << endl << "//diagonal _xxx l->r" << endl;
				return j;
			}

	//diagonal xxx_ r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i - 3][j - 3] == rival && map[i - 2][j - 2] == rival && map[i - 1][j - 1] == rival && map[i][j] == ' ' && map[i + 1][j] != ' ')
			{
				// cout << endl << "//diagonal xxx_ r->l" << endl;
				return j;
			}

	//diagonal _xxx r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i][j] == rival && map[i - 1][j - 1] == rival && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == ' ' && map[i - 2][j - 3] != ' ')
			{
				// cout << endl << "//diagonal _xxx r->l" << endl;
				return j - 3;
			}

	//diagonal xx_x l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == ' ' && map[i - 3][j + 3] == rival && map[i - 1][j + 2] != ' ')
			{
				// cout << endl << "//diagonal xx_x l->r" << endl;
				return j + 2;
			}

	//diagonal x_xx l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i - 1][j + 1] == ' ' && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i][j + 1] != ' ')
			{
				// cout << endl << "//diagonal x_xx l->r" << endl;
				return j + 1;
			}

	//diagonal x_xx r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i - 3][j - 3] == rival && map[i - 2][j - 2] == ' ' && map[i - 1][j - 1] == rival && map[i][j] == rival && map[i - 1][j - 2] != ' ')
			{
				// cout << endl << "//diagonal x_xx r->l" << endl;
				return j - 2;
			}

	//diagonal xx_x r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i][j] == rival && map[i - 1][j - 1] == ' ' && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == rival && map[i][j - 1] != ' ')
			{
				// cout << endl << "//diagonal xx_x r->l" << endl;
				return j - 1;
			}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

	//horizontal _xx__
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i][j + 1] == player && map[i][j + 2] == player && map[i][j + 3] == ' ' && map[i][j + 4] == ' ' && map[i + 1][j + 4] != ' ' && map[i + 1][j + 3] != ' ' && map[i + 1][j] != ' ')
			{
				// cout << endl << "//horizontal _xx__" << endl;
				return j + 3;
			}

	//horizontal __xx_
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i+1][j] != ' ' && map[i][j + 1] == ' ' && map[i+1][j + 1] != ' ' && map[i][j + 2] == player && map[i][j + 3] == player && map[i][j + 4] == ' ' && map[i + 1][j + 4] != ' ')
			{
				// cout << endl << "//horizontal __xx_" << endl;
				return j + 1;
			}

	//horizontal _xx__
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i][j + 1] == rival && map[i][j + 2] == rival && map[i][j + 3] == ' ' && map[i][j + 4] == ' ' && map[i+1][j + 4] != ' ' && map[i + 1][j + 3] != ' ' && map[i+1][j] != ' ')
			{
				// cout << endl << "//horizontal _xx__" << endl;
				return j + 3;
			}

	//horizontal __xx_
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i][j + 1] == ' ' && map[i + 1][j + 1] != ' ' && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i][j + 4] == ' ' && map[i + 1][j + 4] != ' ')
			{
				// cout << endl << "//horizontal __xx_" << endl;
				return j + 1;
			}

	//diagonal __xx_ l->r
	for (int i = height - 2; i >= 4; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j]==' ' && map[i+1][j] != ' ' && map[i-1][j+1] == ' ' && map[i][j+1] != ' ' && map[i - 2][j + 2] == player && map[i-3][j + 3] == player && map[i - 4][j + 4] == ' ' && map[i - 3][j +4] != ' ')
			{
				// cout << endl << "//diagonal __xx_ l->r" << endl;
				return j + 1;
			}

	//diagonal _xx__ l->r
	for (int i = height - 2; i >= 4; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j + 1] == player && map[i - 2][j + 2] == player && map[i - 3][j + 3] == ' ' && map[i - 2][j + 3] != ' ' && map[i - 4][j + 4] == ' ' && map[i - 3][j + 4] != ' ')
			{
				// cout << endl << "//diagonal _xx__ l->r" << endl;
				return j + 3;
			}

	//diagonal __xx_ r->l
	for (int i = height - 2; i >= 4; i--)
		for (int j = length-2; j > 4; j--)
			if (map[i][j] == ' ' && map[i+1][j] != ' ' && map[i - 1][j - 1] == ' ' && map[i-1][j - 1] != ' ' && map[i - 2][j - 2] == player && map[i - 3][j - 3] == player && map[i - 4][j - 4] == ' ' && map[i - 3][j - 4] != ' ')
			{
				// cout << endl << "//diagonal __xx_ r->l" << endl;
				return j - 1;
			}

	//diagonal _xx__ r->l
	for (int i = height - 2; i >= 4; i--)
		for (int j = length - 2; j > 4; j--)
			if (map[i][j]==' ' && map[i+1][j] != ' ' && map[i-1][j-1] == player && map[i-2][j-2] == player && map[i-3][j-3] == ' ' && map[i-2][j-3] != ' ' && map[i-4][j-4] == ' ' && map[i-3][j-4] != ' ')
			{
				// cout << endl << "//diagonal _xx__ r->l" << endl;
				return j - 3;
			}

	//diagonal __xx_ l->r
	for (int i = height - 2; i >= 4; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j + 1] == ' ' && map[i][j + 1] != ' ' && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i - 4][j + 4] == ' ' && map[i - 3][j + 4] != ' ')
			{
				// cout << endl << "//diagonal __xx_ l->r" << endl;
				return j + 1;
			}

	//diagonal _xx__ l->r
	for (int i = height - 2; i >= 4; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == ' ' && map[i - 2][j + 3] != ' ' && map[i - 4][j + 4] == ' ' && map[i - 3][j + 4] != ' ')
			{
				// cout << endl << "//diagonal _xx__ l->r" << endl;
				return j + 3;
			}

	//diagonal __xx_ r->l
	for (int i = height - 2; i >= 4; i--)
		for (int j = length - 2; j > 4; j--)
			if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j - 1] == ' ' && map[i - 1][j - 1] != ' ' && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == rival && map[i - 4][j - 4] == ' ' && map[i - 3][j - 4] != ' ')
			{
				// cout << endl << "//diagonal __xx_ r->l" << endl;
				return j - 1;
			}

	//diagonal _xx__ r->l
	for (int i = height - 2; i >= 4; i--)
		for (int j = length - 2; j > 4; j--)
			if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j - 1] == rival && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == ' ' && map[i - 2][j - 3] != ' ' && map[i - 4][j - 4] == ' ' && map[i - 3][j - 4] != ' ')
			{
				// cout << endl << "//diagonal _xx__ r->l" << endl;
				return j - 3;
			}

	//horizontal _x_x_
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j]==' ' && map[i+1][j] != ' ' && map[i][j+1] == player && map[i][j+2] == ' ' && map[i+1][j+2] != ' ' && map[i][j+3] == player && map[i][j+4] == ' ' && map[i+1][j+4] != ' ')
			{
				// cout << endl << "//horizontal _x_x_" << endl;
				return j + 2;
			}

	//horizontal _x_x_
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 4; j++)
			if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i][j + 1] == rival && map[i][j + 2] == ' ' && map[i + 1][j + 2] != ' ' && map[i][j + 3] == rival && map[i][j + 4] == ' ' && map[i + 1][j + 4] != ' ')
			{
				// cout << endl << "//horizontal _x_x_" << endl;
				return j + 2;
			}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////

	if (check_columns_free()>1)
	{

		int dont=-1;

		//horizontal _xxx_
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 4; j++)
				if (map[i][j] == ' ' && map[i + 1][j] == ' ' && map[i + 2][j] != ' ' && map[i][j + 1] == rival && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i][j + 4] == ' ' && map[i + 1][j + 4] == ' ' && map[i + 2][j + 4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j || dont == j + 4);
					// cout << endl << "dont horizontal _xxx_" << endl;
					return dont;
				}

		//diagonal _xxx_ l->r
		for (int i = height - 3; i >= 4; i--)
			for (int j = 1; j < 4; j++)
				if (map[i][j] == ' ' && map[i + 1][j] == ' ' && map[i + 2][j] != ' ' && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i - 4][j + 4] == ' ' && map[i - 3][j + 4] == ' ' && map[i - 2][j+4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j || dont == j + 4);
					// cout << endl << "dont diagonal _xxx_ l->r" << endl;
					return dont;
				}

		//diagonal _xxx_ r->l
		for (int i = height - 3; i >= 4; i--)
			for (int j = length - 2; j > 4; j--)
				if (map[i][j] == ' ' && map[i + 1][j] == ' ' && map[i + 2][j] != ' ' && map[i - 1][j - 1] == rival && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == rival && map[i - 4][j - 4] == ' ' && map[i - 3][j - 4] == ' ' && map[i - 2][j-4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j || dont == j - 4);
					// cout << endl << "dont diagonal _xxx_ r->l" << endl;
					return dont;
				}

		//horizonal xxx_
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == rival && map[i][j + 1] == rival && map[i][j + 2] == rival && map[i][j + 3] == ' ' && map[i + 1][j + 3] == ' ' && map[i + 2][j + 3] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 3);
					// cout << endl << "dont horizonal xxx_" << endl;
					return dont;
				}

		//horizonal _xxx
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == ' ' && map[i][j + 1] == rival && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i + 1][j] == ' ' && map[i + 2][j] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j );
					// cout << endl << "dont horizonal _xxx" << endl;
					return dont;
				}

		//horizonal xx_x
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == rival && map[i][j + 1] == rival && map[i][j + 2] == ' ' && map[i+2][j + 2] != ' ' && map[i + 1][j + 2] == ' ' && map[i][j + 3] == rival)
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 2);
					// cout << endl << "dont horizonal xx_x" << endl;
					return dont;
				}

		//horizonal x_xx
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == rival && map[i][j + 1] == ' ' && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i + 1][j + 1] == ' ' && map[i + 2][j + 1] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 1);
					// cout << endl << "dont horizonal x_xx" << endl;
					return dont;
				}

		//diagonal xxx_ l->r
		for (int i = height - 3; i >= 3; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == rival && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == ' ' && map[i - 2][j + 3] == ' ' && map[i - 1][j + 3] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 3);
					// cout << endl << "dont diagonal xxx_ l->r" << endl;
					return dont;
				}

		//diagonal _xxx l->r
		for (int i = height - 3; i >= 3; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == ' ' && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i + 1][j] == ' ' && map[i + 2][j] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j);
					// cout << endl << "dont diagonal _xxx l->r" << endl;
					return dont;
				}

		//diagonal xxx_ r->l
		for (int i = height - 3; i >= 3; i--)
			for (int j = length - 2; j > 3; j--)
				if (map[i - 3][j - 3] == rival && map[i - 2][j - 2] == rival && map[i - 1][j - 1] == rival && map[i][j] == ' ' && map[i + 1][j] == ' ' && map[i + 2][j] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j);
					// cout << endl << "dont diagonal xxx_ r->l" << endl;
					return dont;
				}

		//diagonal _xxx r->l
		for (int i = height - 3; i >= 3; i--)
			for (int j = length - 2; j > 3; j--)
				if (map[i][j] == rival && map[i - 1][j - 1] == rival && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == ' ' && map[i - 2][j - 3] == ' ' && map[i - 1][j - 3] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j - 3);
					// cout << endl << "dont diagonal _xxx r->l" << endl;
					return dont;
				}

		//diagonal xx_x l->r
		for (int i = height - 3; i >= 3; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == rival && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == ' ' && map[i - 3][j + 3] == rival && map[i - 1][j + 2] == ' ' && map[i][j + 2] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 2);
					// cout << endl << "dont diagonal xx_x l->r" << endl;
					return dont;
				}

		//diagonal x_xx l->r
		for (int i = height - 3; i >= 3; i--)
			for (int j = 1; j < 5; j++)
				if (map[i][j] == rival && map[i - 1][j + 1] == ' ' && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i][j + 1] == ' ' && map[i+1][j + 1] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 1);
					// cout << endl << "dont diagonal x_xx l->r" << endl;
					return dont;
				}

		//diagonal x_xx r->l
		for (int i = height - 3; i >= 3; i--)
			for (int j = length - 2; j > 3; j--)
				if (map[i - 3][j - 3] == rival && map[i - 2][j - 2] == ' ' && map[i - 1][j - 1] == rival && map[i][j] == rival && map[i - 1][j - 2] == ' ' && map[i][j - 2] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j - 2);
					// cout << endl << "dont diagonal x_xx r->l" << endl;
					return dont;
				}

		//diagonal xx_x r->l
		for (int i = height - 3; i >= 3; i--)
			for (int j = length - 2; j > 3; j--)
				if (map[i][j] == rival && map[i - 1][j - 1] == ' ' && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == rival && map[i][j - 1] == ' ' && map[i+1][j - 1] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j - 1);
					// cout << endl << "dont diagonal xx_x r->l" << endl;
					return dont;
				}

		//horizontal _xx__
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 4; j++)
				if (map[i][j] == ' ' && map[i][j + 1] == rival && map[i][j + 2] == rival && map[i][j + 3] == ' ' && map[i][j + 4] == ' ' && map[i + 1][j + 4] != ' ' && map[i + 1][j + 3] == ' ' && map[i + 2][j + 3] != ' ' && map[i + 1][j] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 3);
					// cout << endl << "dont horizontal _xx__" << endl;
					return dont;
				}

		//horizontal __xx_
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 4; j++)
				if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i][j + 1] == ' ' && map[i + 1][j + 1] == ' ' && map[i + 2][j + 1] != ' ' && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i][j + 4] == ' ' && map[i + 1][j + 4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 1);
					// cout << endl << "dont horizontal __xx_" << endl;
					return dont;
				}

		//diagonal __xx_ l->r
		for (int i = height - 3; i >= 4; i--)
			for (int j = 1; j < 4; j++)
				if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j + 1] == ' ' && map[i + 1][j + 1] != ' ' && map[i][j + 1] == ' ' && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i - 4][j + 4] == ' ' && map[i - 3][j + 4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 1);
					// cout << endl << "dont diagonal __xx_ l->r" << endl;
					return dont;
				}

		//diagonal _xx__ l->r
		for (int i = height - 3; i >= 4; i--)
			for (int j = 1; j < 4; j++)
				if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == ' ' && map[i - 2][j + 3] == ' ' && map[i - 1][j + 3] != ' ' && map[i - 4][j + 4] == ' ' && map[i - 3][j + 4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 3);
					// cout << endl << "dont diagonal _xx__ l->r" << endl;
					return dont;
				}

		//diagonal __xx_ r->l ////
		for (int i = height - 3; i >= 4; i--)
			for (int j = length - 2; j > 4; j--)
				if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i - 1][j - 1] == rival && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == ' ' && map[i - 2][j - 3] == ' ' && map[i - 1][j - 3] != ' ' && map[i - 4][j - 4] == ' ' && map[i - 3][j - 4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j - 3);
					// cout << endl << "dont diagonal __xx_ r->l" << endl;
					return dont;
				}

		//diagonal _xx__ r->l
		for (int i = height - 3; i >= 4; i--)
			for (int j = length - 2; j > 4; j--)
				if (map[i][j]==' ' && map[i+1][j] != ' ' && map[i-1][j-1] == ' ' && map[i][j - 1] == ' ' && map[i + 1][j - 1] != ' ' && map[i - 2][j - 2] == rival && map[i - 3][j - 3] == rival && map[i - 4][j - 4] == ' ' && map[i -3][j - 4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j - 3);
					// cout << endl << "dont diagonal _xx__ r->l" << endl;
					return dont;
				}

		//horizontal _x_x_
		for (int i = height - 3; i >= 0; i--)
			for (int j = 1; j < 4; j++)
				if (map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i][j + 1] == rival && map[i][j + 2] == ' ' && map[i + 1][j + 2] == ' ' && map[i + 2][j + 2] != ' ' && map[i + 2][j + 2] != ' ' && map[i][j + 3] == rival && map[i][j + 4] == ' ' && map[i + 1][j + 4] != ' ')
				{
					do
					{
						dont = rand() % 7 + 1;
					} while (dont == j + 2);
					// cout << endl << "dont horizontal _x_x_" << endl;
					return dont;
				}
	}

	//horizonal xx__
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i][j + 1] == player && map[i][j + 2] == ' ' && map[i][j + 3] == ' ' && map[i + 1][j + 3] != ' ' && map[i + 1][j + 2] != ' ')
			{
				// cout << endl << "//horizonal xx__" << endl;
				return j + 2;
			}

	//horizonal __xx
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i][j + 1] == ' ' && map[i][j + 2] == player && map[i][j + 3] == player && map[i + 1][j] != ' ' && map[i + 1][j + 1] != ' ')
			{
				// cout << endl << "//horizonal __xx" << endl;
				return j + 1;
			}

	//diagonal xx__ l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == player && map[i - 1][j + 1] == player && map[i - 2][j + 2] == ' ' && map[i - 3][j + 3] == ' ' && map[i - 2][j + 3] != ' ' && map[i - 1][j + 2] != ' ')
			{
				// cout << endl << "//diagonal xx__ l->r" << endl;
				return j + 2;
			}

	//diagonal __xx l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i - 1][j + 1] == ' ' && map[i - 2][j + 2] == player && map[i - 3][j + 3] == player && map[i + 1][j] != ' ' && map[i][j + 1] != ' ')
			{
				// cout << endl << "//diagonal __xx l->r" << endl;
				return j + 1;
			}

	//diagonal xx__ r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i - 3][j - 3] == player && map[i - 2][j - 2] == player && map[i - 1][j - 1] == ' ' && map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i][j - 1] != ' ')
			{
				// cout << endl << "//diagonal xx__ r->l" << endl;
				return j - 1;
			}

	//diagonal __xx r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i][j] == player && map[i - 1][j - 1] == player && map[i - 2][j - 2] == ' ' && map[i - 3][j - 3] == ' ' && map[i - 2][j - 3] != ' ' && map[i - 1][j - 2] != ' ')
			{
				// cout << endl << "//diagonal __xx r->l" << endl;
				return j - 2;
			}

	//horizonal xx__
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i][j + 1] == rival && map[i][j + 2] == ' ' && map[i][j + 3] == ' ' && map[i + 1][j + 3] != ' ' && map[i + 1][j + 2] != ' ')
			{
				// cout << endl << "//horizonal xx__" << endl;
				return j + 2;
			}

	//horizonal __xx
	for (int i = height - 2; i >= 0; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i][j + 1] == ' ' && map[i][j + 2] == rival && map[i][j + 3] == rival && map[i + 1][j] != ' ' && map[i + 1][j + 1] != ' ')
			{
				// cout << endl << "//horizonal __xx" << endl;
				return j + 1;
			}

	//diagonal xx__ l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == rival && map[i - 1][j + 1] == rival && map[i - 2][j + 2] == ' ' && map[i - 3][j + 3] == ' ' && map[i - 2][j + 3] != ' ' && map[i - 1][j + 2] != ' ')
			{
				// cout << endl << "//diagonal xx__ l->r" << endl;
				return j + 2;
			}

	//diagonal __xx l->r
	for (int i = height - 2; i >= 3; i--)
		for (int j = 1; j < 5; j++)
			if (map[i][j] == ' ' && map[i - 1][j + 1] == ' ' && map[i - 2][j + 2] == rival && map[i - 3][j + 3] == rival && map[i + 1][j] != ' ' && map[i][j + 1] != ' ')
			{
				// cout << endl << "//diagonal __xx l->r" << endl;
				return j + 1;
			}

	//diagonal xx__ r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i - 3][j - 3] == rival && map[i - 2][j - 2] == rival && map[i - 1][j - 1] == ' ' && map[i][j] == ' ' && map[i + 1][j] != ' ' && map[i][j - 1] != ' ')
			{
				// cout << endl << "//diagonal xx__ r->l" << endl;
				return j - 1;
			}

	//diagonal __xx r->l
	for (int i = height - 2; i >= 3; i--)
		for (int j = length - 2; j > 3; j--)
			if (map[i][j] == rival && map[i - 1][j - 1] == rival && map[i - 2][j - 2] == ' ' && map[i - 3][j - 3] == ' ' && map[i - 2][j - 3] != ' ' && map[i - 1][j - 2] != ' ')
			{
				// cout << endl << "//diagonal __xx r->l" << endl;
				return j - 2;
			}

	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////

	// cout << endl << "//return 0" << endl;
	return 0;
}

