#include <iostream>
#include "Fila.h"
#include <string>
#include <cstddef>


/// <summary>
/// Adiciona uma alma ao buffer solicitado
/// </summary>
/// <param name="servidor">Servidor onde a alma será adicionada</param>
/// <param name="mensagem">Alma a ser adicionada</param>
void Info(Fila* servidor, std::string mensagem)
{
	TipoCelula* tipoCelula = new TipoCelula();
	tipoCelula->SetChave(mensagem);
	servidor->Enfileira(*tipoCelula);
	delete tipoCelula;
}

/// <summary>
/// Transfere as almas de um servidor 1 para outro.
/// </summary>
/// <param name="servidor1">Servidor de onde virão as almas</param>
/// <param name="servidor2">Servidor para onde irão as almas</param>
void Tran(Fila* servidor1, Fila* servidor2)
{
	int n = servidor1->GetTamanho();
	for (int i = 0; i < n; i++)
	{
		servidor2->Enfileira(servidor1->Desenfilera());
	}
}

/// <summary>
/// Imprime as almas de um servidor que ocorreu um erro.
/// </summary>
/// <param name="servidor">Servidor onde as almas estão.</param>
/// <param name="numeroServer">Indice do servidor</param>
void Erro(Fila* servidor, int numeroServer)
{
	TipoCelula tc;
	std::cout << "ERRO " << numeroServer << "\n";
	int n = servidor->GetTamanho();
	for (int i = 0; i < n; i++)
	{
		tc = servidor->Desenfilera();
		tc.Imprime();
	}
}

/// <summary>
/// Envia as primeiras almas de cada servidor.
/// </summary>
/// <param name="servidores">Array com os servidores.</param>
/// <param name="historico">Fila com o historico de envios.</param>
void Send(Fila(&servidores)[2000], Fila* historico, int tamanho)
{
	TipoCelula tc;
	for (int i = 0; i < tamanho; i++)
	{
		if (servidores[i].GetTamanho() != 0)
		{
			tc = servidores[i].Desenfilera();
			historico->Enfileira(tc);
		}
	}
}

/// <summary>
/// Imprime todas as almas do historico e de cada servidor.
/// </summary>
/// <param name="servidores">Array com os servidores.</param>
/// <param name="historico">Fila com o historico de almas.</param>
void Flush(Fila(&servidores)[2000], Fila* historico, int tamanho)
{
	TipoCelula tc;
	int n = historico->GetTamanho();
	for (int i = 0; i < n; i++)
	{
		tc = historico->Desenfilera();
		tc.Imprime();
		historico->Enfileira(tc);
	}

	for (int j = 0; j < tamanho; j++)
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

/// <summary>
/// Move o valor de determinada posicao para a primeira colocação da fila.
/// </summary>
/// <param name="servidor">Servidor de onde deve-se mover a alma.</param>
/// <param name="posicao">Index da alma.</param>
void Warn(Fila* servidor, int posicao)
{
	posicao++;
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
	FILE* arquivo = fopen(argv[1], "rt");
	int numeroDeServidores = *fgets(Linha, 100, arquivo) - 48;
	i = 1;
	Fila servidores[2000];
	Fila* historico = new Fila();
	while (!feof(arquivo))
	{
		result = fgets(Linha, 100, arquivo);

		if (result == NULL)break;

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
			Erro(&servidores[server], server);
		}
		else if (command == "SEND")
		{
			Send(servidores, historico, numeroDeServidores);
		}
		else if (command == "FLUS")
		{
			Flush(servidores, historico, numeroDeServidores);
		}
		else
		{
			numeroDeServidores = *result - 48;
		}
	}
	fclose(arquivo);
	return 0;
}