/**
* @file	cache.h
* @brief	Definição da classe Cache
* @author	Dionísio Carvalho (dionisio@naracosta.com.br)
* @since	15/06/2017
* @date	15/06/2017
*/
#ifndef CACHE_H
#define CACHE_H

	#include <iostream>
	#include <ctime>
	#include <list>
	using std::ostream;
	using std::endl;
	using std::list;

	//! Mapeamentos
    /*! Tipos de mapeamentos de memória. */
	enum Mapeamentos {
		Diretamente = 1,	/**< Mapeamento direto */
		AssociativoTotal,	/**< Totalmente associativo */
		AssociativoParcial	/**< Parcialmente associativo */
	};

	//! Políticas
    /*! Políticas de substituição de blocos. */
	enum Politicas {
		Aleatorio = 1,		/**< Aleatória */
		FIFO,				/**< FIFO - First in, first out */
		LFU,				/**< LFU  - Least frequently used */
		LRU					/**< LRU  - Least recently used */
	};

	/**
    * @class   Bloco cache.h
    * @brief   Classe que representa um bloco
    * @details Os atributos são: valor, acessos, ultacesso
    */  
	class Bloco {
		public:
			int valor;											/**< Valor */
			int acessos;										/**< Quantidade de acessos */
			int fifo;											/**< Controle para FIFO */
			std::time_t ultacesso;								/**< Data/hora do último acesso */

			Bloco() { 											/**< @brief Construtor padrão */
				valor = -1;
				acessos = 0;
				fifo = 0;
			}
			~Bloco() {}											/**< @brief Destrutor padrão */
			friend ostream& operator<<(ostream& os, Bloco &b) {	/** @brief Sobrecarga do operador de extração em stream */
				os << b.valor;
                return os;
            }
			bool operator==(int v) {							/** @brief Sobrecarga do operador de comparação == */
				if(valor == v)
					return true;
				return false;
			}
			bool operator!=(int v) {							/** @brief Sobrecarga do operador de comparação != */
				if(valor != v)
					return true;
				return false;
			}
			int operator*(int v) {								/** @brief Sobrecarga do operador de multiplicação (*) */
				return valor * v;
			}
			void operator=(int v) {								/** @brief Sobrecarga do operador de atribuição = */
				valor = v;
				fifo = 0;
				acessos = 1;
				ultacesso = time(NULL);
			}
	};

	/**
    * @class   Historico cache.h
    * @brief   Classe que representa um historico
    * @details Os atributos são: palavra, bloco, qtd_blocos, blocos, resultado
    */  
	class Historico {
		public:
			int palavra;										    /**< Palavra */
			int bloco;	    									    /**< Número do bloco em que a palavra se encontra */
            int qtd_blocos;    									    /**< Número do blocos da cache */
			int *val_blocos;									    /**< Vetor de blocos com a situação de cada um na cache */
			bool resultado;     								    /**< HIT (1) ou MISS (0) */

			Historico(int p, int b, int qtd, Bloco *bls, bool r) {	/**< @brief Construtor parametrizado */
				palavra = p;
				bloco = b;
                qtd_blocos = qtd;
				val_blocos = new int[qtd];
				for(int i = 0; i < qtd; i++)
					val_blocos[i] = bls[i].valor;
				resultado = r;
			}
			~Historico() {										    /**< @brief Destrutor padrão */
				delete[] val_blocos;
			}
	};

	/**
    * @class   Cache cache.h
    * @brief   Classe que representa uma cache
    * @details Os atributos são: tam_bloco, qtd_linhas, qtd_blocos, map_tipo, qtd_vias, substituicao
    */  
	class Cache {
		public:
			Bloco *bloco;										/**< Bloco */
			int tam_bloco;  									/**< Quantidade de palavras no bloco */
			int qtd_linhas; 									/**< Quantidade de linhas */
			int qtd_blocos; 									/**< Quantidade de blocos */
			int map_tipo;   									/**< Tipo de mapeamento */
			int qtd_vias;   									/**< Número de vias (para o caso de ser parcialmente associativo) */
			int substituicao; 									/**< Política de substituição */
			list<Historico*> historico;							/**< Histórico de acessos da cache */
		
			Cache(); 											/**< @brief Construtor padrão */
			~Cache();											/**< @brief Destrutor padrão */
			void Inicia();										/**< @brief Inicializa a cache com -1 */
			int MaisAcessado();									/**< @brief Retorna o bloco mais acessado */
			int MenosAcessado(int b = -1);						/**< @brief Retorna o bloco menos acessado */
			int MaiorFifo(int b = -1);							/**< @brief Retorna o bloco com maior fifo */
			int MenorFifo();									/**< @brief Retorna o bloco com menor fifo */
			int MaisNova();										/**< @brief Retorna o bloco com acesso mais recente */
			int MaisAntiga(int b = -1);							/**< @brief Retorna o bloco com acesso mais antigo */
			int *Acessa(int palavra);							/**< @brief Acessa uma palavra */
			void GravaHistorico(int p, int r);					/**< @brief Grava o histórico de acessos à cache */
			int Busca(int b);									/**< @brief Busca um bloco */
			void AtualizaFIFO();								/**< @brief Atualiza os números fifo dos blocos não vazios */
			int Vaga(int b = -1);								/**< @brief	Função que busca um bloco vazio	*/
			friend ostream& operator<<(ostream &os, Cache &c); 	/** @brief Sobrecarga do operador de extração em stream */
			bool operator==(Cache &c);							/** @brief Sobrecarga do operador de comparação == */
	};

#endif