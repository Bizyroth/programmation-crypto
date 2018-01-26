#include <stdio.h>
#include <stdlib.h>
#define L 9
unsigned int Etat; 			// registre code sur un bit
unsigned int Polynome=0xc9; // polynome caracteristique

/*-----------initialisation du registre-----------------*/

void initialise(unsigned int e){
	Etat=e;
}
/*------------------------------------------------------*/

/*--------------affiche l'etat du registre---------------------*/

void Affiche(){
	int i;
	for(i=L-1; i>=0; i--){
		printf("%2d", (Etat>>i) &1);
	}
	printf("\n");
}
/*--------------------------------------------------------------*/

/*------------calcul du premier coefficent du registre----------*/
unsigned int Rebouclage(){
	unsigned int x;
	x=Etat&Polynome;
	x^=(x>>8);
	x^=(x>>4);
	x^=(x>>2);
	return (x^(x>>1))&1;
}

/*--------------------------------------------------------------*/

/*-----------focntion qui fait tourner le registre------------------*/

void Avance(){
	unsigned int a = Rebouclage();
	Etat=(Etat>>1)^(a<<(L-1));
}
/*-------------------------------------------------------------------*/

int periode(unsigned int EtatInitial){
	int i=1;
	Avance();
	while(Etat!=EtatInitial){
		Avance();
		i++;
	}
	printf("La periode est: %d\n", i);
	return i;
}

int main(){
	int i=20;
	initialise(1);
	while(i>0){
	Avance();
	Affiche();
	i--;
	}
	Affiche();
	return 0;
}

















