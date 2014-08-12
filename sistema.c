#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Recursos.h"

#define BASICO 1
#define INTERMEDIARIO 2
#define AVANCADO 3
#define TOTAL 4

void alocar(LList* emProcesso, LList* alocado, ULList* usuarios) {
	Recurso* recurso = Recurso_new();
	char aux_s[256];
	char dia[3];
	char mes[3];
	char ano[5];
	char hora[3];
	char min[3];

	printf("Identificação do Recurso (sem espaços)\n>> ");
	fgets(aux_s, sizeof(aux_s), stdin);

	setId(recurso, aux_s);

	printf("Data e Hora início (dd/mm/aaaa 00:00)\n");
	printf(">> Dia: ");
	fgets(dia, sizeof(dia), stdin);
	getchar();

	printf(">> Mes: ");
	fgets(mes, sizeof(mes), stdin);
	getchar();

	printf(">> Ano: ");
	fgets(ano, sizeof(ano), stdin);
	getchar();

	printf(">> Hora: ");
	fgets(hora, sizeof(hora), stdin);
	getchar();

	printf(">> Minutos: ");
	fgets(min, sizeof(min), stdin);
	getchar();

	setDia(getInicio(recurso), dia);
	setMes(getInicio(recurso), mes);
	setAno(getInicio(recurso), ano);
	setHora(getHoraD(getInicio(recurso)), hora);
	setMinutos(getHoraD(getInicio(recurso)), min);

	printf("Data e Hora término (dd/mm/aaaa 00:00)\n");
	printf(">> Dia: ");
	fgets(dia, sizeof(dia), stdin);
	getchar();

	printf(">> Mes: ");
	fgets(mes, sizeof(mes), stdin);
	getchar();

	printf(">> Ano: ");
	fgets(ano, sizeof(ano), stdin);
	getchar();

	printf(">> Hora: ");
	fgets(hora, sizeof(hora), stdin);
	getchar();

	printf(">> Minutos: ");
	fgets(min, sizeof(min), stdin);
	getchar();

	setDia(getFim(recurso), dia);
	setMes(getFim(recurso), mes);
	setAno(getFim(recurso), ano);
	setHora(getHoraD(getFim(recurso)), hora);
	setMinutos(getHoraD(getFim(recurso)), min);

	
	printf("Responsável\n>> ");
	fgets(aux_s, sizeof(aux_s), stdin);

	if (!(findNome(usuarios, aux_s))) {
		printf("Usuario não cadastrado!\n");
		cadastrarUsuario(usuarios);
	}

	setResponsavel(recurso, aux_s);

	appendR(recurso, alocado);
}

void mostrarRecursos(Recurso* rec) {
	
	printf("Identificação: %s\n", getId(rec));
	printf("Data e Hora de inicio: %s/%s/%s %s:%s\n", getDia(getInicio(rec)), getMes(getInicio(rec)), getAno(getInicio(rec)), 
													  getHora(getHoraD(getInicio(rec))), getHora(getHoraD(getInicio(rec))));
	printf("Data e Hora de término: %s/%s/%s %s:%s\n", getDia(getFim(rec)), getMes(getFim(rec)), getAno(getFim(rec)),
													   getHora(getHoraD(getFim(rec))), getHora(getHoraD(getFim(rec))));
	printf("Responsável: %s\n", getResponsavel(rec));
	printf("Status: %s\n", getStatus(rec));
}

void verificarAlocacoes(LList* alocado, LList* emAndamento, ULList* usuario) {
	int entrada = 0;
	char* aux_s;
	char* responsavel;
	bool run = false;
	bool runChoice = false;
	Recurso* rec = Recurso_new();
	Usuario* user = Usuario_new();

	printf("Alocações pendentes que precisão da sua atenção!\n");
	printf("\n");

	beginR(alocado);
	for(int i = 0; i < getSizeR(alocado); i++) {
		printf("%d- %s\n", i, getId(getCurrentR(alocado)));
		nextR(alocado);
	}
	printf(">> ");

	scanf("%d", &entrada);
	getchar();

	moveAtR(entrada, alocado);

	mostrarRecursos(getCurrentR(alocado));

	while (run) {
		printf("Escolha um recurso pelo nome\n>> ");
		fgets(aux_s, sizeof(aux_s), stdin);

		if (find(alocado, aux_s)) {
			while (runChoice) {
				printf("Confimar esta alocação?\n1- Sim\t2- Não\n>> ");
				scanf("%d", &entrada);
				if (entrada == 1) {
					rec = removeR(alocado);
					responsavel = getResponsavel(rec);
					if (findNome(usuario, responsavel)) {
						user = getCurrentU(usuario);
						if (!(isEmAndamento(user))) {
							setEmAndamento(user);
						}
						else {
							msgError("Este responsável já possui um recurso em andamento no seu nome!");
						}
					}
					else {
						msgError("Responsavel não encontrado. Erro de Alocação!");
						return ;
					}
					appendR(rec, emAndamento);
					runChoice = false;
				}
				else if (entrada == 2) {
					runChoice = false;
				}
				else {
					msgError("Comando incorreto!");
					runChoice = true;
				}
			}
			
			run = false;
		}
		else {
			run = true;
		}
	}
}

