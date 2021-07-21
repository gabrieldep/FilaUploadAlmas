#include "TipoItem.h"
#include <iostream>
#include <string>

TipoItem::TipoItem()
{
	this->chave = -1;
}

TipoItem::TipoItem(std::string caractere)
{
	this->chave = caractere;
}

void TipoItem::SetChave(std::string caractere)
{
	this->chave = caractere;
}

std::string TipoItem::GetChave()
{
	return this->chave;
}

void TipoItem::Imprime()
{
	std::string a = GetChave();
	std::cout << a;
}
