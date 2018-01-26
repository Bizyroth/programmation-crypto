#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---------------------------fait a*b mod m-------------------------------*/

long unsigned mulmod(long unsigned a, long unsigned b, long unsigned m){
	return ((a%m)*(b%m))%m;
}
/*------------------------------------------------------------------------*/
/*----------------renvoie l tq 2^l*t=x avec t impair----------------------*/

int last_one(long unsigned x){
	long res=x;
	int r=0;
	if(res==0){
		return -1;
	}
	while((res&1)==0){
		res>>=1;
		r++;
	}
	return r;
}
/*-------------------------------------------------------------------------*/
/*----------------renvoie un entier aleatoire x tq x in [a,b[-------------------*/

long rand_a_b(long a, long b){
    return (long)rand()%(b-a) +a;
}
/*-------------------------------------------------------------------------------*/
/*--------------------------------calcul a^n mod m-------------------------------*/

long unsigned expmod(long unsigned a, long unsigned n, long unsigned m){
	long i=n;
	long res=1;
	long temp =a;
	
	while(i>0){
		if(i&1!=0){
			res=mulmod(res, temp, m);			
		}
			temp=mulmod(temp, temp, m);
			i>>=1;
		
	}
	return res;
}
/*----------------------------------------------------------------------------------*/
/*renvoie 0 si n est composé en base a et 1 si il est probablement premier en base a*/

int TestMiller(int n, int a){
	int power;
	int t;
	int b;	
	int j;
	
	power=last_one(n-1);
	t=(n-1)>>power;
	b=expmod(a, t, n);
	if(b==1){
		return 1;
	}
	for(j=0; j<power; j++){
		if(b==(n-1)){
			return 1;
		}
		if(b==1){
			return 0;
		}
		b=expmod(b, 2, n);
	}
	return 0;
}
/*----------------------------------------------------------------*/
/*-----------applique le test de miller k fois sur des temoisn aleatoire-------------*/
/*----------renvoie 0 si n est compse 1 si il est probablement premier---------------------*/
int miller(int n, int k){
	int i, j;
	int alea;
	if(n==2){
		printf("2 est premier mais aviez vous vraiment besoin de le verifier?\n");
		return 1;
	}
	if((n&1)==0){
		printf("%d est pair different de 2 donc compose\n", n);
		return 0;
	}
	srand(time(NULL));
	
	for(i=0; i<k; i++){
		alea=rand_a_b(2, n-1);
		if(TestMiller(n, alea)==0){
			printf("%d n'est pas premier pour le temoin %d\n", n, alea);
			return 0;
		}
	}
	printf("%d est probablement premier\n", n);
}

/*----------------------------------------------------------------------------------------*/

int main(){

	miller(55, 10);
	miller(13, 5);
	miller(45, 50);
	miller(4756245, 100);
	miller(1013, 20);
	return 0;
}
	
	
	
	
	
	
	
	
	
	
