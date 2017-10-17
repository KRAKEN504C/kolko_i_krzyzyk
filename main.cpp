/*
Konrad Roszczynialski
kó³ko i krzy¿yk wersja 9-planszowa.

Do zrobienia:
-poprawa funkcji przemieszczajacej miêdzy mini planszami.
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

//funkcja przyjmuje wspó³rzêdne dla SI
void moveSI(int *x, int *y, int Ox1, int Oy1)
{
	int innex, inney;

	//srand(time(NULL));

	innex = rand() % 3 + 1;
	inney = rand() % 2;
	inney++;

	if (Ox1 == -1 || Oy1 == -1)
	{
		while (sq[innex][inney] != 0)
		{
			innex = rand() % 3 + 1;
			inney = rand() % 2;
			inney++;
		}
	}
	else
		
		//cos tu jest nie tak
	{
		if (Ox1 == 3 || Oy1 == 3 || Ox1 == 2 || Oy1 == 2)
		{
			innex = 3; inney = 3;
			while (sq[innex][inney] != 0)
			{
				for (int i = 3; i >= 1; i--)
				{
					for (int j = 3; j >= 1; j--)
					{
						innex = i;
						inney = j;
					}
				}
			}
		}
		else
		{
			if (Ox1 == 1 || Oy1 == 1)
			{
				innex = 1; inney = 1;
				while (sq[innex][inney] != 0)
				{
					for (int i = 1; i <= 3; i++)
					{
						for (int j = 1; j <= 3; j++)
						{
							innex = i;
							inney = j;
						}
					}
				}
			}
		}


	}


	*x = innex;
	*y = inney;
	//cout<<"\tinnex=="<<*x<<"\tinney=="<<*y<<endl;
	//cout<<"\tprawdziweinnex=="<<innex<<"\tprawdziweinney=="<<inney<<endl;
}

//3.ta funkcja bierze zmodyfikawane wspolrzedne, i wstawia znak w odpowiednie miejsce.
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

//4.ta funkcja przesuwa pole, na ktorym odbywa sie rozgrywka.
//specjalna alternatywa. 9 if-ów. kazdy zmienia pole w zaleznosci od niezmodyfikowanych wspolrzednych
//trza poprawic
int moveminiboard(int x, int y, int chboard)
{
	if (x == 1 && y == 1)
	{
		if (chboard == 4 || chboard == 7) { return chboard -= 3; }
		else
			if (chboard == 3 || chboard == 2) { return chboard -= 1; }
			else
				if (chboard == 1) { return chboard; }
				else
					return chboard -= 4;
	}
	else
		if (x == 1 && y == 2)
		{
			if (chboard == 1 || chboard == 4 || chboard == 7) { return chboard; }
			else
				return chboard -= 1;
		}
		else
			if (x == 1 && y == 3)
			{
				if (chboard == 1 || chboard == 4) { return chboard += 3; }
				else
					if (chboard == 8 || chboard == 9) { return chboard -= 1; }
					else
						if (chboard == 7) { return chboard; }
						else
							return chboard += 2;
			}
			else
				if (x == 2 && y == 1)
				{
					if (chboard >= 1 && chboard <= 3) { return chboard; }
					else
						return chboard -= 3;
				}
				else
					if (x == 2 && y == 2)
					{
						return chboard;
					}
					else
						if (x == 2 && y == 3)
						{
							if (chboard >= 7 && chboard <= 9) { return chboard; }
							else
								return chboard += 3;
						}
						else
							if (x == 3 && y == 1)
							{
								if (chboard == 2 || chboard == 1) { return chboard += 1; }
								else
									if (chboard == 6 || chboard == 9) { return chboard -= 3; }
									else
										if (chboard == 3) { return chboard; }
										else
											return chboard -= 2;
							}
							else
								if (x == 3 && y == 2)
								{
									if (chboard == 3 || chboard == 6 || chboard == 9) { return chboard; }
									else
										return chboard += 1;
								}
								else
									if (x == 3 && y == 3)
									{
										if (chboard == 3 || chboard == 6) { return chboard += 3; }
										else
											if (chboard == 7 || chboard == 8) { return chboard += 1; }
											else
												if (chboard == 9) { return chboard; }
												else
													return chboard += 4;
									}
}

//pomniejsza funkcja wskazujaca miejsce akcji, i aktualnego gracza.
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

//2.ta funkcja modyfikuje podane wspolrzedne, zeby wskazywaly poprawna plansze.
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
		*y = 0;
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

//0. ta funkcja wyswietla pole gry.
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

//funkcja sprawdzajaca, czy ktorys gracz wygra³. albo cay nie bylo remisu. Jest 8 mozliwosci wygranej w normalne kolko i krzyzyk. dziala z opuznieniem jednego ruchu.
int fcheckwin()
{
	//int x=0,y=0;
	int check = 0;
	int wincondition = 0;

	for (int x = 0; x <= 8; x += 3)
	{
		for (int y = 0; y <= 8; y += 3)
		{

			//if(sq[x][y]==0 || sq[x+1][+1]==0 || sq[x+2][y+2]==0){return 0;}else   {
			if (sq[x][y] == sq[x + 1][y] && sq[x + 1][y] == sq[x + 2][y]) { if (sq[x][y] == 88) { return 1; } else if (sq[x][y] == 79) { return 2; } }
			else
				if (sq[x][y + 1] == sq[x + 1][y + 1] && sq[x + 1][y + 1] == sq[x + 2][y + 1]) { if (sq[x][y + 1] == 88) { return 1; } else if (sq[x][y + 1] == 79) { return 2; } }
				else
			if (sq[x][y + 2] == sq[x + 1][y + 2] && sq[x + 1][y + 2] == sq[x + 2][y + 2]) { if (sq[x][y + 2] == 88) { return 1; } else if (sq[x][y + 2] == 79) { return 2; } }
			else

				if (sq[x][y] == sq[x][y + 1] && sq[x][y + 1] == sq[x][y + 2]) { if (sq[x][y] == 88) { return 1; } else if (sq[x][y] == 79) { return 2; } }
				else
			if (sq[x + 1][y] == sq[x + 1][y + 1] && sq[x + 1][y + 1] == sq[x + 1][y + 2]) { if (sq[x + 1][y] == 88) { return 1; } else if (sq[x + 1][y] == 79) { return 2; } }
			else
				if (sq[x + 2][y] == sq[x + 2][y + 1] && sq[x + 2][y + 1] == sq[x + 2][y + 2]) { if (sq[x + 2][y] == 88) { return 1; } else if (sq[x + 2][y] == 79) { return 2; } }
				else

			if (sq[x][y] == sq[x + 1][y + 1] && sq[x + 1][y + 1] == sq[x + 2][y + 2]) { if (sq[x][y] == 88) { return 1; } else if (sq[x][y] == 79) { return 2; } }
			else
				if (sq[x + 3][y] == sq[x + 1][y + 1] && sq[x + 1][y + 1] == sq[x][y + 3]) { if (sq[x + 3][y] == 88) { return 1; } else if (sq[x + 3][y] == 79) { return 2; } }   //}

																																																		 //cout << x << "\t" << y << endl;
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

//do naprawy
//prawdopodobnie ten sam blad jest w funkcji logikaSI.
//chyba dzia³a. funkcja for liczy³a od 0 do 3 zamiast od 0 do 2.
int emptyCheck(int *x, int *y, int *ptchboard)
{
	int refx=-1, refy=-1;
	int SIMark = 0;
	int SIx = -1, SIy = -1;

	cout << "\n\nFunkcja emptyCheck jest wykonywana na planszy: " << *ptchboard << endl;
	cout << "\n\n\t *x: " << *x << endl;
	cout << "\n\n\t *y: " << *y << endl;

	switch (*ptchboard)
	{
	case 1:
		refx = 0;
		refy = 0;
		break;
	case 2:
		refx = 3;
		refy = 0;
		break;
	case 3:
		refx = 6;
		refy = 0;
		break;
	case 4:
		refx = 0;
		refy = 3;
		break;
	case 5:
		refx = 3;
		refy = 3;
		break;
	case 6:
		refx = 6;
		refy = 3;
		break;
	case 7:
		refx = 0;
		refy = 6;
		break;
	case 8:
		refx = 3;
		refy = 6;
		break;
	case 9:
		refx = 6;
		refy = 6;
		break;

	}

	/*
	if (*x <= 3) { refx = 0; }
	else
		if (*x <= 6) { refx = 3; }
		else
		{
			refx = 6;
		}

	if (*y <= 3) { refy = 0; }
	else
		if (*y <= 6) { refy = 3; }
		else
		{
			refy = 6;
		}
	*/


	for (int ix = 0; ix <= 2; ix++)
	{
		for (int iy = 0; iy <= 2; iy++)
		{
			if (sq[refx + ix][refy + iy] == 79)
			{
				SIMark = 1;
				SIx = refx + ix+1;//!!! ISTOTNA ZMIANA!!! +1!!!
				SIy = refy + iy+1;
			}
		}
	}
	cout << "\n\n*x= " << *x << " *y= " << *y << endl;
	cout << "\n\nrefx= " << refx << " refy= " << refy << endl;

	cout << "\n\n\temptycheck SIx: " << SIx << endl;
	cout << "\n\n\t SIy: " << SIy << endl;

	if (SIMark == 0)
	{
		cout << "nie znaleziono znaku O  na aktywnej planszy." << endl;
		return 0;
	}
	else {
		cout << "znaleziono znak O na aktywnej planszy" << endl;
		return 1;
	}
}

