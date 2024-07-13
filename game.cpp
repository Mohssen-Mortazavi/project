#include<iostream>
#include <string>
#include<windows.h>
#include <time.h>
#include <math.h>




using namespace std;


int life =3,key=0,data[12][2],R=0,dead[11];
void DATA ()
{
//player data
data[11][0]=5;data[11][1]=55;
//enemy data
data[0][0]=15;data[0][1]=4;
data[1][0]=2;data[1][1]=17;
data[2][0]=30;data[2][1]=7;
data[3][0]=7;data[3][1]=17;
data[4][0]=25;data[4][1]=55;
data[5][0]=20;data[5][1]=70;
data[6][0]=27;data[6][1]=40;
data[7][0]=16;data[7][1]=42;
data[8][0]=18;data[8][1]=55;
data[9][0]=25;data[9][1]=17;
data[10][0]=20;data[10][1]=3;

	for(int i=0;i<11;i++)
		dead[i]=1;
}
char world[40][100],HUD[100];


//  Q ACTION AND ENEMY MOVEMENT


void f_one ()
{	
	for (int x=25;x<85;x++)
		world[34][x]='-';
	for (int x=0;x<25;x++)
		world[10][x]='-';
	for (int x=0;x<100;x++)
		world[0][x]='-';
	for (int x=0;x<100;x++)
		world[39][x]='-';
	
	for (int y=0;y<35;y++)
		world[y][84]='|';
	for (int y=0;y<40;y++)
		world[y][25]='|';
		
	for (int y=0;y<40;y++)
		world[y][0]='|';
	for (int y=0;y<40;y++)
		world[y][99]='|';	
		
		world [4][92]='H';
		world[4][25]=' ';
		world[5][25]=' ';
		world[data[11][0]][data[11][1]]='A';
		world[16][25]='#';
		world[34][45]='#';
		world[3][4]='P';
		world[6][4]='G';
		
		for (int i=0;i<11;i++)
			world[data[i][0]][data[i][1]]='*';
			
			
		world[35][7]='P';
		world[35][17]='G';
		world[38][12]='G';
		
}



void draw ()
{
 	system("cls");
 	
 	HUD[24]= char(R % 3+ 48) ;
 	
 	for (int i = 0; i < 100; i++)
 		cout<<HUD[i];
 	cout<<endl;
 	for (int i = 0; i < 100; i++)
 		cout<<'=';
 	cout<<endl;
	for (int y = 0; y < 40; y++) {
		for (int x = 0; x < 100; x++)
			cout<<world[y][x] ;
		cout<<endl;
	}	
	
	
}

void lives(int x)
{
	life+=x;
	
	if (x>0)
		HUD[104-life*5]='G';
	else if (x<0)
		HUD[99-life*5]=' ';
	
}

void keys (int x)
{
 	key+=x;
 	if (x>0)
		HUD[(key-1)*5]='P';	
	else if (x<0)
		HUD[(key)*5]=' ';
 		
 	
}

