#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include "TADListaReg.h"
#include "TADListaLisArv.h"


//Pegar uma frase e checar a frequencia de cada palavra quanto mais frequente o caracter menor o codigo que deverá ser expresso
void checarFreq(LencReg**LR,char frase[],int*j)
{
	char spc[2]= " ";
	char palv[100];
	int i,x=0;
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
				insereLR(&*LR,1,*j,palv,NULL);
				(*j)++;
				x=0;
			}
		}
	}
	if(acrsFrq(&*LR,palv))
		x=0;
	else
	{
		insereLR(&*LR,1,*j,palv,NULL);
		(*j)++;
		x=0;
	}
	insereLR(&*LR,0,*j,spc,NULL);
	(*j)++;
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

void colocaCodg(LencReg **LR,char codgh[],int simb)
{
	LencReg *aux;
	aux = *LR;
	while(aux!=NULL && aux->simb!=simb)
		aux = aux->prox;
	if(aux!=NULL)
		strcpy(aux->codgh,codgh);
}
void criaCodH(Tree*no,LencReg **LR,char codgh[],int i,int tam)
{
	if(i==1)
	{
		codgh[tam]='1';
		tam++;
		codgh[tam]='\0';
	}
	else if(i==0)
	{
		codgh[tam]='0';
		tam++;
		codgh[tam]='\0';
	}
	if(no!=NULL)
	{
		if(no->simb!=-1)
		{
			colocaCodg(&*LR,codgh,no->simb);
		}
		criaCodH(no->esq,&*LR,codgh,0,tam);
		criaCodH(no->dir,&*LR,codgh,1,tam);
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
	printf(" Palavra			Frequencia				Simbolo				Codigo\n\n");
	while(LR!=NULL)
	{
		printf(" %s					%d		   		%d				%s\n",LR->palv,LR->frq,LR->simb,LR->codgh);
		LR = LR->prox;
	}
}


void criaEstruturas(LencReg**LR,LArv**LA,char frase[])
{
	int tam=0;
	char codgh[300];
	int j=0,i=-1;
	checarFreq(&*LR,frase,&j);
	criaListaArv(*LR,&*LA);
	criaArv(&*LA);
	criaCodH((*LA)->no,&*LR,codgh,i,tam);
}

void salvaArqB(FILE**arqb,LencReg* LR)
{
	LencReg reg;
	while(LR!=NULL)
	{
		strcpy(reg.codgh,LR->codgh);
		reg.frq = LR->frq;
		strcpy(reg.palv,LR->palv);
		reg.simb = LR->simb;
		reg.prox = NULL;
		fwrite(&reg,sizeof(LencReg),1,*arqb);
		LR = LR->prox;
	}
}

void salvaArqT(FILE**arqt,LencReg*LR,char frase[])
{
	LencReg *aux;
	char spc[2]=" ";
	aux = buscaPorPalv(&LR,spc);
	strcpy(spc,aux->codgh);
	char *palv = strtok(frase," ");
	while(palv!=NULL)
	{
		aux = buscaPorPalv(&LR,palv);
		fputs(aux->codgh,*arqt);
		fputs(spc,*arqt);
		palv = strtok(NULL," ");
	}
}

void salvaArquivo(LencReg**LR,char frase[])
{
	FILE *arqb = fopen("huffman.dat","wb+");
	FILE *arqt = fopen("huffman.txt","w+");
	salvaArqB(&arqb,*LR);
	salvaArqT(&arqt,*LR,frase);
	fclose(arqb);
	fclose(arqt);
}

int main()
{
	LencReg *LR;
	LArv *LA;
	char frase[500];
	strcpy(frase,"Amo como ama o amor. Nao conheco nenhuma outra razao para amar senao amar. Que queres que te diga, alem de que te amo, se o que quero dizer-te e que te amo?");
	initLR(&LR);
	initLA(&LA);
	criaEstruturas(&LR,&LA,frase);
	salvaArquivo(&LR,frase);
	exibeListaLR(LR);
	getch();
	clrscr();
	exibe(LA->no);
	getch();
	
}
