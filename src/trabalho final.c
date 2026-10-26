#include <stdio.h>
#include <mysql/mysql.h> 
#define MAX_REGISTROS 100

////////////////////////////////////////////////////////////////////////////////////////////////////

// ESTRUTURA DADOS DOS PACIENTES 
typedef struct 
{
    int id;
    char nome[100];
    int idade;
    char cpf[15];
    char telefone[20];
} paciente;

// ESTRUTURA DADOS DOS MÉDICOS
typedef struct 
{
    int id;
    char nome[100];
    char crm[20];
    char especialidade[50];
} medico;

// ESTRTURA DADOS CONSULTA
typedef struct 
{
    int id;
    int idPaciente;
    int idMedico;
    char data[11]; // DD/MM/AAAA
    char hora[9];  // HH:MM
} consulta;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// LISTAS DE FUNCOES

int compararTextos(char t1[], char t2[]);
MYSQL* conectarMySQL();
void carregarDadosDoMySQL(MYSQL *conn, paciente p[], int *totP, medico m[], int *totM, consulta c[], int *totC);

// PACIENTES
void cadastrarPaciente(MYSQL *conn, paciente p[], int *tot, int *ordenado);
void alterarPaciente(MYSQL *conn, paciente p[], int tot);
void excluirPaciente(MYSQL *conn, paciente p[], int *tot, int *ordenado);
void listarPacientes(paciente p[], int tot);
void ordenarPacientesPorNome(paciente p[], int tot, int *ordenado); // Bubble Sort
void ordenarPacientesPorIdade(paciente p[], int tot, int *ordenado); // Bubble Sort
void buscarPacienteNomeBinaria(paciente p[], int tot, int ordenado); // Busca Binária

// MEDICOS
void cadastrarMedico(MYSQL *conn, medico m[], int *tot);
void listarMedicos(medico m[], int tot);
void buscarMedicoNomeLinear(medico m[], int tot); // Busca Linear

// CONSULTAS
void agendarConsulta(MYSQL *conn, consulta c[], int *tot);
void cancelarConsulta(MYSQL *conn, consulta c[], int *tot);
void listarConsultasPorPaciente(consulta c[], int tot);
void listarConsultasPorMedico(consulta c[], int tot);

/////////////////////////////////////////////////////////////////////////////////////////////////////////


 //MAIN

