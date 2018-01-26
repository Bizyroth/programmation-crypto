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
/*----------------------calcule de (-1)^table et met le resultat dans res----------------------*/
void power(int * res, int * table, int n){
	unsigned int nn=1<<n;
	int i=0;
	for(i=0; i<nn; i++){
		if(table[i]==0){
			res[i]=1;
		}
		else{
			res[i]=-1;
		}
	}
}
/*-------------------------------------------------------------------------------------------------*/
/*----------------calcule de la transforme de fourier de table et place le resultat dans res----------------*/
void Fourier(int * res, int * table, int n){
	unsigned int nn; // taille du tableau = 2^n
	unsigned int jj; // taille de la sous fonction
	
	int i, temp1, temp2;
	
	nn=1<<n; // 2^n
	for(i=0; i<nn; i++){
		res[i]=table[i];
	}
	jj=nn>>1; // 
	do{
		i=0;
		do{
			temp1=res[i];
			temp2=res[i+jj];
			res[i]=temp1+temp2;
			res[i+jj]=temp1-temp2;
			i++;
			if((i&(jj-1))==0){i+=jj;}

		}while(i<nn);
		jj>>=1;
	}while(jj!=0);
}
/*-------------------------------------------------------------------------------------------------*/

/*--------------------------calcule de la transforme de Walsh de table et place le resultat dans res--------------*/
void Walsh(int * res, int * table, int n){
	power(res, table, n);
	Fourier(res, res, n);
}
/*-------------------------------------------------------------------------------------------------*/




void AutocorrelationNaif(int * r, int * f, int n){
	unsigned int nn = 1<<n;
	int i, j;
	
	for(i=0; i<nn; i++){
		r[i]=0;
		for(j=0; j<nn; j++){
		
			r[i]+= 1 - 2*(f[j]^f[i^j]);        //astuce : (-1)^f = 1 - 2f
		}
	}
}

void Autocorrelation(int * r, int * f, int n){
	unsigned int nn=1<<n;
	int i;
	int w[nn];
	Walsh(w, f, n);

	for(i=0; i<nn; i++){
		w[i]*=w[i];
	}
	 n,,Fourier(r, w, n);
	for(i=0; i<nn; i++){
		r[i]>>=n;
	}
}

int PC(int * f, int n){
	unsigned int nn=1<<n;
	int temp[nn];
	Autocorrelation(temp, f, n);
	int i, r, w;
	r=n+1;
	for(i=nn-1; i>0; i--){
		if(temp[i]!=0){
			w=poids(i);
		}
		if(w<r){
			r=w;
		}
	}
	return r-1;
}

void Derive(int * res, int * f, int n, int a){
	unsigned int nn = 1<<n;
	int i;
	for(i=0; i<nn; i++){
		res[i]=f[i]^f[i^a];
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


int pi[8]={0x0b, 0x07, 0x1e, 0x1b, 0x1d, 0x0f, 0xff, 0x17};
	
	void F(int * table, int n){
		unsigned nn=(n<<1);
		int i, j;
		for(i=0; i<16; i++){
			for(j=0; j<16; j++){
				table[i+(j<<4)]=ProdScal(pi[i], j);
			}
		}
	}
	

int main(){
	int fu[256];
	F(fu, 8);
	int r[256];
	int x;
	/*int r1[512];
	int r2[512];
	AutocorrelationNaif(r1, hhhh, 9);
	Autocorrelation(r2, hhhh, 9);
	for(x=0; x<512; x++){
		printf("%5d,%3d%c",r1[x], r2[x], ((x+1)%7==0)?'\n': ' ');
	}*/
	
	Derive(r, fu, 8, 123);
	for(x=0; x<256; x++){
		printf("%d ", r[x]);
	}
	printf("\n");
		
	return 0;
}
	
		
	
	
	
	
	
	
	
	
	
	
	
	
	
