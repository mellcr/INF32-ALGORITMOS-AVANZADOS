#include <iostream>
#define MAX 6
int vacsol[MAX]={0};
int costo=0;

using namespace std;

int valida(int ciud[MAX][MAX],int ini,
	int n,int vac,int nvcan,int cong[]){
	
	if(vac==1 && cong[ini]!=1) return 0;
	for(int i=0;i<n;i++){
		if(ciud[ini][i]==1)
			if(vacsol[i]==vac) return 0;
		if(ciud[i][ini]==1)
			if(vacsol[i]==vac) return 0;		
	}
	return 1;	
}
int buscasol(int ciud[MAX][MAX],int ini,
	int n,int nvcan,int costos[],int cong[]){

	if(ini==n){
		for(int i=0;i<n;i++)
			cout << vacsol[i] << " ";
		cout <<"Costo= "<<costo<< endl;		
		return 0;
	}
	if(ini<n && vacsol[ini]==0){
		for(int vac=1;vac<=nvcan;vac++){
			if(valida(ciud,ini,n,vac,nvcan,cong)){
				vacsol[ini]=vac;	
				costo=costo+costos[vac-1];
				if(buscasol(ciud,ini+1,n,nvcan,costos,cong))
					return 1;
				costo = costo-costos[vac-1];	
				vacsol[ini]=0;				
			}	
		}
	}
	return 0;
}


int main(){
	int n,nvac;
	int ciudades[MAX][MAX]={
		{0,1,1,0,0,1},
		{1,0,1,1,0,0},
		{1,1,0,1,0,1},
		{0,1,1,0,1,1},
		{0,0,0,1,0,1},
		{1,0,1,1,1,0}};

	int cong[MAX]={0,0,1,0,1,0};
	int costos[]={10,5,12,8};
	n=MAX;
	int nvcan=4;

	buscasol(ciudades,0,n,nvcan,costos,cong);

	return 0;
}
