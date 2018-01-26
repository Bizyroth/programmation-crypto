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

int poids(unsigned int n){
	unsigned x=n;
	x=(x&0x55555555)+((x>>1)&0x55555555);
	x=(x&0x33333333)+((x>>2)&0x33333333);
	x=(x&0x0f0f0f0f)+((x>>4)&0x0f0f0f0f);
	x=(x&0x00ff00ff)+((x>>8)&0x00ff00ff);
	return x;
}

int degre(int * table, int n){
	int d;
	int w;
	int i;
	d=0;
	ANF(table, n);
	for(i=(1<<n)-1; i>=0; --i){
		if(table[i]!=0){
			w=poids(i);
			if(w>d){
				d=w;
			}
		}
	}
	return d;
}

int parite(unsigned int x){
	return poids(x)&1;
}

int ProdScal(unsigned int x, unsigned int y){
	return parite(x&y);
} 	


	int pi[8]={0x0b, 0x07, 0x1e, 0x1b, 0x1d, 0x0f, 0xff, 0x17};

void verifdegre(){
	int f[256];
	int x, y;
	for(x=0; x<8; x++){
		for(y=0; y<32; y++){
			f[x+(y<<3)]=parite(pi[x]&y);
		}
	}
	printf("degre: %d\n", degre(f, 8));
}

int main(){
	
verifdegre();

return 0;
}

