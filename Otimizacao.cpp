#include "Otimizacao.hpp"

Individuo::Individuo(codificacao x, codificacao y, codificacao z) :
    _x(x), _y(y), _z(z), _fitness(0.0) {}

codificacao Individuo::getX() const { return _x; }
codificacao Individuo::getY() const { return _y; }
codificacao Individuo::getZ() const { return _z; }
double Individuo::getFitness() const { return _fitness; }
void Individuo::setFitness(double fitness) { _fitness = fitness; }
