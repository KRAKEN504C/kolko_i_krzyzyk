/*
Konrad Roszczynialski
k��ko i krzy�yk wersja 9-planszowa.

Do zrobienia:
-poprawa funkcji przemieszczajacej mi�dzy mini planszami.
-naprawic SI
*/
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <time.h>

using namespace std;
char sq[9][9] = {};
int checkwin = 0;

//1.ta funkcja przyjmuje od gracza wspolrzedne, gdzie gracz chce umiescic swoj znak.
void move(int *x, int *y);

//funkcja przyjmuje wsp��rz�dne dla SI
void moveSI(int *ptchboard,int *x, int *y);

//3.ta funkcja bierze zmodyfikawane wspolrzedne, i wstawia znak w odpowiednie miejsce.
void makemove(int *x, int *y, int *plr);


//4.ta funkcja przesuwa pole, na ktorym odbywa sie rozgrywka.
//specjalna alternatywa. 9 if-�w. kazdy zmienia pole w zaleznosci od niezmodyfikowanych wspolrzednych
//trza poprawic
int moveminiboard(int x, int y, int chboard);

//pomniejsza funkcja wskazujaca miejsce akcji, i aktualnego gracza.
void miejsceakcji(int chboard, int plr);

//2.ta funkcja modyfikuje podane wspolrzedne, zeby wskazywaly poprawna plansze.
void checkboard(int chboard, int *x, int *y);

//0. ta funkcja wyswietla pole gry.
void board();

//funkcja sprawdzajaca, czy ktorys gracz wygra�. albo cay nie bylo remisu. Jest 8 mozliwosci wygranej w normalne kolko i krzyzyk. dziala z opuznieniem jednego ruchu.
int fcheckwin();


void logikaSI(int *x, int *y, int *ptchboard);

//sztuczna inteligencja. Bardzo sztuczna.
int SI(int *x, int *y, int *wspplr, int* ptchboard);  //(int ruchSI)



int main()
{
	int player = 0;
	int *wspplr = &player;
	int chboard = 5;
	int *ptchboard = &chboard;
	int newchboard;
	int wartoscx = -1;
	int wartoscy = -1;
	int niezmienionex;
	int niezmienioney;
	int *wspx = &wartoscx;
	int *wspy = &wartoscy;

	while (checkwin == 0)
	{
		board();

			board();
			miejsceakcji(chboard, player);

			if (player == 0)
			{

			move(wspx, wspy);

			//cout << *wspx << *wspy << endl;

			niezmienionex = *wspx; niezmienioney = *wspy;
			checkboard(chboard, wspx, wspy);
			while (sq[*wspx - 1][*wspy - 1] != 0)
			{
				cout << "\nBlad! podano wspolrzedne, ktora juz jest oznaczona.\n\n";
				move(wspx, wspy);
				niezmienionex = *wspx; niezmienioney = *wspy;
				checkboard(chboard, wspx, wspy);
			}

			//cout << *wspx << *wspy;

			makemove(wspx, wspy, wspplr);

			newchboard = moveminiboard(niezmienionex, niezmienioney, chboard);
			chboard = newchboard;
			//system("pause");
			checkwin = fcheckwin();
			system("pause");
		}
			else
			{
				board();
				checkwin = SI(wspx, wspy, wspplr, ptchboard);  board();
			}
	}


	board();

	if (checkwin == 1) { cout << "\n\n\t\tGratulacje Wygrales!!!"; }
	else
		if (checkwin == 2) { cout << "\n\n\t\tKomputer wygral."; }
		else
			if (checkwin == 3) { cout << "\n\n\t\tnie ma mozliwosci wykonania ruchu. Remis."; }
			else
			{
				cout << "\n\n\n\tNastapil jakis niespodziewany blad. hmmm... ciekawe.";
			}
	//board();
	system("pause");
	return 0;
}





