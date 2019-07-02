#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Arvore.h"

using namespace std;

struct REGISTRO
{
	int Chave;
	char Nome[30];
	int NumConta;
	int NumAg;
	char Tel[15];
	char CPF[11];
	double Sal;
	char Status;
}R;
void InicializaArvore(Chave *T, FILE *arq)
{
	REGISTRO Rg;
	arq = fopen("registros.dat", "rb+");
	fseek(arq, 0, SEEK_END);
	if (arq != NULL)
	{
		long n = sizeof(REGISTRO);
		long m = (ftell(arq) / n);
		for (long i = 0; i < m; i++)
		{
			fseek(arq, sizeof(REGISTRO) * i, 0);
			fread(&Rg, sizeof(REGISTRO), 1, arq);
			if(Rg.Status == 1)
				T->Insere(Rg.Chave, i);
		}
	}
	fclose(arq);
}

void main()
{
	FILE *reg;	
	Chave *T1= new Chave;
	REGISTRO R;
	int OP;
	int Teste;
	char NomeArq[20];
	long n, m;
	int End;
	char ok;

	reg = fopen("registros.dat", "rb+");
	if (reg == NULL)
		reg = fopen("registros.dat", "wb+");
	reg = fopen("registros.dat", "rb+");
	InicializaArvore(T1, reg);
	fclose(reg);
	do
	{
		system("CLS");
		cout << "=============================================================" << endl;
		cout << "||                      SystemBank                         ||" << endl;
		cout << "=============================================================" << endl;
		cout << "\nMENU" << endl;
		cout << "1. Cadastrar Clientes" << endl;
		cout << "2. Consultar Clientes" << endl;
		cout << "3. Alterar Clientes" << endl;
		cout << "4. Remover Clientes" << endl;
		cout << "5. Emitir um relatorio" << endl;
		cout << "6. Sair" << endl;
		cout << "\nDigite sua opcao: ";
		cin >> OP;
		
		switch (OP)
		{
			case 1://CADASTRAR
				reg = fopen("registros.dat", "rb+");
				if (reg == NULL)
				{
					cout << "ERRO ao abrir o registro!" << endl;
					return;
				}

				fseek(reg, 0, SEEK_END);
				n = sizeof(REGISTRO);
				m = (ftell(reg) / n);

				cout << "Digite o nome do cliente...: ";
				cin >> R.Nome;
				cout << "Digite o codigo do cliente.: ";
				cin >> R.Chave;
				cout << "Digite o numero da conta...: ";
				cin >> R.NumConta;
				cout << "Digite o numero da agencia.: ";
				cin >> R.NumAg;
				cout << "Digite o telefone..........: ";
				cin >> R.Tel;
				cout << "Digite o CPF...............: ";
				cin >> R.CPF;
				cout << "Digite o saldo disponivel..: ";
				cin >> R.Sal;
				R.Status = 1;
				if (T1->Procura(R.Chave) > -1)
					cout << "\nJa existe um cliente cadastrado com esse codigo!" << endl;
				else
				{
					fseek(reg, 0, 2);
					fwrite(&R, sizeof(REGISTRO), 1, reg);
					cout << "\nCLIENTE CADASTRADO!" << endl;
					T1->Insere(R.Chave, m);
				}
				fclose(reg);
				system("pause");
				break;
			case 2://CONSULTAR
				cout << "\nDigite o codigo do cliente: ";
				cin >> Teste;
				
				if (T1->Procura(Teste) > -1)
				{
					End = T1->Procura(Teste);
					reg = fopen("registros.dat", "rb+");
					if (reg == NULL)
					{
						cout << "ERRO ao abrir o registro!" << endl;
						system("pause");
						return;
					}
					fseek(reg, 0, SEEK_END);
					fseek(reg, sizeof(REGISTRO) * (End), 0);
					fread(&R, sizeof(REGISTRO), 1, reg);
					if (R.Status == 1)
					{
						cout << "\nNome do cliente..: " << R.Nome;
						cout << "\nCodigo do cliente: " << R.Chave;
						cout << "\nNumero da conta..: " << R.NumConta;
						cout << "\nNumero da agencia: " << R.NumAg;
						cout << "\nTelefone.........: " << R.Tel;
						cout << "\nDeposito inicial.: " << R.Sal << endl;
					}
					else
						cout << "\nRegistro inexistente!" << endl;
					fclose(reg);
				}
				else
					cout << "\nCliente inexistente ou codigo invalido!" << endl;
				system("pause");
				break;
			case 3://ALTERAR
				cout << "\nDigite o codigo do cliente: ";
				cin >> Teste;

				if (T1->Procura(Teste) > -1)
				{
					End = T1->Procura(Teste);
					reg = fopen("registros.dat", "rb+");
					if (reg == NULL)
					{
						cout << "ERRO ao abrir o registro!" << endl;
						system("pause");
						return;
					}
					fseek(reg, 0, SEEK_END);
					fseek(reg, sizeof(REGISTRO) * End, 0);
					fread(&R, sizeof(REGISTRO), 1, reg);

					cout << "\nNome do cliente..: " << R.Nome;
					cout << "\nCPF do cliente...: " << R.CPF;
					cout << "\nNumero da conta..: " << R.NumConta;
					cout << "\nNumero da agencia: " << R.NumAg;
					cout << "\nTelefone.........: " << R.Tel;
					cout << "\nDeposito inicial.: " << R.Sal << endl;

					cout << "\nDeseja alterar?(s/n): ";
					cin >> ok;
					if ((ok == 's') || (ok == 'S'))
					{	
						cout << "\nDigite o nome do cliente..: ";
						cin >> R.Nome;
						cout << "Digite o numero da conta..: ";
						cin >> R.NumConta;
						cout << "Digite o numero da agencia: ";
						cin >> R.NumAg;
						cout << "Digite o telefone.........: ";
						cin >> R.Tel;
						cout << "Digite o CPF..............: ";
						cin >> R.CPF;

						fseek(reg, sizeof(REGISTRO) * End, 0);
						fwrite(&R, sizeof(REGISTRO), 1, reg);
						T1->Remove(Teste);
						T1->Insere(R.Chave, End);
						cout << "\nRegistro alterado com sucesso!" << endl;
					}
					fclose(reg);
				}
				else
					cout << "\nCliente inexistente ou codigo invalido!" << endl;
				system("pause");
				break;
			case 4://APAGAR
				cout << "\nDigite o codigo do cliente: ";
				cin >> Teste;

				if (T1->Procura(Teste) > -1)
				{
					End = T1->Procura(Teste);
					reg = fopen("registros.dat", "rb+");
					if (reg == NULL)
					{
						cout << "ERRO ao abrir o registro!" << endl;
						system("pause");
						return;
					}
					fseek(reg, 0, SEEK_END);
					fseek(reg, sizeof(REGISTRO) * End, 0);
					fread(&R, sizeof(REGISTRO), 1, reg);

					cout << "\nNome do cliente..: " << R.Nome;
					cout << "\nCPF do cliente...: " << R.CPF;
					cout << "\nNumero da conta..: " << R.NumConta;
					cout << "\nNumero da agencia: " << R.NumAg;
					cout << "\nTelefone.........: " << R.Tel;
					cout << "\nDeposito inicial.: " << R.Sal << endl;

					cout << "\nDeseja realmente apagar?(s/n): ";
					cin >> ok;
					if ((ok == 's') || (ok == 'S'))
					{
						R.Status = 0;
						fseek(reg, sizeof(REGISTRO) * End, 0);
						fwrite(&R, sizeof(REGISTRO), 1, reg);
						T1->Remove(Teste);
						cout << "\nRegistro removido com sucesso!" << endl;
					}
					fclose(reg);
				}
				else 
					cout << "\nCliente inexistente ou codigo invalido!" << endl;
				system("pause");
				break;
			case 5://RELATORIO
				reg = fopen("registros.dat", "rb+");
				if (reg == NULL)
				{
					cout << "Nao ha arquivo de registros!" << endl;
					system("pause");
				}
				else
				{
					fseek(reg, 0, SEEK_END);
					cout << "\nDigite o nome do arquivo a ser gerado: ";
					cin >> NomeArq;
					strcat(NomeArq, ".txt");
					FILE *arqtxt = fopen(NomeArq, "w");
					if (!arqtxt)
					{
						cout << "Nao foi possivel criar esse arquivo!" << endl;
						system("pause");
						return;
					}
					fprintf(arqtxt, "                                    CLIENTES COM POPANÇA PRÉVIA                                    \n");
					fprintf(arqtxt, "\n");
					fprintf(arqtxt, "===================================================================================================\n");
					fprintf(arqtxt, "Nome                          Código   Conta  Agência  Telefone        CPF         Poupança Inicial\n");
					fprintf(arqtxt, "===================================================================================================\n");
					fprintf(arqtxt, "\n");
					
					n = sizeof(REGISTRO);
					m = (ftell(reg) / n);
					
					for (long i = 0; i < m; i++)
					{
						fseek(reg, sizeof(REGISTRO) * i, 0);
						fread(&R, sizeof(REGISTRO), 1, reg);
						if ((R.Status == 1) && (R.Sal > 0))
							fprintf(arqtxt, "%-30s%-9d%-7d%-9d%-16s%-12s%-16.2f\n", R.Nome, R.Chave, R.NumConta, R.NumAg, R.Tel, R.CPF, R.Sal);
						
					}
					fprintf(arqtxt, "===================================================================================================\n");
					fclose(arqtxt);
					cout << "\nRelatorio gerado com sucesso!" << endl;
					system("pause");
				}
				fclose(reg);
				break;
		}
	} while (OP != 6);
}
