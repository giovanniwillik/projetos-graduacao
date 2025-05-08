# Diretório com os arquivos-fonte
SRC_DIR = src

# Arquivos que você precisa compilar
SOURCES = $(SRC_DIR)/Player.java $(SRC_DIR)/Score.java $(SRC_DIR)/Shot.java $(SRC_DIR)/Wall.java

# Detecta separador de classpath por SO
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CPSEP = :
else
	CPSEP = ;
endif

# O classpath inclui o diretório com os .class das dependências
CLASSPATH = $(SRC_DIR)

JAVAC = javac
JAVA = java

all: build

build:
	@echo "Compilando arquivos Java..."
	$(JAVAC) -cp $(CLASSPATH) $(SOURCES)

run:
	@echo "Executando o jogo..."
	$(JAVA) -cp $(CLASSPATH) Combat

clean:
	@echo "Limpando arquivos compilados do usuário..."
	@rm -f $(SRC_DIR)/Player.class $(SRC_DIR)/Score.class $(SRC_DIR)/Shot.class $(SRC_DIR)/Wall.class
