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

int main()
{
	Fila* historico = new Fila();
	Fila servidores[20];
	Info(&servidores[0], "Patricia");
	Info(&servidores[0], "Silvino");
	Info(&servidores[1], "Gabriel");
	Info(&servidores[1], "Vini");
	Info(&servidores[2], "Daniel");
	Info(&servidores[2], "Mateus");
	Info(&servidores[3], "Barbara");
	Info(&servidores[3], "Lorena");


	Send(servidores, historico);

	Tran(&servidores[1], &servidores[2]);

	Erro(&servidores[2]);
}