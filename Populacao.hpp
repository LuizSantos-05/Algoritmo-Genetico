#pragma once

#include "Otimizacao.hpp"

class Populacao {
private:
    int _tamanho;
    vector<Individuo> _individuos;
public:
    Populacao(int tamanho);
    void inicializarPopulacao();
};