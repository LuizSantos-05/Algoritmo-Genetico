#include "Criar CSV.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

namespace
{
	void escreverCabecalho(ofstream &arquivo)
	{
		arquivo << "cromossomo_x,cromossomo_y,fitness,geracao,fitness_medio\n";
	}

	void escreverPopulacao(ofstream &arquivo, const Populacao &populacao, int geracao)
	{
		const vector<Individuo> &individuos = populacao.getIndividuos();

		for (const Individuo &individuo : individuos)
		{
			arquivo << fixed << setprecision(3)
					<< individuo.getX() << ','
					<< individuo.getY() << ','
					<< individuo.getFitness() << ','
					<< geracao << ",\n";
		}

		arquivo << ",,," << geracao << ','
				<< fixed << setprecision(3)
				<< populacao.getFitnessMedio() << '\n';
	}
}

bool criarCSV(const string &nomeArquivo, const Populacao &populacao, int geracao)
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

bool criarCSV(const string &nomeArquivo, const vector<Populacao> &populacoes, int primeiraGeracao)
{
	ofstream arquivo(nomeArquivo);
	if (!arquivo.is_open())
	{
		return false;
	}

	escreverCabecalho(arquivo);
	for (size_t indice = 0; indice < populacoes.size(); ++indice)
	{
		escreverPopulacao(arquivo, populacoes[indice], primeiraGeracao + static_cast<int>(indice));
	}

	return arquivo.good();
}

bool adicionarGeracaoCSV(const string &nomeArquivo, const Populacao &populacao, int geracao)
{
	ifstream arquivoExistente(nomeArquivo);
	const bool arquivoVazio = !arquivoExistente.good() || arquivoExistente.peek() == ifstream::traits_type::eof();

	ofstream arquivo(nomeArquivo, ios::app);
	if (!arquivo.is_open())
	{
		return false;
	}

	if (arquivoVazio)
	{
		escreverCabecalho(arquivo);
	}

	escreverPopulacao(arquivo, populacao, geracao);
	return arquivo.good();
}

