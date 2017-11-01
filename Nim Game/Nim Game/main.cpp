#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <dos.h>
#include <windows.h>
#include <cmath>
#include <assert.h>
#include <algorithm>

using namespace std;

int Size;
vector<int> Piles;
bool turn = false;
//0 player 1 computer
void GeneratePiles()
{
	srand(clock());
	Size = rand() % 9 + 2;
	int Xor = 0, num;
	for (int i = 1; i <= Size - 2; i++)
	{
		_sleep(1000);
		srand(clock());
		num = rand() % 15 + 1;
		Piles.push_back(num);
		Xor ^= num;
	}
	_sleep(1000);
	if (Xor == 0)
	{
		srand(clock());
		int num = rand() % 15 + 1;
		Piles.push_back(num);
		Piles.push_back(num);
	}
	else
	{
		while (true)
		{
			srand(clock());
			num = rand() % 15 + 1;
			if ((Xor ^ num) != 0)
			{
				Piles.push_back(num);
				Xor ^= num;
				break;
			}
			Sleep(100);
		}
		Piles.push_back(Xor);
	}
	random_shuffle(Piles.begin(), Piles.end());
}

void GetPiles()
{
	do
	{
		cout << "\nEnter number of piles from 2 to 10: ";
		cin >> Size;
		if (Size > 10 || Size < 2)
		{
			cout << "Wrong Size" << endl;
		}
	} while (Size > 10 || Size < 2);
	int Xor = 0;
	for (int i = 0; i < Size; i++)
	{
		int a;
		do
		{
			cout << "Enter number of stones from 1 to 15 in pile number " << i + 1 << ": ";
			cin >> a;
			if (a < 0 || a > 15)
			{
				cout << "Wrong number" << endl;
			}
		} while (a < 0 || a > 15);
		Piles.push_back(a);
		Xor ^= a;
	}
	if (Xor != 0)
	{
		turn = 1;
		cout << "\nComputer starts" << endl;
	}
	else
	{
		turn = 0;
		cout << "\nHuman Starts" << endl;
	}
}

int GetLargest(int largest)
{
	int Max = 0, pos = -1, num = pow(2, largest - 1);
	for (int i = 0; i < Piles.size(); i++)
	{
		if ((Piles[i] & num) && (Piles[i] > Max))
		{
			pos = i;
			Max = Piles[i];
		}
	}
	return pos;
}

void ComputerPlay()
{
	cout << "Computer Thinking" << endl;
	_sleep(3000);
	int Xor = 0, largest = 0, temp;
	for (int i = 0; i < Size; i++)
	{
		Xor ^= Piles[i];
	}
	temp = Xor;
	while (temp != 0)
	{
		temp /= 2;
		largest++;
	}
	int pos = GetLargest(largest);
	assert(pos != -1);
	cout << "computer takes " << Piles[pos] - (Piles[pos] ^ Xor) << " From Pile number " << pos + 1 << endl;
	Piles[pos] = Piles[pos] ^ Xor;
}

void display()
{
	cout << "\nNumber of Piles : " << Size << endl;
	cout << "*******************" << endl;
	for (int i = 0; i < Piles.size(); i++)
	{
		cout << "Number of stones in pile number " << i + 1 << " : " << Piles[i] << "\n";
	}
	cout << "\n";
}

void PlayerPlay()
{
	int choice1, choice2;
	bool Looping = true;
	do
	{
		cout << "Enter the pile you want to choose: ";
		cin >> choice1;
		if (choice1 < 1 || choice1 > Size)
		{
			cout << "Wrong Pile" << endl;
			continue;
		}
		if (Piles[choice1 - 1] <= 0)
		{
			cout << "Wrong Pile" << endl;
			continue;
		}
		Looping = false;
	} while (Looping);
	Looping = true;
	do
	{
		cout << "Enter the number of stones you want to remove: ";
		cin >> choice2;
		if (Piles[choice1 - 1] < choice2)
		{
			cout << "Wrong!";
		}
		else
		{
			Piles[choice1 - 1] -= choice2;
			break;
		}
	} while (true);
}

bool check()
{
	for (int i = 0; i < Size; i++)
	{
		if (Piles[i] != 0)
		{
			return false;
		}
	}
	return true;
}
void play()
{
	while (true)
	{
		display();
		if (turn == 1)
		{
			ComputerPlay();
		}
		else
		{
			PlayerPlay();
		}
		if (check())
		{
			if (turn)
			{
				cout << "Computer Wins :p";
			}
			else
			{
				cout << "Player Wins :(";
			}
			cout << "\n\n";
			break;
		}
		turn ^= 1;
	}
}

int main()
{
	cout << "**** Welcome To The Nim Game ****\n\n";
	cout << "Nim is a game of strategy in which two players take turns removing objects from distinct heaps. On each turn,"
		<< "a player must remove at least one object, and may remove any number of objects provided they all come from the same heap. The player who can't"
		<< "remove any stones loses. \n";
	char c;
	do
	{
		int choice1;
		cout << "\nPress 1 to play first or Press 2 to choose the piles: ";
		cin >> choice1;
		switch (choice1)
		{
		case 1:
			turn = 0;
			cout << "\nGenerating Piles :)" << endl;
			GeneratePiles();
			play();
			break;
		case 2:
			GetPiles();
			play();
			break;
		}
		Piles.clear();
		cout << "Press 'Y' To play again: ";
		cin >> c;
		c = tolower(c);
		if (c == 'y')
		{
			system("CLS");
		}
	} while (c == 'y');
	cout << "****** Thanks for playing our game hope you win next time :P ******";
	return 0;
}
