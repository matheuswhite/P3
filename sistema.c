#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	int val;
	Node* next;
}Node;

typedef struct {
	int size;
	bool empty;
	Node* head;
	Node* tail;
	Node* current;
}LList;

void initLList(LList* list) {
	list->empty = true;
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

void append(int it, LList* list) {	
	Node* temp = (Node*)malloc(sizeof(Node));	
	temp.val = it;
	if(size == 0) {
		temp->next = NULL;			
		list->head = temp;
	}
	else {
		list->current->next = temp;	
	}
	list->tail = temp;
	list->current = temp;
	list->size++;
	list->empty = false;
}

void next(LList* list) {
	if(list->current->next == NULL) {
		msgError("Final da Lista!");
	}
	else {
		Node* temp = list->current;
		list->current = temp.next;
	}
}
void prev(LList* list) {
	if(list->current == list->head) {
		msgError("Inicio da Lista!")
	}
	else {
		Node* temp = list->current;
		for(list->current = list->head; list->curretn->next != temp; list->next()) {} 
	}
	
}
void begin(LList* list) {
	list->current = list->head;
}
void end(LList* list) {
	list->current = list->tail;
}
void moveAt(int pos) {
	if(pos < 1 || pos > size) {
		msgError("Fora de alcance!");
	}
	else {
		Node* temp = list->current;
		for(list->current = list->head, int i = 0; i < pos; list->next(), i++) {}
	}
}

int remove(LList* list) {
	int num = 0;
	
	if(list->size == 0) {
		msgError("Lista Vazia!");
	}
	else {
		Node* temp = list->current;
		num = temp->val;
		if(list->current == list->head) {
			temp = list->head;
			list->head = temp->next;
			list->current = list->head;
			temp->next = NULL;
		}
		else if (list->cuurent == list->tail) {
			list->prev();
			list->tail = list->current;
			list->tail->next = NULL;
			list->current->next = NULL;
		}
		else {
			list->prev();
			list->current->next = temp->next;
		}
		size--;
	}
	if(list->size == 0) {
		list->empty = true;
	}

	return num;
}

void msgError(string error) {
	printf("Error: %s \n", error);
}

/* End LList */




enum nivelAcesso {basico = 0; intermediario = 1, avancado = 2, total = 3};

typedef struct
{
	int hora;
	int minutos;
}Hora;

typedef struct
{
	int dia;
	int mes;
	int ano;
	Hora* hora;
}DataHora;

typedef struct 
{
	string funcao;
	short acesso;
	bool emAndamento = false;
}Usuario;

typedef struct
{
	string indentificacao;
	DataHora* inicio;
	DataHora* fim;
	string responsavel;
	string status = "Em processo de alocação";
	Atividade* atividade;
}Recurso;

typedef struct
{
	string info;
	string tipo;
}Atividade;

void msgAcessoRestrito() {
	printf("Você não tem acesso a esta Área!\n");
}

bool Menu(Usuario* usuario) {
	bool run = true;
	int x;

	LList* emProcesso = (LList*)malloc(sizeof(LList));
	LList* alocado = (LList*)malloc(sizeof(LList));
	LList* emAndamento = (LList*)malloc(sizeof(LList));
	LList* concluido = (LList*)malloc(sizeof(LList));

	initLList(emProcesso);
	initLList(alocado);
	initLList(emAndamento);
	initLList(concluido);

	printf("1- Alocar um Recurso\n");
	printf("2- Acompanhar Recursos\n");
	printf("3- Consulta\n");
	printf("4- Relatórios\n");
	printf("5- Administrar o sistema\n");
	printf("6- Sair\n>>");
	scanf("%d", &x);

	switch(x) {
		case 1:
			if(usuario->acesso != basico) {
				alocar(usuario, emProcesso);
			}
			else {
				msgAcessoRestrito();
			}
			break;
		case 2:
			if(usuario->acesso != basico) {
				verificarAlocacoes(usuario, emProcesso, emAndamento);
			}
			else {
				msgAcessoRestrito();
			}
			break;
		case 3:
			consulta();
			break;
		case 4:
			relatorios();
			break;
		case 5:
			if(usuario == total) {
				admArea();
			}
			else {
				msgAcessoRestrito();
			}
			break;
		case 6:
			run = false;
			break;
		default:
			msgError("Comando não reconhecido!");
			break;
	}

	return run;
}



void alocar(Usuario* usuario, LList* emProcesso) {
	Recurso* recurso = (Recurso*)malloc(sizeof(Recurso));

	printf("Identificação do Recurso\n>>");
	scanf("%s", &recurso->indentificacao);
	getchar();
	printf("Data e Hora início (dd/mm/aaaa 00:00)\n>>");
	scanf("%d/%d/%d %d:%d", &recurso->inicio->dia, &recurso->inicio->mes, &recurso->inicio->ano,
							 &recurso->inicio->hora->hora, &recurso->inicio->hora->minutos);
	getchar();
	printf("Data e Hora término (dd/mm/aaaa 00:00)\n>>");
	scanf("%d/%d/%d %d:%d", &recurso->fim->dia, &recurso->fim->mes, &recurso->fim->ano,
							 &recurso->fim->hora->hora, &recurso->fim->hora->minutos);
	getchar();
	printf("Responsável\n>>");
	scanf("%s", &recurso->responsavel);
	getchar();

	append(recurso);

	return 0;
}

void verificarAlocacoes(Usuario* usuario, LList* alocado, LList* emAndamento) {

	/*  $ Criar um Menu para:
			& Confirmar Alocações
			& Colocar uma descrição no recurso alocado
		$ A descrição só pode ser feita para recursos que estiverem com o status 'Em Andamento', ou seja,
		   na lista 'emAndamento'
	*/
	printf("Alocações pendentes que precisão da sua atenção!\n");
	printf("\n");
	/*  $ Procurar recursos na lista 'alocado' como responsável este usuário
		$ Dar a opção de confirmar alocação, se o membro 'emAndamento' estiver false
		$ Quando confirmada:
			& Tirar o recurso da lista 'alocado' e colocar na lista 'emAndamento'
			& Colocar o membro emAndamento do usuario como 'true'
			& Isso quer dizer que o usuario já possui um recurso em Andamento e não poderá pegar outro
		$ Se passar o dia e a hora da alocação o recurso vai para o 'Lixo'
	*/
}

void consulta() {

}

void relatorios() {

}

void admArea() {

}

int msgLogin() {
	int usuario = 0;

	printf("1- Aluno de Graduação\t4- Professor\n2- Aluno de Mestrado\t5- Pesquisador\n3- Aluno de Doutorado\t6- Administrador\n7- Sair\n>>");
	scanf("%d", &usuario);
	getchar();

	return usuario;
}

int main(int argc, char** argv) {
	int entrada = 0;
	Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));
	bool run = true;
	bool runLogin = false;



	
	/*
	enum usuarios {graduacao, mestrado, doutorado, professores, pesquisadores, administrador};
	enum recursoInfo {identificacao, inicio, termino, responsavel};
	enum Responsavel {professores, pesquisadores, administrador};
	enum status {"Em processo de alocação", "Alocado", "Em andamento", "Concluído"};
	enum atividades {aula, apresentacoes, lab};
	enum ativRestricao {professores, aula, lab};
	enum ativInfo {titulo, descrisao, participantes, materialApoio};
	*/

	while(runLogin) {
		entrada = msgLogin();

		switch(entrada) {
			case 1:
				usuario->funcao = "Aluno de Graduação";
				usuario->acesso = basico;
				runLogin = false;
				break;
			case 2:
				usuario->funcao = "Aluno de Mestrado";
				usuario->acesso = basico;
				runLogin = false;
				break;
			case 3:
				usuario->funcao = "Aluno de Doutorado";
				usuario->acesso = basico;
				runLogin = false;
				break;
			case 4:
				usuario->funcao = "Professor";
				usuario->acesso = avancado;
				runLogin = false;
				break;
			case 5:
				usuario->funcao = "Pesquisador";
				usuario->acesso = intermediario;
				runLogin = false;
				break;
			case 6:
				usuario->funcao = "Administrador";
				usuario->acesso = total;
				runLogin = false;
				break;
			case 7:
				break;
			default:
				msgError("Comando não reconhecido!");
				runLogin = true;
				break;
		}
	}

	
	
	while(run) {
		run = Menu(usuario);
	}

	
	return 0;
}
