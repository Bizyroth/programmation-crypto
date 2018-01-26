#include <stdio.h>
#include <stdlib.h>

#define L 9      // taille du registre

int Etat[L];  // registre interne

int Polynome[L]={1,0,0,1,0,0,1,1,0}; // Polynome caracteristique


/*---------initialisation de l'etat initial avec une table d'entier donné-----------*/

void initialise(int *e){
	int i;
	for(i=0; i<L; i++){
		Etat[i]=e[i];
	}
}
/*----------------------------------------------------------------------------------*/

/*-------------------------affichage de l'etat interne------------------------------*/

void AfficheEtat(){
	int i;
	for(i=L-1; i>=0; i--){
		printf("%2d", Etat[i]>>i &1);
	}
	printf("\n");
}
/*----------------------------------------------------------------------------------*/


/*----------------------Procedure d'avancement du registre--------------------------*/

void Avance(){
	int i;
	unsigned int a=0;
	for(i=0; i<L; i++){
		a^=Etat[i]&Polynome[i];
	}
	for(i=0; i<L-1; i++){
		Etat[i]=Etat[i+1];
	}
	Etat[L-1]=a;
}

/*---------------------------------------------------------------------------------*/

/*------------------test si deux etats du registre sont egaux-----------------------*/
int sontEgaux(int *a, int *b){
	int i;
	for(i=0; i<L; i++){
		if(a[i]!=b[i]) return 0;
	}
	return 1;
}

/*---------------------------------------------------------------------------------*/

/*------------------------determine la periode d'un registre-----------------------*/

int periode(int * EtatInitial){

	int i=1;
	Avance();
	while(sontEgaux(EtatInitial, Etat)!=1){
		Avance();
		i++;
	}
	printf("La periode est: %d\n", i);
	return i;
}

int main(){
	int i=20;
	int EtatInitial[L]={1,0,0,0,0,0,0,0,0};
	initialise(EtatInitial);
	periode(EtatInitial);
	
	return 0;
}




































