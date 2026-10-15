#ifndef CONSULTA_H
#define CONSULTA_H


typedef struct 
{
    int id;
    int id_paciente;       
    int id_medico;         
    char data[11];         
    char horario[6];       
} consulta;


void agendarConsulta();
void listarConsultas();

#endif