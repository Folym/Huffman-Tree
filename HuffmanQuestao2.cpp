#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TADListaLisArv.h"
#include "TADListaReg.h"

void criaListaReg(LencReg**LR,FILE**arqb)
{
	LencReg reg;
	fseek(*arqb,0,0);
	fread(&reg,sizeof(LencReg),1,*arqb);
	while(!feof(*arqb))
	{
		insereLR(&*LR,reg.frq,reg.simb,reg.palv,reg.codgh);
		fread(&reg,sizeof(LencReg),1,*arqb);
	}
	
}
void criaListaArv(LencReg*LR,LArv**LA)
{
	while(LR!=NULL)
	{
		insereLA(&*LA,LR->simb,LR->frq);
		LR = LR -> prox;
	}
}

void criaArv(LArv**LA)
{
	LArv *ant,*aux;
	int frqT;
	ant = *LA;
	aux = ant->prox;
	while(aux!=NULL)
	{
		frqT = (aux->no->frq)+(ant->no->frq);
		insereArv(&*LA,&aux,&ant,-1,frqT);
		exclusaoLA(&*LA,ant->no->simb);
		exclusaoLA(&*LA,aux->no->simb);
		ant = *LA;
		aux = ant->prox;
	}
}

void exibe(Tree *raiz){
	static int n=-1,i;
	if(raiz!=NULL)
	{
		n++;
		exibe(raiz->dir);
		for(i=0;i<5*n;i++)
			printf(" ");
		printf("(%d, %d)\n",raiz->simb,raiz->frq);
		exibe(raiz->esq);
		n--;	
	}			
}

void exibeListaLR(LencReg*LR)
{
	printf(" Palavra		Frequencia			Simbolo			Codigo\n\n");
	while(LR!=NULL)
	{
		printf(" %s				%d		   	%d			%s\n",LR->palv,LR->frq,LR->simb,LR->codgh);
		LR = LR->prox;
	}
}

void criandoFrase(LencReg**LR,Tree*no,char codgh[],char frase[])
{
	int i=0,j=0;
	Tree *aux = no;
	while(codgh[i]!='\0')
	{	
		if(aux->simb!=-1)
		{
			buscaPorSimb(&*LR,aux->simb,frase,&j);
			aux = no;
		}
		if(codgh[i]=='0')
			aux = aux->esq;
		else
		if(codgh[i]=='1')
			aux = aux->dir;
		i++;
	}
}

int main(void)
{
	char frase[500];
	char codgh[301];
	FILE *arqb = fopen("huffman.dat","rb+");
	FILE *arqt = fopen("huffman.txt","r+");
	LArv *LA;
	LencReg *LR;
	initLA(&LA);
	initLR(&LR);
	fgets(codgh,300,arqt);
	criaListaReg(&LR,&arqb);
	criaListaArv(LR,&LA);
	criaArv(&LA);
	exibeListaLR(LR);
	getch();
	clrscr();
	exibe(LA->no);
	criandoFrase(&LR,(LA->no),codgh,frase);
	getch();
	clrscr();
	printf("%s",frase);
}
