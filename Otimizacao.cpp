#include "Otimizacao.hpp"

Individuo::Individuo()
{
    // inicializa os cromossomos com valores aleatorios entre 0 e 15
    _x = ((double)rand() / RAND_MAX) * 30.0 - 15.0;
    _y = ((double)rand() / RAND_MAX) * 30.0 - 15.0;
    _z = 0.0;

    // calcula o fitness do individuo
    _fitness = calcularFitness();
}
Individuo::Individuo(codificacao x, codificacao y, codificacao z) : _x(x), _y(y), _z(z){
    _fitness = calcularFitness();
}

codificacao Individuo::getX() const { return _x; }
codificacao Individuo::getY() const { return _y; }
codificacao Individuo::getZ() const { return _z; }

double Individuo::getFitness() const { return _fitness; }
void Individuo::setFitness(double fitness) { _fitness = fitness; }

//modulo do fitness. Aqui calcula-se a funcao fitness com base nos parametros da funcao
double Individuo::calcularFitness(){
    double fitness = (2 * (pow(_x, 2))) - (13 * _x) + (_x * _y) - (7 * (_y / 3));
    return fitness;
}
    
//modulo da selecao. Aqui o individuo e escolhido por roleta, de maneira aleatoria
int Individuo::selecao(int tamanhoPopulacao){
    int aleatorio = rand() % tamanhoPopulacao;
    return aleatorio;
}
//modulo do cruzamento
Individuo Individuo::cruzamento(vector<Individuo> &populacao){
    //aqui decretamos que o contador deve estar zerado e que o numero de pais e limitado a 2
    int contador = 0;
    int pais[2];
    //enquanto o contador for menor que dois, realiza-se o processo de cruzamento
    while(contador < 2){
        if (contador == 0)
        {
        pais[contador] = selecao(populacao.size());
        contador++;
        }
        else
        {
            pais[contador] = selecao(populacao.size());
            if(pais[contador] == pais[contador -1]){
                continue;
            }
            else{
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