int main() 
{
    MYSQL *conn = conectarMySQL();
    if (conn == NULL) 
    {
        printf("[ERRO CRITICO] Nao foi possivel conectar ao MySQL. Encerrando...\n");
        return 1;
    }

    // CRIAR AS LISTAS DE PACIENTES, MEDICOS E CONSULTAS
    paciente listaP[MAX_REGISTROS]; 
    medico listaM[MAX_REGISTROS];   
    consulta listaC[MAX_REGISTROS]; 

    // CONTADORES ZERADOS
    int totP = 0;
    int ordP = 0;
    int totM = 0;
    int totC = 0;

    // CARREGA OS DADOS DO BANCO MYSQL NAS LISTAS
    carregarDadosDoMySQL(conn, listaP, &totP, listaM, &totM, listaC, &totC);

    int op = -1;
    
    do {
        printf("          SISTEMA DE CLINICA MEDICA            \n");
        printf("\n");
        printf("Selecione uma opção\n");
        printf("\n");
        printf(" 1 - Cadastrar Paciente\n");
        printf(" 2 - Alterar Paciente\n");
        printf(" 3 - Excluir Paciente\n");
        printf(" 4 - Listar Pacientes\n");
        printf(" 5 - Ordenar Pacientes/Nome (Bubble Sort)\n");
        printf(" 6 - Ordenar Pacientes/Idade (Bubble Sort)\n");
        printf(" 7 - Buscar Paciente (Busca Binaria)\n");
        printf(" 8 - Cadastrar Medico\n");
        printf(" 9 - Listar Medicos\n");
        printf(" 10 - Buscar Medico (Busca Linear)\n");
        printf(" 11 - Agendar Consulta\n");
        printf(" 12 - Cancelar Consulta\n");
        printf(" 13 - Consultas por Paciente\n");
        printf(" 14 - Consultas por Medico\n");
        printf(" 0 - SAIR\n");
        printf("\n");
        printf("Opcao: "); 
        scanf("%d", &op);

        switch (op) {
            case 1: cadastrarPaciente(conn, listaP, &totP, &ordP); break;
            case 2: alterarPaciente(conn, listaP, totP); break;
            case 3: excluirPaciente(conn, listaP, &totP, &ordP); break;
            case 4: listarPacientes(listaP, totP); break;
            case 5: ordenarPacientesPorNome(listaP, totP, &ordP); break;
            case 6: ordenarPacientesPorIdade(listaP, totP, &ordP); break;
            case 7: buscarPacienteNomeBinaria(listaP, totP, ordP); break;
            case 8: cadastrarMedico(conn, listaM, &totM); break;
            case 9: listarMedicos(listaM, totM); break;
            case 10: buscarMedicoNomeLinear(listaM, totM); break;
            case 11: agendarConsulta(conn, listaC, &totC); break;
            case 12: cancelarConsulta(conn, listaC, &totC); break;
            case 13: listarConsultasPorPaciente(listaC, totC); break;
            case 14: listarConsultasPorMedico(listaC, totC); break;
            case 0:
                mysql_close(conn);
                printf("\nConexao MySQL encerrada. Programa finalizado!\n");
                break;
            
            default: 
                printf("Opcao invalida.\n");
        }
    } while (op != 0);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

// 2. FUNÇÃO PRÓPRIA DE COMPARAÇÃO DE TEXTO (Sem <string.h>)
int compararTextos(char t1[], char t2[]) {
    int i = 0;
    while (t1[i] != '\0' && t2[i] != '\0') {
        if (t1[i] != t2[i]) {
            return t1[i] - t2[i];
        }
        i++;
    }
    return t1[i] - t2[i];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

// CONEXÇÃO AO BANCO DE DADOS + CARREGAR OS DADOS JA EXISTENTES NO BANCO

// CONECTAR BANCO MYSQL
MYSQL* conectarMySQL() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("[ERRO MYSQL] Falha ao inicializar o driver.\n");
        return NULL;
    }

    // Ajuste "localhost", "root" e "senha" para as credenciais do seu servidor MySQL
    if (mysql_real_connect(conn, "localhost", "root", "senha", "clinica_medica", 3306, NULL, 0) == NULL) {
        printf("[ERRO MYSQL] Conexao falhou: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }
    return conn;
}



// CARREGAR OS DADOS DO BANCO DE DADOS
void carregarDadosDoMySQL(MYSQL *conn, paciente p[], int *totP, medico m[], int *totM, consulta c[], int *totC) {
    MYSQL_RES *res;
    MYSQL_ROW linha;

    // CARREGAR OS PACIENTES E GUARDA EM (p)  --  (TIVE Q PESQUISAR POR IA COMO FAZER)
    *totP = 0;
    if (mysql_query(conn, "SELECT id, nome, idade, cpf, telefone FROM paciente") == 0) {
        res = mysql_store_result(conn);
        while ((linha = mysql_fetch_row(res)) && *totP < MAX_REGISTROS) {
            sscanf(linha[0], "%d", &p[*totP].id);
            sprintf(p[*totP].nome, "%s", linha[1]);
            sscanf(linha[2], "%d", &p[*totP].idade);
            sprintf(p[*totP].cpf, "%s", linha[3]);
            sprintf(p[*totP].telefone, "%s", linha[4]);
            (*totP)++;
        }
        mysql_free_result(res);
    }

    // CARREGAR OS MEDICOS  E GUARDA EM (m)
    *totM = 0;
    if (mysql_query(conn, "SELECT id, nome, crm, especialidade FROM medico") == 0) {
        res = mysql_store_result(conn);
        while ((linha = mysql_fetch_row(res)) && *totM < MAX_REGISTROS) {
            sscanf(linha[0], "%d", &m[*totM].id);
            sprintf(m[*totM].nome, "%s", linha[1]);
            sprintf(m[*totM].crm, "%s", linha[2]);
            sprintf(m[*totM].especialidade, "%s", linha[3]);
            (*totM)++;
        }
        mysql_free_result(res);
    }

    // CARREGAR AS CONSULTAS E GUARDA EM (c)
    *totC = 0;
    if (mysql_query(conn, "SELECT id, id_paciente, id_medico, data, hora FROM consulta") == 0) {
        res = mysql_store_result(conn);
        while ((linha = mysql_fetch_row(res)) && *totC < MAX_REGISTROS) {
            sscanf(linha[0], "%d", &c[*totC].id);
            sscanf(linha[1], "%d", &c[*totC].idPaciente);
            sscanf(linha[2], "%d", &c[*totC].idMedico);
            sprintf(c[*totC].data, "%s", linha[3]);
            sprintf(c[*totC].hora, "%s", linha[4]);
            (*totC)++;
        }
        mysql_free_result(res);
    }
}


//////////////////////////////////////////////////////////////////////////////////////

// FUNCOES DO MENU

// 1 - CADASTRAR PACIENTES

void cadastrarPaciente(MYSQL *conn, paciente p[], int *tot, int *ordenado)
{
    if (*tot >= MAX_REGISTROS) 
    {
        printf("\nO BANCO DE DADOS ATINGIU A QUANTIDADE MÁXIMA DE REGISTROS\n");
        return;
    }
    paciente novo;
    printf("\nCADASTRAR UM NOVO PACIENTE \n");
    
    printf("INFORME O ID: "); 
    scanf("%d", &novo.id);
    
    printf("Nome Completo: "); 
    scanf(" %[^\n]", novo.nome);
    
    printf("Idade: "); 
    scanf("%d", &novo.idade);
    
    printf("CPF: "); 
    scanf("%s", novo.cpf);
    
    printf("Telefone: "); 
    scanf("%s", novo.telefone);

    
    //MONTA O COMANDO EM SQL PARA SER ENVIADO AO MYSQL
    char query[300];
    sprintf(query, "INSERT INTO paciente VALUES (%d, '%s', %d, '%s', '%s');", novo.id, novo.nome, novo.idade, novo.cpf, novo.telefone); 
    
    // ENVIA O COMANDO EM SQL PARA O MYSQL, O MYSQL RETORN COM VALOR 0 SE DER CERTO
    if (mysql_query(conn, query) == 0) 
    {
        p[*tot] = novo;
        (*tot)++;
        *ordenado = 0; // Novo item desordena a lista por nome
        printf("[SUCESSO] Paciente cadastrado no banco e na RAM!\n");
    } 
    else 
    {
        printf("[ERRO MYSQL] %s\n", mysql_error(conn));
    }
}


// FUNÇÃO 2 - ALTERAR DADOS DO PACIENTE
void alterarPaciente(MYSQL *conn, paciente p[], int tot)
{
    if (*tot == 0)
    {
        printf("Não tem nenhum paciente no banco de dados\n");
    }

    int idalterarpaciente;

    printf("Informe qual é o ID do paciente que deseja alterar: ")
    scanf("%d", &idalterarpaciente);

    for (int i = 0; i < *tot; i++) 
    {
        if (p[i].id == idalterarpaciente) 
        {
            int op;
            printf("Esta prestes a alterar dados do paciente %s. Deseja continuar?\n 1 - Sim 2 - Não", p[i].nome);
            scanf("%d", &op);
            if (op != 1 || op != 2)
            {
                break;
            }
            if (op == 2)
            {
                break;
            }

            paciente temp;
            temp.id = idalterarpaciente;
            printf("Novo Nome Completo: ");
            scanf(" %[^\n]", temp.nome);

            printf("Nova Idade: ");
            scanf("%d", &temp.idade);

            printf("Novo CPF: ");
            scanf("%s", temp.cpf);

            printf("Novo Telefone: ");
            scanf("%s", temp.telefone);

            //MONTAR O COMANDO PARA ALTERAR EM SQL
            char query[300];
            sprintf(query, "UPDATE paciente SET nome='%s', idade=%d, cpf='%s', telefone='%s' WHERE id=%d;",
                    temp.nome, temp.idade, temp.cpf, temp.telefone, idalterarpaciente);

            // ENVIA O COMANDO PARA MYSQL
            if (mysql_query(conn, query) == 0) 
            {
                p[i] = temp;
                printf("Dados Atualizados!\n");
            } 
            else 
            {
                printf("[ERRO MYSQL] %s\n", mysql_error(conn));
            }
            return; 
        }  
}

// FUNÇÃO 3 - EXCLUIR PACIENTE
void excluirPaciente(MYSQL *conn, paciente p[], int *tot, int *ordenado)
{
    if(*tot == 0)
    {
        printf("Não tem nenhum paiente no banco de dados! Não tem quem ser excluido");
        return;
    }

    int idapagarpaciente;
    printf("Digite o ID do paciente a excluir: ");
    scanf("%d", &idapagarpaciente);
    

    for(int i = 0; i < *tot -1; i++)
    {
        if (p[i].id == idapagarpaciente) 
        {
            int op;
            printf("Esta prestes a apagar os dados do paciente %s. Deseja continuar?\n 1 - Sim 2 - Não", p[i].nome);
            scanf("%d", &op);
            if (op != 1)
            {
                printf("OPERAÇÃO CANCELADA!\N")
                return;
            }
        

            char query[300];
            sprintf(query, "DELETE FROM paciente WHERE id=%d;", idapagarpaciente);
        
            if (mysql_query(conn, query) == 0) 
            {
                // Remove o item da RAM reordenando o vetor para nao deixar espacos vagos
                for (int j = i; j < *tot - 1; j++)
                {
                    p[j] = p[j + 1];
                }
        
                (*tot)--;      // Diminui o total de pacientes na RAM
                *ordenado = 0; // Desmarca a flag de ordenacao
            }
            else
            {
                printf("[ERRO MYSQL] %s\n", mysql_error(conn));
            }
        }  

        else
        {
            printf("Paciente não encontrado!\n");
        }

        return;
}


// FUNÇÃO 4 - LISTAR PACIENTES
void listarPacientes(paciente p[], int tot)
{
    if (tot == 0) 
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    
    printf("  ID    |   NOME    |    IDADE    |    CPF    |    TELEFONE\n\n ");
    for(int i = 0; i<tot; i++)
        {
            printf("  %d         %s         %d         %s         %s\n", p[i].id, p[i].nome, p[i].idade, p[i].cpf, p[i].telefone);
            
        }
        return;
}