void move_p(char w)
{
	if (w=='a'&& data[11][1] > 0 && world[data[11][0]][(data[11][1])-1]!='|' && world[data[11][0]][(data[11][1])-1]!='-' && world[data[11][0]][(data[11][1])-1]!='#' && world[data[11][0]][data[11][1]-1]!='*')
		{
		if(world[data[11][0]][data[11][1]-1]=='G')
			lives(1);
		else if((world[data[11][0]][data[11][1]-1]=='P'))
			keys(1);
		world[data[11][0]][data[11][1]]=' ';
		world[data[11][0]][data[11][1]-1]='A';
		data[11][1]--;
		 			
		}
	if (w=='d'&& data[11][1] < 99 && world[data[11][0]][data[11][1]+1]!='|' && world[data[11][0]][data[11][1]+1]!='-' && world[data[11][0]][data[11][1]+1]!='#' && world[data[11][0]][data[11][1]+1]!='*')
		{
		if(world[data[11][0]][data[11][1]+1]=='G')
			lives(1);
		else if((world[data[11][0]][data[11][1]+1]=='P'))
			keys(1);
		world[data[11][0]][data[11][1]]=' ';
		world[data[11][0]][data[11][1]+1]='A';
		data[11][1]++;
		}	
	if (w=='w'&& data[11][0] > 0 && world[data[11][0]-1][data[11][1]]!='|' && world[data[11][0]-1][data[11][1]]!='-' && world[data[11][0]-1][data[11][1]]!='#' && world[data[11][0]-1][data[11][1]]!='*')
		{
		if(world[data[11][0]-1][data[11][1]]=='G')
			lives(1);
		else if((world[data[11][0]-1][data[11][1]]=='P'))
			keys(1);
		world[data[11][0]][data[11][1]]=' ';
		world[data[11][0]-1][data[11][1]]='A';
		data[11][0]--;
		}
	if (w=='s'&& data[11][0] < 39 && world[data[11][0]+1][data[11][1]]!='|' && world[data[11][0]+1][data[11][1]]!='-' && world[data[11][0]+1][data[11][1]]!='#' && world[data[11][0]+1][data[11][1]]!='*')
		{
		if(world[data[11][0]+1][data[11][1]]=='G')
			lives(1);
		else if((world[data[11][0]+1][data[11][1]]=='P'))
			keys(1);
		world[data[11][0]][data[11][1]]=' ';
		world[data[11][0]+1][data[11][1]]='A';
		data[11][0]++;
		}		
}

void Enemy_move()
{	
	int s = rand() % 8, Mx , My ;
	bool R=true;
	for (int i=0;i<11;i++)
	   {R=true;
	    if (dead[i]==1){
		
			if(abs(data[i][0]-data[11][0])<8 && abs(data[i][1]-data[11][1])<8)
			   {
				
				if ((data[11][0]-data[i][0])==0)
					Mx=0;
				else if ((data[11][0]-data[i][0])<0)
					Mx=-1;
				else if ((data[11][0]-data[i][0])>0)
					Mx=1;
				
				if ((data[11][1]-data[i][1])==0)
					My=0;
				else if ((data[11][1]-data[i][1])<0)
					My=-1;
				else if ((data[11][1]-data[i][1])>0)
					My=1;
				
				if(world[data[i][0]+Mx][data[i][1]+ My]==' ')
					{
					world[data[i][0]+Mx][data[i][1]+ My]='*';
					world[data[i][0]][data[i][1]]=' ';
					data[i][0]+=Mx;
					data[i][1]+=My;
					}
					R=false;
					}	
	
			else if (R)
			   { 
			    s = rand() % 8;
			    
			   	if(s==0 &&  world[data[i][0]+1][data[i][1]+1]==' ' )
			   			{
							world[data[i][0]+1][data[i][1]+ 1]='*';
							world[data[i][0]][data[i][1]]=' ';
						   
							data[i][0]++;data[i][1]++;
						   }
			   			
			   	else if(s==1 &&  world[data[i][0]+1][data[i][1]-1]==' ' )
			   			{	world[data[i][0]+1][data[i][1]- 1]='*';
							world[data[i][0]][data[i][1]]=' ';
							data[i][0]++;data[i][1]--;}
			   			
			   	else if(s==2 &&  world[data[i][0]-1][data[i][1]+1]==' ' )
			   			{	world[data[i][0]-1][data[i][1]+ 1]='*';
							world[data[i][0]][data[i][1]]=' ';
						   data[i][0]--;data[i][1]++;}
			   			
			   	else if(s==3 &&  world[data[i][0]-1][data[i][1]-1]==' ' )
			   			{	world[data[i][0]-1][data[i][1]- 1]='*';
							world[data[i][0]][data[i][1]]=' ';
						   data[i][0]--;data[i][1]--;}
			   	
				else if(s==4 &&  world[data[i][0]+1][data[i][1]]==' ' )
			   			{	world[data[i][0]+1][data[i][1]]='*';
							world[data[i][0]][data[i][1]]=' ';
						   data[i][0]++;}
			   			
			   	else if(s==5 &&  world[data[i][0]-1][data[i][1]]==' ' )
			   			{	world[data[i][0]-1][data[i][1]]='*';
							world[data[i][0]][data[i][1]]=' ';
						   data[i][0]--;}
			   			
			   	else if(s==6 &&  world[data[i][0]][data[i][1]+1]==' ' )
			   			{	world[data[i][0]][data[i][1]+ 1]='*';
							world[data[i][0]][data[i][1]]=' ';
						   data[i][1]++;}
			   			
			   	else if(s==7 &&  world[data[i][0]][data[i][1]-1]==' ' )
			   			{	world[data[i][0]][data[i][1]- 1]='*';
							world[data[i][0]][data[i][1]]=' ';
						   data[i][1]--;}
			   		
				   }
			}
		}		
			
	
}

