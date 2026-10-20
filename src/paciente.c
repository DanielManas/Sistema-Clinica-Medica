#include <stdio.h>
#include <string.h>
#include "../include/paciente.h"

void cadastrarPaciente(Paciente lista[], int *total) 
{
    // 1. Verifica se o vetor de pacientes ja esta cheio
    if (*total >= MAX_PACIENTES) 
    {
        printf("\n[ERRO] Memoria cheia! Nao e possivel cadastrar mais pacientes.\n");
        return;
    }

    printf("\n--- CADASTRO DE PACIENTE ---\n");

    // 2. Le os dados salvando diretamente na posicao livre do vetor (lista[*total])
    printf("Digite o ID: ");
    scanf("%d", &lista[*total].id);
    getchar();

    printf("Digite o nome do paciente: ");
    scanf("%s", lista[*total].nome);

    printf("Digite o sobrenome do paciente: ");
    scanf("%s", lista[*total].sobrenome);

    printf("Informe o CPF do paciente: ");
    scanf("%s", lista[*total].cpf);

    printf("Informe o telefone do paciente: ");
    scanf("%s", lista[*total].telefone);

    printf("\n[SUCESSO] Paciente %s %s cadastrado na memoria RAM!\n", 
           lista[*total].nome, lista[*total].sobrenome);

    // 3. Soma +1 no contador total para o proximo cadastro ir para a posicao seguinte
    (*total)++;
}

void listarPacientes(Paciente lista[], int total) 
{
    printf("\n--- LISTA DE PACIENTES (%d cadastrados) ---\n", total);

    if (total == 0) 
    {
        printf("[Nenhum paciente cadastrado na memoria no momento]\n");
        return;
    }

    printf("ID | NOME COMPLETO | CPF | TELEFONE\n");
    printf("-----------------------------------\n");

    // Imprime cada paciente guardado no vetor
    for (int i = 0; i < total; i++) 
    {
        printf("%d | %s %s | %s | %s\n", 
               lista[i].id, 
               lista[i].nome, 
               lista[i].sobrenome, 
               lista[i].cpf, 
               lista[i].telefone);
    }
}
