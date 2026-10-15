#include <stdio.h>
#include "../include/paciente.h"
#include "../include/medico.h"
#include "../include/consulta.h"

int main() 
{
    int opcao;
   
    do
    {
        printf("Sistema de Clinica Medica - Projeto Integrador\n");
        printf("=== SISTEMA DE CLÍNICA MÉDICA ===\n\n");
        printf("1 - Pacientes\n");
        printf("2 - Médicos\n");
        printf("3 - Consultas\n");
        printf("4 - Buscar\n");
        printf("5 - Relatórios\n");
        printf("0 - Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) 
        {
            case(1):
                printf("Opção 1 selecionada: Pacientes\n");
                cadastrarPaciente(conn);
                listarPacientes(conn);
                break;
            case(2):
                printf("Opção 2 selecionada: Médicos\n");
                printf("cadastrarMedico()");
                break;
            case(3):
                printf("Opção 3 selecionada: Consultas\n");
                printf("agendarConsulta()");
                break;
            case(4):
                printf("Opção 4 selecionada: Buscar\n");
                break;
            case(5):
                printf("Opção 5 selecionada: Relatórios\n");
                break;
            case(0):
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;    
        }
    
    } while (opcao != 0);
    
    return 0;
}
