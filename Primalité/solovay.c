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

unsigned int EuclideBinaire(unsigned int a, unsigned int b){
	int d=0;
	while(pair(a)&&pair(b)){
		if(pair(a)&&pair(b)){
			d++;
			a>>=1;
			b>>=1;
		}
		else if(pair(a)){
			a>>=1;
		}
		else if(pair(b)){
			b>>=1;
		}
	}

	while(a!=b){

		if(a>b){
			a-=b;
		}
		else{
			b-=a;
		}
	}
	return a<<d;
}


long rand_a_b(long a, long b){
    return (long)rand()%(b-a) +a;
}

int jacobi(int p, int q){
	int res;         // valeur retourne
	int k;			// valeur diadyque
	long unsigned a0, a1;
	long unsigned b1, b0;
	res=1;
	if(p==0){
		return 0;
	}
	else if(p<0){
		p=-p;
		if((q&3)==3){ 
			res=-1;
		}
	}
	if(EuclideBinaire(p, q)!=1) return 0;
	
	a0=p;
	b0=p;
	b1=q;
	if(b1==0){
		return 0;
	}
	k=last_one(b1);
	a1=b1>>k;                          //b1=2^k * a1 a1 impair
	res=1;
	
	if( (k&1) && (((a0&7)==3) || ((a0&7)==5))){
		res=-1;
	}
	
	if(a1==1){
		return res;
	}
	
	while(1){
		if(b0==0){
			return 0;
		}
		b0=b1;
		b1=a0%a1;
		a0=a1;
		k=last_one(b1);
		a1=b1>>k;
		if(a0==1){
			return res;
		}
		if( (k&1) && (((a0&7)==3) || ((a0&7)==5))){
			res=-res;
		}
		if( ((a0&3)==3) && ((a1&3)==3)){
			res=-res;
		}
	}
	
}

int Test(int n, int a){
	int i;
	long alea;
	int jac;
	int power=(n-1);
	power>>=1;
	int exp;
	
	srand(time(NULL));
	
	for(i=0; i<a; i++){
		alea=rand_a_b(2, n);
		jac=jacobi(alea,n);
		exp=expmod(alea, power, n);
		if(jac!=exp && jac!=(exp-n)){
			printf("%d est composé\n", n);
			return 0;
		}
	}
	printf("%d est probablement premier\n", n);
	return 1;
}
	
	
	int pair(unsigned int a){
	return !(a&1);	
}

	

	
	
	


int main(){

	Test(27, 5);
	Test(367, 10);
	Test(101, 6);
	return 0;
}
