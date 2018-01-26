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
	jj=nn>>1; // 
	do{
		i=0;
		do{
			temp1=table[i];
			temp2=table[i+jj];
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

/*-------------------------------calcule de la non linearite de f fonction a n variable-------------*/
unsigned int NL(int *f, int n){    

	unsigned int maxtw=0;           // le max de la valeur absolue de la transforme de Walsh
	unsigned int atw;               // valeur absolue de la transforme de Walsh
	int i;
	unsigned int nn=1<<n;
	int * res=malloc(sizeof(int)*nn);
	Walsh(res, f,n);
	/*recherche du max de la transforme de Walsh*/
	for(i=0; i<nn; i++){
		atw=((res[i]>=0) ? res[i] : -res[i]);  //valeur absolu de walsh de f
		if(atw>maxtw) maxtw=atw;
	}
	free(res);
	
	return (nn-maxtw)>>1; // calcule de la non linearite
}
/*-------------------------------------------------------------------------------------------------*/

/*----------------trois methodes pour calculer qu'une fonction est courbe--------------------------*/
                
                /*--------teste si Walsh(f) vaut +-2^(n/2)-----------------*/      //marche
int estCourbeCar(int * f, int n){
		int i;
		unsigned int nn;
		nn=1<<n;
		int * res=malloc(sizeof(int)*nn);
		Walsh(res, f, n);
		if(n&1==1) return 0;             // si n impair n'est pas courbe
		unsigned int a=1<<(n>>1);
		for(i=0; i<nn; i++){
			if(res[i]!=a && res[i]!=-a){
				return 0;
			}
		}
		return 1;			
}
				/*-----teste si la fonction a autant de 0 que de 1------*/            // marche pas
int estCourbeEqui(int * f, int n){
		unsigned int nn=1<<n;
		if(n&1==1) return 0;
		int i;
		int res=0;
		for(i=0; i<nn; i++){
			if(f[i]==0) res++;
			if(f[i]==1) res--;
		}
		if(res==0) return 1;
		
		return 0;
}
/*-----------------------teste si une fonction est courbe en verifiant l'egalite NL(f)= 2^(n-1) - 2^((n/2)-1) ----------------*/ // marche	
int estCourbeMax(int * f, int n){
		if(n&1==1) return 0;               // si n est impair la fonction n'est pas courbe
		unsigned int res=NL(f, n);         //calcul de NL(f)
		unsigned int nn=1<<n;			   
		unsigned int a=(1<<(n-1));
		unsigned int b=((1<<((n>>1))-1));
		if(a-b==res) return 1;
		
		return 0;
}
/*----------------------------------------------------------------------------------------------------------------------------*/
/*-----------calcule de la fonction pi du TP1-----------------------------*/

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
/*-------------------------------------------------------------------------*/
/*--------fonction qui calcule le produit scalaire de deux nombres à 4 bits-----------*/
void courbe(int * f){
		int i, j;
		for(i=0; i<16; i++){
			for(j=0; j<16; j++){
				f[i+(j<<4)]=ProdScal(i, j);
			}
		}
}
/*------------------------------------------------------------------------------------*/
	

int main(){
	int i;
/*-----------------calcul de la fonction f de la 5eme question du TP3--------------------*/
char ff[512] ="10010111011111110011111111111010000011101111101010101110110010010101010111111000111110101100110111001100101010011010000010000011011101100110011011101011110000001111101010001000111000001011001111110100111000001000100110000011110010000100010110010001010111100111111101111100001011000010100111111100110010111010000100000001111010101001100011000000100001011110100000010001100010110101111011111110001000011110100100010001100001001000001110000101000111101110000110010101001000010011011010010111000101100111011011101001";
	
int fff[512];
for(i=0; i<512; i++){
	fff[i]=ff[i]-'0';
}
/*-----------------------------------------*/	
	
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
	
int fu[256];
F(fu, 8);
		
int fa1[256];
courbe(fa1);
	
	
printf("non linearite de hhhh: %u\n", NL(hhhh, 9));
printf("non linearite de ff: %u\n", NL(fff, 9));
printf("non linearite pi: %u\n", NL(fu, 8));
printf("non linearite de courbe: %u\n", NL(fa1, 8));
printf("est courbe de c: %u\n", estCourbeCar(fa1, 8));
return 0;

}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
