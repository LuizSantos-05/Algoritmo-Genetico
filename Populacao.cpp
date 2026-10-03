#include "Populacao.hpp"
#include "Otimizacao.hpp"

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

vector<bool> Populacao::getElitismoBool()
{
    return _elitismoBool;
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

vector<Individuo> &Populacao::getIndividuos()
{
    return _individuos;
}

const vector<Individuo> &Populacao::getIndividuos() const
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

void Populacao::novaGeracao(int numeroOperacao)
{
    vector<Individuo> novaPopulacao;    // vetor de nova população
    int novoTamanho = _tamanho / 2;     // tamanho da nova população (metade da população atual)
    _tamanho = novoTamanho;             // atualiza o tamanho da população
    novaPopulacao.reserve(novoTamanho); // reserva espaço para a nova população

    for (int i = 0; i < novoTamanho; i++)
    {
        Individuo filho;
        if (numeroOperacao < _elitismo)
        {
            // Se o valor de elitismo for ímpar, seleciona o melhor indivíduo da elite
            filho = _individuos[i].cruzamentoElitista(*this); // realiza o cruzamento elitista entre os indivíduos da população
        }
        else
        {
            filho = _individuos[i].cruzamento(_individuos); // realiza o cruzamento entre os indivíduos da população
        }
        novaPopulacao.push_back(filho); // adiciona o indivíduo filho à nova população
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

bool Populacao::avaliarMelhorPopulacao(const Populacao &populacao)
{
    const vector<Individuo> &individuos = populacao.getIndividuos();
    for (const Individuo &individuo : individuos)
    {
        if (individuo.getFitness() == 905)
        {
            continue; // Este indivíduo é o melhor possível, avaliando o próximo indivíduo
        }
        else
        {
            return false; // Encontrou um indivíduo que não é o melhor possível
        }
    }
    return true; // Todos os indivíduos são o melhor possível
}