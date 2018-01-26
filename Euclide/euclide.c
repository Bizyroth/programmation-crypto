#include <stdio.h>
#include <stdlib.h>

int pair(unsigned int a){
	return !(a&1);	
}
/*----------------calucul de pgcd (bete)------------------------------*/
unsigned int EuclideBinaire1(unsigned int a, unsigned int b){
	int d=0;
	unsigned int min;
	while(a!=b){
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
		else if(a>b){
			a-=b;
		}
		else{
			b-=a;
		}
	}
	return a<<d;
}
/*----------------------------------------------------------------*/
/*----------------algo euclide 2 (moins bete)---------------------*/

unsigned int EuclideBinaire2(unsigned int a, unsigned int b){
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


/*-----------------------calcul x/2 mod b----------------------------------*/
unsigned int MoitieModImpair(unsigned int x, unsigned int b){
	if(pair(x)) return x>>1;
	return (x>>1)+(b>>1)+1;
}
/*-------------------------------------------------------------------------*/
/*----------------------calcul de |x-y|mod b-------------------------------*/

unsigned int SubMod(unsigned int x, unsigned int y, unsigned int b){
	if(x>y) return x-y;
	return x-y+b;
}
/*---------------------------------------------------------------------------*/

/*--------------calcule dans pu la valeur u tq au = p[b]----------------------*/
unsigned int InvModImpair(unsigned int * pu, unsigned int a, unsigned int b){

	unsigned int p, q, u, t;
	p=a;
	q=b;
	u=1;
	t=0;
	while(pair(p)){
		p>>=1;
		u=MoitieModImpair(u, b);		
	}

	while(p!=q){

		if(p>q){
			p-=q;
			u=SubMod(u,t,b);
			do{
				p>>=1;
				u=MoitieModImpair(u,b);
			}while(pair(p));
		}
		else{
			q-=p;
			t=SubMod(t,u,b);
			do{
				q>>=1;
				t=MoitieModImpair(t,b);
			}while(pair(q));
		}
	}
	*pu=u;
	return p;
}	


/*-----------------------------------------------------------------------------*/


int main(){
	unsigned int pu=0;
	unsigned int pv=0;
	unsigned int p1;
	unsigned int a, b;
	a=1610000010;
	b=1000019920;
	p1=EuclideBinaire2(a, b);
	printf("Le pgcd de %d et %d est %d \n", a, b, p1);
	return 0;
}











