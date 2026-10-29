#include <stdio.h>
#include <mysql/mysql.h> 
#define MAX_REGISTROS 100
#define MAX_CONSULTAS 5000

////////////////////////////////////////////////////////////////////////////////////////////////////



//      TEM ALGUNS DADOS QUE TALVEZ VALE A PENA ALTERAR, TIPO O TELEFONE É UM INT, assim como o CRM




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
void agendarConsulta(MYSQL *conn, paciente p[], int totP, medico m[], int totM, consulta c[], int *totC);
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
    consulta listaC[MAX_CONSULTAS]; 

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
            case 11: agendarConsulta(conn, listaP, totP, listaM, totM, listaC, &totC); break;
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
// ESSA FUNÇÃO VAI SER USADA EM FUNÇÕES DE ORDENAÇÃO DE NOME COMO NA FUNÇÃO 5 E 6


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
        while ((linha = mysql_fetch_row(res)) && *totC < MAX_CONSULTAS) {
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


// FUNÇÃO 1 - CADASTRAR PACIENTES
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
    if (tot == 0)
    {
        printf("Não tem nenhum paciente no banco de dados\n");
    }

    int idalterarpaciente;

    printf("Informe qual é o ID do paciente que deseja alterar: ");
    scanf("%d", &idalterarpaciente);

    for (int i = 0; i < tot; i++) 
    {
        if (p[i].id == idalterarpaciente) 
        {
            int op;
            printf("Esta prestes a alterar dados do paciente %s. Deseja continuar?\n 1 - Sim 2 - Não", p[i].nome);
            scanf("%d", &op);
            if (op != 1 && op != 2)
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
    

    for(int i = 0; i < *tot; i++)
    {
        if (p[i].id == idapagarpaciente) 
        {
            int op;
            printf("Esta prestes a apagar os dados do paciente %s. Deseja continuar?\n 1 - Sim 2 - Não", p[i].nome);
            scanf("%d", &op);
            if (op != 1)
            {
                printf("OPERAÇÃO CANCELADA!\n");
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

            return;
        }  

    }
    
 printf("Paciente não encontrado!\n");
    
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


// FUNÇÃO 5 - ORDENAR PACIENTES POR NOME (BOBBLE SORT)
void ordenarPacientesPorNome(paciente p[], int tot, int *ordenado)
{
    if (tot < 2) 
    {
        if (tot == 0) 
            printf("Nenhum paciente cadastrado.\n");
        else 
            printf("Apenas um paciente cadastrado. Lista ja ordenada.\n");
            
        *ordenado = 1;
        return;
    }

    // Algoritmo Bubble Sort
    for (int i = 0; i < tot - 1; i++) 
    {
        for (int j = 0; j < tot - 1 - i; j++) 
        {
            // Usa a sua função compararTextos na LINHA 152
            if (compararTextos(p[j].nome, p[j + 1].nome) > 0) 
            {
                // Troca as structs inteiras
                paciente temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    
    *ordenado = 1; //MOSTRA QUE A LISTA ESTA ORDENADA
    printf("A lista agora esta ordenada por Nome!");
}


// FUNÇÃO 6 - ORDENAR OS PACIENTES POR IDADE (BOBBLE SORT)
void ordenarPacientesPorIdade(paciente p[], int tot, int *ordenado)
{
    

    if (tot < 2) 
    {
        if (tot == 0) 
            printf("Nenhum paciente cadastrado.\n");
        else 
            printf("Apenas um paciente cadastrado. Lista ja ordenada.\n");
            
        *ordenado = 1;
        return;
    }

    for (int i = 0; i < tot - 1; i++) 
    {
        for (int j = 0; j < tot - 1 - i; j++) 
        { 
            if (p[j].idade > p[j + 1].idade) 
            {   
                paciente temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    *ordenado = 0; //SEI QUE É CONTRADITORIO, MAS O ORDENADO SERVE PARA APENAS OS NOMES, SE NÃO A FUNÇÃO 7 NÃO RODA
    printf("A lista agora esta ordenada por idade!");
}



// FUNÇÃO 7 - BUSCAR PACIENTE POR NOME (BUSCA BINARIA)
void buscarPacienteNomeBinaria(paciente p[], int tot, int ordenado)
{
    if (tot == 0) 
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    if (ordenado != 1)
    {
        printf("A lista não esta ordenada por Nome. Para executar esta função, execute a função 5 primeiro!");
        return;
    }

    char nomeBusca[100];
    printf("\nInforme o nome exato do paciente que esta buscando: ");
    scanf(" %[^\n]", nomeBusca);

    
    int inicio = 0;
    int fim = tot - 1;
    int encontrado = 0;

    while(inicio <= fim)
    {
        
        int meio = (inicio + fim) / 2;
        int res = compararTextos(p[meio].nome, nomeBusca);

        if (res == 0) // PESSOA ENCONTRADA
        {
            printf("  ID    |   NOME    |    IDADE    |    CPF    |    TELEFONE\n\n ");
            printf("  %d         %s         %d         %s         %s\n", p[meio].id, p[meio].nome, p[meio].idade, p[meio].cpf, p[meio].telefone);
            encontrado = 1;
            return;
        }

        else if (res < 0) // ACIMA DO MEIO
        {
            inicio = meio + 1;
        }

        else     // ABAIXO DO MEIO
        {
            fim = meio - 1;
        }
        
    }

    if (encontrado != 1)
    {
        printf("Não foi possivel encontrar o paciente, verifique se digitou corretamente!");
    }
    
    return;
}


// FUNÇÃO 8 - CADASTRAR MEDICOS
void cadastrarMedico(MYSQL *conn, medico m[], int *tot)
{
    if (*tot >= MAX_REGISTROS) 
        {
            printf("\nO BANCO DE DADOS ATINGIU A QUANTIDADE MÁXIMA DE REGISTROS\n");
            return;
        }
    
        medico novo;
        printf("\nCADASTRAR UM NOVO MEDICO \n");
        
        printf("INFORME O ID: "); 
        scanf("%d", &novo.id);
        
        printf("Nome Completo: "); 
        scanf(" %[^\n]", novo.nome);
        
        printf("CRM: "); 
        scanf("%s", &novo.crm);
        
        printf("Especialidade: "); 
        scanf("%s", novo.especialidade);
    
        
        //MONTA O COMANDO EM SQL PARA SER ENVIADO AO MYSQL
        char query[300];
        sprintf(query, "INSERT INTO medico VALUES (%d, '%s', '%s', '%s');", novo.id, novo.nome, novo.crm, novo.especialidade); 
        
        // ENVIA O COMANDO EM SQL PARA O MYSQL, O MYSQL RETORN COM VALOR 0 SE DER CERTO
        if (mysql_query(conn, query) == 0) 
        {
            m[*tot] = novo;
            (*tot)++;
            *ordenado = 0; // Novo item desordena a lista por nome
            printf("[SUCESSO] Medico cadastrado no banco e na RAM!\n");
        } 
        else 
        {
            printf("[ERRO MYSQL] %s\n", mysql_error(conn));
        }
}


// FUNÇÃO 9 - LISTAR MEDICOS
void listarMedicos(medico m[], int tot)
{
    if (tot == 0) 
        {
            printf("Nenhum medico cadastrado.\n");
            return;
        }
        
        printf("  ID    |   NOME    |    CMR    |    ESPECIALIDADE\n\n ");
        for(int i = 0; i<tot; i++)
            {
                printf("  %d         %s         %s         %s         \n", m[i].id, m[i].nome, m[i].crm, m[i].especialidade);
                
            }
    return;    
}


// FUNÇÃO 10 - BUSCAR MEDICO (BUSCA LINEAR)
void buscarMedicoNomeLinear(medico m[], int tot)
{
    if(tot == 0)
    {
        printf("Nenhum medico cadastrado\n");
        return;
    }
    
    char nomeBusca[100];
    printf("\nInforme o nome exato do medico que esta buscando: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;
    for(int i = 0; i < tot; i++)
    {
        int res = compararTextos(p[i].nome, nomeBusca);

        if (res == 0) // PESSOA ENCONTRADA
        {
            printf("  ID    |   NOME    |    CRM    |    ESPECIALIDADE\n\n ");
            printf("  %d         %s         %S         %s         \n", m[i].id, m[i].nome, m[i].crm, m[i].especialidade);
            encontrado = 1;
            return;
        }
    }
    
    if (encontrado == 0)
    {
        printf("Não foi possível encontrar o médico, verifique se digitou corretamente!");
    }
    return;
}


// FUNÇÃO 11 - AGENDAR CONSULTA
void agendarConsulta(MYSQL *conn, paciente p[], int totP, medico m[], int totM, consulta c[], int *totC)
{
    if (*totC >= MAX_CONSULTAS)
    {
        printf("\nLimite de consultas atingida pelo banco de dados (%d consultas). Exclua ou arquive registros antigos.\n", MAX_CONSULTAS);
        return;
    }

    consulta nova;
    printf("\n--- AGENDAR CONSULTA ---\n");

    printf("Informe o ID da Consulta: ");
    scanf("%d", &nova.id);

    printf("Informe o ID do Paciente: ");
    scanf("%d", &nova.idPaciente);

    // VERIFICAR SE O ID PACIENTE EXISTE
    int pacienteExiste = 0;
    for (int i = 0; i < totP; i++)
    {
        if (p[i].id == nova.idPaciente)
        {
            pacienteExiste = 1;
            break;
        }
    }
    
    if (pacienteExiste = 0)
    {
        printf("ID do paciente não encontrado! Saindo da Função");
        return;
    }

    printf("Informe o ID do Medico: ");
    scanf("%d", &nova.idMedico);

    // VERIFICAR SE O ID MEDICO EXISTE
    int medicoExiste = 0;
    for (int i = 0; i < totM; i++)
    {
        if (m[i].id == nova.idMedico)
        {
            medicoExiste = 1;
            break;
        }
    }

    if (medicoExiste == 0)
    {
        printf("ID do medico não encontrado! Saindo da Função");
        return;
    }

    // LEITURA DE DATA E HORA
    printf("Informe a Data (DD/MM/AAAA): ");
    scanf("%s", nova.data);

    printf("Informe a Hora (HH:MM): ");
    scanf("%s", nova.hora);

    // VERIFICAR SE O MÉDICO TEM CONSULTA NESSA DATA E NESSE HORARIO
    for (int i = 0; i < *totC; i++)
    {
        if (c[i].idMedico == nova.idMedico && 
            compararTextos(c[i].data, nova.data) == 0 && 
            compararTextos(c[i].hora, nova.hora) == 0)
        {
            printf("\n ATENÇÃO! O medico ja possui uma consulta agendada no dia %s as %s!\n", 
                   nova.data, nova.hora);
            return;
        }
    }

    // COLOCAR A NOVA CONSULTA NO BANCO DE DADOS
    char query[300];
    sprintf(query, "INSERT INTO consulta (id, id_paciente, id_medico, data, hora) VALUES (%d, %d, %d, '%s', '%s');",
            nova.id, nova.idPaciente, nova.idMedico, nova.data, nova.hora);

    if (mysql_query(conn, query) == 0)
    {
        c[*totC] = nova;
        (*totC)++;
        printf("Consulta agendada com sucesso!\n");
    }
    else
    {
        printf("[ERRO MYSQL] %s\n", mysql_error(conn));
    }
}


// FUNÇÃO 12 - CANCELAR CONSULTA
void cancelarConsulta(MYSQL *conn, consulta c[], int *tot)
{
    if (*tot == 0)
        {
            printf("\nNenhuma consulta agendada no sistema.\n");
            return;
        }

    int idCancelar;
    printf("\n--- CANCELAR CONSULTA ---\n");
    printf("Informe o ID da consulta que deseja cancelar: ");
    scanf("%d", &idCancelar);

    for (int i = 0; i < *tot; i++)
    {
        if (c[i].id == idCancelar)
        {
            int op;
            printf("Prestes a cancelar a Consulta ID %d (Data: %s as %s). Confirma?\n1 - Sim | 2 - Nao: ", 
                   c[i].id, c[i].data, c[i].hora);
            scanf("%d", &op);

            if (op != 1)
            {
                printf("Operacao cancelada.\n");
                return;
            }

            // DELETAR DO BANCO DE DADOS
            char query[300];
            sprintf(query, "DELETE FROM consulta WHERE id=%d;", idCancelar);

            if (mysql_query(conn, query) == 0)
            {
                // ORGANIZA O VETOR PARA N DEIXAR ESPACOS VAZIOS
                for (int j = i; j < *tot - 1; j++)
                {
                    c[j] = c[j + 1];
                }

                (*tot)--;
                printf("Consulta ID %d cancelada e removida do sistema!\n", idCancelar);
            }
            else
            {
                printf("[ERRO MYSQL] %s\n", mysql_error(conn));
            }
            return; 
        }
    }

    printf("Consulta com ID %d nao foi encontrada!\n", idCancelar);
}


// FUNÇÃO 13 - LISTAR AS CONSULTAS POR PACIENTE
void listarConsultasPorPaciente(consulta c[], int tot)
{
    if (tot == 0)
    {
        printf("\nNenhuma consulta agendada no sistema.");
        return;
    }

    int idpaciente;
    printf("Informe o ID do paciente que deseja consultar: ");
    scanf("%d", &idpaciente);

    printf("  ID CONSULTA    |   ID PACIENTE    |    ID MEDICO    |    DIA    |    HORA\n\n ");
    for (int i = 0; i<tot; i++)
    {
        if(c[i].idPaciente == idpaciente)
        {
            printf("  %d         %d         %d         %s         %s\n", c[i].id, c[i].idPaciente, c[i].idMedico, c[i].data, c[i].hora);
        }
    }

    printf("Finalizado");
    return;
}


// FUNÇÃO 14 - LISTAR AS CONSULTAS POR MÉDICO
void listarConsultasPorMedico(consulta c[], int tot)
{

}


