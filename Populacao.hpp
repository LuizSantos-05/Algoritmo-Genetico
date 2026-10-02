#pragma once

#include "Otimizacao.hpp"

class Populacao
{
private:
    int _tamanho;                  // tamanho da população
    int _elitismo;                 // quantidade de indivíduos que serão mantidos na próxima geração
    vector<Individuo> _individuos; // vetor de indivíduos
public:
    Populacao(int tamanho);      // construtor da população
    ~Populacao();                // destrutor da população

    int getTamanho() const;        // retorna o tamanho da população
    int getElitismo() const;       // retorna a quantidade de indivíduos que serão mantidos na próxima geração
    vector<Individuo> getIndividuos() const; // retorna o vetor de indivíduos

    void inicializarPopulacao(); // inclui os individuos no vetor da população
    void novaGeracao();          // gera uma nova geração de indivíduos
};