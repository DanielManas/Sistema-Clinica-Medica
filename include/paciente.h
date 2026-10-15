
#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct
{
    int id;
    char nome[20];
    char sobrenome[50];
    char cpf[15];
    char telefone[20];
}  paciente;

void cadastrarPaciente(MYSQL *conn);
void listarPacientes(MYSQL *conn);

#endif
