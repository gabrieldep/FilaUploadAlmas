#include "Fila.h"
#include <cstddef>

Fila::Fila()
{
	tamanho = 0;
	frente = new TipoCelula;
	tras = frente;
}

Fila::~Fila()
{
	Limpa();
	delete frente;
}

int Fila::GetTamanho()
{
	return tamanho;
}

bool Fila::Vazia()
{	
	return tamanho == 0;
}

void Fila::Enfileira(TipoCelula tipoCelula)
{
	TipoCelula* nova;

	nova = new TipoCelula();
	nova->SetChave(tipoCelula.GetChave());
	tras->prox = nova;
	tras = nova;
	tamanho++;
}

TipoCelula Fila::Desenfilera()
{
	TipoCelula* p;
	TipoCelula aux;

	if (tamanho == 0) {
		throw "Fila vazia";
	}

	aux = *frente->prox;
	p = frente;
	frente = frente->prox;
	delete p;
	tamanho--;
	return aux;
}

void Fila::Limpa()
{
	TipoCelula* p;

	p = frente->prox;
	while (p != NULL) {
		frente->prox = p->prox;
		delete p;
		p = frente->prox;
	}
	tamanho = 0;
	tras = frente;
}