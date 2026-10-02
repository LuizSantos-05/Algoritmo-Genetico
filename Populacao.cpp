#include "Populacao.hpp"

Populacao::Populacao(int tamanho)
{
    _tamanho = tamanho;
    _individuos.reserve(tamanho); // reserva espaço para os indivíduos
    _elitismo = tamanho * 0.005;  // define a quantidade de indivíduos que serão mantidos na próxima geração (0,5% da população)
}

Populacao::~Populacao()
{
    _individuos.clear(); // limpa o vetor de indivíduos
}

int Populacao::getTamanho() const
{
    return _tamanho;
}

int Populacao::getElitismo() const
{
    return _elitismo;
}

vector<Individuo> Populacao::getIndividuos() const
{
    return _individuos;
}

void Populacao::inicializarPopulacao()
{
    for (int i = 0; i < _tamanho; i++)
    {
        Individuo individuo;              // cria um novo indivíduo
        _individuos.push_back(individuo); // adiciona o indivíduo à população
    }
}

void Populacao::novaGeracao()
{
    vector<Individuo> novaPopulacao;    // vetor de nova população
    int novoTamanho = _tamanho / 2;     // tamanho da nova população (metade da população atual)
    novaPopulacao.reserve(novoTamanho); // reserva espaço para a nova população

    for (int i = 0; i < novoTamanho; i++)
    {
        Individuo filho; // cria um novo indivíduo
        novaPopulacao.push_back(filho);
    }
    _individuos = novaPopulacao; // atualiza a população com a nova população
}