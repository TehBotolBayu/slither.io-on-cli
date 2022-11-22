#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; 
COORD coordBufSize;

void gotoXY(int x, int y)
{
	CursorPosition.X = x; 
	CursorPosition.Y = y; 
	SetConsoleCursorPosition(console,CursorPosition); 
}

char get(int x, int y){
	CHAR_INFO ci;
	COORD xy = {0, 0};
	coordBufSize.X = 1;
	coordBufSize.Y = 1;
	SMALL_RECT rect = {x, y, x, y};
	return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect)
		? ci.Char.AsciiChar
		: '0';
}

char a='<';
char bar=219;
int point, x, y,  n=1, lv = 800, tail;
bool running = true;
string st = "lef";

void food(){
	while(true){
		srand(time(0));
		int p, q;
		p = rand() % 49 + 1;
		q = rand() % 19 + 1;
		if(get(p, q) == bar || get(p, q)=='<' || get(p, q)=='>' || get(p, q)=='^' || get(p, q)=='v'){
			continue;
		}
		gotoXY(p, q); cout<<'X';
		break;
	}
	
}


void menu();

void end();


struct BODY{
	int x;
	int y;
};

BODY body[100];

void move(string s){
	
	
	if (s == "up"){
		y--;
		a='^';
	}	
	else if(s == "down"){
		y++;
		a='v';
	}	
	else if(s == "rig"){
		x++;
		a='>';
	}	
	else if(s == "lef"){
		x--;
		a='<';
	}
	else{
		return;
	}
	
	gotoXY(body[tail].x, body[tail].y); cout << " "; 
		
	if(get(x, y)=='X'){
		point+=850 - lv;
		tail++;
		gotoXY(2, 21); cout << "POINT: " << point;
		food();
	}	
	
	if(get(x, y)==bar || get(x, y)=='^' || get(x, y)=='v' || get(x, y)=='>' || get(x, y)=='<' ){
		end();
	}
	
	gotoXY(x,y); cout << a;
	
	for(int i=tail; i-1>=0; i--){
		body[i].x=body[i-1].x;
		body[i].y=body[i-1].y;
	}
	//gotoXY(body[tail].x, body[tail].y); cout << bar; 
	body[0] = {x, y};
	
	
	
	gotoXY(50, 21);
}

void level();

void menu(){
	int pil = 1, item = 0;
	char row = 16;
	while(1){
	gotoXY(2, 1);cout << "MULAI";
	gotoXY(2, 2);cout << "LEVEL";
	gotoXY(2, 3);cout << "REKOR";
	gotoXY(2, 4);cout << "KELUAR";
	
	system("pause>nul");
	if(GetAsyncKeyState(VK_UP) && pil > 1){
		gotoXY(0, pil); cout << " ";
		pil--;
		item--;
		gotoXY(0, pil); cout << row;
		continue;
	}
	if(GetAsyncKeyState(VK_DOWN) && pil < 4){
		gotoXY(0, pil); cout << " ";
		pil++;
		item++;
		gotoXY(0, pil); cout << row;
		continue;
	}
	if(GetAsyncKeyState(VK_RETURN) & 0x8000){
		switch(item){
			case 0:
				system("cls");
				return;
			case 1:
				system("cls");
				level();
				continue;
			case 2:
				system("cls");
				cout<<"Belum dibikin";
				//rekor();
			case 3:
				exit(1);
			}
		}
	}
}

void level(){
	while(1){
		gotoXY(9, 2); cout << "LEVEL";
		gotoXY(4, 4); cout << string(n, bar);
		system("pause>nul");
		if(GetAsyncKeyState(VK_RIGHT) && n<=15){
			lv-=50;
			n++;
		}
		if(GetAsyncKeyState(VK_LEFT) & n>=1){
			lv+=50;
			gotoXY(n+4, 4); cout << " ";
			n--;
		}
		if(GetAsyncKeyState(VK_RETURN) & 0x8000){
			system("cls");
			return;
		}
	}
}
	

int main(){
	tail = 10;
	body[0].x = x; 
	body[0].y = y;
	
	menu();
	
	point = 0;
	x = 40; y = 10;
	//gotoXY(x, y); cout<<a;
	food();
	gotoXY(2, 21); cout << "POINT: " << point;
		
		while(running){
			gotoXY(0, 0); cout<<string(50, bar);
			
			for(int i = 0; i<20; i++){
				gotoXY(0, i); cout << bar;
				gotoXY(50, i); cout << bar;
			}
			gotoXY(0, 20); cout<<string(50, bar);
			
			move(st);
			Sleep(lv);
			
			if(GetAsyncKeyState(VK_UP) && st != "down"){
				st = "up";
				continue;
			}
			if(GetAsyncKeyState(VK_DOWN) && st != "up"){
				st = "down";
				continue;
			}
			if(GetAsyncKeyState(VK_RIGHT) && st != "lef"){
				st = "rig";
				continue;
			}
			if(GetAsyncKeyState(VK_LEFT) && st != "rig"){
				st = "lef";
				continue;
			}			
			
			
	}
}

void end(){
	gotoXY(15, 23);cout << "YOU ARE DEAD!"<<endl<<"PRESS ENTER TO EXIT";
	while(true){
		if(GetAsyncKeyState(VK_RETURN) & 0x8000){
			system("cls");
			main();
		}
	}
}	



