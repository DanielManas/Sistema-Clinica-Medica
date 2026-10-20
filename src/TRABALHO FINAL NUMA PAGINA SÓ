#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PACIENTES 100

// 1. ESTRUTURA DE DADOS
typedef struct {
    int id;
    char nome[50];
    char sobrenome[50];
    char cpf[15];
    char telefone[20];
} paciente;

// 2. DECLARAÇÃO DAS FUNÇÕES
void cadastrarPaciente(paciente lista[], int *total);
void listarPacientes(paciente lista[], int total);
void ordenarPorNome(paciente lista[], int total);
void buscarPorCPF_Linear(paciente lista[], int total);
void buscarPorNome_Binaria(paciente lista[], int total, int estaOrdenado);

// 3. FUNÇÃO PRINCIPAL (MENU)
int main() {
    paciente listaPacientes[MAX_PACIENTES];
    int totalPacientes = 0;
    int estaOrdenado = 0; // Controle para saber se a lista foi ordenada antes da busca binaria
    int opcao = -1;

    do {
        printf("\n=== SISTEMA DE CLINICA MEDICA ===\n");
        printf("1 - Cadastrar Paciente\n");
        printf("2 - Listar Pacientes\n");
        printf("3 - Ordenar por Nome (Bubble Sort)\n");
        printf("4 - Buscar por CPF (Busca Linear)\n");
        printf("5 - Buscar por Nome (Busca Binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPaciente(listaPacientes, &totalPacientes);
                estaOrdenado = 0; // Novos cadastros desordenam a lista
                break;
            case 2:
                listarPacientes(listaPacientes, totalPacientes);
                break;
            case 3:
                ordenarPorNome(listaPacientes, totalPacientes);
                estaOrdenado = 1; // Sinaliza que o vetor está ordenado
                listarPacientes(listaPacientes, totalPacientes);
                break;
            case 4:
                buscarPorCPF_Linear(listaPacientes, totalPacientes);
                break;
            case 5:
                buscarPorNome_Binaria(listaPacientes, totalPacientes, estaOrdenado);
                break;
            case 0:
                printf("\nSaindo do sistema... Ate logo!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}

// 4. IMPLEMENTAÇÃO DAS FUNÇÕES

void cadastrarPaciente(paciente lista[], int *total) {
    if (*total >= MAX_PACIENTES) {
        printf("\n[ERRO] Limite de memoria atingido!\n");
        return;
    }

    printf("\n--- CADASTRO DE PACIENTE ---\n");
    printf("Digite o ID: ");
    scanf("%d", &lista[*total].id);
    getchar();

    printf("Digite o Nome: ");
    scanf("%s", lista[*total].nome);

    printf("Digite o Sobrenome: ");
    scanf("%s", lista[*total].sobrenome);

    printf("Informe o CPF: ");
    scanf("%s", lista[*total].cpf);

    printf("Informe o Telefone: ");
    scanf("%s", lista[*total].telefone);

    (*total)++;
    printf("\n[SUCESSO] Paciente cadastrado com sucesso!\n");
}

void listarPacientes(paciente lista[], int total) {
    printf("\n--- LISTA DE PACIENTES (%d) ---\n", total);
    if (total == 0) {
        printf("[Nenhum paciente cadastrado na memoria]\n");
        return;
    }

    printf("ID | NOME COMPLETO | CPF | TELEFONE\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%d | %s %s | %s | %s\n",
               lista[i].id, lista[i].nome, lista[i].sobrenome, lista[i].cpf, lista[i].telefone);
    }
}

// ALGORITMO DE ORDENAÇÃO: Bubble Sort (Obrigatorio no PDF)
void ordenarPorNome(paciente lista[], int total) {
    if (total < 2) {
        printf("\n[INFO] Poucos pacientes para ordenar.\n");
        return;
    }

    paciente temp;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    printf("\n[SUCESSO] Lista ordenada por nome via Bubble Sort!\n");
}

// ALGORITMO DE BUSCA 1: Busca Linear (Percorre posicao por posicao)
void buscarPorCPF_Linear(paciente lista[], int total) {
    if (total == 0) {
        printf("\n[INFO] Nenhum paciente cadastrado.\n");
        return;
    }

    char cpfBusca[15];
    printf("\n--- BUSCA LINEAR POR CPF ---\n");
    printf("Digite o CPF procurado: ");
    scanf("%s", cpfBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].cpf, cpfBusca) == 0) {
            printf("\n[ENCONTRADO] Paciente localizado na posicao %d:\n", i);
            printf("ID: %d | Nome: %s %s | CPF: %s | Tel: %s\n",
                   lista[i].id, lista[i].nome, lista[i].sobrenome, lista[i].cpf, lista[i].telefone);
            return; // Encontrou e encerra a funcao
        }
    }

    printf("\n[NAO ENCONTRADO] Nenhum paciente possui o CPF %s.\n", cpfBusca);
}

// ALGORITMO DE BUSCA 2: Busca Binaria (Divide a lista ao meio repetidamente)
void buscarPorNome_Binaria(paciente lista[], int total, int estaOrdenado) {
    if (total == 0) {
        printf("\n[INFO] Nenhum paciente cadastrado.\n");
        return;
    }

    // A busca binaria EXIGE que os dados estejam ordenados (Requisito do PDF)
    if (!estaOrdenado) {
        printf("\n[ATENCAO] A Busca Binaria exige que a lista esteja ordenada primeiro!\n");
        printf("Por favor, execute a opcao 3 (Ordenar) antes de buscar.\n");
        return;
    }

    char nomeBusca[50];
    printf("\n--- BUSCA BINARIA POR NOME ---\n");
    printf("Digite o Primeiro Nome procurado: ");
    scanf("%s", nomeBusca);

    int inicio = 0;
    int fim = total - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;

        int comparacao = strcmp(lista[meio].nome, nomeBusca);

        if (comparacao == 0) {
            printf("\n[ENCONTRADO via Busca Binaria] Posicao %d:\n", meio);
            printf("ID: %d | Nome: %s %s | CPF: %s | Tel: %s\n",
                   lista[meio].id, lista[meio].nome, lista[meio].sobrenome, lista[meio].cpf, lista[meio].telefone);
            return;
        }

        if (comparacao < 0) {
            inicio = meio + 1; // Busca na metade da direita
        } else {
            fim = meio - 1;    // Busca na metade da esquerda
        }
    }

    printf("\n[NAO ENCONTRADO] O paciente %s nao esta cadastrado.\n", nomeBusca);
}
