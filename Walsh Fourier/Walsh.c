#include <stdio.h>
#include <stdlib.h>

int poids(unsigned int n){
	unsigned x=n;
	x=(x&0x55555555)+((x>>1)&0x55555555);
	x=(x&0x33333333)+((x>>2)&0x33333333);
	x=(x&0x0f0f0f0f)+((x>>4)&0x0f0f0f0f);
	x=(x&0x00ff00ff)+((x>>8)&0x00ff00ff);
	return x;
}

int parite(unsigned int x){
	return poids(x)&1;
}

int ProdScal(unsigned int x, unsigned int y){
	return parite(x&y);
}

void power(int * table, int n){
	unsigned int nn=1<<n;
	int i=0;
	for(i=0; i<nn; i++){
		if(table[i]==0){
			table[i]=1;
		}
		else{
			table[i]=-1;
		}
	}
}

void Fourier(int * table, int n){
	unsigned int nn; // taille du tableau = 2^n
	unsigned int jj; // taille de la sous fonction
	
	int i, temp1, temp2;
	nn=1<<n; // 2^n
	jj=nn>>1; // 
	do{
		i=0;
		do{
			temp1=table[i];
			temp2=table[i+jj];
			table[i]=temp1+temp2;
			table[i+jj]=temp1-temp2;
			i++;
			if((i&(jj-1))==0){i+=jj;}

		}while(i<nn);
		jj>>=1;
	}while(jj!=0);
}

void Walsh(int * table, int n){
	power(table, n);
	Fourier(table, n);
}

int resilience(int * table, int n){

	int i,j, r, k;
	k=0;
	r=n;
	Walsh(table, n);

	for(j=r;j>=0; j--){

		for(i=(1<<n); i>=0; i--){

			if(poids(i)<=j && table[i]!=0){
				k=1;
				break;
			}
		}
		if(k==0){
			printf("resilience: %d\n", j);
			return j;
		}
		k=0;
	}
	printf("resilience -1\n");
	return -1;
}
	int pi[8]={0x0b, 0x07, 0x1e, 0x1b, 0x1d, 0x0f, 0xff, 0x17};
	
	void F(int * table, int n){
		unsigned nn=(n<<1);
		int i, j;
		for(i=0; i<8; i++){
			for(j=0; j<32; j++){
				table[i+(j<<3)]=ProdScal(pi[i], j);
			}
		}
	}
	
	int hhhh[512]= {
0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,1,1,0,0,1,1,1,
0,1,1,0,0,0,0,1,1,0,0,1,0,0,0,1,0,1,1,0,1,0,1,1,0,0,0,0,0,0,1,0,
0,1,0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,1,1,0,1,
0,0,1,1,1,1,0,0,1,0,1,0,1,0,1,1,0,0,1,1,1,1,0,0,1,0,0,0,1,0,1,0,
0,1,0,1,1,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,1,0,0,1,0,0,0,1,
0,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,0,0,1,0,0,
0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,0,0,1,0,0,0,1,0,0,1,0,1,1,0,1,1,0,
0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,1,1,0,0,1,0,
0,1,1,0,0,1,0,0,1,1,1,1,1,1,0,1,1,1,0,0,1,0,1,1,1,1,0,0,1,0,1,1,
0,0,0,0,1,0,0,0,1,0,0,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,0,0,1,
0,1,1,1,0,0,1,1,1,1,1,1,1,0,1,0,1,1,0,0,0,1,0,0,1,0,1,0,0,0,0,0,
0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0,
0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,
0,0,1,1,0,1,0,0,0,0,1,1,1,0,1,1,1,0,1,0,0,1,1,1,0,0,1,1,0,0,0,1,
0,1,1,0,1,0,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,
0,0,0,1,1,0,1,0,1,1,1,0,0,1,0,0,1,0,1,0,1,1,0,1,0,1,1,1,0,0,1,0};




int main(){
	int i=0;
	int n=9;
			
	int table[8]={0,1,1,0,1,1,0,1};
	Walsh(hhhh, 9);
	for(i=0; i<(1<<n); i++){
		printf("%d ", hhhh[i]);
	}
	printf("\n");
	return 0;
}


