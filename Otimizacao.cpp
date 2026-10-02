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
void Individuo::cruzamento(vector<Individuo> &populacao)
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
    
    //identifica o melhor e o pior pai com base no fitness
    Individuo paiX = populacao[pais[0]];
    Individuo paiY = populacao[pais[1]];
    
    Individuo melhorPai = (paiX.getFitness() > paiY.getFitness()) ? paiX : paiY;
    Individuo piorPai = (paiX.getFitness() > paiY.getFitness()) ? paiY : paiX;
    
    //gera um fator r aleatorio dentro do intervalo de [0,1]
    double r = (double)rand() / RAND_MAX;

    //formula do cruzamento heuristico
    double novoX = melhorPai.getX() + r * (melhorPai.getX() - piorPai.getX());
    double novoY = melhorPai.getY() + r * (melhorPai.getY() - piorPai.getY());

    //validar o intervalo da funcao 10
    if (novoX > 15.0) novoX = 15.0;
    if (novoX < -15.0) novoX = -15.0;

    if (novoY > 15.0) novoY = 15.0;
    if (novoY < -15.0) novoY = -15.0;

    //declaracao do individuo filho
    Individuo filho(novoX, novoY, 0.0);
    
    return filho;
}

bool Individuo::sortearMutacao(int percentual)
{
    int aleatorio = rand() % 100;
    return aleatorio < percentual;
}


void Individuo::mutacao(int limite_inferior, int limite_superior, Populacao &populacao, Individuo &individuo)
{
    int tamanhoPopulacao = populacao.getTamanho();
    int sorteio = rand() % tamanhoPopulacao;            // Escolhe um indivíduo aleatório da população
    Individuo &individuoSorteado = populacao.getIndividuos()[sorteio]; // Referência ao indivíduo sorteado

    int cromossomoSorteado = (rand() % 30) / 10; // Escolhe aleatoriamente qual cromossomo será mutado (0: x, 1: y, 2: z)   
}