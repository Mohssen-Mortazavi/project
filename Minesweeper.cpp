#include<iostream>
#include<time.h>
#include<conio.h>
#include<windows.h>
//#include<cstdlib>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int Bombs=50,Founded_Bombs=0;
const int width = 25,height = 20;
char table[height+2][width+2],table2[height+2][width+2];
void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console,CursorPosition);	
}

void set_color_text(int color)
{
	SetConsoleTextAttribute(console , color);
}

void Draw()
{
	system("cls");
	for(int i=0;i<width;i++)
		cout<<"------";
	cout<<"-\n";
	
		for(int i=0;i<height;i++)
		{cout<<"| ";
		for(int j=0;j<width;j++)
			{
			cout.width(3);
			cout.fill('.');
			cout<<(i*width)+j+1<<" | ";
			}
			cout<<endl;
			for(int k=0;k<width;k++)
				cout<<"------";
			cout<<"-\n";
			}

}

void Find_Bomb(int i,int j)
{
	int num=0;
	
	for(int x=i-1;x<=i+1;x++)
		for(int y=j-1;y<=j+1;y++)
			if(table[x][y]=='*')
				num++;
	if(num != 0)
		{
		table2[i][j]=char(48+num);
		gotoxy(6*j-4,2*i-1);
		set_color_text(9);
		cout<<' '<<num<<' ';
		set_color_text(7);}
	else
		{table2[i][j]=' ';
		gotoxy(6*j-4,2*i-1);
		cout<<"   ";
		 for(int x=-1;x<=1;x++)
		 	for (int y=-1;y<=1;y++)
		 		if((x + y == -1 || x + y == 1) && (table2[i+x][j+y] =='#'))
		 		 	Find_Bomb(i+x,j+y);
		 for(int x=-1;x<=1;x+=2)
		 	for (int y=-1;y<=1;y+=2)
		 		if (table2[i+x][j+y] =='#')
		 			Find_Bomb(i+x,j+y);
	
		}		
}

int main()
{
	bool playing = true;
	srand(time(0));
	while(playing)
	{
	Founded_Bombs=0;
	
	for(int i=0;i<height+2;i++)
		for(int j=0;j<width+2;j++)
			{
			table[i][j]=' ';
			table2[i][j]=' ';}
			
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)
			table2[i+1][j+1]='#';		 
	
	for(int k=0;k<Bombs;k++)
		{
		int i =rand() % height+1;
		int j =rand() % width+1;
		while(table[i][j] != ' ')
			{
				i =rand() % height +1;
				j =rand() % width +1;
			}
		table[i][j]='*';
		}
	
	Draw();
	
	cout<<"you have to find "<<Bombs<<" bombs\n\n";
	
	while(1)
	{	int i,j;
		char x;
		cout<<"do you wanna put flag ?(y or n):";
		cin>>x;
		
		if(x == 'n')
		{
		
			cout<<"enter position number :";
			cin>>i;
			i--;
			j = i % width + 1;
			i = i / width + 1;
			
			
			
			if(table[i][j] == '*')
				{
				cout<<"you lose\ndo you wanna play again?(y or n):";
				cin>>x;
				if(x =='y')
					break;
				else
					{
					playing =false;
					break;
					}
				}		
			Find_Bomb(i,j);}
		else
			{
			cout<<"enter position number for flag:";
			cin>>i;
			i--;
			j = i % width + 1;
			i = i / width + 1;
			if( table2[i][j]=='#')
				{gotoxy(6*j-4,2*i-1);
				 set_color_text(4);
				cout<<" F ";
				set_color_text(7);
				table2[i][j]='F';
				if(table[i][j]=='*')
					Founded_Bombs++;
				}
				if(Founded_Bombs == Bombs)
			 		{gotoxy(0,height*2+5);
				cout<<"you Win\ndo you wanna play again?(y or n):";
				cin>>x;
				if(x =='y')
					break;
				else
					{
					playing =false;
					break;
					}
				}	
			 	
			}
		
		gotoxy(30,height*2+3);
		cout<<"     \n                                      ";
		gotoxy(0,height*2+3);
		}
	}
}
