#include <iostream>
#include "Fila.h"
#include <string>
#include <cstddef>


void Info(Fila* servidor, std::string mensagem)
{
	TipoCelula* tipoCelula = new TipoCelula();
	tipoCelula->SetChave(mensagem);
	servidor->Enfileira(*tipoCelula);
	delete tipoCelula;
}

void Tran(Fila* servidor1, Fila* servidor2)
{
	int n = servidor1->GetTamanho();
	for (int i = 0; i < n; i++)
	{
		servidor2->Enfileira(servidor1->Desenfilera());
	}
}

void Erro(Fila* servidor)
{
	TipoCelula tc;
	std::cout << "ERRO <S>" << "\n";
	int n = servidor->GetTamanho();
	for (int i = 0; i < n; i++)
	{
		tc = servidor->Desenfilera();
		tc.Imprime();
	}
}

void Send(Fila(&servidores)[20], Fila* historico)
{
	TipoCelula tc;
	for (int i = 0; i < 20; i++)
	{
		if (servidores[i].GetTamanho() != 0)
		{
			tc = servidores[i].Desenfilera();
			historico->Enfileira(tc);
		}
	}
}

void Flush(Fila(&servidores)[20], Fila* historico)
{
	TipoCelula tc;
	int n = historico->GetTamanho();
	for (int i = 0; i < n; i++)
	{
		tc = historico->Desenfilera();
		tc.Imprime();
		historico->Enfileira(tc);
	}

	for (int j = 0; j < 20; j++)
	{
		int n = servidores[j].GetTamanho();
		for (int i = 0; i < n; i++)
		{
			tc = servidores[j].Desenfilera();
			tc.Imprime();
			servidores[j].Enfileira(tc);
		}
	}
}

void Warn(Fila* servidor, int posicao)
{
	Fila* auxiliar = new Fila();
	TipoCelula tc;
	for (int i = 0; i < posicao - 1; i++)
	{
		auxiliar->Enfileira(servidor->Desenfilera());
	}

	tc = servidor->Desenfilera();
	while (!servidor->Vazia())
	{
		auxiliar->Enfileira(servidor->Desenfilera());
	}

	servidor->Enfileira(tc);
	int n = auxiliar->GetTamanho();
	while (!auxiliar->Vazia())
	{
		servidor->Enfileira(auxiliar->Desenfilera());
	}
}

int main(int argc, char* argv[])
{
	char Linha[100];
	char* result;
	int i;
	int numeroDeServidores = 0;
	FILE* arquivo = fopen("C:/Users/Gabriel/Documents/Arquivo.txt", "rt");
	i = 1;
	Fila servidores[20];
	Fila* historico = new Fila();
	while (!feof(arquivo))
	{
		result = fgets(Linha, 100, arquivo);
		std::string s = result;

		std::string command = s.substr(0, 4);
		if (command == "INFO")
		{
			int servidor = std::stoi(s.substr(4, 4));
			int posicaoFinal = s.length() - 10;
			std::string mensagem = s.substr(8, posicaoFinal);
			Info(&servidores[servidor], mensagem);
		}
		else if (command == "WARN")
		{
			int server = std::stoi(s.substr(4, 4));
			int posicao = std::stoi(s.substr(6, 6));
			Warn(&servidores[server], posicao);
		}
		else if (command == "TRAN")
		{
			int server1 = std::stoi(s.substr(4, 4));
			int server2 = std::stoi(s.substr(6, 6));
			Tran(&servidores[server1], &servidores[server2]);
		}
		else if (command == "ERRO")
		{
			int server = std::stoi(s.substr(4, 4));
			Erro(&servidores[server]);
		}
		else if (command == "SEND")
		{
			Send(servidores, historico);
		}
		else if (command == "FLUS")
		{
			Flush(servidores, historico);
		}
		else
		{
			numeroDeServidores = *result - 48;
			Fila servidores[20];
		}
	}
	fclose(arquivo);
	return 0;
}