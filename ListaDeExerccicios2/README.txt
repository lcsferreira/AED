--------------------------------DADOS PESSOAIS--------------------------------

Nome: Lucas Simões Ferreira
Matrícula: 20102119
Email: lucas.simoes.ferreira@gmail.com (pessoal)
	lsferreira@inf.ufpel.edu.br(ufpel)
Repositório da Lista de exercícios 1: 
	https://github.com/lcsferreira/AED/tree/main/ListaDeExercicios2

--------------------------------ENUNCIADOS DAS QUESTÕES--------------------------------

Exercício 5
	Faça um programa que armazene a informações de várias pessoas.
	typedef struct{
		char nome[30];
		int idade;
		int altura;
	}Pessoa;
	O programa só deve sair quando o usário disser que não deseja mais entrar com os dados
	de outra pessoa.
	Antes de sair o programa deve apresentar, de fomra organizada, os dados de todas
	as pessoas.
Exercício 7
	O programa deve armazenar no máximo 10 pessoas
	Todas as variáveis que forma usadas no programa deve ser ponteiros.A única exceção
	é o item 1 que deve ser uma variável global Pessoa pessoas[10].
		1. Os ponteiros devem apontar para um buffer chamado pBuffer onde os dados 
		devem ser armazenados. Por exemplo, um contador para um for deve ser um
		ponteiro para int e o int ficar armazenado dentro de pBuffer.
		2. Não pode usar struct dentro do pBuffer

--------------------------------EXPLICAÇÃO DAS PASTAS--------------------------------

Na pasta prinicpal, as atividades estão separados individualmente em pastas.
/Exercicio5/Exercicio5.c
/Exercicio7/exercicio7.c
Há uma última pasta chamada "ResultadosDrMemory" com os .txt gerados pelo Dr. Memory de cada exercício.

--------------------------------COMO EXECUTAR--------------------------------

Todos os exercícios foram feitos no VSCode utilizando extensões em conjunto com o gcc para facilitar a compilação.
Caso for efetuado por linha de comando no terminal, segue abaixo os comandos.
Dentro da diretório do programa:
-- (WINDOWS) --
gcc exercicio.c -o exercicio.exe 
-- (LINUX) --
gcc exercicio.c -o exercicio.out 
./exercicio.out

--------------------------------COMENTÁRIOS--------------------------------
 