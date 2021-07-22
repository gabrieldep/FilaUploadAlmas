#include <iostream>
#include "Fila.h"
#include <string>

void Info(Fila* servidor, std::string mensagem) {
	TipoCelula* tipoCelula = new TipoCelula();
	tipoCelula->SetChave(mensagem);
	servidor->Enfileira(*tipoCelula);
	delete tipoCelula;
}

void Tran(Fila* servidor1, Fila* servidor2) {
	int n = servidor1->GetTamanho();
	for (int i = 0; i < n; i++) {
		servidor2->Enfileira(servidor1->Desenfilera());
	}
}

void Erro(Fila* servidor) {
	TipoCelula tc;
	std::cout << "ERRO <S>" << "\n";
	int n = servidor->GetTamanho();
	for (int i = 0; i < n; i++) {
		tc = servidor->Desenfilera();
		tc.Imprime();
	}
}

void Send(Fila(&servidores)[20], Fila* historico) {
	TipoCelula tc;
	for (int i = 0; i < 20; i++) {
		if (servidores[i].GetTamanho() != 0) {
			tc = servidores[i].Desenfilera();
			historico->Enfileira(tc);
		}
	}
}

void Flush(Fila(&servidores)[20], Fila* historico) {
	TipoCelula tc;
	int n = historico->GetTamanho();
	for (int i = 0; i < n; i++) {
		tc = historico->Desenfilera();
		tc.Imprime();
		historico->Enfileira(tc);
	}

	for (int j = 0; j < 20; j++) {
		int n = servidores[j].GetTamanho();
		for (int i = 0; i < n; i++) {
			tc = servidores[j].Desenfilera();
			tc.Imprime();
			servidores[j].Enfileira(tc);
		}
	}
}

void Warn(Fila* servidor, int posicao) {
	Fila* auxiliar = new Fila();
	TipoCelula tc;
	for (int i = 0; i < posicao - 1; i++) {
		auxiliar->Enfileira(servidor->Desenfilera());
	}

	tc = servidor->Desenfilera();
	while(!servidor->Vazia()) {
		auxiliar->Enfileira(servidor->Desenfilera());
	}

	servidor->Enfileira(tc);
	int n = auxiliar->GetTamanho();
	while (!auxiliar->Vazia()) {
		servidor->Enfileira(auxiliar->Desenfilera());
	}
}

int main()
{
	Fila* historico = new Fila();
	Fila servidores[20];
	Info(&servidores[0], "Patricia");
	Info(&servidores[0], "Silvino");
	Info(&servidores[1], "Gabriel");
	Info(&servidores[1], "Vini");
	Info(&servidores[1], "Sonia");
	Info(&servidores[1], "Joao");
	Info(&servidores[1], "Cesar");
	Info(&servidores[2], "Daniel");
	Info(&servidores[2], "Mateus");
	Info(&servidores[3], "Barbara");
	Info(&servidores[3], "Lorena");

	Warn(&servidores[1], 3);
	Send(servidores, historico);
	Flush(servidores, historico);

	Tran(&servidores[1], &servidores[2]);

	Erro(&servidores[2]);
}