void skos(int x, int y, int *wskos11, int *wskos13, int *wskos22, int *wskos33, int *wskos31)
{
	if (x == 1 && y == 1)
	{
		*wskos11 = 1;
	}
	if (x == 2 && y == 2)
	{
		*wskos22 = 1;
	}
	if (x == 3 && y == 3)
	{
		*wskos33 = 1;
	}
	if (x == 3 && y == 1)
	{
		*wskos31 = 1;
	}
	if (x == 1 && y == 3)
	{
		*wskos13 = 1;
	}
}


void logikaSI(int *x, int *y, int *ptchboard)
{
	int SIx, SIy;
	int Ox1, Oy1, Ox2, Oy2, Ox3 = -1, Oy3 = -1;
	int found2 = 0;

	int skos11=0, skos22=0, skos33=0, skos31=0, skos13=0;
	int *wskos11 = &skos11;
	int *wskos13 = &skos13;
	int *wskos22 = &skos22;
	int *wskos33 = &skos33;
	int *wskos31 = &skos31;


	cout << "program wszedl w funkcje logikaSI." << endl;


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

	cout << "logikSI SIx= " << SIx << " SIy= " << SIy << endl;

	//pêtelka znajdujaca pierwesze po³o¿enie x, y, znaku O na aktualnie rozgrywanej planszy.
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (sq[SIx + i][SIy + j] == 79)
			{
				Ox1 = SIx + i;
				Oy1 = SIy + j;
				skos(Ox1, Oy1, wskos11, wskos13, wskos22, wskos33, wskos31);
			}
		}
	}

	//pêtelka znajdujaca po³o¿enie drugiego x, y znaku O. Je¿eli brak, to stawic obok pierwszego O.
	for (int i = 0; i <= 2; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			if (sq[SIx + i][SIy + j] == 79 && SIx + i != Ox1 && SIy + j != Oy1)
			{
				Ox2 = SIx + i;
				Oy2 = SIy + j;
				found2 = 1;
				skos(Ox2, Oy2, wskos11, wskos13, wskos22, wskos33, wskos31);
			}
		}
	}

	

	cout << "found2 ==" << found2<<endl;

	cout << "\n\n\tznaleziono pierwszy punkt O na aktualnej planszy w punkcie: x: " << Ox1 + 1 << " y: " << Oy1 + 1 << endl;
	if (found2 == 1)
	{
		cout << "\n\n\tznaleziono drugi punkt O na aktualnej planszy w punkcie: x: " << Ox2 + 1 << " y: " << Oy2 + 1 << endl;
	}
	else {
		cout << "\n\n\tnie znaleziono drugiego punktu O na aktualnej planszy. " << endl;
	}


	//masa if-ów.
	{
		//cos tu jest nie tak
		if (found2 == 0)
		{
			do {
				moveSI(x, y, Ox1, Oy1);
				cout << "wspolrzedne wybrane przez funkcje moveSI aktywowana przez funkcje do while w logikaSI: " << endl;
				cout << "x== " << *x << endl;
				cout << "y== " << *y << endl;
				checkboard(*ptchboard, x, y);
			} while (sq[*x - 1][*y - 1] != 0);//&& sq[*x-1][*y-1]!=0);
		}
		else
		{

			if (Ox1 == Ox2)
			{
				Ox3 = Ox2;
				Oy3 = 1;
				while (Oy3 != Oy2 || Oy3 != Oy1)
				{
					Oy3++;
				}
				if (sq[Ox3][Oy3] != 0)
				{
					moveSI(x, y, Ox2, Oy2);
				}
			}
			else

				if (Oy1 == Oy2)
				{
					Oy3 = Oy2;
					Ox3 = 1;
					while (Ox3 != Ox2 || Ox3 != Ox1)
					{
						Ox3++;
					}
					if (sq[Ox3][Oy3] != 0)
					{
						moveSI(x, y, Ox2, Oy2);
					}
				}
				else
				{
					//start bezsensownych if-ów, bez których pewnie da³oby siê to zrobic w 300 linijkach.

					if (skos11 == 1 && skos22 == 1)
					{
						Ox3 = 3; Oy3 = 3;
						if (sq[Ox3 - 1][Oy3 - 1] != 0)
						{
							moveSI(x, y, Ox2, Oy2);
						}
					}else

					if (skos33 == 1 && skos22 == 1)
					{
						Ox3 = 1; Oy3 = 1;
						if (sq[Ox3 - 1][Oy3 - 1] != 0)
						{
							moveSI(x, y, Ox2, Oy2);
						}
					}else

					if (skos11 == 1 && skos33 == 1)
					{
						Ox3 = 2; Oy3 = 2;
						if (sq[Ox3 - 1][Oy3 - 1] != 0)
						{
							moveSI(x, y, Ox2, Oy2);
						}
					}else

					if (skos31 == 1 && skos22 == 1)
					{
						Ox3 = 1; Oy3 = 3;
						if (sq[Ox3 - 1][Oy3 - 1] != 0)
						{
							moveSI(x, y, Ox2, Oy2);
						}
					}else

					if (skos13 == 1 && skos22 == 1)
					{
						Ox3 = 3; Oy3 = 1;
						if (sq[Ox3 - 1][Oy3 - 1] != 0)
						{
							moveSI(x, y, Ox2, Oy2);
						}
					}else

					if (skos31 == 1 && skos13 == 1)
					{
						Ox3 = 2; Oy3 = 2;
						if (sq[Ox3 - 1][Oy3 - 1] != 0)
						{
							moveSI(x, y, Ox2, Oy2);
						}
					}
				}
		}
		Ox3 = *x;
		Oy3 = *y;
	}

	cout << "\n\n\tpolozenie kolejnego punktu na tej planszy komputer uznal za: " << Ox3 << " oraz :" << Oy3 << endl;

}


