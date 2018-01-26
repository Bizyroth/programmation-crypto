#include <stdio.h>
#include <stdlib.h>


void ANF(int * table, int n){
	unsigned int nn; // taille du tableau = 2^n
	unsigned int jj; // taille de la sous fonction
	
	int i;
	nn=1<<n; // 2^n
	jj=nn>>1; // 
	do{
		i=0;
		do{
			table[i+jj]^=table[i];
			i++;
			if((i&(jj-1))==0){i+=jj;}

		}while(i<nn);
		jj>>=1;
	}while(jj!=0);
} 

int main(){
	int i=0;
	int n=3;
	
	int table[8]={0,1,1,0,0,1,0,1};
	ANF(table, n);
	for(i=0; i<(1<<n); i++){
		printf("%d ", table[i]);
	}
	printf("\n");
	return 0;
}
	
