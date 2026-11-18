
CREATE DATABASE clinica_medica;
USE clinica_medica;

CREATE TABLE paciente (
    id INT PRIMARY KEY NOT NULL,
    nome VARCHAR(100) NOT NULL,
    idade INT NOT NULL,
    cpf VARCHAR(15) NOT NULL,
    telefone VARCHAR(20)
);

CREATE TABLE medico (
    id INT PRIMARY KEY NOT NULL,
    nome VARCHAR(100) NOT NULL,
    crm VARCHAR(20) NOT NULL,
    especialidade VARCHAR(50) NOT NULL
);

CREATE TABLE consulta (
    id INT PRIMARY KEY NOT NULL,
    id_paciente INT NOT NULL,
    id_medico INT NOT NULL,
    data VARCHAR(10) NOT NULL,
    hora VARCHAR(8) NOT NULL,
    FOREIGN KEY (id_paciente) REFERENCES paciente(id),
    FOREIGN KEY (id_medico) REFERENCES medico(id)
);
