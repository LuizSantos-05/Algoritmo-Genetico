#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

typedef double codificacao;     // tipo de codificacao do individuo

class Individuo {
private:
    // cromossomos
    codificacao _x;
    codificacao _y;
    codificacao _z;
    // fitness do individuo
    double _fitness;
public:
    Individuo(codificacao x, codificacao y, codificacao z); // construtor do individuo
    
    // getters e setters
    codificacao getX() const;
    codificacao getY() const;
    codificacao getZ() const;
    double getFitness() const;
    void setFitness(double fitness);

    // metodos para calcular o fitness, selecao, cruzamento e mutacao
    double calcularFitness();
    void selecao(int tamanhoPopulacao, vector<Individuo> &populacao);
    void cruzamento(const Individuo &paiX, Individuo &paiY);
    void sortearMutacao();
    void mutacao();

    // metodo para selecao por roleta
    Individuo selecaoRoleta();
};