bool criarGraficoFitness(const string &nomeArquivoCSV, const string &nomeArquivoSVG)
{
    ifstream arquivo(nomeArquivoCSV);

    if (!arquivo.is_open())
    {
        return false;
    }

    vector<int> geracoes;
    vector<double> fitnessMedios;

    string linha;

    // Ignora o cabeçalho.
    getline(arquivo, linha);

    while (getline(arquivo, linha))
    {
        if (linha.empty())
        {
            continue;
        }

        stringstream ss(linha);

        string cromossomoX;
        string cromossomoY;
        string fitness;
        string geracao;
        string fitnessMedio;

        getline(ss, cromossomoX, ',');
        getline(ss, cromossomoY, ',');
        getline(ss, fitness, ',');
        getline(ss, geracao, ',');
        getline(ss, fitnessMedio, ',');

        // As linhas do fitness médio possuem:
        //
        // ,,,geracao,fitness_medio
        //
        // Portanto, fitnessMedio não estará vazio nessas linhas.

        if (geracao.empty() || fitnessMedio.empty())
        {
            continue;
        }

        geracoes.push_back(stoi(geracao));
        fitnessMedios.push_back(stod(fitnessMedio));
    }

    arquivo.close();

    if (geracoes.empty())
    {
        return false;
    }

    ofstream svg(nomeArquivoSVG);

    if (!svg.is_open())
    {
        return false;
    }

    // Dimensões do gráfico.
    const int largura = 1000;
    const int altura = 600;

    // Margens.
    const int margemEsquerda = 80;
    const int margemDireita = 40;
    const int margemSuperior = 60;
    const int margemInferior = 70;

    const int larguraGrafico =
        largura - margemEsquerda - margemDireita;

    const int alturaGrafico =
        altura - margemSuperior - margemInferior;

    // Descobre os valores mínimo e máximo do eixo Y.
    double menorFitness =
        *min_element(fitnessMedios.begin(), fitnessMedios.end());

    double maiorFitness =
        *max_element(fitnessMedios.begin(), fitnessMedios.end());

    // Evita divisão por zero caso todos os valores sejam iguais.
    if (menorFitness == maiorFitness)
    {
        menorFitness -= 1.0;
        maiorFitness += 1.0;
    }

    // Pequena margem visual no eixo Y.
    double intervalo = maiorFitness - menorFitness;

    menorFitness -= intervalo * 0.05;
    maiorFitness += intervalo * 0.05;

    // Início do SVG.
    svg << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

    svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << largura << "\" "
        << "height=\"" << altura << "\" "
        << "viewBox=\"0 0 " << largura << " " << altura << "\">\n";

    // Fundo.
    svg << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

    // Título.
    svg << "<text x=\"" << largura / 2
        << "\" y=\"30\" "
        << "text-anchor=\"middle\" "
        << "font-family=\"Arial\" "
        << "font-size=\"22\" "
        << "font-weight=\"bold\">"
        << "Evolução do Fitness Médio"
        << "</text>\n";

    // Eixos.
    const int xInicial = margemEsquerda;
    const int yInicial = margemSuperior + alturaGrafico;

    const int xFinal = margemEsquerda + larguraGrafico;
    const int yFinal = margemSuperior;

    svg << "<line x1=\"" << xInicial
        << "\" y1=\"" << yInicial
        << "\" x2=\"" << xFinal
        << "\" y2=\"" << yInicial
        << "\" stroke=\"black\"/>\n";

    svg << "<line x1=\"" << xInicial
        << "\" y1=\"" << yInicial
        << "\" x2=\"" << xInicial
        << "\" y2=\"" << yFinal
        << "\" stroke=\"black\"/>\n";

    // Nome do eixo X.
    svg << "<text x=\"" << largura / 2
        << "\" y=\"" << altura - 20
        << "\" text-anchor=\"middle\" "
        << "font-family=\"Arial\" "
        << "font-size=\"16\">"
        << "Geração"
        << "</text>\n";

    // Nome do eixo Y.
    svg << "<text x=\"20\" y=\"" << altura / 2
        << "\" text-anchor=\"middle\" "
        << "font-family=\"Arial\" "
        << "font-size=\"16\" "
        << "transform=\"rotate(-90 20 " << altura / 2 << ")\">"
        << "Fitness Médio"
        << "</text>\n";

    /*
     * Pontos da curva.
     */
    stringstream pontos;

    for (size_t i = 0; i < fitnessMedios.size(); ++i)
    {
        double porcentagemX;

        if (fitnessMedios.size() == 1)
        {
            porcentagemX = 0.5;
        }
        else
        {
            porcentagemX =
                static_cast<double>(i) /
                static_cast<double>(fitnessMedios.size() - 1);
        }

        double porcentagemY =
            (fitnessMedios[i] - menorFitness) /
            (maiorFitness - menorFitness);

        double x =
            xInicial + porcentagemX * larguraGrafico;

        double y =
            yInicial - porcentagemY * alturaGrafico;

        pontos << x << "," << y << " ";
    }

    // Linha do gráfico.
    svg << "<polyline points=\""
        << pontos.str()
        << "\" fill=\"none\" "
        << "stroke=\"blue\" "
        << "stroke-width=\"3\"/>\n";

    /*
     * Pontos individuais.
     */
    for (size_t i = 0; i < fitnessMedios.size(); ++i)
    {
        double porcentagemX;

        if (fitnessMedios.size() == 1)
        {
            porcentagemX = 0.5;
        }
        else
        {
            porcentagemX =
                static_cast<double>(i) /
                static_cast<double>(fitnessMedios.size() - 1);
        }

        double porcentagemY =
            (fitnessMedios[i] - menorFitness) /
            (maiorFitness - menorFitness);

        double x =
            xInicial + porcentagemX * larguraGrafico;

        double y =
            yInicial - porcentagemY * alturaGrafico;

        svg << "<circle cx=\"" << x
            << "\" cy=\"" << y
            << "\" r=\"4\" fill=\"blue\"/>\n";
    }

    /*
     * Marcações do eixo X.
     *
     * Mostra até 10 gerações para evitar sobreposição.
     */
    size_t quantidadeMarcacoes =
        min<size_t>(10, geracoes.size());

    for (size_t i = 0; i < quantidadeMarcacoes; ++i)
    {
        size_t indice;

        if (quantidadeMarcacoes == 1)
        {
            indice = 0;
        }
        else
        {
            indice =
                i * (geracoes.size() - 1) /
                (quantidadeMarcacoes - 1);
        }

        double porcentagemX;

        if (geracoes.size() == 1)
        {
            porcentagemX = 0.5;
        }
        else
        {
            porcentagemX =
                static_cast<double>(indice) /
                static_cast<double>(geracoes.size() - 1);
        }

        double x =
            xInicial + porcentagemX * larguraGrafico;

        svg << "<text x=\"" << x
            << "\" y=\"" << yInicial + 25
            << "\" text-anchor=\"middle\" "
            << "font-family=\"Arial\" "
            << "font-size=\"12\">"
            << geracoes[indice]
            << "</text>\n";
    }

    /*
     * Marcações do eixo Y.
     */
    const int quantidadeMarcacoesY = 5;

    for (int i = 0; i <= quantidadeMarcacoesY; ++i)
    {
        double porcentagem =
            static_cast<double>(i) /
            quantidadeMarcacoesY;

        double valor =
            menorFitness +
            porcentagem * (maiorFitness - menorFitness);

        double y =
            yInicial - porcentagem * alturaGrafico;

        svg << "<text x=\"" << xInicial - 10
            << "\" y=\"" << y + 4
            << "\" text-anchor=\"end\" "
            << "font-family=\"Arial\" "
            << "font-size=\"12\">"
            << fixed << setprecision(2)
            << valor
            << "</text>\n";
    }

    svg << "</svg>\n";

    svg.close();

    return svg.good();
}