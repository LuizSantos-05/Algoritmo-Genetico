#include "Otimizacao.hpp"

Individuo::Individuo()
{
    // inicializa os cromossomos com valores aleatórios entre 0 e 15
    _x = (rand() % 150) / 10.0;
    _y = (rand() % 150) / 10.0;

    // calcula o fitness do indivíduo
    _fitness = calcularFitness(_x, _y);
}

codificacao Individuo::getX() const { return _x; }
codificacao Individuo::getY() const { return _y; }

codificacao Individuo::setX(codificacao x) { _x = x; }
codificacao Individuo::setY(codificacao y) { _y = y; }

double Individuo::getFitness() const { return _fitness; }
void Individuo::setFitness(double fitness) { _fitness = fitness; }

// modulo do fitness. Aqui calcula-se a funcao fitnes com base nos parametros da funcao
double Individuo::calcularFitness(int x, int y)
{
    double fitness = (2 * (pow(x, 2))) - (13 * x) + (x * y) - (7 * (y / 3));
    return fitness;
}

// modulo da selecao. Aqui o individuo e escolhido por roleta, de maneira aleatoria
int Individuo::selecao(int tamanhoPopulacao)
{
    int aleatorio = rand() % tamanhoPopulacao;
    return aleatorio;
}

// modulo do cruzamento
Individuo Individuo::cruzamento(vector<Individuo> &populacao)
{
    // aqui decretamos que o contador deve estar zerado e que o numero de pais e limitado a 2
    int contador = 0;
    int pais[2];

    // enquanto o contador for menor que dois, realiza-se o processo de cruzamento
    while (contador < 2)
    {
        int tamanhoPopulacao = populacao.size();
        if (contador == 0)
        {
            pais[contador] = selecao(tamanhoPopulacao);
            contador++;
        }
        else
        {
            pais[contador] = selecao(tamanhoPopulacao);
            if (pais[contador] == pais[contador - 1])
            {
                continue;
            }
            else
            {
                contador++;
            }
        }
    }

    // identifica o melhor e o pior pai com base no fitness
    Individuo paiX = populacao[pais[0]];
    Individuo paiY = populacao[pais[1]];

    Individuo melhorPai = (paiX.getFitness() > paiY.getFitness()) ? paiX : paiY;
    Individuo piorPai = (paiX.getFitness() > paiY.getFitness()) ? paiY : paiX;

    // gera um fator r aleatorio dentro do intervalo de [0,1]
    double r = (double)rand() / RAND_MAX;

    // formula do cruzamento heuristico
    double novoX = melhorPai.getX() + r * (melhorPai.getX() - piorPai.getX());
    double novoY = melhorPai.getY() + r * (melhorPai.getY() - piorPai.getY());

    // validar o intervalo da funcao 10
    if (novoX > 15.0)
        novoX = 15.0;
    if (novoX < -15.0)
        novoX = -15.0;

    if (novoY > 15.0)
        novoY = 15.0;
    if (novoY < -15.0)
        novoY = -15.0;

    // declaracao do individuo filho
    Individuo filho(novoX, novoY);

    return filho;
}

Individuo Individuo::cruzamentoElitista(Populacao &populacao)
{
    populacao.ordenarElitismo(); // Ordena a população com base no fitness
    int primeiroElitista = 0;    // Índice do melhor indivíduo da elite
    for (int i = primeiroElitista; i < populacao.getElitismo(); i++)
    {
        if (populacao.getElitismoBool()[i]) // Verifica se o indivíduo ainda está na elite
        {
            primeiroElitista = i;
            break;
        }
    }
    if (populacao.getElitismo() % 2) // Se o valor de elitismo for ímpar, seleciona o último individuo da elite e aleatorisa o outro
    {
        int tamanhoPopulacao = populacao.getTamanho();
        int aleatorio = rand() % (tamanhoPopulacao - populacao.getElitismo());
        Individuo pai1 = populacao.getIndividuos()[primeiroElitista]; // Primeiro indivíduo da elite
        Individuo pai2 = populacao.getIndividuos()[aleatorio];        // Indivíduo aleatório fora da elite

        // Gera um fator r aleatório dentro do intervalo de [0,1]
        double r = (double)rand() / RAND_MAX;

        // Fórmula do cruzamento heurístico
        double novoX = pai1.getX() + r * (pai1.getX() - pai2.getX());
        double novoY = pai1.getY() + r * (pai1.getY() - pai2.getY());

        // Valida o intervalo da função [-15, 15]
        if (novoX > 15.0)
            novoX = 15.0;
        if (novoX < -15.0)
            novoX = -15.0;

        if (novoY > 15.0)
            novoY = 15.0;
        if (novoY < -15.0)
            novoY = -15.0;

        // Declaração do indivíduo filho
        Individuo filho(novoX, novoY);

        return filho;
    }
    else
    {
        // Se o valor de elitismo for par, seleciona os dois melhores indivíduos da elite
        Individuo pai1 = populacao.getIndividuos()[primeiroElitista];     // Melhor indivíduo da elite
        Individuo pai2 = populacao.getIndividuos()[primeiroElitista + 1]; // Segundo melhor indivíduo da elite

        // Gera um fator r aleatório dentro do intervalo de [0,1]
        double r = (double)rand() / RAND_MAX;

        // Fórmula do cruzamento heurístico
        double novoX = pai1.getX() + r * (pai1.getX() - pai2.getX());
        double novoY = pai1.getY() + r * (pai1.getY() - pai2.getY());

        // Valida o intervalo da função [-15, 15]
        if (novoX > 15.0)
            novoX = 15.0;
        if (novoX < -15.0)
            novoX = -15.0;

        if (novoY > 15.0)
            novoY = 15.0;
        if (novoY < -15.0)
            novoY = -15.0;

        // Declaração do indivíduo filho
        Individuo filho(novoX, novoY);
        populacao.decrementarElitismoBool(); // Decrementa o valor de elitismo para a próxima geração
        populacao.decrementarElitismo();     // Decrementa o valor de elitismo para a próxima geração
        populacao.decrementarElitismoBool(); // Decrementa novamente para considerar os dois melhores indivíduos da elite
        populacao.decrementarElitismo();     // Decrementa novamente para considerar os dois melhores indivíduos da elite

        return filho;
    }
}

bool Individuo::sortearMutacao(int percentual)
{
    int aleatorio = rand() % 100;
    return aleatorio < percentual;
}

void Individuo::mutacao(int limite_inferior, int limite_superior, Populacao &populacao, Individuo &individuo)
{
    int tamanhoPopulacao = populacao.getTamanho();
    int sorteio = rand() % tamanhoPopulacao;                           // Escolhe um indivíduo aleatório da população
    Individuo &individuoSorteado = populacao.getIndividuos()[sorteio]; // Referência ao indivíduo sorteado

    int cromossomoSorteado = (rand() % 30) / 10; // Escolhe aleatoriamente qual cromossomo será mutado (0: x, 1: y, 2: z)
}