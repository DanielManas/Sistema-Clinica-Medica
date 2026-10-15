#include <stdio.h>
#include <stdlib.h>
#include "../include/db.h"

MYSQL* conectarBanco() 
{
    // Inicia a estrutura interna da biblioteca MySQL
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("\n[ERRO] Falha ao inicializar estrutura do MySQL!\n");
        return NULL;
    }

    // Tenta conectar ao banco
    // Parametros: estrutura, host, usuario, senha, nome do banco, porta, socket, flags
    if (mysql_real_connect(conn, "localhost", "root", "123456", "clinica_medica", 3306, NULL, 0) == NULL) {
        printf("\n[ERRO] Falha na conexao com o banco: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    printf("\n[SUCESSO] Conectado ao banco de dados MySQL!\n");
    return conn;
}

void fecharBanco(MYSQL *conn) {
    if (conn != NULL) {
        mysql_close(conn);
        printf("\n[INFO] Conexao com o banco encerrada.\n");
    }
}
