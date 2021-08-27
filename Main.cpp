#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "Matriz.h"

using namespace std;

int main()
{
	vector<Matriz*> matrizes; // Vetor de ponteiros para matrizes
	
	while(true) {
		string cmd;
		getline(cin, cmd);

		std::stringstream ss{ cmd };
		vector<string> tokens;
		string buffer;

		while(ss >> buffer) {
			tokens.push_back(buffer);
		}

		if(tokens[0] == "libera" || tokens[0] == "exit") {
			for(int i = 0; i < matrizes.size(); ++i) {
				delete matrizes[i];
				matrizes[i] = nullptr;
			}
			matrizes.clear();
			break;
		}
		// cria [l] [c]
		else if(tokens[0] == "cria") {
            int l = std::stoi(tokens[1]);
            int c = std::stoi(tokens[2]);
            Matriz *m = new Matriz(l, c);
            matrizes.push_back(m);
            }
            // imprime [k]
		else if(tokens[0] == "imprime") {
			int k = std::stoi(tokens[1]);
			matrizes[k]->print();
		}
		// insere na matriz k o valor v na posição [i] [j]
		else if(tokens[0] == "insere") {
            int k= std::stoi(tokens[1]);
			int i = std::stoi(tokens[2]);
            int j = std::stoi(tokens[3]);
            double v = std::stoi(tokens[4]);
            matrizes[k]->insert(i, j, v);
		}
        // valor [i] [j] [k]
		else if(tokens[0] == "lerMatrizDeArquivo") {
			int k = std::stoi(tokens[1]);
            std::string arquivo = tokens[2];
			//cout<<"Lendo arquivo "<<arquivo<<endl;
			Matriz *c;
			c=c->lerMatrizDeArquivo(arquivo);
			// matrizes[k]->lerMatrizDeArquivo(arquivo);
			if (matrizes[k] != nullptr) 
				delete matrizes[k];

			c=c->lerMatrizDeArquivo(arquivo);
			matrizes[k]=c;
		}

		// soma [p] [q] 
		else if(tokens[0] == "soma") {
            int p = std::stoi(tokens[1]);
            int q = std::stoi(tokens[2]);
			Matriz *C = matrizes[p]->soma(matrizes[p], matrizes[q]);
			if(C == nullptr) 
                cout << "nao foi possivel somar" << endl;
            else {
                C->print();
                delete C;
            }
		 }
        // multiplica [p] [q] 
		else if(tokens[0] == "multiplica") {
            int p = std::stoi(tokens[1]);
            int q = std::stoi(tokens[2]);
			Matriz *C = multiplica(matrizes[p], matrizes[q]);
			if(C == nullptr) 
                cout << "nao foi possivel multiplicar" << endl;
            else {
                C->print();
                delete C;
            }
        }
        // valor [k] [i] [j]
		else if(tokens[0] == "valor") {
			int k = std::stoi(tokens[1]);
            int i = std::stoi(tokens[2]);
            int j = std::stoi(tokens[3]);
			double v = matrizes[k]->getValue(i,j);
            cout << "valor: " << v << endl;

		}
		
		else {
			cout << "comando inexistente" << endl;
		}
	}
	return 0;
}