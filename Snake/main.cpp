#include <iostream>
#include "Header.h"
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <MMsystem.h>

#define MAX 100

using namespace std;

int sl = 5;
void kiemtrahuong(int &check ,int &x , int &y) {
	
	//kiemtrahuong
	if (check == 0 ) {
		y++;
		if (y > 26)
			y = 2;
	}
	else if (check == 1) {
		y--;
		if (y < 2)
			y = 26;
	}
	else if (check == 2) {
		x--;
		if (x < 5)
			x = 111;
		
	}
	else if (check == 3) {
		x++;
		if (x > 111)
			x = 5;
	}
	
	
	
}
void vetuong() {
	textcolor(112);
	for (int i = 5; i <= 111; i++) {
		for (int j = 2; j <= 26; j++) {
			
			gotoXY(i, j);
			cout << " ";
			
		}
	}
}
void taoran(int toadox[], int toadoy[]) {
	int x = 50, y = 13;
	for (int i = 0; i < sl; i++) {
		toadox[i] = x;
		toadoy[i] = y;
		x--;
	}
}
void ve_ran(int toadox[] , int toadoy[]) {
	gotoXY(toadox[0], toadoy[0]);
	SetColor(2);
	cout << (char)258;
	for (int i = 1; i < sl; i++) {
		gotoXY(toadox[i], toadoy[i]);
		if (i % 2 != 0)
			SetColor(16);
		else
			SetColor(2);

		cout << (char)260;
	}
}
void them(int a[], int x) {
	for (int i = sl; i > 0; i--) {
		a[i] = a[i - 1];
	}
	a[0] = x;
	sl++;
}
void xoa(int a[], int vt) {
	for (int i = vt; i <sl ; i++) {
		a[i] = a[i + 1];
	}
	sl--;
}
bool kt_dequa(int xqua, int yqua, int toadox[], int toadoy[]) {
	for (int i = 0; i < sl; i++) {
		if (xqua == toadox[i] && yqua == toadoy[i]) {
			return true;
		}
	}
	return false;
}
bool kt_anqua(int xqua, int yqua, int x0, int y0) {
	if (xqua == x0 && yqua == y0) {
		return true;

	}
	return false;

}
void taoqua(int& xqua, int& yqua, int toadox[], int toadoy[]) {
	do {
		xqua = rand() % (110 - 5 + 1) + 5;
		yqua = rand() % (25 - 2 + 1) + 2;

	} while (kt_dequa(xqua, yqua, toadox, toadoy) == true);
	int i = rand() % (15 - 1 + 1) + 1;
	SetColor(12);
	gotoXY(xqua, yqua);
	cout << (char)3;
}
void xulyran(int toadox[], int toadoy[], int x, int y,int &xqua,int &yqua) {
	them(toadoy, y);
	them(toadox, x);

	if (kt_anqua(xqua, yqua, toadox[0], toadoy[0]) == false) {
		xoa(toadox, sl - 1);
		xoa(toadoy, sl - 1);
	}
	else {
		sl--;
		taoqua(xqua, yqua, toadox, toadoy);
	}
	ve_ran(toadox, toadoy);
}
void xoadulieucu(int toadox[], int toadoy[]) {

	for (int i = 0; i < sl; i++) {
		gotoXY(toadox[i], toadoy[i]);
		cout << " ";
	}
}
bool ktchamtuong(int x, int y) {
	if (y == 1 && (x >= 5 && x < 111)) {
		return true;
	}
	else if (y == 26 && (x >= 5 && x < 111))
		return true;
	else if (x == 5 && (y >= 1 && x <= 26))
		return true;
	else if (x == 110 && (y >= 1 && x <= 26))
		return true;
	else return false;
}
bool ktchamduoi(int toadox[], int toadoy[]) {
	for (int i = 1; i < sl; i++) {
		if ((toadox[0] == toadox[i]) && (toadoy[0] == toadoy[i])) {
			return true;
		}
	}
	return false;
}
bool kt_ran(int toadox[], int toadoy[]) {


	bool kt1 = ktchamtuong(toadox[0], toadoy[0]);
	bool kt2 = ktchamduoi(toadox, toadoy);
	if (kt1 == true || kt2 == true) {
		return true;
	}
	return false;
}
void chedo1() {
	gotoXY(50, 0);
	SetColor(10);
	cout << "Che do dung tuong - press 0 to back" << endl;

	bool gameover = false;
	int toadox[MAX], toadoy[MAX];
	int x = 50, y = 13;
	int xcu = x;
	int ycu = y;
	int check = 0;
	vetuong();
	taoran(toadox, toadoy);
	ve_ran(toadox, toadoy);
	srand(time_t(NULL));
	int xqua = 0, yqua = 0;
	taoqua(xqua, yqua, toadox, toadoy);

	while (gameover == false) {
		gotoXY(90, 0);
		textcolor(1);
		SetColor(14);
		cout << "SO DIEM HIEN TAI :" << sl*10;
		textcolor(112);
		xoadulieucu(toadox, toadoy);

		if (_kbhit()) {
			char kitu = _getch();
			if (kitu == '0') {
				gameover = true;
				continue;
			}
			else if  (kitu == -32) {
				char kitu = _getch();
				if (kitu == 72 && check != 0)
				{
					check = 1;
				}
				else if (kitu == 80 && check != 1) {
					check = 0;
				}
				else if (kitu == 75 && check != 3) {
					check = 2;
				}
				else if (kitu == 77 && check != 2) {
					check = 3;
				}
			}
		}
		kiemtrahuong(check, x, y);
		xulyran(toadox, toadoy, x, y, xqua, yqua);

		gameover = kt_ran(toadox, toadoy);

		Sleep(200);
		ShowCur(0);

	}

}
void chedo2() {
	gotoXY(40, 0);
	SetColor(10);
	cout << "Che do xuyen tuong va tang toc - press 0 to back" << endl;

	bool gameover = false;
	int toadox[MAX], toadoy[MAX];
	int x = 50, y = 13;
	int xcu = x;
	int ycu = y;
	int check = 0;
	vetuong();
	taoran(toadox, toadoy);
	ve_ran(toadox, toadoy);
	srand(time_t(NULL));
	int xqua = 0, yqua = 0;
	taoqua(xqua, yqua, toadox, toadoy);

	while (gameover == false) {
		gotoXY(90, 0);
		textcolor(1);
		SetColor(14);
		cout << "SO DIEM HIEN TAI :" << sl*10;
		textcolor(112);
		xoadulieucu(toadox, toadoy);

		if (_kbhit()) {
			char kitu = _getch();
			if (kitu == '0') {
				gameover = true;
				continue;
			}
			else if (kitu == -32) {
				char kitu = _getch();
				if (kitu == 72 && check != 0)
				{
					check = 1;
				}
				else if (kitu == 80 && check != 1) {
					check = 0;
				}
				else if (kitu == 75 && check != 3) {
					check = 2;
				}
				else if (kitu == 77 && check != 2) {
					check = 3;
				}
			}
		}
		kiemtrahuong(check, x, y);
		xulyran(toadox, toadoy, x, y, xqua, yqua);
		gameover = ktchamduoi(toadox, toadoy);
		Sleep(1000/sl);
		ShowCur(0);

	}

}
void box(int x, int y, int w, int h , int b_color, string nd , int canle) {
	textcolor(b_color);
	gotoXY(x + canle, y + 1);
	cout << nd;
	textcolor(1);
	SetColor(11);
	for (int i = x; i <= x+ w; i++) {
		gotoXY(i, y);
		cout << "+";
		gotoXY(i, y + h);
		cout << "+";
	}
	
}
void boxs() {
	box(75, 1, 30, 2, 48, "         M  E  N  U          ",1);
	box(80, 3, 20, 2, 96, "CHE DO 1",8);
	box(80, 5, 20, 2, 1, "CHE DO 2",8);
	box(80, 7, 20, 2, 1, "THOAT",8);
}
void thanh_sang(int x, int y, int w, int h, int b_color, string nd) {
	textcolor(b_color);
	for (int j = y + 1; j < y + h; j++) {
		for (int i = x; i < x + w; i++) {
			gotoXY(i, j);
			cout << "  ";
		}
	}
	gotoXY(x + 8, y + 1);
	cout << nd;
	textcolor(1);
}
void snake_art() {
	ifstream docfile;
	docfile.open("snake.txt", ios_base::in);
	string snakeart;
	while (getline(docfile, snakeart)) {
		cout << snakeart << endl;
	}
	docfile.close();
}

