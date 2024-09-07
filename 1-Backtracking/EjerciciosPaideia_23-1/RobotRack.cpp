#include <iostream>
#define MAX 10
using namespace std;
int y=0,x=0;
int solu[MAX];

int hallarpeso(int ind,int n,int peso,int paq[],int rack[]){
	
	if(ind==n || peso<0)
		return 0;
	if(paq[ind]==peso){
		solu[y] = paq[ind];
		rack[ind] = 1;
		for(int i=0;i<=y;i++)
			cout << solu[i]<<" ";
		cout << endl;	
		for(int i=0;i<n;i++){
			if(rack[i]){
				if(i%4==0)
					cout << " IA"<< (i/4)+1;
				if(i%4==1)
					cout << " IB"<< (i/4)+1;
				if(i%4==2)
					cout << " DA"<< (i/4)+1;
				if(i%4==3)
					cout << " DB"<< (i/4)+1;				
			}			
		}
		cout << endl;		
		x=1;
		//return 1; quiero todas las soluciones
	}	
	solu[y]=paq[ind];
	rack[ind] = 1;
	y++;
	if(hallarpeso(ind+1,n,peso-paq[ind],paq,rack))	
		return 1;
	else{
		y--;
		rack[ind] = 0;
		return hallarpeso(ind+1,n,peso,paq,rack);
	}	
}


int main(){
	int paq[]={7,9,8,18,17,12,6,7,14,11,10,15,19,8,12,11}; 
	int rack[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int n=16;
	int peso=23;
	hallarpeso(0,n,peso,paq,rack);
	cout << endl;
	if(x)
		cout <<"Lo encontre";
	else		
		cout <<"No lo encontre";
	return 0;
}

