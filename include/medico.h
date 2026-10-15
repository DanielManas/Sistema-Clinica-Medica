#ifndef MEDICO_H
#define MEDICO_H

typedef struct
{
    int id;
    char nome[20];
    char sobrenome[50];
    char crm[20];
    char especialidade[50];
}  medico;

void cadastrarMedico();
void listarMedicos();

#endif