
struct tree
{
	int frq,simb;
	struct tree *dir,*esq;
};
typedef struct tree Tree;

struct listaArv
{
	struct tree *no;
	struct listaArv *prox;
};
typedef struct listaArv LArv;

void initLA(LArv**LA)
{
	*LA = NULL;
}

Tree* criaNo(int simb,int frq)
{
	Tree *no = (Tree*)malloc(sizeof(Tree));
	no -> dir = no -> esq = NULL;
	no -> simb = simb;
	no -> frq = frq;
	return no;
}

void insereLA(LArv**LA,int simb,int frq)
{
	LArv *ant,*aux,*novo = (LArv*)malloc(sizeof(LArv));
	novo->no = NULL;
	novo -> prox = NULL;
	if((*LA)==NULL)
		*LA = novo;
	else
	{
		ant = aux = *LA;
		while(aux!=NULL&&aux->no->frq<=frq)
		{
			ant = aux;
			aux = aux->prox;
		}
		if(aux==NULL)
			ant->prox = novo;
		else
		{
			if(aux==ant)
			{
				novo->prox = aux;
				*LA = novo;
			}
			else
			{
				novo -> prox = aux;
				ant -> prox = novo;
			}
		}
	}
	novo->no = criaNo(simb,frq);
}

void insereArv(LArv**LA,LArv**auxP, LArv**antP, int simb, int frq)
{
	LArv *ant,*aux,*novo = (LArv*)malloc(sizeof(LArv));
	novo->no = NULL;
	novo -> prox = NULL;
	if((*LA)==NULL)
		*LA = novo;
	else
	{
		ant = aux = *LA;
		while(aux!=NULL&&aux->no->frq<=frq)
		{
			ant = aux;
			aux = aux->prox;
		}
		if(aux==NULL)
			ant->prox = novo;
		else
		{
			if(aux==ant)
			{
				novo->prox = aux;
				*LA = novo;
			}
			else
			{
				novo -> prox = aux;
				ant -> prox = novo;
			}
		}
	}
	novo->no = criaNo(simb,frq);
	novo->no->esq = (*antP)->no;
	novo->no->dir = (*auxP)->no;
}
void exclusaoLA(LArv**LA,int simb)
{
	LArv *aux,*ant;
	ant = aux = *LA;
	while(aux!=NULL && aux->no->simb!=simb)
	{
		ant = aux;
		aux = aux->prox;
	}
	if(aux==NULL)
		printf("Simbolo nao encontrado");
	else
	{
		if(aux==ant)
			*LA = aux->prox;	
		else
			ant-> prox = aux -> prox;
		free(aux);
	}
}
