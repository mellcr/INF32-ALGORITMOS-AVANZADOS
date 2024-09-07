
#include <iostream>

using namespace std;

int empaca(int i,int n,int peso,int paq[]){
	
	if(i==n||peso<0) return 0;
	if(paq[i]==peso) return 1;

	if(empaca(i+1,n,peso-paq[i],paq)) return 1;
	else
		return(empaca(i+1,n,peso,paq));	
	
}

int main(){
	int n=5;
	int paq[]={2,5,5,7,55};
	int peso=8;
	
	if(empaca(0,n,peso,paq))
		cout <<"Que bueno lo encontro";
	else
		cout <<"Que pena no entra";
	
	return 0;
}
