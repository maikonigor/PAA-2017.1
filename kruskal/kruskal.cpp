
/*
	Implementa��o do algoritmo de Kruskal
	Para detectar ciclos iremos utilizar o algoritmo Union-Find que detecta
	ciclos em grafos N�O direcionados.
*/

#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h> // memset
using namespace std;

class Aresta
{
	int vertice1, vertice2, peso,cod;

public:

	Aresta(int v1, int v2, int peso,int cod)
	{
		vertice1 = v1;
		vertice2 = v2;
		this->cod = cod;

		this->peso = peso;
	}

	int obterVertice1()
	{
		return vertice1;
	}

	int obterVertice2()
	{
		return vertice2;
	}

	int obterCod()
	{
		return cod;
	}

	int obterPeso()
	{
		return peso;
	}

	// sobrescrita do operador "<"
	bool operator < (const Aresta& aresta2) const
	{
		return (peso < aresta2.peso);
	}
};

class Grafo
{
	int V; // n�mero de v�rtices
	vector<Aresta> arestas; // vetor de arestas

public:

	Grafo(int V)
	{
		this->V = V;
	}

	// fun��o que adiciona uma aresta
	void adicionarAresta(int v1, int v2, int peso, int cod)
	{
		Aresta aresta(v1, v2, peso,cod);
		arestas.push_back(aresta);
	}

	// fun��o que busca o subconjunto de um elemento "i"
	int buscar(int subset[], int i)
	{
		if(subset[i] == -1)
			return i;
		return buscar(subset, subset[i]);
	}

	// fun��o para unir dois subconjuntos em um �nico subconjunto
	void unir(int subset[], int v1, int v2)
	{
		int v1_set = buscar(subset, v1);
		int v2_set = buscar(subset, v2);
		subset[v1_set] = v2_set;
	}

	/// fun��o que roda o algoritmo de Kruskal
	vector<int> kruskal(vector<int> colorP)
	{
		vector<Aresta> arvore;
		int size_arestas = arestas.size();

		// ordena as arestas pelo menor peso
		sort(arestas.begin(), arestas.end());

		// aloca mem�ria para criar "V" subconjuntos
		int * subset = new int[V];

		// inicializa todos os subconjuntos como conjuntos de um �nico elemento
		memset(subset, -1, sizeof(int) * V);

		for(int i = 0; i < size_arestas; i++)
		{
			int v1 = buscar(subset, arestas[i].obterVertice1());
			int v2 = buscar(subset, arestas[i].obterVertice2());

			if(v1 != v2)
			{
				// se forem diferentes � porque N�O forma ciclo, insere no vetor
				arvore.push_back(arestas[i]);
				unir(subset, v1, v2); // faz a uni�o
			}
		}

		int size_arvore = arvore.size();

		// mostra as arestas selecionadas com seus respectivos pesos
		for(int i = 0; i < size_arvore; i++)
		{
			int v1 = 'A' + arvore[i].obterVertice1();
			int v2 = 'A' + arvore[i].obterVertice2();
			int cod = arvore[i].obterCod();

            colorP[i]=cod;

			cout << arvore[i].obterPeso() << endl;
		}

		return colorP;
	}
};
