/**
* @file 	funcoescache.h
* @brief	Arquivo de cabeçalho com a definição de funções para a cache
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    15/06/2017
* @date     15/06/2017
*/
#include "funcoescache.h"

using namespace std;

/**
* @brief		Exibe a cache
* @param[in]	cache Cache
* @param[in]	conteudo Conteudo
*/
void ExibirCache(Cache *cache, int *conteudo) {
	cout << "Cache L1" << endl;
	cout << "Linha - Bloco - Endereço - Conteúdo" << endl;

	if(cache->map_tipo != 3) { //DIRETO OU TOTALMENTE ASSOCIATIVO
		for(int i = 0; i < cache->qtd_linhas; i++) {
			if(cache->bloco[i] == -1) {
				for(int j = 0; j < cache->tam_bloco; j++)
					cout << i << " - x - x - x" << endl; 

			} else {
				for(int j = 0; j < cache->tam_bloco; j++) {
					cout << i << " - " << cache->bloco[i] << " - " << (cache->bloco[i] * cache->tam_bloco + j);
					cout << " - " << conteudo[(cache->bloco[i] * cache->tam_bloco) + j] << endl;
				}
			}
		}

	} else { //PARCIALMENTE ASSOCIATIVO
		int linhasPorVia = cache->qtd_linhas / cache->qtd_vias;
		for(int i = 0; i < cache->qtd_linhas; i++){
			if(cache->bloco[i] == -1) {
				for(int j = 0; j < cache->tam_bloco; j++)
					cout << i % linhasPorVia << " - x - x - x" << endl;
			} else {
				for(int j = 0; j < cache->tam_bloco; j++) {
					cout << i % linhasPorVia << " - " << cache->bloco[i] << " - " << (cache->bloco[i] * cache->tam_bloco + j);
					cout << " - " << conteudo[(cache->bloco[i] * cache->tam_bloco) + j] << endl;
				}
			}
		}
	}
}

/**
* @brief		Exibe a memória principal
* @param[in]	cache Cache
* @param[in]	conteudo Conteudo
*/
void ExibirMem(Cache *cache, int *conteudo) {
	cout << endl << "Memória Principal" << endl;
	cout << "Bloco - Endereço - Conteúdo" << endl;
	for(int i = 0; i < cache->qtd_blocos; i++)
		for(int j = 0; j < cache->tam_bloco; j++)
			cout << i << " - " << (i * cache->tam_bloco) + j << " - " << conteudo[(i * cache->tam_bloco) + j] << endl;
}

/**
* @brief      Ler palavra no modo de mapeamento direto
* @param[in]  cache Cache
* @param[in]  palavra Palavra a ser lida
 */
void LerPalavra(Cache *cache, int palavra) {
	int *ret = cache->Acessa(palavra);
	if(ret[0] == 0)
		cout << "MISS -> alocado na linha ";
	if(ret[0] == 1)
		cout << "HIT: linha ";
	cout << ret[1] << endl;
	delete[] ret;
}