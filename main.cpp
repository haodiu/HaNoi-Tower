#include<iostream>
#include<graphics.h>
#include<mylib.h>

using namespace std;

const int cao = 15;
const int max_dia = 7;
const int step = 5;
const int DELAY = 20;

int x, y, n, rong;
int demdia[7], vitridia[7], cot[3];

void BaoLoi (char *s){
	gotoxy (10,24);
	cout <<s;
	Sleep(2000);
	gotoxy(10,24);
	clreol();
	gotoxy(x,y);
}

void tieude(){
	char a[100];
	sprintf(a, "DEMO THAP HA NOI WITH C++");
	setcolor(4);
	settextstyle(0, HORIZ_DIR, 2);
	outtextxy(115, 420, a);
	setcolor(8);
	line(100, 445, getmaxx()-100, 445);
}

void thapHaNoi(int n){
	int i;
	for(i = 0; i<3; i++){
		x = 20+i*200;
		y = 280+n*15;
		setfillstyle(SOLID_FILL, BLACK);
		bar(x, y, x+24+max_dia*24, y+7);
	}
	for(i = 0; i < n; i++){
		x = 30+cot[i]*200+(max_dia-1-i)*12;
		y = 280+vitridia[i]*15;
		rong = 24+i*24;
		setfillstyle(SOLID_FILL,5+i);
		bar(x,y,x+rong,y+cao);
	}
}

void move(int sodia, int from, int to){
	int to_x, to_y;
	rong = sodia*24;
	x = 30+(cot[sodia-1]*200)+((max_dia-sodia)*12);
	y = 280+vitridia[sodia-1]*15;
	
	do{
		setfillstyle(SOLID_FILL, 15);
		bar(x, y, x+rong, y+cao);
		y = y-step;
		setfillstyle(SOLID_FILL, 4+sodia);
		bar(x, y, x+rong, y+cao);
		delay(DELAY);
	}while(y>150);

	to_x = 30+to*200 + (max_dia-sodia)*12;
	do{
		setfillstyle(SOLID_FILL, 15);
		bar(x, y, x+rong, y+cao);
		if(to_x < x)	
			x = x-step;
		else	x = x+step;
		setfillstyle(SOLID_FILL, 4+sodia);
		bar(x, y, x+rong, y+cao);
		delay(DELAY);
	}while(x != to_x);
	
	vitridia[sodia-1] = n-1-demdia[to];
	demdia[to]++;
	demdia[from]--;
	cot[sodia-1] = to;
	
	to_y = 280+vitridia[sodia-1]*15;
	do{
		setfillstyle(SOLID_FILL, 15);
		bar(x, y, x+rong, y+cao);
		y = y + step;
		setfillstyle(SOLID_FILL, 4+sodia);
		bar(x, y, x+rong, y+cao);
		delay(DELAY);
	}while(y < to_y);
}

void solveThapHN(int n, int from, int to, int tmp){
	if(n == 1){
		move(1, from, to);
		return;
	}
	solveThapHN(n-1, from, tmp, to);
	move(n, from, to);
	solveThapHN(n-1, tmp, to, from);
}

int main(){
	char a[30];
	cout<<"Hay nhap so dia: ( 0 < n < " <<max_dia+1<<"): ";
	x=wherex() , y=wherey();
	do{
		clreol();
		cin>>n;
		if(n<1 || n>max_dia)	BaoLoi("So dia khong nam trong gioi han cho phep!");
	}while(n<1 || n>max_dia);
	
	int gd = DETECT, gmode;
	initgraph(&gd, &gmode, "");
	setbkcolor(15);
	cleardevice();
	demdia[0] = n;
	demdia[1] = 0;
	demdia[2] = 0;
	for(int i=0; i<n; i++){
		vitridia[i] = i;
	}
	for(int i = 3; i > 0; i--){
		thapHaNoi(n);
		sprintf(a, "Start in %d second!", i);
		setcolor(12);
		settextstyle(0, HORIZ_DIR, 3);
		rectangle(60, 80, 565, 145);
		outtextxy(100, 100, a);
		
		tieude();
		delay(1000);
		cleardevice();
	}
	tieude();
	thapHaNoi(n);
	solveThapHN(n,0,2,1);
	getch();
	closegraph();
	return 0;
}
