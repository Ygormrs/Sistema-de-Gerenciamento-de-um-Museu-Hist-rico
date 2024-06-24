//SISTEMA DE GERENCIAMENTO DO MUSEU HIST�RICO UNIP
//CURSO: AN�LISE E DESENVOLVIMENTO DE SISTEMA
//TURMA: DS2R48
//ALUNO: YGOR MELO R. DA SILVA	 - G7640C5

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#define RAND_MAX 20000

struct usuario{
	char nome[25];
	//int notaInteresse;
};

int notaFiscal(){
	srand( (unsigned)time(NULL) );
	return rand() % RAND_MAX;
}

void consultaDados(){
	//fun��o para o administrador consultar o banco de dados
	char linha[100];
	char *result;
	int i;
	
	FILE *arquivo = fopen("BancoDados.txt", "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir ao consultar arquivo.\n");
        	} 
		i = 1;
		while (!feof(arquivo)){
			result = fgets(linha, 100, arquivo);
			if (result){
				printf("Linha %02d : %s", i, linha);
				i++;
			}
		}
}

void apagaBD(){
	//Fun��o para o administrador apagar o banco de dados
	FILE *arquivo = fopen("BancoDados.txt", "w");
    				if (arquivo != NULL) {
        				fclose(arquivo);
        				printf("Conte�do do arquivo apagado com sucesso.\n");
    					}
						else {
        					printf("Erro ao apagar conte�do do arquivo.\n");
    					}
}

