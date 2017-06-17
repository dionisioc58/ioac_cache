/**
* @file 	funcoes.h
* @brief	Arquivo de cabeçalho com a definição de funções auxiliares para a entrada de dados
* @author   Dionísio Carvalho (dionisio@naracosta.com.br)
* @since    11/03/2017
* @date     15/06/2017
*/

#ifndef FUNCOES_H
    #define FUNCOES_H

    #include <iostream>
    using std::cin;
    using std::cout;
    using std::endl;

    #include <sstream>
    using std::stringstream;
    #include <string>
    using std::string;

    /**
    * @brief        Função que coleta um valor float maior que zero pela entrada validando-o
    * @param[in]	msg String com a mensagem à exibir
    * @param[in]	min Int com o valor mínimo aceitável
    * @return       Float capturado
    */
    float recebeFloat(string msg, int min);

    /**
    * @brief        Função que coleta um valor inteiro maior ou igual à zero pela entrada validando-o
    * @param[in]    msg String com a mensagem à exibir
    * @param[in]	min Int com o valor mínimo aceitável
    * @param[in]	max Int com o valor máximo aceitável
    * @return       Int capturado
    */
    int recebeInt(string msg, int min, int max = 0);

    /**
    * @brief        Função que coleta um valor string pela entrada validando-o
    * @param[in]    msg String com a mensagem à exibir
    * @return       String capturada
    */
    string recebeString(string msg);

    /**
    * @brief Funcao que converte todos os caracteres para letra minuscula
    * @param s String a ser convertida
    */
    void minusculas(string& s);

    /**
    * @brief Função que remove acentuações de uma string
    * @param s String com acentuações a remover
    */
    void remove_acentos (string &s);

    /**
    * @brief Função que calcula o comprimento da variável
    * @param x Variável a ser medida
    * @return Comprimento da variável
    */
    template <typename T>
    int comp(T x) {
        stringstream ss;
        ss << x;
        return ss.str().length();
    }

#endif