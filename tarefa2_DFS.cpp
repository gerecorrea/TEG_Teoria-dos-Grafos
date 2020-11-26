#include <iostream>
#include <list>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

/* GRAFOS - TAREFA 09: 
De Geremias Corrêa
Código que possui a resolução do algoritmo DFS

OBS: O grafo escolhido é uma árvore no seguinte formato:
	
		
	   2 --- 5 
	  /
	0	 4
	  \ /
	   1   7
		\ /
		 3
		  \
		   6

	Logo, se o vértice inicial for 0 (e é), o caminho gerado deve ser 0 1 3 6 7 4 2 5
*/

/* ------ INICIO CLASSE ------*/
class Grafo{
	int vertice;
	list<int> *adjacentes;// ponteiro de lista pros adjacentes ao vertice
	
	
	public: 
		bool visitado[100];

		Grafo(int vertice){//o construtor
			this->vertice = vertice;
			adjacentes = new list<int> [vertice];
			for(int i=0;i<vertice;i++){//inicialmente todos os vertices não são visitados
				visitado[i]=false;
			}
		} 

		void addAresta(int v1, int v2){
			//adiciona de forma direcionada, tal que sai de v1 e vai pra v2
				adjacentes[v2].push_back(v1);
		}

		void DFS(int v, bool visitado[]){
			visitado[v]=true;
			list<int>::iterator q;
			
			cout << v << " ";//printa na ordem buscada
			for(q=adjacentes[v].begin(); q!=adjacentes[v].end();++q){
				if(!visitado[*q])
					DFS(*q,visitado);
			}
		}

		int getVertice(){
			return vertice;
		}
};
/* ----- FIM CLASSE -----*/

int main(){
	
	char c;
	string s;
	int linha=0,cont=0,valor,valorvertice;
	bool jafoivertice=false;
	bool eranumero=false;

	Grafo grafo(8);

	//INICIO LEITURA
	FILE *arq = fopen("arq1.txt","r");
	
	while(1){
		if(arq==NULL){
			cout << "Arquivo nulo!" << endl;
			break;
		}
		c=fgetc(arq);
		if(feof(arq)){
			break;
		}
		if(isdigit(c)){
			s[cont] = c;
			cont++;
			eranumero=true;
		}
		else{//caso ":", " " ou "\n"
			if (eranumero==true){
				s[cont] = '\0';
				
				valor = stoi (s,0,10);//converte string pra decimal
				cont=0;
				if(jafoivertice==false){
					valorvertice= valor;
				}
				else{
					grafo.addAresta(valorvertice,valor);
				}
			}		
			if(c=='\n'){
				jafoivertice=false;
				linha++;
			}
			else if(c==':'){
				jafoivertice=true;
			}
			eranumero=false;
		}
	}
	fclose(arq);
	//FIM LEITURA

	int v=0; //vértice inicial
	cout << endl << "------------" << endl;
	cout << "\nCaminho por busca em profundidade a partir do vértice escolhido " << endl;
	cout << "Vertice escolhido: " << v << endl;
	cout << "Caminho DFS gerado: ";
	grafo.DFS(v,grafo.visitado);
	cout << endl;
	
	return 0;
}
