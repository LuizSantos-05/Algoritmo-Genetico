#pragma once

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
    codificacao _z;
    // fitness do individuo
    double _fitness;

public:
    Individuo(); // construtor do indivíduo
    Individuo(codificacao x, codificacao y, codificacao z); //construtor criado com os parametros

    // getters e setters
    codificacao getX() const;
    codificacao getY() const;
    codificacao getZ() const;
    double getFitness() const;
    void setFitness(double fitness);

    // metodos para calcular o fitness, selecao, cruzamento e mutacao
    double calcularFitness();
    int selecao(int tamanhoPopulacao);
    Individuo cruzamento(vector<Individuo> &populacao);
    void sortearMutacao();
    void mutacao();

    // metodo para selecao por roleta
    Individuo selecaoRoleta();
};