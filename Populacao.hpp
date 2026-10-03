#pragma once

#include "Otimizacao.hpp"
#include <vector>

class Populacao
{
private:
    int _tamanho;                  // tamanho da população
    int _elitismo;                 // quantidade de indivíduos que serão mantidos na próxima geração
    double _fitnessMedio;          // fitness médio da população
    vector<bool> _elitismoBool;    // quantidade de indivíduos que serão mantidos na próxima geração
    vector<Individuo> _individuos; // vetor de indivíduos
public:
    Populacao(int tamanho); // construtor da população
    ~Populacao();           // destrutor da população

    int getTamanho() const;
    double getFitnessMedio() const;                 // retorna o fitness médio da população
    int getElitismo() const;                        // retorna o tamanho da população
    vector<bool> getElitismoBool();                 // retorna a quantidade de indivíduos que serão mantidos na próxima geração
    void decrementarElitismo();                     // decrementa a quantidade de indivíduos que serão mantidos na próxima geração
    void decrementarElitismoBool();                 // decrementa a quantidade de indivíduos que serão mantidos na próxima geração
    vector<Individuo> &getIndividuos();             // retorna o vetor de indivíduos
    const vector<Individuo> &getIndividuos() const; // retorna o vetor de indivíduos (constante)

    void inicializarPopulacao();                             // inclui os individuos no vetor da população
    void novaGeracao(int numeroOperacao);                    // gera uma nova geração de indivíduos
    void ordenarElitismo();                                  // ordena os indivíduos da população de acordo com o fitness, mantendo os melhores indivíduos no início do vetor
    bool avaliarMelhorPopulacao(const Populacao &populacao); // avalia se a população atual contém os melhores indivíduos possíveis (fitness = 905)
    void calcularFitnessMedio();                           // calcula o fitness médio da população
};