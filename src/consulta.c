#include <stdio.h>
#include "../include/consulta.h"

void agendarConsulta() 
{
    consulta c;

    printf("\n--- AGENDAMENTO DE CONSULTA ---\n");

    printf("Digite o ID da Consulta: ");
    scanf("%d", &c.id);

    printf("Digite o ID do Paciente: ");
    scanf("%d", &c.id_paciente);

    printf("Digite o ID do Medico: ");
    scanf("%d", &c.id_medico);

    printf("Informe a Data (DD/MM/AAAA): ");
    scanf("%s", c.data);

    printf("Informe o Horario (HH:MM): ");
    scanf("%s", c.horario);

    printf("\nConsulta agendada com sucesso para o dia %s no horario %s!\n", c.data, c.horario);
}

void listarConsultas() 
{
    printf("\n--- LISTA DE CONSULTAS ---\n");
    //printf("[Funcionalidade em desenvolvimento...]\n");
}