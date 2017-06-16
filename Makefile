#Makefile for "Simulador de Memória Cache para IOAC" C++ aplication
#Created by Dionísio Carvalho

# Comandos do sistema operacional
# Linux: rm -rf
# Windows: cmd //C del
RM = rm -rf

# Compilador
CC = g++

# Variaveis para os subdiretorios
BIN_DIR = ./bin
OBJ_DIR = ./build
DOC_DIR = ./doc
INC_DIR = ./include
SRC_DIR = ./src

# Opcoes de compilacao
CFLAGS = -Wall -pedantic -ansi -std=c++11 -I $(INC_DIR)

# Garante que os alvos desta lista nao sejam confundidos com arquivos de mesmo nome
.PHONY: all clean distclean doxy

# Define o alvo (target) para a compilacao completa.
# Ao final da compilacao, remove os arquivos objeto.
all: clean cache doxy
debug: CFLAGS += -g -O0
debug: clean cache

# Alvo (target) para a construcao do executavel main
# Define os arquivos cache.o, funcoescache.o e main.o como dependencias
cache: $(OBJ_DIR)/cache.o $(OBJ_DIR)/funcoescache.o $(OBJ_DIR)/bancodados.o $(OBJ_DIR)/funcoes.o $(OBJ_DIR)/menu.o $(OBJ_DIR)/main.o
	@echo "============="
	@echo "Ligando o alvo $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executavel $@ criado em $(BIN_DIR)] +++"
	@echo "============="

# Alvo (target) para a construcao do objeto cache.o
# Define os arquivos cache.cpp e cache.h como dependencias.
$(OBJ_DIR)/cache.o: $(SRC_DIR)/cache.cpp $(INC_DIR)/cache.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto funcoescache.o
# Define os arquivos funcoescache.cpp e funcoescache.h como dependencias.
$(OBJ_DIR)/funcoescache.o: $(SRC_DIR)/funcoescache.cpp $(INC_DIR)/funcoescache.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto bancodados.o
# Define os arquivos bancodados.cpp e bancodados.h como dependencias.
$(OBJ_DIR)/bancodados.o: $(SRC_DIR)/bancodados.cpp $(INC_DIR)/bancodados.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto funcoes.o
# Define os arquivos funcoes.cpp e funcoes.h como dependencias.
$(OBJ_DIR)/funcoes.o: $(SRC_DIR)/funcoes.cpp $(INC_DIR)/funcoes.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto menu.o
# Define os arquivos menu.cpp e menu.h como dependencias.
$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.cpp $(INC_DIR)/menu.h
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a construcao do objeto main.o
# Define o arquivo main.cpp como dependencia.
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

# Alvo (target) para a geração automatica de documentacao usando o Doxygen.
# Sempre remove a documentacao anterior (caso exista) e gera uma nova.
doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

# Alvo (target) usado para limpar os arquivos temporarios (objeto)
# gerados durante a compilacao, assim como os arquivos binarios/executaveis.
clean:
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