void Attack()	
{
	if(R%3 == 0)
		{
		for(int i=-2;i<=2;i++)
			for (int j=-2;j<=2;j++)
				if(abs(i)+abs(j)<=3)
					if(world[data[11][0]+i][data[11][1]+j]=='*')
						for (int k=0;k<11;k++)
							if(data[k][0] == data[11][0]+i && data[k][1] == data[11][1]+j )	
								{world[data[k][0]][data[k][1]]=' ';
								dead[k]=0;
								break;
								}
		}
	if(R % 3 == 1)
		{
		char D;
		cin>>D;
		if (D == 'a')
			{
			 if(world[data[11][0]][data[11][1]-1]=='*')
				for (int k=0;k<11;k++)
					if(data[k][0] == data[11][0] && data[k][1] == data[11][1]-1 )	
						{world[data[k][0]][data[k][1]]=' ';
						dead[k]=0;
						break;
						}
			 for(int i=-1;i<=1;i++)
			 		if(world[data[11][0]+i][data[11][1]-2] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] +i && data[k][1] == data[11][1]-2 )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
			for(int i=-2;i<=2;i++)
				if(world[data[11][0]+i][data[11][1]-3] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] +i && data[k][1] == data[11][1]-3 )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
			}
		else if (D == 'd')
			{
			 if(world[data[11][0]][data[11][1]+1]=='*')
				for (int k=0;k<11;k++)
					if(data[k][0] == data[11][0] && data[k][1] == data[11][1]+1 )	
						{world[data[k][0]][data[k][1]]=' ';
						dead[k]=0;
						break;
						}
			 for(int i=-1;i<=1;i++)
			 	if(world[data[11][0]+i][data[11][1]+2] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] +i && data[k][1] == data[11][1]+2 )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
			for(int i=-2;i<=2;i++)
				if(world[data[11][0]+i][data[11][1]+3] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] +i && data[k][1] == data[11][1]+3 )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
			}
		else if (D == 'w')
			{
			 if(world[data[11][0]-1][data[11][1]]=='*')
				for (int k=0;k<11;k++)
					if(data[k][0] == data[11][0]-1 && data[k][1] == data[11][1] )	
						{world[data[k][0]][data[k][1]]=' ';
						dead[k]=0;
						break;
						}
			 for(int i=-1;i<=1;i++)
			 	if(world[data[11][0]-2][data[11][1]+i] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] -2 && data[k][1] == data[11][1]+i )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
			for(int i=-2;i<=2;i++)
				if(world[data[11][0]-3][data[11][1]+i] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] -3 && data[k][1] == data[11][1]+i )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
			}
		else if (D == 's')
			{
			 if(world[data[11][0]+1][data[11][1]]=='*')
				for (int k=0;k<11;k++)
					if(data[k][0] == data[11][0]+1 && data[k][1] == data[11][1] )	
						{world[data[k][0]][data[k][1]]=' ';
						dead[k]=0;
						break;
						}
			 for(int i=-1;i<=1;i++)
			 	if(world[data[11][0]+2][data[11][1]+i] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] +2 && data[k][1] == data[11][1]+i )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
				for(int i=-2;i<=2;i++)
				if(world[data[11][0]+3][data[11][1]+i] == '*')
					for (int k=0;k<11;k++)
						if(data[k][0] == data[11][0] +3 && data[k][1] == data[11][1]+i )	
							{world[data[k][0]][data[k][1]]=' ';
							dead[k]=0;
							break;
							}
			}
		
	}

	if(R % 3 == 2)
		{
		char D;
		cin>>D;	
		if(D == 'a')
			for(int i=1;i<=7;i++)
				if (world[data[11][0]][data[11][1]-i] == '*')
					for (int k=0;k<11;k++)
							if(data[k][0] == data[11][0] && data[k][1] == data[11][1]-i )	
								{world[data[k][0]][data[k][1]]=' ';
								dead[k]=0;
								break;
								}
		else if(D == 'd')
			for(int i=1;i<=7;i++)
				if (world[data[11][0]][data[11][1]+i] == '*')
					for (int k=0;k<11;k++)
							if(data[k][0] == data[11][0] && data[k][1] == data[11][1]+i )	
								{world[data[k][0]][data[k][1]]=' ';
								dead[k]=0;
								break;
								}
		else if(D == 'w')
			for(int i=1;i<=7;i++)
				if (world[data[11][0]-i][data[11][1]] == '*')
					for (int k=0;k<11;k++)
							if(data[k][0] == data[11][0]-i && data[k][1] == data[11][1] )	
								{world[data[k][0]][data[k][1]]=' ';
								dead[k]=0;
								break;
								}
		else if(D == 's')
			for(int i=1;i<=7;i++)
				if (world[data[11][0]+i][data[11][1]] == '*')
					for (int k=0;k<11;k++)
							if(data[k][0] == data[11][0]+i && data[k][1] == data[11][1] )	
								{world[data[k][0]][data[k][1]]=' ';
								dead[k]=0;
								break;
								}
								
		}
		
}

