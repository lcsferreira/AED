--------------------------------DADOS PESSOAIS--------------------------------

Nome: Lucas Simões Ferreira
Matrícula: 20102119
Email: lucas.simoes.ferreira@gmail.com (pessoal)
	lsferreira@inf.ufpel.edu.br(ufpel)
Repositório da Lista de exercícios 1: 
	https://github.com/lcsferreira/AED/tree/main/ListaDeExercicios1

--------------------------------ENUNCIADOS DAS QUESTÕES--------------------------------

Exercício 1
	Criar um projeto "Olá Mundo" em C e utilizar o debug com um breakpoint no printf.
Exercício 2
	Faça um programa que armazena nomes.
	O programa deve armazenar todos os nomes na mesma string
	O tamanho da string deve crescer e diminuir confrome nomes forem colocados ou removidos.
	Não pode ter desperdício de memória.
	Faça o seguinte menu:
		- 1) Adicionar nome
		- 2) Remover nome
		- 3) Listar
		- 4) Sair
Exercício 3
	Faça uma agenda capaz de incluir, apagar, buscar e listar quantas pessoas o usuário desejar, porém,
	toda a informação incluída na agenda deve ficar num único lugar chamado:“void *pBuffer”.
	Não pergunte para o usuário quantas pessoas ele vai incluir.
	Não pode alocar espaço para mais pessoas do que o necessário.
	Cada pessoa tem nome[10], idade e telefone.

--------------------------------EXPLICAÇÃO DAS PASTAS--------------------------------

Na pasta prinicpal, as atividades estão separados individualmente em pastas.
/Exercicio2/Exercicio2.c
/Exercicio3/exercicio3.c
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
Os vídeos ficaram muito grandes e foram colocados no Drive no seguinte link: 
Vídeo Exercicio1: https://drive.google.com/file/d/1HZYPnT8O1lSmx42s35TJdz5ChSvoTY1D/view?usp=sharing
Vídeo Exercicio2: https://drive.google.com/file/d/1XwE-uexcAF5pavRZ7gJXAHGTubdRLV_e/view?usp=sharing
Vídeo Exercício3: https://drive.google.com/file/d/1HVL3sn5GPzWaIcoQ0xngfNSn9dIVR9et/view?usp=sharing

No exercício 2 não consegui implementar mais funções para ficar melhor o código, ainda quero estudar para melhorar isso.