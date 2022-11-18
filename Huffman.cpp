#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADListaReg.h"
#include "TADListaLisArv.h"

struct reg
{
	int simb,codh,frq;
	char palv[50];
};
typedef struct reg Reg;

//Pegar uma frase e checar a frequencia de cada palavra quanto mais frequente o caracter menor o codigo que deverá ser expresso
void checarFreq(LencReg**LR,char frase[150])
{
	char palv[50];
	int i,j=0,x=0;
	LencReg *aux;
	for(i=0;i<strlen(frase);i++)
	{
		if(frase[i]!=' ')
		{
			palv[x]=frase[i];
			palv[x+1]='\0';
			x++;
		}
		else
		{
			if(acrsFrq(&*LR,palv))
				x=0;
			else
			{
				insereLR(&*LR,1,j,palv);
				j++;
				x=0;
			}
		}
	}
	if(acrsFrq(&*LR,palv))
		x=0;
	else
	{
		insereLR(&*LR,1,j,palv);
		j++;
		x=0;
	}
	insereLR(&*LR,0,j," \0");
	j++;
	aux = *LR;
	while(aux->prox!=NULL)
		aux = aux -> prox;
	for(i=0;i<strlen(frase);i++)
	{
		if(frase[i]==' ')
			aux->frq++;
	}
}

//Inserindo os itens nas listas com os nós
void criarListaArv(LencReg*LR,LArv**LA)
{
	while(LR!=NULL)
	{
		insereLA(&*LA,LR->simb,LR->frq);
		LR = LR -> prox;
	}
}
void exibeListaLR(LencReg*LG)
{
	while(LG!=NULL)
	{
		printf("%d, %d\n",LG->simb,LG->frq);
		LG = LG->prox;
	}
}
void exibeListaLA(LArv*LA)
{
	while(LA!=NULL)
	{
		printf("%d, %d\n",LA->no->simb,LA->no->frq);
		LA = LA->prox;
	}
}

void criaArv(LArv**LA)
{
	LArv *aux;
	int tam=0;
	aux = *LA;
	while(aux!=NULL)
	{
		tam++;
		aux = aux->prox;
	}
	while(tam>0)
	{
		
	}
}

int main()
{
	LencReg *LR;
	LArv *LA;
	char frase[150];
	strcpy(frase,"Amo como ama o amor. Não conheço nenhuma outra razão para amar senão amar. Que queres que te diga, além de que te amo, se o que quero dizer-te é que te amo?");
	initLR(&LR);
	initLA(&LA);
	checarFreq(&LR,frase);
	criarListaArv(LR,&LA);
	exibeListaLA(LA);
}
