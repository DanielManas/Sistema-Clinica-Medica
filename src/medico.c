#include <stdio.h>
#include "../include/medico.h"


void cadastrarMedico() 
{
    medico m;

    printf("\n--- CADASTRO DE MEDICO ---\n");

    printf("Digite o ID: ");
    scanf("%d", &m.id);
    getchar();

    printf("Digite o nome do medico: ");
    scanf("%s", m.nome);

    printf("Digite o sobrenome do medico: ");
    scanf("%s", m.sobrenome);

    printf("Informe o CRM do medico: ");
    scanf("%s", m.crm);

    printf("Informe a especialidade: ");
    scanf("%s", m.especialidade);

    printf("\nMedico Dr(a). %s %s cadastrado com sucesso!\n", m.nome, m.sobrenome);
}

void listarMedicos() 
{
    printf("\n--- LISTA DE MEDICOS ---\n");
    //printf("[Funcionalidade em desenvolvimento...]\n");
}