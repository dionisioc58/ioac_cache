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
* @return	  Retorna true se houve HIT, false se houve MISS
*/
bool LerPalavra(Cache *cache, int palavra) {
	bool retorno;
	int *ret = cache->Acessa(palavra);
	if(ret[0] == 0)
		cout << "MISS -> alocado na linha ";
	if(ret[0] == 1)
		cout << "HIT: linha ";
	cout << ret[1] << endl;
	retorno = ret[0];
	delete[] ret;
	return retorno;
}

/**
* @brief        Função que exibe o histórico da cache
* @param[in]    num Quantidade de últimos eventos a serem exibidos
* @param[in]    *c Cache
*/
void ExibirHistorico(Cache *c, int num) {
	cout << string(50, '\n');
	if(num == 0)
		num = c->historico.size();	//Exibir todos os eventos

	//Inicializa todos os textos
	stringstream linha1, linha2, linha3;
	stringstream *det = new stringstream[c->qtd_linhas];
	linha1 << "Palavra: ";
	linha2 << "Bloco?   ";
	linha3 << "H ou M : ";
	for(int i = 0; i < c->qtd_linhas; i++) {
		det[i] << "Linha " << i << ":";
		det[i] << string(9 - comp(det[i].str()), ' ');
	}
	
	//Posiciona no primeito evento a ser exibido
	list<Historico*>::iterator it = c->historico.begin();
	advance(it, c->historico.size() - num);

	//Itera sobre os eventos a serem exibidos
    for(; it != c->historico.end(); ++it) {
		linha1 << string(3 - comp((*it)->palavra), ' ') << (*it)->palavra;
		linha2 << string(3 - comp((*it)->bloco), ' ') << (*it)->bloco;
		for(int i = 0; i < c->qtd_linhas; i++) {
			if((*it)->val_blocos[i] == -1)
				det[i] << "  -";
			else
				det[i] << string(3 - comp((*it)->val_blocos[i]), ' ') << (*it)->val_blocos[i];
		}
		if((*it)->resultado)
			linha3 << "  H";
		else
			linha3 << "  M";
	}

	//Exibe todas as linhas
	cout << linha1.str() << endl;
	cout << linha2.str() << endl;
	for(int i = 0; i < c->qtd_linhas; i++)
		cout << det[i].str() << endl;
	cout << linha3.str() << endl;
	cout << string(comp(linha1.str()), '_') << endl;
	delete[] det;
}