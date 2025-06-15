# Makefile Simplificado para o Projeto Gerador de Relatórios

# --- Variáveis de Configuração ---
JAVAC = javac
JAVA = java
RM = rm -rf
MKDIR = mkdir -p

SRC_DIR = src
OUT_DIR = out
DATA_DIR = data

# Nome completo da classe principal (pacote.ClassePrincipal)
MAIN_CLASS = src.com.example.relatorios.GeradorDeRelatorios

# Caminhos padrão para arquivos de entrada/saída
DEFAULT_CSV_FILE = $(DATA_DIR)/produtos.csv
DEFAULT_REPORT_FILE = saida.html

# Encontra todos os arquivos .java recursivamente no diretório de fontes
JAVA_SOURCES = $(shell find $(SRC_DIR) -name "*.java")

# --- Variáveis de Configuração do Algoritmo e Critérios ---
ALG = quick
CRITERIO_ORD = descricao_c
CRITERIO_FILTRO = todos
PARAMETRO_FILTRO = ""
ARQUIVO_CSV = $(DEFAULT_CSV_FILE)

# --- Regras de Construção (Targets) ---

# .PHONY declara targets que não correspondem a nomes de arquivos
.PHONY: all build run1 run2 clean

# Target padrão (executado ao rodar 'make' sem argumentos)
all: build

# Constrói o projeto (compila todos os arquivos Java)
build: $(OUT_DIR)
	@echo "Construindo projeto: Compilando fontes Java em '$(OUT_DIR)'..."
	$(JAVAC) -d $(OUT_DIR) $(JAVA_SOURCES)
	@echo "Construção concluída."

# Regra para garantir que o diretório de saída exista
$(OUT_DIR):
	@echo "Criando diretório de saída: $(OUT_DIR)"
	$(MKDIR) $(OUT_DIR)

# Executa o programa
# Se nenhum argumento for passado para o make run, usará os argumentos padrão.
# Você pode sobrescrever os ARGS passando-os na linha de comando, ex:
# make run ARGS="insertion preco_d estoque_menor_igual 10 $(DEFAULT_CSV_FILE)"
run1: build
	@echo "Executando Gerador de Relatórios com parâmetros vindos da linha de comando..."
	$(JAVA) -cp $(OUT_DIR) $(MAIN_CLASS) $(ALG) $(CRITERIO_ORD) $(CRITERIO_FILTRO) $(PARAMETRO_FILTRO) $(ARQUIVO_CSV)

run2: build
	@echo "Executando Gerador de Relatórios com parâmetros obtidos na interação com usuário..."
	$(JAVA) -cp $(OUT_DIR) $(MAIN_CLASS)

# Limpa os arquivos compilados e os relatórios gerados
clean:
	@echo "Limpando arquivos compilados e relatórios gerados..."
	$(RM) $(OUT_DIR) $(DEFAULT_REPORT_FILE)
	@echo "Limpeza concluída."