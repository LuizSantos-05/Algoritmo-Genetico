#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

typedef double codificacao;

class Individuo {
private:
    codificacao _x;
    codificacao _y;
    codificacao _z;
    double _fitness;
public:
    Individuo(codificacao x, codificacao y, codificacao z);
    codificacao getX() const;
    codificacao getY() const;
    codificacao getZ() const;
    double getFitness() const;
    void setFitness(double fitness);
    double calcularFitness();
    void selecao();
    void cruzamento(const Individuo &paiX, Individuo &paiY);
    void sortearMutacao();
    void mutacao();
    Individuo selecaoRoleta();
};
