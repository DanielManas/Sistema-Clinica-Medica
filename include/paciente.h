
#ifndef PACIENTE_H
#define PACIENTE_H
#define MAX_PACIENTES = 100

typedef struct
{
    int id;
    char nome[20];
    char sobrenome[50];
    char cpf[15];
    char telefone[20];
}  paciente;

void cadastrarPaciente(Lista_Pacientes[], int *total);
void listarPacientes(Lista_Pacientes[], int *total);

#endif
