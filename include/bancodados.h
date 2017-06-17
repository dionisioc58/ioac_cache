/**
* @file 	bancodados.h
* @brief	Arquivo de cabeçalho com a definição de funções para o controle dos dados
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    15/06/2017
* @date     15/06/2017
*/

#ifndef BANCODADOS_H
    #define BANCODADOS_H

    #include <iostream>
    using std::cin;
    using std::cout;
    using std::endl;

    #include <fstream>
    using std::ifstream;
    using std::ofstream;

    #include <string>
    using std::string;

    #include <sstream>
    
    #include "cache.h"
    #include "funcoescache.h"

    /**
    * @brief        Função que recupera o cadastro completo a partir de um arquivo
    * @param[in]    nome Caminho/nome do arquivo de dados
    * @param[out]   *c Cache
    */
    void abrirBD(string nome, Cache *c);

    /**
    * @brief        Função que carreg um arquivo de script e o executa
    * @param[in]    nome Caminho/nome do arquivo de script
    * @param[in]    *c Cache
    * @param[in]    *conteudo Conteúdo da memória
    */
    void execScript(string nome, Cache *c, int *conteudo);

    /**
    * @brief        Função que exibe uma mensagem para manter a tela congelada
    */
    void parar();

#endif