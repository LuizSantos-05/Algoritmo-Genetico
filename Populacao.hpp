#pragma once

#include "Otimizacao.h"

class Populacao {
private:
    int _tamanho;
    vector<Individuo> _individuos;
public:
    Populacao(int tamanho);
    void inicializarPopulacao();
};