void move(int *x, int *y)
{
	int innex = -1, inney = -1;
	cout << "Prosze podac pole w ukladzie wspolrzednych od 1 do 3:\n";
	cout << "Prosze podac wspolrzedna x:\n";
	cin >> innex;
	while (innex<1 || innex>3) {
		cout << "\nBlad! podano wspolrzadna spoza przedzialu od 1 do 3!\n";
		cin >> innex;
	}
	cout << "\nWybrales wspolrzedna x:" << innex << "\n";
	cout << "prosze podac wspolrzedna y:";
	cin >> inney;
	while (inney<1 || inney>3) {
		cout << "\nBlad! podano wspolrzadna spoza przedzialu od 1 do 3!\n";
		cin >> inney;
	}
	cout << "\nWybrales wpolrzedna y:" << inney << "\n";
	*x = innex;
	*y = inney;
	//cout << "test";
}
//ta funkcja jest za prosta, �eby ja zepsu�.
void makemove(int *x, int *y, int *plr)
{
	if (*plr == 0)
	{
		sq[*x - 1][*y - 1] = 88;
		*plr = 1;
	}
	else
	{
		sq[*x - 1][*y - 1] = 79;
		*plr = 0;
	}
}

int moveminiboard(int x, int y, int chboard)
{
	if (x == 1 && y == 1)
	{
		return chboard = 1;
	}
	else
		if (x == 1 && y == 2)
		{
			return chboard = 4;
		}
		else
			if (x == 1 && y == 3)
			{
				return chboard = 7;
			}
			else
				if (x == 2 && y == 1)
				{
					return chboard = 2;
				}
				else
					if (x == 2 && y == 2)
					{
						return chboard = 5;
					}
					else
						if (x == 2 && y == 3)
						{
							return chboard = 8;
						}
						else
							if (x == 3 && y == 1)
							{
								return chboard = 3;
							}
							else
								if (x == 3 && y == 2)
								{
									return chboard = 6;
								}
								else
									if (x == 3 && y == 3)
									{
										return chboard = 9;
									}
}
//ta funkcja nie ma na nic wp�ywu
void miejsceakcji(int chboard, int plr)
{
	cout << "aktualny ruch odbedzie sie na planszy: ";
	switch (chboard)
	{
	case 1:
		cout << "polnocno zachodniej.(1)\n";
		break;
	case 2:
		cout << "polnocnej.(2)\n";
		break;
	case 3:
		cout << "polnocno wschodniej.(3)\n";
		break;
	case 4:
		cout << "zachodniej.(4)\n";
		break;
	case 5:
		cout << "srodkowej.(5)\n";
		break;
	case 6:
		cout << "wschodniej.(6)\n";
		break;
	case 7:
		cout << "poludniowo zachodniej.(7)\n";
		break;
	case 8:
		cout << "poludniowej.(8)\n";
		break;
	case 9:
		cout << "poludniowo wschodniej.(9)\n";
		break;
	}
	cout << "\n\n Aktualny  ruch nalezy do gracza ze znakiem :";
	if (plr == 0) { cout << "\t X\n"; }
	else
	{
		cout << "\t O\n";
	}
}

