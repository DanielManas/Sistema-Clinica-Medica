
#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct
{
    char nome[50];
    char sobrenome[50];
    char cpf[15];
    char telefone[20];
}  paciente;

void cadastrarPaciente();
void listarPacientes();

#endif