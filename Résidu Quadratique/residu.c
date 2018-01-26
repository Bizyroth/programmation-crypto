#include <stdio.h>
#include <stdlib.h>

int pair(unsigned int a){
	return !(a&1);	
}
long pgcd(long a, long b){

	long u,v,r,s,p,q;
	long d=0;
	
	/* tant que a et b sont tout deux pairs, les diviser par deux */
	/* compter l'exposant de la puissance de 2 commune            */
	
	while( ((a&1)==0) && ((b&1)==0) ){
		a>>=1;
		b>>=1;
		d++;
	}
	/*a et b pas tous les deux pairs, on maintient la relation*/
	/*au+bv=p     et     ar+bs=q                              */
	/* On deroule Euclide et a la fin p=pgcd(a,b)             */
	u=1; r=0;
	v=0; s=1;
	p=a;
	q=b;
	
	while(q!=0){
		
		while((p&1)==0){   // on maintient p impair
			p>>=1;
			if( ((u&1)==0) && ((v&1)==0)){
				u>>=1;
				v>>=1;
			}
			else{
				u=(u-b)>>1;
				v=(v+a)>>1;
			}
		}
		
		while((q&1)==0){   // on maintient p impair
			q>>=1;
			if(((r&1)==0) && ((s&1)==0)){
				r>>=1;
				s>>=1;
			}
			else{
				r=(r-b)>>1;
				s=(s+a)>>1;
			}
		}
		if(p>q){      //pgcd(p, q)=pgcd(p-q, q)
		
			p-=q;
			v-=s;
			u-=r;
		}
		else{
			q-=p;
			s-=v;
			r-=u;
		}
	}
	return p<<d;
}


long phi(long n){
	int i;
	int res=0;
	for(i=1; i<n; i++){
		if(pgcd(n, i)==1){
			res++;
		}
	}
	return res;
}

long phi_uti(){
	printf("Entrez un entier pour calculer son indicatrice d'euleer\n");
	long n;
	long i;
	long res=0;
	scanf("%lu", &n);
	for(i=1; i<n; i++){
		if(pgcd(n, i)==1){
			res++;
		}
	}
	printf("phi de %lu vaut %lu\n", n,res);
	return res;
}

int Legendre(int a, int p){
	if(a==1){
		return 1;
	}
	else if((a&1)==0){
		return Legendre(a>>1, p);
	}
	else{
		if((((a-1)*(p-1))>>2)==0){
			return Legendre(p%a, a);
		}
		else{
			return -1*Legendre(p%a,a);
		}
	}
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


int main(){

	printf("%d ", jacobi(14, 51));
	printf("%d ", jacobi(62, 91));
	printf("%d ", jacobi(51, 121));
	printf("%d ", jacobi(2,13));
	printf("%d\n", jacobi(200, 229));
	
	printf("%d ", jacobi(153, 191));
	printf("%d ", jacobi(35, 101));
	printf("%d ", jacobi(29, 115));
	printf("%d ", jacobi(88, 101));
	printf("%d\n", jacobi(32, 121));
	
	printf("%d ", jacobi(32, 125));
	printf("%d ", jacobi(62, 91));
	printf("%d ", jacobi(219, 383));
	printf("%d ", jacobi(-1, 5));
	printf("%d\n", jacobi(541, 2011));
	
	printf("%d\n", jacobi(158, 235));
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	


	