void checkboard(int chboard, int *x, int *y)
{
	switch (chboard)
	{
	case 1:
		*x += 0;
		*y += 0;
		break;
	case 2:
		*x += 3;
		*y += 0;
		break;
	case 3:
		*x += 6;
		*y += 0;
		break;
	case 4:
		*x += 0;
		*y += 3;
		break;
	case 5:
		*x += 3;
		*y += 3;
		break;
	case 6:
		*x += 6;
		*y += 3;
		break;
	case 7:
		*x += 0;
		*y += 6;
		break;
	case 8:
		*x += 3;
		*y += 6;
		break;
	case 9:
		*x += 6;
		*y += 6;
		break;

	}
}
//w board raczej ci��ko co� zepsu�.
void board()
{
	system("cls");
	cout << "\n\n\tTic Tac Toe\n\n";
	//cout << "\nGra zaczyna sie od srodkowego pola i ruch gracza wyznacza 1 z 9 plansz na ktorych bedzie mozna dokonac nastepnego ruchu. tak dopuki ni pojawi sie 3 x lub o pod rzad.\n";
	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][0] << "  |  " << sq[1][0] << "  |  " << sq[2][0] << "          " << sq[3][0] << "  |  " << sq[4][0] << "  |  " << sq[5][0] << "          " << sq[6][0] << "  |  " << sq[7][0] << "  |  " << sq[8][0] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][1] << "  |  " << sq[1][1] << "  |  " << sq[2][1] << "          " << sq[3][1] << "  |  " << sq[4][1] << "  |  " << sq[5][1] << "          " << sq[6][1] << "  |  " << sq[7][1] << "  |  " << sq[8][1] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][2] << "  |  " << sq[1][2] << "  |  " << sq[2][2] << "          " << sq[3][2] << "  |  " << sq[4][2] << "  |  " << sq[5][2] << "          " << sq[6][2] << "  |  " << sq[7][2] << "  |  " << sq[8][2] << endl;
	cout << "     |     |                |     |                |     |     " << endl << endl;

	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][3] << "  |  " << sq[1][3] << "  |  " << sq[2][3] << "          " << sq[3][3] << "  |  " << sq[4][3] << "  |  " << sq[5][3] << "          " << sq[6][3] << "  |  " << sq[7][3] << "  |  " << sq[8][3] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][4] << "  |  " << sq[1][4] << "  |  " << sq[2][4] << "          " << sq[3][4] << "  |  " << sq[4][4] << "  |  " << sq[5][4] << "          " << sq[6][4] << "  |  " << sq[7][4] << "  |  " << sq[8][4] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][5] << "  |  " << sq[1][5] << "  |  " << sq[2][5] << "          " << sq[3][5] << "  |  " << sq[4][5] << "  |  " << sq[5][5] << "          " << sq[6][5] << "  |  " << sq[7][5] << "  |  " << sq[8][5] << endl;
	cout << "     |     |                |     |                |     |     " << endl << endl;

	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][6] << "  |  " << sq[1][6] << "  |  " << sq[2][6] << "          " << sq[3][6] << "  |  " << sq[4][6] << "  |  " << sq[5][6] << "          " << sq[6][6] << "  |  " << sq[7][6] << "  |  " << sq[8][6] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][7] << "  |  " << sq[1][7] << "  |  " << sq[2][7] << "          " << sq[3][7] << "  |  " << sq[4][7] << "  |  " << sq[5][7] << "          " << sq[6][7] << "  |  " << sq[7][7] << "  |  " << sq[8][7] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][8] << "  |  " << sq[1][8] << "  |  " << sq[2][8] << "          " << sq[3][8] << "  |  " << sq[4][8] << "  |  " << sq[5][8] << "          " << sq[6][8] << "  |  " << sq[7][8] << "  |  " << sq[8][8] << endl;
	cout << "     |     |                |     |                |     |     " << endl;
}
//zrewidowana. dzia�a perfekcyjnie.
int fcheckwin()
{
	//int x=0,y=0;
	int check = 0;
	int wincondition = 0;

	for (int x = 0; x <= 8; x += 3)
	{
		for (int y = 0; y <= 8; y += 3)
		{

				if (sq[x][y] == sq[x + 1][y] && sq[x + 1][y] == sq[x + 2][y] && sq[x][y]!=0)// 1 poziom
				{
					if (sq[x][y] == 88) { return 1; }
					else
						if (sq[x][y] == 79) { return 2; }
				}else
				if (sq[x][y + 1] == sq[x + 1][y + 1] && sq[x + 1][y + 1] == sq[x + 2][y + 1] && sq[x][y+1] != 0)// 2 poziom
				{
					if (sq[x][y + 1] == 88) { return 1; }
					else
						if (sq[x][y + 1] == 79) { return 2; }
				}else
				if (sq[x][y + 2] == sq[x + 1][y + 2] && sq[x + 1][y + 2] == sq[x + 2][y + 2] && sq[x][y+2] != 0)// 3 poziom
				{
					if (sq[x][y + 2] == 88) { return 1; }
					else
						if (sq[x][y + 2] == 79) { return 2; }
				}else

				if (sq[x][y] == sq[x][y + 1] && sq[x][y + 1] == sq[x][y + 2] && sq[x][y] != 0)// 1 pion
				{
					if (sq[x][y] == 88) { return 1; }
					else
						if (sq[x][y] == 79) { return 2; }
				}else
				if (sq[x+1][y] == sq[x+1][y + 1] && sq[x+1][y + 1] == sq[x+1][y + 2] && sq[x+1][y] != 0)// 2 pion
				{
					if (sq[x + 1][y] == 88) { return 1; }
					else
						if (sq[x + 1][y] == 79) { return 2; }
				}else
				if (sq[x+2][y] == sq[x+2][y + 1] && sq[x+2][y + 1] == sq[x + 2][y + 2] && sq[x+2][y] != 0)// 3 pion
				{
					if (sq[x + 2][y] == 88) { return 1; }
					else
						if (sq[x + 2][y] == 79) { return 2; }
				}else

				if (sq[x][y] == sq[x+1][y + 1] && sq[x+1][y + 1] == sq[x + 2][y + 2] && sq[x][y] != 0)// 1 skos (\)
				{
					if (sq[x][y] == 88) { return 1; }
					else
						if (sq[x][y] == 79) { return 2; }
				}else
				if (sq[x][y+2] == sq[x + 1][y + 1] && sq[x + 1][y + 1] == sq[x+2][y] && sq[x][y+2] != 0)// 2 skos (/)
				{
					if (sq[x][y+2] == 88) { return 1; }
					else
						if (sq[x][y+2] == 79) { return 2; }
				}

			}

		}



	//if(wincondition==1){return 1;}else if(wincondition==2){return 2;}else
	//funkcja sprawdzajaca remis
	//jezeli funkcja zwroci wartosc 81 oznacza to, ze wwzystkie pola sa zajete.
	for (int i = 0; i <= 8; i++)
	{
		for (int z = 0; z <= 8; z++)
		{
			if (sq[i][z] != 0) { check++; }
		}
	}
	if (check == 81) { return 3; }
	else
		return 0;

}

