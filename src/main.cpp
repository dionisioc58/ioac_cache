/**
* @file    "main.cpp
* @brief 	Arquivo fonte para execução do projeto
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    15/06/2017
* @date     15/06/2017
*/

#include <iostream>
using namespace std;

#include "funcoes.h"
#include "menu.h"
#include "bancodados.h"
#include "cache.h"
#include "funcoescache.h"

#define qtde 4                 /**< Quantidade de opções no menu */

string opcoes[qtde] = {
    "Ler",
    "Exibir",
    "Exibir configurações", 
    "Sair"  //0  - ok
};                /**< Opções do menu */

/**
* @brief        Função principal do programa
* @param[in]	argc	Quantidade de argumentos
* @param[in]    *argv[]	Argumento com o caminho/nome do arquivo de dados a ser lido
* @return		Retorno
*/
int main(int argc, char* argv[]) {
    srand(time(NULL));
    Cache *cache = new Cache();            /**< Memória cache */
    abrirBD("./data/config.dat", cache);   /**< Carrega as configurações da cache */
    cache->Inicia();                       /**< Inicializa a cache com -1 */

    int *conteudo = new int[(cache->qtd_blocos * cache->tam_bloco)]; /**< Define a variável para comportar os conteúdos */

    int busca;                              /**< Variável para busca da palavra */

    /** < Preenche o conteúdo com valores aleatórios */
	for(int i = 0; i < (cache->qtd_blocos * cache->tam_bloco); i++)
		conteudo[i] = rand() % 5000;

    while(1) {
        switch(showMenu("Simulador de Memória Cache", opcoes, qtde)) { //Exibir o menu
            case 0:     //Sair
                cout << endl;
                delete cache;
                delete[] conteudo;
                return 0;

            case 1:     //Ler
                busca = recebeInt("Buscar que palavra: ", 0, ((cache->qtd_blocos * cache->tam_bloco) - 1));
                LerPalavra(cache, busca);
                break;

            case 2:     //Exibir
                Exibir(cache, conteudo);
                break;

            case 3:     //Exibir configurações
                cout << *cache << endl;
        }
        parar();
    }
    cout << endl;
    delete cache;
    delete[] conteudo;
    return 0;
}