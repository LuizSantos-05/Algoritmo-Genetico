#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

typedef double codificacao;     // tipo de codificação do indivíduo

class Individuo {
private:
    // cromossomos
    codificacao _x;
    codificacao _y;
    codificacao _z;
    // fitness do indivíduo
    double _fitness;
public:
    Individuo(codificacao x, codificacao y, codificacao z); // construtor do indivíduo
    
    // getters e setters
    codificacao getX() const;
    codificacao getY() const;
    codificacao getZ() const;
    double getFitness() const;
    void setFitness(double fitness);

    // métodos para calcular o fitness, seleção, cruzamento e mutação
    double calcularFitness();
    void selecao();
    void cruzamento(const Individuo &paiX, Individuo &paiY);
    void sortearMutacao();
    void mutacao();

    // método para seleção por roleta
    Individuo selecaoRoleta();
};
