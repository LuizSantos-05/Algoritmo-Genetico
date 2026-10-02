#include "Populacao.hpp"

Populacao::Populacao(int tamanho)
{
    _tamanho = tamanho;
    _individuos.reserve(tamanho);          // reserva espaço para os indivíduos
    _elitismo = tamanho * 0.005;           // define a quantidade de indivíduos que serão mantidos na próxima geração (0,5% da população)
    _elitismoBool.resize(_elitismo, true); // inicializa o vetor de elitismo com valores true
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

void Populacao::decrementarElitismo()
{
    if (_elitismo > 0)
    {
        _elitismo--;
    }
}

void Populacao::decrementarElitismoBool()
{
    for (int i = 0; i < _elitismoBool.size(); i++)
    {
        if (_elitismoBool[i])
        {
            _elitismoBool[i] = false;
            break;
        }
    }
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

void Populacao::ordenarElitismo()
{
    for (int i = 0; i < _elitismo; i++)
    {
        for (int j = i + 1; j < _tamanho - 1; j++)
        {
            if (_individuos[i].getFitness() < _individuos[j].getFitness())
            {
                swap(_individuos[i], _individuos[j]);
            }
        }
    }
}