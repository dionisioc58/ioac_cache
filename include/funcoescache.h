/**
* @file 	funcoescache.h
* @brief	Arquivo de cabeçalho com a definição de funções para a cache
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    15/06/2017
* @date     15/06/2017
*/
#ifndef FUNCOESCACHE_H
#define FUNCOESCACHE_H

#include "cache.h"
#include <iostream>

    /**
    * @brief	 Exibe a cache
    * @param[in] cache Cache
    * @param[in] conteudo Conteudo
    */
    void ExibirCache(Cache *cache, int *conteudo);

    /**
    * @brief		Exibe a memória principal
    * @param[in]	cache Cache
    * @param[in]	conteudo Conteudo
    */
    void ExibirMem(Cache *cache, int *conteudo);

    /**
    * @brief      Ler palavra no modo de mapeamento direto
    * @param[in]  cache Cache
    * @param[in]  palavra Palavra a ser lida
    */
    void LerPalavra(Cache *cache, int palavra);

#endif