void menu_usuario(){
	int escolhaExposicao;
        while (1) {
            printf("\nEscolha a exposi��o que deseja:\n");
            printf("1. Exposi��o 'I  Guerra Mundial' [Ingresso R$ 25,00]\n");
            printf("2. Exposi��o 'II Guerra Mundial' [Ingresso R$ 25,00]\n");
            printf("0. Sair\n");

            scanf("%d", &escolhaExposicao);

            switch (escolhaExposicao) {
                case 1:
                    printf("\nConhe�a os ve�culos, armas e equipamentos da Primeira Guerra Mundial:\n");
                    break;
                case 2:
                    printf("\nConhe�a os ve�culos, armas e equipamentos da Segunda Guerra Mundial:\n");
                    break;
                case 0:
                    printf("\nVoc� saiu do sistema.\n");
                    return 0;
                default:
                    printf("\nOp��o inv�lida!.\n");
                    return 0;
            }

            char confirmacao;
			
            printf("\nDeseja confirmar a sua escolha? (S/N): \n");
            scanf(" %c", &confirmacao);

            if (confirmacao == 'S' || confirmacao == 's') {
                int quantidadeIngressos;
				printf("Digite a quantidade de ingressos desejado: \n");
				scanf("%d", &quantidadeIngressos);
				while(quantidadeIngressos <= 0){
					printf("Digite um n�mero v�lido!\n");
					while (getchar() != '\n'); // Limpar o buffer do teclado
					scanf("%d", &quantidadeIngressos);
				}
				

                // C�lculo do valor total
                float valorTotal = (quantidadeIngressos * 25.0);
                FILE *arquivo = fopen("BancoDados.txt", "a");
    				if (arquivo != NULL) {
    					fprintf(arquivo, "Ingressos Comprados: %d\n", quantidadeIngressos);
        				fclose(arquivo);
    					}
						else {
        					printf("Erro ao adicionar informa��o ao arquivo.\n");
    					}

                printf("\nValor total a pagar: R$ %.2f\n", valorTotal);

                char metodoPagamento;

                printf("Escolha o m�todo de pagamento (C para cr�dito, D para d�bito, ou 0 para cancelar): ");
                scanf(" %c", &metodoPagamento);
                
                int NF = notaFiscal();

                if (metodoPagamento == 'C' || metodoPagamento == 'c') {
                    printf("Voc� escolheu pagamento com cart�o de cr�dito.\n");
                    FILE *arquivo = fopen("BancoDados.txt", "a");
    				if (arquivo != NULL) {
    					fprintf(arquivo, "Pagamento: %c \n", metodoPagamento);
        				fclose(arquivo);
    					}
						else {
        					printf("Erro ao adicionar informa��o ao arquivo.\n");
    					}
                    printf("Insira seu cart�o...\n");

                    char confirmarPagamento;
                    printf("Digite 'A' para compra aprovada ou 'B' para compra negada: ");
                    scanf(" %c", &confirmarPagamento);

                    if (confirmarPagamento == 'A' || confirmarPagamento == 'a') {
                        printf("Pagamento com cart�o de cr�dito aprovado. Aguarde a impress�o dos ingressos...\n");
                        printf("Gerando Nota Fiscal... %d", NF);
                        
                        FILE *arquivo = fopen("BancoDados.txt", "a");
                        	time_t t = time(NULL);
							struct tm date = *localtime(&t);
                        	if (arquivo != NULL) {
                        		fprintf(arquivo, "Nota Fiscal: %d\n", NF);
                        		fprintf(arquivo, "%d-%02d-%02d %02d:%02d\n----------------------------\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);
        						fclose(arquivo);
        						printf("\nInforma��es gravadas com sucesso.\n");
    						}
						else {
        					printf("Erro ao adicionar informa��o ao arquivo.\n");
    					}
    					
                    } else {
                        printf("Pagamento com cart�o de cr�dito recusado. Sua compra foi encerrada.\n");
                    }
                } else if (metodoPagamento == 'D' || metodoPagamento == 'd') {
                    printf("Voc� escolheu pagamento com cart�o de d�bito.\n");
                    FILE *arquivo = fopen("BancoDados.txt", "a");
                    if (arquivo != NULL) {
                    	fprintf(arquivo, "Pagamento: %c \n", metodoPagamento);
        				fclose(arquivo);
    					}
						else {
        					printf("Erro ao adicionar informa��o ao arquivo.\n");
    					}
                    printf("Insira seu cart�o...\n");

                    char confirmarPagamento;
                    printf("Digite 'A' para compra aprovada ou 'B' para compra negada: ");
                    scanf(" %c", &confirmarPagamento);

                    if (confirmarPagamento == 'A' || confirmarPagamento == 'a') {
                        printf("Pagamento com cart�o de d�bito aprovado. Aguarde a impress�o dos ingressos...\n");
                        printf("Gerando Nota Fiscal... %d", NF);
                        FILE *arquivo = fopen("BancoDados.txt", "a");
                        	time_t t = time(NULL);
							struct tm date = *localtime(&t);
                        	if (arquivo != NULL) {
                        		fprintf(arquivo, "Nota Fiscal: %d\n", NF);
                        		fprintf(arquivo, "%d-%02d-%02d %02d:%02d\n----------------------------\n", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday, date.tm_hour, date.tm_min);
        						fclose(arquivo);
        						printf("\nInforma��es gravadas com sucesso.\n");
    						}
						else {
        					printf("Erro ao adicionar informa��o ao arquivo.\n");
    					}
                    } else {
                        printf("Pagamento com cart�o de d�bito recusado. Sua compra foi encerrada.\n");
                    }
                } else {
                    printf("Pagamento cancelado. Sua compra foi encerrada.\n");
                }
                return 0;
        	} else {
                printf("Escolha cancelada. Voc� retornou ao menu principal.\n");
            }
         }
}

void menu_admin(){
	//Menu do Administrador
	while (1) {
			int escolhaAcao;
            printf("1. Consultar Informa��es\n");
            printf("2. Apagar conte�do'\n");
            printf("0. Sair\n");

            scanf("%d", &escolhaAcao);

            switch (escolhaAcao) {
                case 1:
                    printf("Consultando informa��es...\n");
                    consultaDados();
                    break;
                case 2:
                    printf("\nApagando informa��es do arquivo...:\n");
                    apagaBD();
                    break;
                case 0:
                    printf("\nVoc� saiu do sistema.\n");
                    return 0;
                default:
                    printf("\nOp��o inv�lida!.\n");
                    return 0;
            }
	}
}

int main() {
    setlocale(LC_ALL, "Portuguese");
	
	// sistema de compra de ingressos
    printf("Seja bem vindo(a) ao Museu Hist�rico de Guerra\n");

    printf("Digite [1] para entrar como usu�rio: \n");
    printf("Digite [2] para entrar como adm: \n");
    
    int autenticar;
    scanf("%d", &autenticar);
    
    while(autenticar != 1 && autenticar != 2){
    	printf("Digite um n�mero v�lido: ");
    	scanf("%d", &autenticar);
	}
	
	if (autenticar == 1){
		printf("Entrou como usu�rio, qual o seu nome?: \n");
		struct usuario nomeUsuario;
		scanf("%s", nomeUsuario.nome);
		printf("Seja bem vindo(a) %s \n", &nomeUsuario.nome);
		FILE *arquivo = fopen("BancoDados.txt", "a");
    				if (arquivo != NULL) {
    					fprintf(arquivo, "Nome: %s\n", nomeUsuario.nome);
        				fclose(arquivo);
    					}
						else {
        					printf("Erro ao adicionar informa��o ao arquivo.\n");
    					}
		menu_usuario();
	}
	
	char senhaAdm[] = "admin";
	char senha[10];
	int login_efetuado = 0;
	
	if (autenticar == 2){
		printf("Entrou como Administrador, digite a senha para acessar as informa��es!\n");
		printf("Senha: ");
		scanf("%s", &senha);
	
	
	while(login_efetuado == 0){
		if (strcmp(senha, senhaAdm) == 0){
            printf("\nEntrou como Administrador...\n\n");
            login_efetuado = 1;
        }
        else{
        	printf("\nDADOS INVALIDOS!\n");    
            printf("Digite a senha novamente:\n");
            printf("Senha: ");
            scanf("%s", &senha);
		}
	}
	menu_admin();
	}
    
return 0;
}
