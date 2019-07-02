#include <iostream>

class Chave
{
private:
	struct no
	{
		int Chave;
		int Endereco;
		char fbal;
		no *esq, *dir;	
	}*T;
	void Tins(no **, int, long, char *);
	int Tfind(no *, int);
	char Trem(no **, int);
	void RD(no **);
	void RE(no **);
	int emordem(no *);
	no* getmax(no **T)
	{
		{
			if ((*T)->dir == NULL)
			{
				no *P = *T;
				*T = P->esq;
				return P;
			}
			else  getmax(&((*T)->dir));
			return 0;
		}
	}
public:
	Chave();
	void Insere(int, long);
	char Remove(int);
	int Procura(int);
	int PercursoEmOrdem();
};


Chave::Chave()
{
	T = NULL;
}

void Chave::Insere(int Chv, long End)
{
	char H;
	Tins(&T, Chv, End, &H);
}

char Chave::Remove(int Chv)
{
	return Trem(&T, Chv);
}

int Chave::Procura(int Chv)
{
	return Tfind(T, Chv);
}

void Chave::Tins(no **T, int Chv, long End, char *H)
{
	if (!(*T))
	{
		*T = new no;
		(*T)->fbal = 0;
		(*T)->Chave = Chv;
		(*T)->Endereco = End;
		(*T)->esq = (*T)->dir = NULL;
		*H = 1;
	}
	else
	{
		if (Chv < (*T)->Chave)
		{
			Tins(&((*T)->esq), Chv, End, H);
			if (*H)
			{
				switch ((*T)->fbal)
				{
				case 1:
					(*T)->fbal = 0;
					*H = 0;
					break;
				case 0:
					(*T)->fbal = -1;
					break;
				case -1:
					RD(T);
					*H = 0;
					break;
				}
			}
		}
		else
		{
			Tins(&((*T)->dir), Chv, End, H);
			if (*H)
			{
				switch ((*T)->fbal)
				{
				case -1:
					(*T)->fbal = 0;
					*H = 0;
					break;
				case 0:
					(*T)->fbal = 1;
					break;
				case 1:
					RE(T);
					*H = 0;
					break;
				}
			}
		}
	}
}

int Chave::Tfind(no *T, int C)
{
	if (T == NULL)
		return -1;
	if (T->Chave == C)
		return T->Endereco;
	if (C < T->Chave)
		return Tfind(T->esq, C);
	else
		return Tfind(T->dir, C);

}
void Chave::RD(no **T)
{
	no *pB = (*T)->esq;
	if (pB->fbal == -1)
	{
		(*T)->esq = pB->dir;
		pB->dir = (*T);
		(*T)->fbal = 0;
		pB->fbal = 0;
		*T = pB;
	}
	else
	{
		no *pC = pB->dir;
		pB->dir = pC->esq;
		pC->esq = pB;
		(*T)->esq = pC->dir;
		pC->dir = *T;
		if (pC->fbal == 1)
		{
			pB->fbal = -1;
			(*T)->fbal = 0;
		}
		else {
			pB->fbal = 0;
			(*T)->fbal = 1;
		}
		(*T)->fbal = 0;
	}
}

void Chave::RE(no **T)
{
	no *pB = (*T)->dir;
	if (pB->fbal == 1)
	{
		(*T)->dir = pB->esq;
		pB->esq = (*T);
		(*T)->fbal = 0;
		pB->fbal = 0;
		*T = pB;
	}
	else
	{
		no *pC = pB->esq;
		pB->esq = pC->dir;
		pC->dir = pB;
		(*T)->dir = pC->esq;
		pC->esq = *T;
		if (pC->fbal == -1)
		{
			pB->fbal = 1;
			(*T)->fbal = 0;
		}
		else {
			pB->fbal = 0;
			(*T)->fbal = -1;
		}
		*T = pC;
		(*T)->fbal = 0;
	}
}

char Chave::Trem(no **T, int Chv)
{
	if (*T == NULL) return 0;
	if ((*T)->Chave == Chv)
	{
		no *P = *T;
		if ((*T)->dir == NULL)
			*T = P->esq;
		else if ((*T)->esq == NULL)
			*T = P->dir;
		else {
			P = getmax(&((*T)->esq));
			(*T)->Chave = P->Chave;
		}
		delete P;
		return 1;
	}
	else
		if (Chv < (*T)->Chave)
			Trem(&((*T)->esq), Chv);
		else Trem(&((*T)->dir), Chv);
}

int Chave::emordem(no *T)
{
	if (T != NULL)
	{
		emordem(T->esq);
		return T->Chave;
		emordem(T->dir);
	}
}

int Chave::PercursoEmOrdem()
{
	return emordem(T);
}
