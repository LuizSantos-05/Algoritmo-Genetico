#include <iostream>
#include <string>

#include "Otimizacao.hpp"
#include "Populacao.hpp"
#include "Criar CSV.hpp"

using namespace std;

string arquivoCSV = "geracao_0.csv";

void exibirIndividuo(const Individuo &individuo)
{
    cout << "Individuo: (" << individuo.getX() << ", " << individuo.getY()
         << "), Fitness: " << individuo.getFitness() << endl;
}

void exibirPopulacao(const Populacao &populacao)
{
    const vector<Individuo> &individuos = populacao.getIndividuos();
    for (const Individuo &individuo : individuos)
    {
        exibirIndividuo(individuo);
    }
}

void exibirGeracao(const Populacao &populacao, int geracao)
{
    cout << "Geracao " << geracao << ":" << endl;
    exibirPopulacao(populacao);
    cout << endl;
}

// Intervalo de busca para os valores de x e y [-15, 15]
// Funcao 10 -> Z = (2 * (pow(x, 2))) - (13 * x) + (x * y) - (7 * (y / 3))
// Fitness(x, y) = Z

int main()
{
    int nMaxGeracoes;            // Número máximo de gerações
    int tamanhoPopulacaoInicial; // Tamanho inicial da população

    cout << "Digite o número máximo de gerações: ";
    cin >> nMaxGeracoes;
    cout << "Digite o tamanho inicial da população: ";
    cin >> tamanhoPopulacaoInicial;

    Populacao populacao(tamanhoPopulacaoInicial);
    populacao.inicializarPopulacao();
    populacao.ordenarElitismo();

    for (int i = 0; i < nMaxGeracoes; i++)
    {
        exibirGeracao(populacao, i);
        if (i > 0)
        {
            adicionarGeracaoCSV(arquivoCSV, populacao, i);
        }
        else
        {
            criarCSV(arquivoCSV, populacao, i);
        }
        populacao.novaGeracao();
    }
    return 0;
}
