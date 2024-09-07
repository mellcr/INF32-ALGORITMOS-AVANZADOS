#include <iostream>
using namespace std;

int lista[10];
int y=0,flag=0;

int empaca(int i,int n,int peso,int paq[]){
	
	if(i==n||peso<0) return 0;
	if(paq[i]==peso){
		lista[y]=paq[i];
		for(int j=0;j<=y;j++)cout<< lista[j]<<" ";
		cout << endl;
		flag++;
	} 
	lista[y]=paq[i];
	y++;
	if(empaca(i+1,n,peso-paq[i],paq))return 1;
	else{
		y--;
		return(empaca(i+1,n,peso,paq));	
	}

	
}

int main(){
	int n=5;
	int paq[]={8,5,3,4,3};
	int peso=8;
	empaca(0,n,peso,paq);
	if(flag)
		cout <<"Que bueno lo encontro, son "<<flag <<" combinaciones";
	else
		cout <<"Que pena no entra";
	
	return 0;
}
