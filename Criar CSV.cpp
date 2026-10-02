#include "Criar CSV.hpp"

#include <fstream>
#include <iomanip>

namespace
{
void escreverCabecalho(ofstream &arquivo)
{
	arquivo << "cromossomo_x,cromossomo_y,fitness,geracao\n";
}

void escreverPopulacao(ofstream &arquivo,
					   const Populacao &populacao,
					   int geracao)
{
	const vector<Individuo> individuos = populacao.getIndividuos();

	for (const Individuo &individuo : individuos)
	{
		arquivo << fixed << setprecision(3)
				<< individuo.getX() << ','
				<< individuo.getY() << ','
				<< individuo.getFitness() << ','
				<< geracao << '\n';
	}
}
}

bool criarCSV(const string &nomeArquivo,
			  const Populacao &populacao,
			  int geracao)
{
	ofstream arquivo(nomeArquivo);
	if (!arquivo.is_open())
	{
		return false;
	}

	escreverCabecalho(arquivo);
	escreverPopulacao(arquivo, populacao, geracao);
	return arquivo.good();
}

bool criarCSV(const string &nomeArquivo,
			  const vector<Populacao> &populacoes,
			  int primeiraGeracao)
{
	ofstream arquivo(nomeArquivo);
	if (!arquivo.is_open())
	{
		return false;
	}

	escreverCabecalho(arquivo);
	for (size_t indice = 0; indice < populacoes.size(); ++indice)
	{
		escreverPopulacao(arquivo,
						  populacoes[indice],
						  primeiraGeracao + static_cast<int>(indice));
	}

	return arquivo.good();
}
