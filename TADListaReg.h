
struct lencReg
{
	struct lencReg *prox;
	int frq,simb;
	char codgh[50],palv[50];
};
typedef struct lencReg LencReg;

void initLR(LencReg **LR)
{
	*LR = NULL;
}

void buscaPorSimb(LencReg**LR, int simb, char frase[],int *j)
{
	char palv[50];
	int i=0;
	LencReg *aux;
	aux = *LR;
	while(aux!=NULL && aux->simb!=simb)
		aux = aux -> prox;
	if(aux!=NULL)
	{
		while(aux->palv[i]!='\0')
		{
			strcpy(palv,aux->palv);
			frase[*j]=palv[i];
			i++;
			(*j)++;
		}
	}
	frase[*j]='\0';
}

LencReg* buscaPorPalv(LencReg **LR,char palv[])
{
	LencReg *aux;
	aux = *LR;
	while(aux!=NULL && strcmp(aux->palv,palv)!=0)
		aux = aux->prox;
	if(aux==NULL)
		return NULL;
	else
		return aux;
}


void insereLR(LencReg **LR,int frq,int simb,char palv[],char codgh[])
{
	LencReg *aux,*novo = (LencReg*)malloc(sizeof(LencReg));
	novo->prox = NULL;
	strcpy(novo->palv,palv);
	novo->frq = frq;
	novo->simb = simb;
	if(codgh!=NULL)
		strcpy(novo->codgh,codgh);
	if(*LR==NULL)
		*LR = novo;
	else
	{
		aux = *LR;
		while(aux->prox!=NULL)
			aux = aux->prox;
		aux -> prox = novo;
	}
}

char acrsFrq(LencReg **LR,char palv[])
{
	LencReg *aux;
	aux = *LR;
	while(aux!=NULL&&strcmp(aux->palv,palv)!=0)
		aux = aux->prox;
	if(aux!=NULL)
	{
		aux->frq++;
		return 1;
	}
	return 0;
}
