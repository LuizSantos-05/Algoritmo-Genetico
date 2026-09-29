#pragma once

#include "Otimizacao.hpp"

class Populacao {
private:
    int _tamanho;                       // tamanho da populacao
    vector<Individuo> _individuos;      // vetor de individuos
public:
    Populacao(int tamanho);             // construtor da populacao
    void inicializarPopulacao();        // inclui os individuos no vetor da populacao
};