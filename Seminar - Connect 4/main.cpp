#include <iostream>
#include "header.hpp"
using namespace std;


int main()
{
	srand(time(0));
	Board b;
	char player='X';
	int column;
	int game_type;

	do
	{
		cout << "Press [1] for 1v1 mode or [2] for 1vPC mode: ";
		cin >> game_type;
		try
		{
			if (cin.fail() || (game_type != 1 && game_type != 2))
			{
				cin.clear(); // deletes error flag that cin.fail creates
				cin.ignore(10000, '\n'); // ignores next 10000 lines in buffer but stops when comes to \n
				throw exc<string>("Wrong input, try again!");
			}
		}
		catch(exc<string>& e)
		{
			cout << e.err << endl;
		}
	} while (game_type != 1 && game_type != 2);

	
	if (game_type == 1)
	{
		do
		{
			cout << "Player 1, do you want to be X or O?: ";
			cin >> player;
			try
			{
				if (cin.fail() || player != 'X' && player != 'x' && player != 'O' && player != 'o')
				{
					cin.clear(); // deletes error flag that cin.fail creates
					cin.ignore(10000, '\n'); // ignores next 10000 lines in buffer but stops when comes to \n
					throw exc<string>("Wrong input, try again!");
				}
			}
			catch (exc<string>& e)
			{
				cout << e.err << endl;
			}
		} while (player != 'X' && player != 'x' && player != 'O' && player != 'o');

		player = toupper(player);
		int pl1 = 0;
		int pl2 = 0;
		char status;
		while(1)
		{
				while (1)
				{
					cout << "Player '" << player << "' turn!" << endl;
					while (1)
					{
						cout << "Pick a column: ";
						cin >> column;
						try
						{
							if (cin.fail())
							{
								cin.clear(); // deletes error flag that cin.fail creates
								cin.ignore(10000, '\n'); // ignores next 10000 lines in buffer but stops when comes to \n
								throw exc<string>("Wrong input, try again!");

							}
						}
						catch (exc<string>& e)
						{
							cout << e.err << endl;
							continue;
						}
						//check if in range
						if (column < 1 || column>7)
							cout << "Column out of range! Pick a column between [1-7]" << endl;
						else if (b.put_char(column, player))
							break;
						else
							cout << "Column is full! Pick another one." << endl;
					}
					b.print();
					cout << "=> Player '" << player << "' chose " << column << ". column! <=" << endl << endl;
					if (b.check(player))
					{
						if (player == 'X')
							pl1++;
						else
							pl2++;
						cout << "Player '" << player << "' wins! Final table:" << endl;
						b.print();
						if (player == 'X')
							player = 'O';
						else
							player = 'X';
						break;
					}
					if (b.is_draw())
					{
						cout << " Draw! Final table:" << endl;
						b.print();
						break;
					}
					if (player == 'X')
						player = 'O';
					else
						player = 'X';
				}
				cout << "Scoreboard => Player 'X' " << pl1 << ":" << pl2 << " Player 'O'" << endl;
				cout << "Do you want to play again? Press Y or N: ";
				b.clear();

				do
				{
					cin >> status;
					try
					{
						if (cin.fail() || status != 'Y' && status != 'y' && status != 'N' && status != 'n')
						{
							cin.clear(); // deletes error flag that cin.fail creates
							cin.ignore(10000, '\n'); // ignores next 10000 lines in buffer but stops when comes to \n
							throw exc<string>("Wrong input, try again!");
						}
					}
					catch (exc<string>& e)
					{
						cout << e.err << endl;
					}
				} while (status != 'Y' && status != 'y' && status != 'N' && status != 'n');

				if (status == 'N' || status == 'n')
					break;
		}
			
		cout << "Final scoreboard => Player 'X' " << pl1 << ":" << pl2 << " Player 'O'" << endl;
		if (pl1 > pl2)
			cout << "Player 'X' won!" << endl;
		else if (pl1 < pl2)
			cout << "Player 'O' won!" << endl;
		else if (pl1 == pl2)
			cout << "Draw!" << endl;
		cout << endl;
		cout << "Thanks for playing! Made by Ante Aljinovic." << endl;
	}

	else
	{
		int pl1 = 0;
		int pl2 = 0;
		char status;
		while(1)
		{ 
			while (1)
			{
				cout << "Player '" << player << "' turn!" << endl;

				while (1 && player == 'X')
				{
					cout << "Pick a column: ";
					cin >> column;				
					try
					{
						if (cin.fail())
						{
							cin.clear(); // deletes error flag that cin.fail creates
							cin.ignore(10000, '\n'); // ignores next 10000 lines in buffer but stops when comes to \n
							throw exc<string>("Wrong input, try again!");
						}
					}
					catch (exc<string>& e)
					{
						cout << e.err << endl;
						continue;
					}
					//check if the range is correct
					if (column < 1 || column>7)
						cout << "Column out of range! Pick a column between [1-7]" << endl;
					else if (b.put_char(column, player))
						break;
					else
						cout << "Column is full! Pick another one." << endl;
				}
				while (1 && player=='O')
				{
					int check_flag = b.check_PC(player);
					if (!check_flag)
						column = rand() % 7 + 1;
					else
						column = check_flag;
					if (b.put_char(column, player))
						break;
				}
				b.print();
				cout <<  "=> Player '" << player << "' chose " << column << ". column! <=" << endl<<endl;
				if (b.check(player))
				{
					if (player == 'X')
						pl1++;
					else
						pl2++;
					cout << "Player " << player << " won! Final table:" << endl;
					b.print();
					if (player == 'X')
						player = 'O';
					else
						player = 'X';
					break;
				}		
				if (b.is_draw())
				{
					cout << "Draw!" << endl;
					b.print();
					break;
				}
				if (player == 'X')
					player = 'O';
				else
					player = 'X';
				
			}

			cout << "Scoreboard => Player " << pl1 << ":" << pl2 <<" PC" << endl;
			cout << "Do you want to play again? Press Y or N: ";
			b.clear();

			do
			{

				cin >> status;				
				try
				{
					if (cin.fail() || status != 'Y' && status != 'y' && status != 'N' && status != 'n')
					{
						cin.clear(); // deletes error flag that cin.fail creates
						cin.ignore(10000, '\n'); // ignores next 10000 lines in buffer but stops when comes to \n
						throw exc<string>("Wrong input, try again!");
					}
				}
				catch (exc<string>& e)
				{
					cout << e.err << endl;
				}

			} while (status != 'Y' && status != 'y' && status != 'N' && status != 'n');

			if (status == 'N' || status == 'n')
					break;
		}
		cout << "Final scoreboard => Player " << pl1 << ":" << pl2 << " PC" << endl;
		if (pl1 > pl2)
			cout << "Player won!" << endl;
		else if (pl1 < pl2)
			cout << "PC won!" << endl;
		else if (pl1 == pl2)
			cout << "Draw!" << endl;
		cout << endl;
		cout << "Thanks for playing! Made by Ante Aljinovic." << endl;
	}
	system("pause");
}
