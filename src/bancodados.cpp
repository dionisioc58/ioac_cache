/**
* @file 	bancodados.cpp
* @brief	Arquivo de corpo com a definição de funções para o controle dos dados
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    15/06/2017
* @date     15/06/2017
*/

#include "bancodados.h"

/**
* @brief        Função que recupera o cadastro completo a partir de um arquivo
* @param[in]    nome Caminho/nome do arquivo de dados
* @param[out]   *c Cache
*/
void abrirBD(string nome, Cache *c) {
    ifstream entrada(nome);
    if(!entrada) {
        cout << "Não foi possível abrir o arquivo de configurações." << endl;
        exit(1);
    }
    string texto;
    
    entrada.clear();
    entrada.seekg(0);
    int linha = 0;
    
    while(!entrada.eof()) {
        getline(entrada, texto);
        if(texto != "") {
            switch(linha % 6) {
                case 0:
                    c->tam_bloco = stoi(texto);
                    break;
                case 1:
                    c->qtd_linhas = stoi(texto);
                    break;
                case 2:
                    c->qtd_blocos = stoi(texto);
                    break;
                case 3:
                    c->map_tipo = stoi(texto);
                    break;
                case 4:
                    c->qtd_vias = stoi(texto);
                    break;
                case 5:
                    c->substituicao = stoi(texto);
                    break;
            }
            linha++;
        }
    }
    entrada.close();
    cout << "Arquivo lido com sucesso!" << endl;
    cout << "Configurações: " << endl;
    cout << *c << endl;
    parar();
}

/**
* @brief        Função que exibe uma mensagem para manter a tela congelada
*/
void parar() {
    cin.clear();
    fflush(stdin);
    cout << "Pressione ENTER para continuar...";
    string p;
    getline(cin, p);
}