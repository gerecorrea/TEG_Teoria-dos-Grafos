#include <iostream>
#include <cstdio>
using namespace std;

/* Algoritmo de Dijkstra
	Implementado por Geremias Corrêa

	Diferente dos outros, por ter dado alguns problema por listas, tentei e com sucesso a implementação via matriz adjacência (não padrão, pois não é simétrica) onde dado o elemento posição i,j a posição i é a orgem e j o destino da aresta direcionada.

	Obs:fiz sem arquivos pois não teria de qualquer forma como obedecer o padrão do professor, pois aqui precisamos considerar o peso das arestas. Achei mais simples o teste e inclusão direta mesmo.
*/
//Fazendo tarefa 11 só por matriz adjacencia (estava dando ruim por listas)

#define tam 5 //qtd de vertices do grafo

void inicializar(int grafo[tam][tam], int peso[tam][tam]){
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam;j++){
			if(grafo[i][j]==0)
				peso[i][j]=1000000;
			else
				peso[i][j]=grafo[i][j];
		}
	}
}


void fazDijkstra(int grafo[tam][tam], int inicio){
	bool visitados[tam]; //booleano pros visitados
	int menorcaminho[tam];//vetor dos menores caminhos
	int peso[tam][tam];//matriz dos pesos
	int pai[tam];//vetor dos pais
	int contador=0; //contador de iterações
	int aux; //aux é auxiliar pra guardar menor caminho
	int proximo; //proxima aresta (para trabalhar com o pai)
	
	inicializar(grafo, peso);//inicializando valores
	for(int i=0;i<tam;i++){
		pai[i]=inicio;
		if(i!=inicio){
			visitados[i]=false;
			menorcaminho[i] = peso[inicio][i];
		}
		else{
			visitados[i]=true;
			menorcaminho[i]=0;
		}
	}
	contador++;

	//Algoritmo
	while(tam-1 > contador){
		aux=1000000;

		for(int i=0; i<tam; i++){
			if(visitados[i]==false && menorcaminho[i]<aux){
				proximo=i;
				aux=menorcaminho[i];
			}
		}

		visitados[proximo]=true;
		for(int i=0;i<tam;i++){
			if(visitados[i]==false){
				if(aux+peso[proximo][i] < menorcaminho[i]){
					pai[i]=proximo;
					menorcaminho[i]=aux+peso[proximo][i];
				}
			}
		}
		contador++;
	}

	//RESULTADOS
	cout << endl << "Algoritmo de Dijsktra " << endl << "Impressao da tabela resultante:" << endl;
	cout << endl << "Vertices \t\t|\t";
	for(int i=0;i<tam;i++){
		cout << i << "\t |\t ";
	}
	cout << endl << "Estimativas \t|\t";
	for(int i=0;i<tam;i++)
	{
		cout << menorcaminho[i] << "\t |\t ";
	}
	cout << endl << "Precedentes \t|\t";
	for(int i=0;i<tam;i++){
		cout << pai[i] << "\t |\t ";
	}
	cout << endl;
}

int main() {
	int grafo[tam][tam];
	//Grafo do slide 19	
	grafo[0][1]=10; //[origem][destino]=peso
	grafo[0][3]=5;
	grafo[1][2]=1;
	grafo[1][3]=2;
	grafo[2][4]=4;
	grafo[3][1]=3;
	grafo[3][2]=9;
	grafo[3][4]=2;
	grafo[4][0]=7;
	grafo[4][2]=6;
	fazDijkstra(grafo,0); //grafo, nó inicial
}
