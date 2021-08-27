#include <iostream>
#include "Matriz.h"
#include <fstream>

struct Node
{
    Node *direita;
    Node *abaixo;
    int linha;
    int coluna;
    double valor;
};

Matriz::Matriz(int m, int n){
    // Iniciando o nó cabeca
    _head = new Node;
    _head->valor = 9999;
    _head->linha = -1;
    _head->coluna = -1;
    _head->direita = _head;
    _head->abaixo = _head;

    createHead(m, n);
}

Matriz::~Matriz(){
    // Apagando a matriz
    Node *atual;
    
    _lin = _head->abaixo;
    _col = _head->direita;

    while(_lin != _head){
        atual = _lin->direita;

        while(atual->linha != -1){
            Node* prev = atual;
            atual = atual->direita;
            delete prev;
            _lin->direita = atual;
        }

        _lin = _lin->abaixo;
    }

    _lin = _head->abaixo;

    
    while(_lin != _head || _col != _head){  
        if(_lin != _head){
            Node* prev = _lin;
            _lin = _lin->abaixo;
            delete prev;
        }

        if(_col != _head){
            Node* prev = _col;
            _col = _col->direita;
            delete prev;
        }
    }
    delete _head;

std::cout << "Matriz apagada" << std::endl;
}

void Matriz::createHead(int m, int n){
    // Guardando o tamanho da matriz
    m_linha = m;
    m_coluna = n;
    
    _col = _head;

    Node* novo;

    // Crindo os nós cabeças para coluna
    for(int i = 1; i <= m_coluna; i++){
        novo = new Node;

        _col->direita = novo;                
        novo->valor = 9999;
        //novo->linha = i; // Guardar o indice da coluna
        novo->coluna = -1;
        novo->abaixo = novo; // Circularidade
        _col = _col->direita;
    }
    // ajustar a circularidade
    _col->direita = _head;

    // Crindo os nós cabeças para linha
    _lin = _head;
    for(int i = 1; i <= m_linha; i++){
        novo = new Node;

        _lin->abaixo = novo;                
        novo->valor = 9999;
        novo->linha = -1; 
        //novo->coluna = i; // Guardar o indice da linha
        novo->direita = novo; // Circularidade
        _lin = _lin->abaixo;
    }
    _lin->abaixo = _head;
}

void Matriz::insert(int i, int j, double value){
    // Verificar se os indices de linha e coluna 
    // passados como parametro são válidos
    if (i < 1 || i > m_linha || j < 1 || j > m_coluna)
        return;
  
    /* Buscar: Verificar se ja existe um elemeto na posição */
    Node* prev = nullptr;
    Node* atual;

    _lin = _col = _head;

    // Mover o ponteiro pelo no da coluna até a posição desejada 
    for(int ind = 1; ind <= j; ind++)
        _col = _col->direita;

    // Mover o ponteiro pelo no da linha até a posição desejada 
    for(int ind = 1; ind <= i; ind++)
        _lin = _lin->abaixo;

    atual = _lin;

    //Meu atual recebe o primeiro elemento da linha
    prev = atual;
    atual = atual->direita;

    //Mover o ponteiro pelo no da linha até a posição desejada 
    while(atual->coluna < j && atual->linha != -1){
        prev = atual;
        atual = atual->direita;
    }
    
    /* Atribuir valor: Se o no existir*/
    if (atual != _lin && atual->coluna == j && atual->linha == i){
        if(value == 0){
            if(prev == _lin) 
                _lin->direita = atual->direita;
            else{
                prev->direita = atual->direita; 
                _col->abaixo = atual->abaixo;            
            }
            delete atual;
        }else atual->valor = value;
    }else{ // Caso o no não exista
        Node* novo = new Node;
        novo->linha = i;
        novo->coluna = j;
        novo->valor = value;
        
        novo->direita = atual;
        if(prev == _lin)
            _lin->direita = novo;
        else
            prev->direita = novo;
    }
}

double Matriz::getValue(int i, int j){
    // Verificar se os indices de linha e coluna 
    // passados como parametro são válidos
    if (i < 1 || i > m_linha || j < 1 || j > m_coluna)
        return 0;
    
    _lin = _head->abaixo;

    for(int ind = 1; ind < i; ind++)
        _lin = _lin->abaixo;
    
    Node *atual = _lin->direita;

    while(atual->linha != -1){
        
        if(atual->coluna == j && atual->linha == i)
            return atual->valor;
        else 
            atual = atual->direita;
    }
    return 0;
}

int Matriz::getColuna(){
    return m_coluna;
}

int Matriz::getLinha(){
    return m_linha;
}   

void Matriz::print(){
    Node* linha = _head->abaixo;
    Node*atual = nullptr;

    for(int i = 1; i <= m_linha; i++){
        atual = linha->direita;
        
        for(int j = 1; j <= m_coluna; j++){
        
            if(atual->linha == i && atual->coluna == j){
                 std::cout << atual->valor << " ";
                 atual = atual->direita;
            }else
                 std::cout << "0" << " ";
             
            if(linha->direita->linha == -1 || linha->direita->linha == i)
                linha = linha->abaixo; 
        
       }
        std::cout << std::endl;
    }
}

Matriz *Matriz::soma(Matriz *A, Matriz *B){
    
    if(A->m_linha == B->m_linha && A->m_coluna == B->m_coluna){
		// Cria uma nova matriz para retornar
		Matriz *C = new Matriz(A->m_linha, A->m_coluna);
        //C->createHead(A->m_linha, A->m_coluna);

		for(int i = 1; i <= A->m_linha; i++){
			for(int j = 1; j <= A->m_coluna; j++){               
                C->insert(i,j, (A->getValue(i,j) + B->getValue(i,j)));    
			}
		}
		return C;
	}

    return nullptr;
}

Matriz *multiplica(Matriz *A, Matriz *B){ 
	if(A->getColuna() != B->getLinha())
		return nullptr;
	
	Matriz* C = new Matriz(A->getLinha(), B->getColuna());
    //C->createHead(A->m_linha, B->m_coluna);

	for(int i = 1; i <= A->getLinha(); i++){
		for(int j = 1; j <= B->getColuna(); j++){
			for(int k = 1; k <= A->getColuna(); k++){
                C->insert(i,j, (C->getValue(i,j)+(A->getValue(i,k) * B->getValue(k,j))));  
            }
		}
	}
	return C;
}  

 Matriz *Matriz::lerMatrizDeArquivo(std::string nomeDoArquivo){
    
    // Declaro uma variavel file handle para um arquivo txt
    std::ifstream txtFile;
    int lin, col;
    double value;

    //Abrindo o arquivo
    txtFile.open(nomeDoArquivo);

    //Le o tamanho da matriz no arquivo
    txtFile >> lin >> col;
    //c->createHead(lin, col);
    Matriz* c  = new Matriz(lin, col);

    int i, j ;
    //Le os valores do arquivo e preenche a matriz
    for (int cont = 1; cont <= lin; cont++){
        for (int cont2 = 1; cont2 <= col; cont2++){
            txtFile >> i >> j >> value;
            c->insert(i, j, value); 
        }
    }
    
    return c;
 }
