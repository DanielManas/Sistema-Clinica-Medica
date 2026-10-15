#include <stdio.h>
#include <string.h>
#include "../include/paciente.h"

void cadastrarPaciente(MYSQL *conn) 
{
    paciente p;
    char query[500]; // Array de texto para guardar o comando SQL

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

    // Monta o comando SQL INSERT com os dados preenchidos
    sprintf(query, "INSERT INTO Pacientes (id, nome, sobrenome, cpf, telefone) VALUES (%d, '%s', '%s', '%s', '%s');", p.id, p.nome, p.sobrenome, p.cpf, p.telefone);

    // Executa o comando no MySQL
    if (mysql_query(conn, query) == 0) 
    {
        printf("\n[SUCESSO] Paciente %s %s salvo no Banco de Dados!\n", p.nome, p.sobrenome);
    } 
    else 
    {
        printf("\n[ERRO] Falha ao salvar no banco: %s\n", mysql_error(conn));
    }
}

void listarPacientes(MYSQL *conn) 
{
    printf("\n--- LISTA DE PACIENTES ---\n");
    //printf("[Funcionalidade em desenvolvimento...]\n");
}
