#include "Otimizacao.hpp"

Individuo::Individuo(codificacao x, codificacao y, codificacao z) :
    _x(x), _y(y), _z(z), _fitness(0.0) {}

codificacao Individuo::getX() const { return _x; }
codificacao Individuo::getY() const { return _y; }
codificacao Individuo::getZ() const { return _z; }
double Individuo::getFitness() const { return _fitness; }
void Individuo::setFitness(double fitness) { _fitness = fitness; }

//double Individuo::calcularFitness(Individuo &individuo, int x, int y)
    //

int Individuo::selecao(int tamanhoPopulacao){
    int aleatorio = rand() %_tamanho;
    return aleatorio
}
//módulo do cruzamento
int Individuo::cruzamento(vector<Individuo> &populacao){
    //aqui decretamos que o contador deve estar zerado e que o número de pais é limitado a 2
    int contador = 0;
    int pais[2];
    //enquanto o contador for menor que dois, realiza-se o processo de cruzamento
    while(contador < 2){
        if (contador == 0)
        {
        pais[contador] = selecao();
        contador++;
        }
        else
        {
            pais[contador] = selecao();
            if(pais[contador] == pais[contador -1]){
                continue;
            }
            else{
                contador++;
            }
        }
    }
}