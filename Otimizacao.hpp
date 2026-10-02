#pragma once

#include "Populacao.hpp"
#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

typedef double codificacao; // tipo de codificação do indivíduo

class Individuo
{
private:
    // cromossomos
    codificacao _x;
    codificacao _y;
    // fitness do individuo
    double _fitness;

public:
    Individuo(); // construtor do indivíduo

    // getters e setters
    codificacao getX() const;
    codificacao getY() const;
    codificacao setX(codificacao x);
    codificacao setY(codificacao y);
    double getFitness() const;
    void setFitness(double fitness);

    // metodos para calcular o fitness, selecao, cruzamento e mutacao
    double calcularFitness(int x, int y);
    int selecao(int tamanhoPopulacao);
    void cruzamento(vector<Individuo> &populacao);
    bool sortearMutacao(int percentual);
    void mutacao(int limite_inferior, int limite_superior, Populacao &populacao, Individuo &individuo);
};