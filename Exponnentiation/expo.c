#include <stdio.h>
#include <stdlib.h>


long unsigned mulmod(long unsigned a, long unsigned b, long unsigned m){
	return ((a%m)*(b%m))%m;
}

long unsigned sqrmod(long unsigned a, long unsigned m){
	return mulmod(a,a,m);
}

long unsigned expmod1(long unsigned a, long unsigned n, long unsigned m){
	if(n==0){
		return 1;
	}
	if(n&1==1){
		return mulmod(a, expmod1(a, n-1, m), m);
	}
	else{
		return sqrmod(expmod1(a, n>>1, m), m);
	}
}


long unsigned expmod3(long unsigned a, long unsigned n, long unsigned m){
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
	

int main(){
	
	long n,e, m,d, chiffre, dechiffre;
	n=64507;
	e=3;
	m=0x5555;
	d=42667;
	chiffre=expmod3(m,e,n);
	printf("m vaut %lu\n", m);
	printf("Le chiffre est %lu\n", chiffre);
	dechiffre=expmod3(chiffre, d, n);
	printf("Le dechiffre est %lu\n", dechiffre);
	return 0;
}

	
	
	
	
	
	
