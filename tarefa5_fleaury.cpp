#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

/* GRAFOS - TAREFA 05: 
Geremias CorrÃªa
CÃ³digo que possui apenas a resolução do ciclo euleriano - Tarefa 05
*/


/* ------ INICIO CLASSE ------*/
class Grafo{
	int vertice;
	list<int> *adjacentes;// ponteiro de lista pros adjacentes ao vertice
	
	public: 
		Grafo(int vertice){//o construtor
			this->vertice = vertice;
			adjacentes = new list<int> [vertice];	
		} 
	

		void addAresta(int v1, int v2){
			//adiciona de forma direcionada, tal que sai de v1 e vai pra v2
				adjacentes[v2].push_back(v1);
		}
	
		int Euleriano(){
			int res;
			if(conexo()==false)
				return 0;
			int cont=0;
			for(int i=0;i<vertice;i++){//conta vÃ©rtices de arestas Ã­mpar
				if(adjacentes[i].size()%2!=0)
					cont++;
			}	
			if(cont>=2) //se contador maior ou igual a 2, nÃ£o Ã© cliclo euleriano/totalmente euleriano
				return 0;
			else
				return 1;
			//Obs: se cont == 2 na realidade seria semi-euleriano
		}
	
		bool conexo(){
			bool visitado[vertice];
			int i;
			for(i=0;i<vertice;i++){//inicialmente todos os vertices nÃ£o sÃ£o visitados
				visitado[i]=false;
			}
			for(i=0;i<vertice;i++){//verificando se o grau Ã© diferente de 0
				if(adjacentes[i].size()!=0)
					break;
			}
			if(i==vertice)//
				return true;
			DFS(i,visitado);
			for(i=0;i<vertice;i++){// verifica se todos o vÃ©rtices com ao menos uma adjacencia sÃ£o visitados
				if(visitado[i] == false && adjacentes[i].size()>0)
					return false;
			}
			return true;
		}
	
		void DFS(int v, bool visitado[]){
			visitado[v]=true;
			list<int>::iterator q;
			for(q=adjacentes[v].begin(); q!=adjacentes[v].end();++q){
				if(!visitado[*q])
					DFS(*q,visitado);
			}
			// Nesse crio um iterador de listas de inteiros, iterando sobre todos os adjacentes e fazendo uma busca em profundidade.
		}


		void printEulerian(){
			int var = Euleriano();
			if (var==1)
				cout << "Possui ciclo euleriano" << endl;
			else
				cout << "Nao possui ciclo euleriano" << endl;
		}

		int getVertice(){
			return vertice;
		}
};
/* ----- FIM CLASSE -----*/

int main(){
	
	Grafo grafo(4);
	Grafo grafo2(4);
	Grafo grafo3(5);
 
	/*----------------------------*/
	//GRAFO 1 - exemplo que Ã© euleriano: 
	//{{1,1,0,1},{1,0,1,0},{0,1,0,1,{1,0,1,0}}
	grafo.addAresta(0,1);
	grafo.addAresta(1,0);
	grafo.addAresta(0,3);
	grafo.addAresta(3,0);
	grafo.addAresta(1,2);
	grafo.addAresta(2,1);
	grafo.addAresta(2,3);
	grafo.addAresta(3,2);
	cout << endl <<"GRAFO 1:" << endl;
	grafo.printEulerian();
	/*----------------------------------*/

	//*GRAFO 2 - EXEMPLO DIRECIONADO que nÃ£o Ã© euleriano
	//ex matriz incid{{0,-1,0,1},{0,1,1,0},{0,-1,0,1},{-1,0,-1,0}}
	//o0 -> o3
	///\    /\
	//o1 -> o2
	grafo2.addAresta(0,3);
	grafo2.addAresta(1,0);
	grafo2.addAresta(1,2);
	grafo2.addAresta(2,3);
	cout << endl << "------------" << endl;
	cout << "GRAFO 2: " << endl;
	grafo2.printEulerian();
	/*----------------------------------*/
	
	//GRAFO 3 - EX que Ã© euleriano/tem circuito euleriano (pdf slide 24 Omir)
	grafo3.addAresta(0,1);
	grafo3.addAresta(1,0);
	grafo3.addAresta(2,1);
	grafo3.addAresta(1,2);
	grafo3.addAresta(0,2);
	grafo3.addAresta(2,0);
	grafo3.addAresta(3,2);
	grafo3.addAresta(2,3);
	grafo3.addAresta(2,4);
	grafo3.addAresta(4,2);
	grafo3.addAresta(4,3);
	grafo3.addAresta(3,4);
	cout << endl << "------------" << endl;
	cout << "GRAFO 3: " << endl;
	grafo3.printEulerian();
	
	return 0;
}
