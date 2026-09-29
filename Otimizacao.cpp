#include "Otimizacao.hpp"

Individuo::Individuo(codificacao x, codificacao y, codificacao z) :
    _x(x), _y(y), _z(z), _fitness(0.0) {}

codificacao Individuo::getX() const { return _x; }
codificacao Individuo::getY() const { return _y; }
codificacao Individuo::getZ() const { return _z; }
double Individuo::getFitness() const { return _fitness; }
void Individuo::setFitness(double fitness) { _fitness = fitness; }

//modulo do fitness. Aqui calcula-se a funcao fitnes com base nos parametros da funcao
double Individuo::calcularFitness(int x, int y, int z){
    double fitness = (2 * (pow(x, 2))) - (13 * x) + (x * y) - (7 * (y / 3));
    return fitness;
}
    
//modulo da selecao. Aqui o individuo e escolhido por roleta, de maneira aleatoria
int Individuo::selecao(int tamanhoPopulacao){
    int aleatorio = rand() %_tamanho;
    return aleatorio
}
//modulo do cruzamento
int Individuo::cruzamento(vector<Individuo> &populacao){
    //aqui decretamos que o contador deve estar zerado e que o numero de pais e limitado a 2
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