//sztuczna inteligencja. Bardzo sztuczna.
int SI(int *x, int *y, int *wspplr, int* ptchboard)  //(int ruchSI)
{
	int niezmienionex = 1, niezmienioney = 1;
	int newchboard;
	int checkEmpty;

	board();
	cout << "\n\n\t Komputer nie wykonal jeszce ruchu. chboard== " << *ptchboard <<"  *x= "<<*x<<"  *y= "<<*y<< endl;
	//miejsceakcji(chboard,player);
	//moveSI(x,y);
	//cout << *wspx << *wspy << endl;
	//niezmienionex=*x; niezmienioney=*y;

	//checkboard(*ptchboard, x, y);

	checkEmpty = emptyCheck(x, y, ptchboard);
	cout << "\n\n\t emptyCheck== " << checkEmpty << endl;
	if (checkEmpty == 0)
	{
		do {
			moveSI(x, y, -1, -1);
			niezmienionex = *x; niezmienioney = *y;
			checkboard(*ptchboard, x, y);
		} while (sq[*x - 1][*y - 1] != 0);
	}
	else { logikaSI(x, y, ptchboard); }
	cout << "\n\n\t Komputer przed wpisaniem nowego chboard. chboard== " << *ptchboard << endl;
	cout << "\n\n\t *x== " << *x << " *y== " << *y << *ptchboard << endl;
	cout << "\t niezmienione x==" << niezmienionex << "niezmienione y==" << niezmienioney << endl;


	//cout << *wspx << *wspy;

	//logikaSI();

	makemove(x, y, wspplr);

	newchboard = moveminiboard(niezmienionex, niezmienioney, *ptchboard);
	*ptchboard = newchboard;

	//cout <<niezmienionex << "\t" <<niezmienioney << endl << chboard << "\t" << newchboard;
	//system("pause");
	//checkwin=fcheckwin();
	cout << "\n\n\t Komputer wykonal ruch. chboard== " << *ptchboard << endl;
	system("pause");
	return fcheckwin();

}



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
		//if (player == 0)
		{

			board();
			miejsceakcji(chboard, player);

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

			cout << niezmienionex << "\t" << niezmienioney << endl << chboard << "\t" << newchboard;
			//system("pause");
			checkwin = fcheckwin();
			//system("pause");
		}
		//else
		//{
	//		board();
	//		checkwin = SI(wspx, wspy, wspplr, ptchboard);  board();
	//	}
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
