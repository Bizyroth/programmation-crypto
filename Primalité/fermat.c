#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long unsigned mulmod(long unsigned a, long unsigned b, long unsigned m){
	return ((a%m)*(b%m))%m;
}

long unsigned sqrmod(long unsigned a, long unsigned m){
	return mulmod(a,a,m);
}

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
/*renvoie un entier dans l'intervalle [a, b[*/
long rand_a_b(long a, long b){
    return (long)rand()%(b-a) +a;
}

unsigned int TestPrimaliteFermat(unsigned long n, unsigned int K){
	int i;
	long alea;
	srand(time(NULL));
	for(i=0; i<K; i++){
		alea=rand_a_b(2, n);
		if(expmod(alea, n-1, n)!=1){
			return 0;
		}
	}
	return 1;
}
	
	
int main(){
	int a = TestPrimaliteFermat(97, 10);
	printf("est premier %d\n",a);
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
