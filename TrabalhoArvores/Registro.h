#include <iostream>
#include "Arvore.h"
struct REGISTRO
{
	int Chave;
	char Nome[30];
	int NumConta;
	int NumAg;
	char Tel[15];
	char CPF[11];
	double Sal;
}R;

void InicializaArvore(Chave *T, REGISTRO *Rg, FILE *arq)
{
	arq = fopen("registros.dat", "rb+");
	fseek(arq, 0, SEEK_END);
	if (arq != NULL)
	{
		long n = sizeof(REGISTRO);
		long m = (ftell(arq) / n) + 1;
		for (long i = 0; i < m; i++)
		{
			fseek(arq, sizeof(REGISTRO) * (i - 1), 0);
			fread(&Rg, sizeof(REGISTRO), 1, arq);
			T->Insere(Rg->Chave, i + 1);
		}
	}
	fclose(arq);
}

