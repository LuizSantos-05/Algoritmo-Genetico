#pragma once

#include "Populacao.hpp"

#include <string>
#include <vector>

using namespace std;

// Cria ou substitui o arquivo CSV com os indivíduos de uma geração.
bool criarCSV(const string &nomeArquivo, const Populacao &populacao, int geracao);

// Cria ou substitui o arquivo CSV usando o índice do vetor como geração.
bool criarCSV(const string &nomeArquivo, const vector<Populacao> &populacoes, int primeiraGeracao = 0);

// Adiciona uma nova geração ao final de um arquivo CSV existente.
bool adicionarGeracaoCSV(const string &nomeArquivo, const Populacao &populacao, int geracao);
