/**
* @file	cache.cpp
* @brief	Implementação da classe Cache
* @author	Dionísio Carvalho (dionisio@naracosta.com.br)
* @since	15/06/2017
* @date	15/06/2017
*/
#include "cache.h"
#include <iostream>

/**
* @details Os valores de todos os atributos são inicializados com 0
*/	
Cache::Cache(){
	srand(time(NULL));
	tam_bloco 	 = 0;
	qtd_linhas 	 = 0;
	qtd_blocos 	 = 0;
	map_tipo 	 = 0;
	qtd_vias 	 = 0;
	substituicao = 0;
}

/**
* @details Destrutor padrão
*/
Cache::~Cache() {
    if(bloco)
		delete[] bloco;
	for (list<Historico*>::iterator it = historico.begin(); it != historico.end(); ++it)
		delete *it;
}

/**
* @details Inicializa a cache com -1
*/
void Cache::Inicia() {
	bloco = new Bloco[qtd_linhas];
}

/**
* @details Função que procura o bloco mais acessado
* @return  Posição do bloco com maior número de acessos 
*/
int Cache::MaisAcessado() {
	Bloco maior = bloco[0];
	int retorno = 0;
	for(int j = 1; j < qtd_linhas; j++)
		if(maior.acessos < bloco[j].acessos) {
			maior = bloco[j];
			retorno = j;
		}

	return retorno;
}

/**
* @details 		Função que procura o bloco menos acessado
* @param[in]	b Bloco que será inserido ou -1 para modo direto ou totalmente associativo
* @return  		Posição do bloco com menor número de acessos 
*/
int Cache::MenosAcessado(int b) {
	int retorno = 0;
	if(b == -1) {
		Bloco menor = bloco[0];
		for(int j = 1; j < qtd_linhas; j++)
			if(menor.acessos > bloco[j].acessos) {
				menor = bloco[j];
				retorno = j;
			}
	} else {
		int inicio = (b % qtd_vias) * (qtd_linhas / qtd_vias);
		retorno = inicio;
		Bloco menor = bloco[inicio];
		for(int j = inicio; j < (inicio + (qtd_linhas / qtd_vias)); j++) {
			if(menor.acessos > bloco[j].acessos) {
				menor = bloco[j];
				retorno = j;
			}
		}
	}

	return retorno;
}

/**
* @details 		Função que procura o bloco com maior fifo
* @param[in]	b Bloco que será inserido ou -1 para modo direto ou totalmente associativo
* @return  		A posição do bloco com maior fifo
*/
int Cache::MaiorFifo(int b) {
	int retorno = 0;
	if(b == -1) {
		Bloco maior = bloco[0];
		for(int j = 1; j < qtd_linhas; j++)
			if(maior.fifo < bloco[j].fifo) {
				maior = bloco[j];
				retorno = j;
			}
	} else {
		int inicio = (b % qtd_vias) * (qtd_linhas / qtd_vias);
		retorno = inicio;
		Bloco maior = bloco[inicio];
		for(int j = inicio; j < (inicio + (qtd_linhas / qtd_vias)); j++) {
			if(maior.fifo < bloco[j].fifo) {
				maior = bloco[j];
				retorno = j;
			}
		}
	}

	return retorno;
}

/**
* @details Função que procura o bloco com menor fifo
* @return  A posição do bloco com menor fifo
*/
int Cache::MenorFifo() {
	Bloco menor = bloco[0];
	int retorno = 0;
	for(int j = 1; j < qtd_linhas; j++)
		if(menor.fifo > bloco[j].fifo) {
			menor = bloco[j];
			retorno = j;
		}

	return retorno;
}

/**
* @details Função que procura o bloco com acesso mais recente
* @return  A posição do bloco com acesso mais recente
*/
int Cache::MaisNova() {
	Bloco menor = bloco[0];
	int retorno = 0;
	for(int j = 1; j < qtd_linhas; j++)
		if(menor.ultacesso < bloco[j].ultacesso) {
			menor = bloco[j];
			retorno = j;
		}

	return retorno;
}

/**
* @details 		Função que procura o bloco com acesso mais antigo
* @param[in]	b Bloco que será inserido ou -1 para modo direto ou totalmente associativo
* @return  		A posição do bloco com acesso mais antigo
*/
int Cache::MaisAntiga(int b) {
	int retorno = 0;
	if(b == -1) {
		Bloco maior = bloco[0];
		for(int j = 1; j < qtd_linhas; j++)
			if(maior.ultacesso > bloco[j].ultacesso) {
				maior = bloco[j];
				retorno = j;
			}
	} else {
		int inicio = (b % qtd_vias) * (qtd_linhas / qtd_vias);
		retorno = inicio;
		Bloco maior = bloco[inicio];
		for(int j = inicio; j < (inicio + (qtd_linhas / qtd_vias)); j++) {
			if(maior.ultacesso > bloco[j].ultacesso) {
				maior = bloco[j];
				retorno = j;
			}
		}
	}

	return retorno;
}

