#include "Otimizacao.hpp"

Individuo::Individuo()
{
    // inicializa os cromossomos com valores aleatórios entre 0 e 15
    _x = (rand() % 150) / 10.0;
    _y = (rand() % 150) / 10.0;
    _z = (rand() % 150) / 10.0;

    // calcula o fitness do indivíduo
    _fitness = calcularFitness();
}

codificacao Individuo::getX() const { return _x; }
codificacao Individuo::getY() const { return _y; }
codificacao Individuo::getZ() const { return _z; }

double Individuo::getFitness() const { return _fitness; }
void Individuo::setFitness(double fitness) { _fitness = fitness; }