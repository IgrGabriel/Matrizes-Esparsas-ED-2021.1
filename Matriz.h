#ifndef MATRIZ_H
#define MATRIZ_H

struct Node;

class Matriz{
    private:
        Node *_head;
        Node *_lin;
        Node *_col;
        int m_linha, m_coluna;

    public:
        /*Inicializa uma matriz esparsa vazia com 
        capacidade para m linhas e n colunas.*/
        Matriz(int m, int n);
        /*Destrutor que libera toda a memoria que foi alocada 
        dinamicamente para esta estrutura de dados.*/
        ~Matriz();
        /*Inicializa os no cabeça das linha e das colunas*/
        void createHead(int m, int n);
        /*Insere um valor na célula (i, j) da matriz, 
        onde i é a linha e j é a coluna.*/
        void insert(int i, int j, double value); 
        /*Devolve o valor na célula (i, j) da matriz, 
        onde i é a linha e j é a coluna.*/
        double getValue(int i, int j);
        /*Devolve o valor na célula (i, j) da matriz, 
        onde i é a linha e j é a coluna.*/
        int getColuna();
        int getLinha();
        //  double getValue(int i, int j);
        /*Esse método imprime a matriz A,
        inclusive os elementos iguais a zero.*/
        void print();

        Matriz *soma(Matriz *A, Matriz *B);
        

        Matriz *lerMatrizDeArquivo (std::string nomeDoArquivo);

};
       Matriz *multiplica(Matriz *A, Matriz *B);


#endif