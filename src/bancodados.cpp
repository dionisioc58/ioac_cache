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
    
    while((!entrada.eof()) && (linha < 6)) { //DESCONSIDERAR A LINHA COM POLÍTICA DE ESCRITA - 7ª LINHA
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
* @brief        Função que carreg um arquivo de script e o executa
* @param[in]    nome Caminho/nome do arquivo de script
* @param[in]    *c Cache
* @param[in]    *conteudo Conteúdo da memória
*/
void execScript(string nome, Cache *c, int *conteudo) {
    if(nome == "")
        nome = recebeString("Digite o caminho/nome do arquivo de script: ");

    cout << "Abrindo arquivo de script..." << endl;
    ifstream entrada(nome);
    if(!entrada) {
        cout << "Não foi possível abrir o arquivo de script." << endl;
        return;
    }
    string texto;
    
    entrada.clear();
    entrada.seekg(0);
    int linha = 0;
    int count_miss = 0, count_hit = 0;
    
    while(!entrada.eof()) {
        getline(entrada, texto);
        if(texto != "") {
            if(texto.substr(0, 1) != "#") { //Linha não comentada
                if(texto.substr(0, 4) == "READ") {
                    if(LerPalavra(c, stoi(texto.substr(5))))
                        count_hit++;
                    else
                        count_miss++;
                    ExibirHistorico(c, 0);
                    parar(200);
                } else if(texto.substr(0, 4) == "SHOW") {
                    ExibirCache(c, conteudo);
                    parar();
                    ExibirMem(c, conteudo);
                } else {
                    cout << "Comando não reconhecido na linha " << (linha + 1) << endl;
                    parar();
                }
                linha++;
            }
        }
    }
    entrada.close();
    cout << "Script executado com sucesso!" << endl;
    cout << "Quantidade de comandos: " << linha << endl;
    cout << count_hit << " HIT e " << count_miss << " MISS." << endl;
    cout << "Taxa de hit: " << (count_hit * 100 / (count_hit + count_miss)) << "%" << endl;
}

/**
* @brief        Função que exibe uma mensagem para manter a tela congelada
* @param[in]    milissegundos Tempo em milissegundos até continuar automaticamente
*               Se 0, aguarda o ENTER
*/
void parar(int milissegundos) {
    cin.clear();
    fflush(stdin);
    string p;
    if(milissegundos == 0) {
        cout << "Pressione ENTER para continuar...";
        getline(cin, p);
    } else {
        //Aguardar um tempo em milissegundos
        std::chrono::milliseconds dura(milissegundos);
        std::this_thread::sleep_for(dura);
    }
}