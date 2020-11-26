
#include <iostream>
#include <limits.h>
#include <clocale>
#include <list>
#include <stack>
#define INFINITO INT_MIN
using namespace std;


/* 

Algoritmo de calculo de caminho mais longo.

Implementado pela dupla Geremias e Rafael de Melo

*/

class Adjacentes {
    int v;
    int peso;

public:
    Adjacentes(int v1, int w1)
    {
        v = v1;
        peso = w1;
    }
    int getVertices() {
		return v;
	}

	int getPeso() {
		return peso;
	}
};

class Grafo {
    int V; // Número de vértices
    list<Adjacentes>* adj;
    void DFS(int v, bool visited[], stack<int>& Stack);

public:
    Grafo(int V);
    void addAresta(int u, int v, int peso);
    void maiorCaminho(int s);
};

Grafo::Grafo(int V) // Construtor
{
    this->V = V;
    adj = new list<Adjacentes>[V];
}

void Grafo::addAresta(int u, int v, int peso)
{
    Adjacentes node(v, peso);
    adj[u].push_back(node);
}

void Grafo::DFS(int v, bool visited[], stack<int>& Stack)
{
    visited[v] = true; // marca o nó atual

    //busca em profundidade por cada vértice e no fim empilha para futuro processamento
	list<Adjacentes>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
        Adjacentes node = *i;
        if (!visited[node.getVertices()])
            DFS(node.getVertices(), visited, Stack);
    }
    Stack.push(v);
}

void Grafo::maiorCaminho(int s)
{
  stack<int> pilha;
  int distancias[V];
	int pai[V];
	int maiorvalor, maior;

	//TOdos os vértices inicialmente não visitados
    bool* visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            DFS(i, visited, pilha);

	//Inicializa inicialmente as distancias como infinito
	for (int i = 0; i < V; i++){
        distancias[i] = INFINITO;
		pai[i]= INFINITO;
	}
    distancias[s] = 0; //Poruqe é a origem

    // Processa os vértices na ordem de empilhamento
    while (pilha.empty() == false) {
        int u = pilha.top();
        pilha.pop();

        // Atualiza as distâncias para todos os vértices
        list<Adjacentes>::iterator i;
        if (distancias[u] != INFINITO) {
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
                if (distancias[i->getVertices()] < distancias[u] + i->getPeso()){ 
                    distancias[i->getVertices()] = distancias[u] + i->getPeso();
					pai[i->getVertices()] = u;
				}
        }
    }


	//RESULTADOS
	cout << "Vertices:\t";
	for (int i = 0; i < V; i++){
		cout << i << "\t|\t";
	}
	cout << endl << "Distâncias:\t";
    for (int i = 0; i < V; i++){
        if(distancias[i] == INFINITO)
			cout << "oo\t|\t";
		else
			cout << distancias[i] << "\t|\t";
		if(i==0){
			maiorvalor = distancias[i];
			maior = i;
		}
		else if (distancias[i] > maiorvalor)
			maiorvalor = distancias[i];
			maior = i;
	}
	cout << endl << "Precedente:\t";
	for(int i = 0; i < V; i++){
		if(pai[i] == INFINITO)
			cout << i << "\t|\t";
		else
			cout << pai[i] << "\t|\t";
	}

	cout << endl << endl << "Maior caminho: " << maiorvalor << endl;
}

int main()
{
    Grafo g(10);
	//(origem, destino, peso);
	/*
	g.addAresta(0, 1, 2);
    g.addAresta(0, 2, 1);
    g.addAresta(1, 3, 3);
    g.addAresta(1, 2, 2);
    g.addAresta(2, 3, 3);
    g.addAresta(2, 4, 1);
    g.addAresta(0, 4, 5);
    g.addAresta(3, 4, 1);
    g.addAresta(3, 5, 5);
    g.addAresta(4, 5, 2);
	*/

	g.addAresta(0, 1, 3);
    g.addAresta(0, 2, 2);
    g.addAresta(1, 3, 4);
    g.addAresta(2, 1, 2);
    g.addAresta(1, 4, 1);
    g.addAresta(1, 6, 1);
    g.addAresta(2, 4, 1);
    g.addAresta(2, 5, 3);
    g.addAresta(3, 4, 2);
    g.addAresta(4, 7, 3);
	g.addAresta(6, 4, 2);
    g.addAresta(6, 8, 2);
    g.addAresta(7, 5, 1);
    g.addAresta(7, 6, 2);
    g.addAresta(7, 9, 5);
    g.addAresta(8, 9, 2);



    int s = 0;
	cout << "Algoritmo de cálculo das maiores distâncias." << endl << endl;
    cout << "Vértice origem: " << s << endl;
    g.maiorCaminho(s);

    return 0;
}
