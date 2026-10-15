#include <stdio.h>
#include "../include/paciente.h"

void cadastrarPaciente() 
{
    paciente p;

    printf("\n--- CADASTRO DE PACIENTE ---\n");

    printf("Digite o ID: ");
    scanf("%d", &p.id);
    getchar();

    printf("Digite o nome do paciente: ");
    scanf("%s", &p.nome);

    printf("Digite o sobrenome do paciente: ");
    scanf("%s", &p.sobrenome);

    printf("Informe o CPF do paciente: ");
    scanf("%s", &p.cpf);

    printf("Informe o telefone do paciente: ");
    scanf("%s", &p.telefone);

    printf("\nPaciente %s %s foi cadastrado com sucesso!\n", p.nome, p.sobrenome);
}

void listarPacientes() 
{
    printf("\n--- LISTA DE PACIENTES ---\n");
    //printf("[Funcionalidade em desenvolvimento...]\n");
}