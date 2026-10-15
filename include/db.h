#ifndef DB_H
#define DB_H

#include <mysql/mysql.h>

// Inicia a conexao com o servidor MySQL
MYSQL* conectarBanco();

// Encerra a conexao com o servidor MySQL
void fecharBanco(MYSQL *conn);

#endif