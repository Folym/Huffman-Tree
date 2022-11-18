
struct lencReg
{
	struct lencReg *prox;
	int frq,simb,codgh;
	char palv[50];
};
typedef struct lencReg LencReg;

void initLR(LencReg **LR)
{
	*LR = NULL;
}

void insereLR(LencReg **LR,int frq,int simb,char palv[50])
{
	LencReg *aux,*novo = (LencReg*)malloc(sizeof(LencReg));
	novo->prox = NULL;
	strcpy(novo->palv,palv);
	novo->frq = frq;
	novo->simb = simb;
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

char acrsFrq(LencReg **LR,char palv[50])
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