void concluirAlocacoes(LList* emAndamento, LList* concluido) {

}

void menuAlocar(LList* emProcesso, LList* alocado, LList* emAndamento, LList* concluido , ULList* usuario) {
	int entrada = 0;
	bool run = true;

	while(run) {
		printf("1- Iniciar alocações\n");
		printf("2- Confirmar alocações\n");
		printf("3- Concluir alocações\n");
		printf("4- Voltar\n>> ");
		scanf_s("%d", &entrada);
		getchar();

		switch(entrada) {
			case 1:
				alocar(emProcesso, alocado, usuario);
				break;
			case 2:
				verificarAlocacoes(alocado, emAndamento, usuario);
				break;
			case 3:
				concluirAlocacoes(emAndamento, concluido);
				break;
			case 4:
				run = false;
				break;
			default:
				break;
		}
	}

}

void consulta() {

}

void relatorios() {

}

void cadastrarUsuario(ULList* list) {
	int entrada;
	char* aux_s;
	Usuario* user = Usuario_new();
	bool run = false;
	
	printf("Usuários existentes:\n");
	
	if (getSize(list) == 0) {
		printf("Sem usuários cadastrados");
	}
	else {
		begin(list);
		for (int i = 0; i < getSize(list); i++)
		{
			user = getVal(list);
			printf("%d- %s\n", i, getNome(user));
			next(list);
		}
		printf("\n");
	}

	user = NULL;

	while (run)
	{
		printf("Nome do Usuário\n>> ");
		fgets(aux_s, sizeof(aux_s), stdin);
		getchar();

		if (findNome(list, aux_s)) {
			run = true;
			msgError("Nome já existente");
		}
		else {
			run = false;
		}
	}
	
	setNome(user, aux_s);

	while (run)
	{
		printf("E-mail\n>> ");
		fgets(aux_s, sizeof(aux_s), stdin);
		getchar();

		if (findEmail(list, aux_s)) {
			run = true;
			msgError("Email já existente");
		}
		else {
			run = false;
		}
	}

	setEmail(user, aux_s);

	printf("Função do Usuário\n1- Aluno de Graduação\t4- Professor\n2- Aluno de Mestrado\t5- Pesquisador\n3- Aluno de Doutorado\t6- Administrador\n>> ");
	scanf("%d", &entrada);
	getchar();

	switch (entrada)
	{
	case 1:
		setFuncao(user, "Aluno de Graduação");
		setAcesso(user, BASICO);
		break;
	case 2:
		setFuncao(user, "Aluno de Mestrado");
		setAcesso(user, BASICO);
		break;
	case 3:
		setFuncao(user, "Aluno de Doutorado");
		setAcesso(user, BASICO);
		break;
	case 4:
		setFuncao(user, "Professor");
		setAcesso(user, AVANCADO);
		break;
	case 5:
		setFuncao(user, "Pesquisador");
		setAcesso(user, INTERMEDIARIO);
		break;
	case 6:
		setFuncao(user, "Administrador");
		setAcesso(user, TOTAL);
		break;
	default:
		break;
	}

	append(user, list);
}

bool menuPrincipal() {
	bool run = true;
	int entrada;
	LList* emProcesso = LList_new();
	LList* alocado = LList_new();
	LList* emAndamento = LList_new();
	LList* concluido = LList_new();

	ULList* usuario = ULList_new();

	printf("1- Alocar um Recurso\n");
	printf("2- Consulta\n");
	printf("3- Relatórios\n");
	printf("4- Cadastrar novo usuário\n");
	printf("5- Sair\n>> ");
	scanf_s("%d", &entrada);

	switch(entrada) {
		case 1:
			menuAlocar(emProcesso, alocado, emAndamento, concluido, usuario);
			break;
		case 2:
			consulta();
			break;
		case 3:
			relatorios();
			break;
		case 4:
			cadastrarUsuario(usuario);
			break;
		case 5:
			run = false;
			break;
		default:
			msgError("Comando não reconhecido!");
			break;
	}

	return run;
}

int main(int argc, char** argv) {
	char* user = "";
	char* password = "";
	//Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));
	bool run = true;
	bool runLogin = false;

	while(runLogin) {
		printf("***LOGIN***\nUsuário:\n>> ");
		scanf_s("%s", user);
		getchar();
		printf("Senha:\n>> ");
		scanf_s("%s", password);
		getchar();

		/*Verificar o login*/
		
		//if /*Se o login estiver correto*/ 
		//	runLogin = false;
		//else /*Se o login estiver errado*/
		//	msgError("lOGIN INCORRETO");
	}
	
	while(run) {
		run = menuPrincipal();
	}

	return 0;
}