void Any_Damage()
{
	for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
			if(world[data[11][0]+i][data[11][1]+j] == '*')
				{
				 world[data[11][0]][data[11][1]]=' ';
				 data[11][0]+=i*-2;
				 data[11][1]+=j*-2;
				 world[data[11][0]][data[11][1]]='A';
				 lives(-1);
				}
	
}

void lock()
{int locks=0;
	if (key!=0)
		for (int i=-1;i<2;i++)
			for (int j=-1;j<2;j++)
				if(world[data[11][0]+i][data[11][1]+j]=='#')
					locks++;
					
	if(locks==1)
		for (int i=-1;i<2;i++)
			for (int j=-1;j<2;j++)
				if(world[data[11][0]+i][data[11][1]+j]=='#')
					{
					 world[data[11][0]+i][data[11][1]+j]=' ';
					 keys(-1);
					 }
		
		
}
int main()
{ char inp='y';
 srand(time(0));
 	
 	 for (int y = 0; y < 100; y++) 
       {
		HUD[y]=' ';
  		for (int x = 0; x < 40; x++)
			world[x][y]=' ';
		}
			
 	
	HUD[99]='G';
	HUD[94]='G';
	HUD[89]='G';
	DATA();
	f_one();
	lives(0);
	keys(0);
			
	while(inp!='h')
	   {
	   	Enemy_move();
	   	draw();
	   	
	   	//usleep(10);
		cin>>inp;
	    if (inp == 'w' || inp == 'a' || inp == 's' || inp == 'd')
			move_p(inp);
		else if (inp == 'e')
			lock();
		else if (inp == 'r')
			R++;
		else if (inp == 'q')
			Attack();
		Any_Damage();
		if(life==0)
			{inp='h';
			 cout<<"GAME OVER";
			}
	   }
	
  


}
