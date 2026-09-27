#pragma once

#include "Otimizacao.hpp"

class Populacao {
private:
    int _tamanho;                       // tamanho da população
    vector<Individuo> _individuos;      // vetor de indivíduos
public:
    Populacao(int tamanho);             // construtor da população
    void inicializarPopulacao();        // inclui os individuos no vetor da população
};