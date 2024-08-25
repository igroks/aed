#Arquivo de diretivas de compilação de promagas

####### Variavéis #######:

#diretórios:
SRC = ./src
BIN = ./bin
APPS = ./apps
INCLUDE = ./include
OBJ = ./obj

#compilador:
CC = gcc

#arquivos:
EXC = testeHeap # Nome do arquivo que sera executado
NAME_TAD = myHeap.o # Nome do arquivo com a implementação dos TAD + .o


#-------

all: lib app
	

lib: $(OBJ)/$(NAME_TAD)


app: $(BIN)/$(EXC)
	


$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	$(CC) -c $< -I $(INCLUDE) -o $@


$(BIN)/%: $(APPS)/%.c
	$(CC) $< $(OBJ)/*.o -I $(INCLUDE) -o $@

# $< pega a primeira dependencia($(SRC)/%.c)
# $@ pega o target/alvo($(OBJ)/%.o)


run:
	$(BIN)/$(EXC)


clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*
