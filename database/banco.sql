
CREATE DATABASE clinica_medica;
USE clinica_medica;

CREATE TABLE Pacientes
(
    id INT PRIMARY KEY NOT NULL,
    nome VARCHAR(20) NOT NULL,
    sobrenome VARCHAR (50) NOT NULL,
    cpf VARCHAR(15) NOT NULL, 
    telefone VARCHAR(20)
);

CREATE TABLE Medicos
(
    id INT PRIMARY KEY NOT NULL,
    nome VARCHAR(20) NOT NULL,
    sobrenome VARCHAR(50) NOT NULL,
    crm VARCHAR(20) NOT NULL,
    especialidade VARCHAR(50) NOT NULL
);

CREATE TABLE Consultas
(
    id INT PRIMARY KEY NOT NULL,
    id_paciente INT NOT NULL, 
    id_medico INT NOT NULL,
    data_consulta DATE NOT NULL,
    horario_consulta TIME NOT NULL,

    FOREIGN KEY (id_paciente) REFERENCES Pacientes(id),
    FOREIGN KEY  (id_medico) REFERENCES Medicos(id)
);