//moveSI operuje na liczbach OD 1 DO 3! NIE od 0 do 2 !!!
void moveSI(int *ptchboard,int *x, int *y)
{
	int moveSIx, moveSIy,SIx,SIy;

	srand(time(NULL));

	switch (*ptchboard)
	{
	case 1:
		SIx = 0;  SIy = 0;
		break;
	case 2:
		SIx = 3;  SIy = 0;
		break;
	case 3:
		SIx = 6;  SIy = 0;
		break;
	case 4:
		SIx = 0;  SIy = 3;
		break;
	case 5:
		SIx = 3;  SIy = 3;
		break;
	case 6:
		SIx = 6;  SIy = 3;
		break;
	case 7:
		SIx = 0;  SIy = 6;
		break;
	case 8:
		SIx = 3;  SIy = 6;
		break;
	case 9:
		SIx = 6;  SIy = 6;
		break;
	}

		do {
			moveSIx = rand() % 3 + 1;
			moveSIy = rand() % 2;
			moveSIy++;
		} while (sq[SIx + moveSIx - 1][SIy + moveSIy - 1] != 0);

	*x = moveSIx;
	*y = moveSIy;
}

//funkcja znajduje polozenie 2 punktow O na aktualnej planszy.
void logikaSI(int *x, int *y, int *ptchboard)
{
	int Ox1 = -1, Ox2 = -1, Oy1 = -1, Oy2 = -1, Ox3 = -1, Oy3 = -1;
	bool checkO1=0, checkO2=0;
	int SIx, SIy;
	int test = 0;

	switch (*ptchboard)
	{
	case 1:
		SIx = 0;  SIy = 0;
		break;
	case 2:
		SIx = 3;  SIy = 0;
		break;
	case 3:
		SIx = 6;  SIy = 0;
		break;
	case 4:
		SIx = 0;  SIy = 3;
		break;
	case 5:
		SIx = 3;  SIy = 3;
		break;
	case 6:
		SIx = 6;  SIy = 3;
		break;
	case 7:
		SIx = 0;  SIy = 6;
		break;
	case 8:
		SIx = 3;  SIy = 6;
		break;
	case 9:
		SIx = 6;  SIy = 6;
		break;
	}

	//test sprawdzajacy ile jest znakow O na aktualnej planszy.
	for (int ix = 0; ix <= 2; ix++)
	{
		for (int iy = 0; iy <= 2; iy++)
		{
			if (sq[SIx + ix][SIy + iy] == 79)
			{
				test++;
				checkO1 = 1;
				Ox1 = ix;
				Oy1 = iy;
			}
		}
	}
	//test wydaje sie dobrym pomyslem :)
	if (test == 1)
	{
		while (checkO1 == 0)
		{
			for (int ix = 0; ix <= 2; ix++)
			{
				for (int iy = 0; iy <= 2; iy++)
				{
					if (sq[SIx + ix][SIy + iy] == 79)
					{
						checkO1 = 1;
						Ox1 = ix;
						Oy1 = iy;
					}
				}
			}
		}
	}

	if (test>1)
	{
		while(checkO2==0)
		{
			for (int ix = 0; ix <= 2; ix++)
			{
				for (int iy = 0; iy <= 2; iy++)
				{
					if (sq[SIx + ix][SIy + iy] == 79 && (ix!=Ox1 || iy!=Oy1))
					{
						checkO2 = 1;
						Ox2 = ix;
						Oy2 = iy;
					}
				}
			}
		}
	}
	if (checkO2 == 1)
	{
	}


	if (test < 2)
	{
		moveSI(ptchboard,x,y);
	}
	else
		//poziom
		if (Ox1 == Ox2)
		{
			Ox3 = Ox1;
			for (int iy = 0; iy <= 2; iy++)
			{
				Oy3 = iy;
				if (sq[SIx + Ox3][SIy + Oy3] == 0)
				{
					*x = Ox3+1;
					*y = Oy3+1;
				}
			}
		}
		else
			//pion
		if (Oy1 == Oy2)
		{

			{
				Oy3 = Oy1;
				for (int ix = 0; ix <= 2; ix++)
				{
					Ox3 = ix;
					if (sq[SIx + Ox3][SIy + Oy3] == 0)
					{
						*x = Ox3+1;
						*y = Oy3+1;
					}
				}
			}
		}
		else
			//skos
			if(sq[SIx+1][SIy+1]!=88)
			{
				if (sq[SIx][SIy] == 79 || sq[SIx+2][SIy+2] == 79)
				{
					Ox3 = 0;
					Oy3 = 0;
					if (sq[SIx+Ox3][SIy+Oy3] != 0)
					{
						Ox3 = 1;
						Oy3 = 1;
						if (sq[SIx + Ox3][SIy + Oy3] != 0)
						{
							Ox3 = 2;
							Oy3 = 2;
							if (sq[SIx + Ox3][SIy + Oy3] != 0)
							{

							}
						}

					}
				}
				if (sq[SIx + 2][SIy] == 79 || sq[SIx][SIy + 2] == 79)
				{
					Ox3 = 2;
					Oy3 = 0;
					if (sq[SIx + Ox3][SIy + Oy3] != 0)
					{
						Ox3 = 1;
						Oy3 = 1;
						if (sq[SIx + Ox3][SIy + Oy3] != 0)
						{
							Ox3 = 0;
							Oy3 = 2;
							if (sq[SIx + Ox3][SIy + Oy3] != 0)
							{

							}
						}

					}
				}
				*x = Ox3+1;
				*y = Oy3+1;
			}

			else
			{
				moveSI(ptchboard, x, y);
			}


}

int SI(int *wspx, int *wspy, int *wspplr, int* ptchboard)
{
	int newchboardSI;
	int niezSIx, niezSIy;


	logikaSI(wspx, wspy, ptchboard);

		//moveSI(ptchboard,wspx, wspy);
		niezSIx = *wspx; niezSIy = *wspy;
		checkboard(*ptchboard, wspx, wspy);



	makemove(wspx, wspy, wspplr);

	newchboardSI = moveminiboard(niezSIx, niezSIy, *ptchboard);
	*ptchboard = newchboardSI;
	checkwin = fcheckwin();
	system("pause");

	return checkwin;
}