int main()	 {
	
	
	ShowCur(0);
	int x = 80, y = 3;
	int h = 2, w = 20;
	string nd[3] = { "CHE DO 1","CHE DO 2","THOAT" };
	bool menu = true;

	while (menu == true) {
		bool i = PlaySound(TEXT("NEWDAY.wav"), NULL, SND_ASYNC);
		snake_art();
		boxs();
		int xp = x, yp = y;
		bool kt = true;
		int xcu = xp, ycu = y;
		int chedo = 1;
		int chedocu = 1;
		bool ketthucgame = true;
		while (ketthucgame == true) {
			chedo = (yp - 1) / 2;
			chedocu = (ycu - 1) / 2;
			if (kt == true) {

				gotoXY(xcu, ycu);
				thanh_sang(xcu, ycu, w, h, 1, nd[chedocu - 1]);
				xcu = xp; ycu = yp;
				thanh_sang(xp, yp, 20, 2, 96, nd[chedo - 1]);
				kt = false;

			}

			if (_kbhit()) {
				char t = _getch();
				if (t == 13) {
					switch (chedo) {
					case 1:
						system("cls");
						chedo1();
						system("cls");
						system("color 06");
						gotoXY(50, 12);
						cout << "GAME OVER ! ";
						for (int i = 5; i > 0; i--) {
							gotoXY(50, 15);
							cout << "QUAY VE MENU SAU " << i << " GIAY !";
							Sleep(1200);
						}
						system("cls");
						ketthucgame = false;
						system("color 07");
						

						break;
					case 2:
						system("cls");
						chedo2();
						
						system("cls");
						system("color 06");
						gotoXY(50, 12);
						cout << "GAME OVER ! ";
						for (int i = 5; i > 0; i--) {
							gotoXY(50, 15);
							cout << "QUAY VE MENU SAU " << i << " GIAY !";
							Sleep(1200);
						}
						system("cls");
						ketthucgame = false;
						system("color 07");


						break;
					case 3:
						system("cls");
						ketthucgame = false;
						menu = false;
						break;
					}
				}
				else if (t == -32) {
					kt = true;
					t = _getch();

					if (t == 80) {
						yp += 2;
						if (yp > 7) {
							yp = 3;
						}

					}
				}
			}


		}
		
	}
	    system("color 06");
	    gotoXY(50, 14);
		cout << "DA THOAT TRO CHOI !";
		gotoXY(50, 15);
		cout << "SEE YOU AGAIN :>";
	_getch();
	//bool i = PlaySound(TEXT("C:\\Users\\hp\\Desktop\\NEWDAY.wav"), NULL, SND_SYNC);
	return 0;
	system("pause");
}