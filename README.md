# Sistema Clinica Médica
Simulador Banco de Dados de Clinica Medica para o projeto final do curso de Programação 2

Projeto Integrador desenvolvido para a disciplina de Algoritmos e Programação II do curso de Engenharia da Computação.


## Integrantes

Daniel Manasterski - 10426829

Pedro Bender da Silva Prado - 10743385

Jhonny Kuanyu Wang - 10438969

Lais De Paula Carneiro - 10418061

André Ramos Cancelo - 10772065


## Descrição do Projeto

O projeto consiste no desenvolvimento de um Sistema de Clínica Médica em linguagem C, com interface de console, integrado a um banco de dados MySQL

O objetivo do sistema é auxiliar no gerenciamento de informações de uma clínica médica, permitindo armazenar e consultar dados de pacientes, médicos e consultas.

Os dados serão manipulados pelo programa em C e armazenados no banco de dados, permitindo que permaneçam disponíveis mesmo após o encerramento do programa.


## Principais Funcionalidades

### Pacientes

* Cadastrar pacientes;

* Alterar dados de pacientes;

* Excluir pacientes;

* Listar pacientes cadastrados;

* Pesquisar pacientes por nome (busca binária);

* Ordenar pacientes por nome;

* Ordenar pacientes por idade.

### Médicos

* Cadastrar médicos e suas especialidades;

* Listar médicos cadastrados;

* Pesquisar médicos por nome (busca linear).

### Consultas

* Agendar consultas (impedindo dois agendamentos do mesmo médico no mesmo dia e horário);

* Cancelar consultas;

* Listar consultas de determinado paciente;

* Listar consultas de determinado médico.


## Algoritmos Implementados
 
### Busca Linear
 
Usada na pesquisa de médico por nome (opção 10). Percorre sequencialmente o array de structs até encontrar o registro desejado.
 
### Busca Binária
 
Usada na pesquisa de paciente por nome (opção 7). Como a busca binária exige dados ordenados, o sistema só permite a busca depois que a lista de pacientes foi ordenada por nome (opção 5).
 
### Bubble Sort
 
Implementado para ordenar pacientes por nome (opção 5) e por idade (opção 6). A comparação de nomes é feita pela função própria `compararTextos`.
 
### Ponteiros e passagem por referência
 
- `MYSQL *conn` é passado às funções que acessam o banco;
- contadores como `int *tot` e a flag `int *ordenado` são alterados dentro das funções;
- os arrays de structs (`paciente p[]`, `medico m[]`, `consulta c[]`) são passados por referência.
## Banco de Dados e Biblioteca
 
- **Banco de dados:** MySQL
- **Biblioteca/driver:** MySQL C API (`libmysqlclient`, cabeçalho `mysql.h`)