/**
* @brief 		Acessa um bloco
* @param[in] 	palavra Palavra à ser acessada
* @return 		Vetor com HIT/MISS (1 ou 0) e Posição da linha
*/
int *Cache::Acessa(int palavra) {
	int *ret = new int[2];
	int b = palavra / tam_bloco;
	int calc_mapeamento = map_tipo;

	if(map_tipo == AssociativoParcial) {			//Alterar o tipo de mapeamento
		if(qtd_vias == 1)							//Se parcial e só uma via => mapeamento direto
			calc_mapeamento = Diretamente;
		if(qtd_vias == qtd_linhas)					//Se parcial e vias = linhas => associativo total
			calc_mapeamento = AssociativoTotal;
	}
	int linha;
	ret[0] = 0; //MISS
	ret[1] = -1;
	if(calc_mapeamento == Diretamente) {
		linha = b % qtd_linhas;
		if(bloco[linha] == b)
			ret[0] = 1; //HIT
		else {
			ret[0] = 0; //MISS
			bloco[linha] = b;
		}
		ret[1] = linha;
	}

	if(calc_mapeamento == AssociativoTotal) {
		ret[1] = Busca(b); //Procura o bloco
		if(ret[1] > -1) {
			ret[0] = 1; //HIT
		} else {
			ret[0] = 0; //MISS
			ret[1] = Vaga();		//Busca uma vaga
			if(ret[1] > -1) {
				bloco[ret[1]] = b;	//Guarda na vaga
			} else {				//Não tem vaga
				//Aplicar política de substituição
				if(substituicao == Aleatorio)
					linha = rand() % qtd_linhas;	//Pega uma linha aleatoriamente
				if(substituicao == FIFO)
					linha = MaiorFifo();			//Pega a linha com maior fifo (entrou primeiro)
				if(substituicao == LFU)
					linha = MenosAcessado();		//Pega a linha com menos acessada
				if(substituicao == LRU)
					linha = MaisAntiga();			//Pega a linha acessada há mais tempo
				bloco[linha] = b;
				ret[1] = linha;
			}
		}
	}

	if(calc_mapeamento == AssociativoParcial) {
		ret[1] = Busca(b); //Procura o bloco
		if(ret[1] > -1) {
			ret[0] = 1; //HIT
		} else {
			ret[0] = 0; //MISS
			ret[1] = Vaga(b);		//Busca uma vaga - modo parcial
			if(ret[1] > -1) {
				bloco[ret[1]] = b;	//Guarda na vaga
			} else {				//Não tem vaga
				linha = (b % qtd_vias) * (qtd_linhas / qtd_vias);	//Posiciona na primeira linha da via apropriada
				//Aplicar política de substituição
				if(substituicao == Aleatorio)
					linha += rand() % (qtd_linhas / qtd_vias);	//Pega uma linha aleatoriamente
				if(substituicao == FIFO)
					linha = MaiorFifo(b);			//Pega a linha com maior fifo (entrou primeiro)
				if(substituicao == LFU)
					linha = MenosAcessado(b);		//Pega a linha com menos acessada
				if(substituicao == LRU)
					linha = MaisAntiga(b);			//Pega a linha acessada há mais tempo
				bloco[linha] = b;
				ret[1] = linha;
			}
		}
	}
	GravaHistorico(palavra, ret[0]);
	AtualizaFIFO();
	return ret;
}

/**
* @details Função que grava o histórico de acessos à cache
* @param[in] p Palavra que foi acessada
* @param[in] r HIT (1) ou MISS (0)
*/
void Cache::GravaHistorico(int p, int r) {
	historico.push_back(new Historico(p, (p / tam_bloco), tam_bloco, bloco, r));
}

/**
* @details 		Função que busca um bloco
* @param[in] 	b Número do bloco
* @return		Retorna a posição do bloco ou -1 caso não seja encontrado
*/
int Cache::Busca(int b) {
	for(int i = 0; i < qtd_linhas; i++)
		if(bloco[i] == b) {
			bloco[i].acessos++;
			bloco[i].ultacesso = time(NULL);
			return i;
		}
	return -1;
}

void Cache::AtualizaFIFO() {
	for(int i = 0; i < qtd_linhas; i++)
		if(bloco[i] != -1)
			bloco[i].fifo++;
}

/**
* @details 		Função que busca um bloco vazio
* @param[in]	b Bloco que será inserido ou -1 para modo direto ou totalmente associativo
* @return		Retorna a posição do bloco ou -1 caso não tenha vaga
*/
int Cache::Vaga(int b) {
	if(b == -1) {
		for(int i = 0; i < qtd_linhas; i++)
			if(bloco[i] == -1)
				return i;
	} else {
		int inicio = (b % qtd_vias) * (qtd_linhas / qtd_vias);
		for(int i = inicio; i < (inicio + (qtd_linhas / qtd_vias)); i++) {
			if(bloco[i] == -1)
				return i;
		}
	}
	return -1;
}

/** 
* @details  	O operador é sobrecarregado para representar o Fornecedor e 
*           	a quantidade de seus produtos
* @param[inout]	os Referência para stream de saída
* @param[inout]	c Referência para o objeto Fornecedor a ser impresso
* @return		Referência para stream de saída
*/
ostream& operator<<(ostream &os, Cache &c) {
	os << "Palavras no bloco: " << c.tam_bloco << endl;
	os << "Quantidade de linhas: " << c.qtd_linhas << endl;
	os << "Quantidade de blocos: " << c.qtd_blocos << endl;
	os << "Tipo de mapeamento: " << c.map_tipo  << " (";
	os << (c.map_tipo == 1 ? "Mapeamento direto" : (c.map_tipo == 2 ? "Totalmente associativo" : "Parcialmente associativo"));
	os << ")" << endl;
	os << "Quantidade de vias: " << c.qtd_vias << (c.map_tipo != 3 ? " (Desconsiderado)" : "") << endl;
	os << "Política de substituição: " << c.substituicao << " (";
	os << (c.substituicao == 1 ? "Aleatório" : (c.substituicao == 2 ? "FIFO" : (c.substituicao == 3 ? "LFU" : "LRU")));
	os << ")" << (c.map_tipo == 1 ? " (Desconsiderado)" : "") << endl;
	return os;
}