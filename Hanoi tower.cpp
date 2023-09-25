#include<iostream>
#include<vector>
using namespace std;


vector <vector<int> > Data (3);


void draw ()
{
	for(int i=0;i<3;i++)
		{for(int j=0;j < Data[i].size();j++)
			cout<<Data[i][j]<<"\t";
			cout<<endl;
		}
		
	cout<<"------------------------"<<endl;
}
	
	
void Hanoi (int nr,int &s,int &d,int &h)
	{
	if(nr<2)
		{
		Data[s].pop_back();
		Data[d].push_back(1);
		
		return;
		}
	
	
	
	Hanoi(nr-1,s,h,d);

	draw();
		
	Data[s].pop_back();
	Data[d].push_back(nr);
	
	draw();
	
	Hanoi(nr-1,h,d,s);
	
	}


int main()
{
	int nr,a=0,b=1,c=2;
	cout<<"enter the disk number:";
	cin>>nr;
	
	while(nr<1)
	{cout<<"error,please enter another number:";
	 cin>>nr;
		}	
	for(int i=0;i<nr;i++)
		Data[0].push_back(nr-i);
		
	draw();

	Hanoi(nr,a,b,c);

	draw();
	
	return 0;
}
