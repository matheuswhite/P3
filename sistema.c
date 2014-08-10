#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
	char* titulo;
	char** participantes;
	char* info;
	char** materialApoio;
	char* tipo;
}Atividade;

typedef struct
{
	char* identificacao;
	DataHora* inicio;
	DataHora* fim;
	char* responsavel;
	char* status;
	Atividade* atividade;
}Recurso;

/* Begin LList */

struct element{
	Recurso* val;
	struct element* next;
};

typedef struct element Node;

typedef struct {
	int size;
	bool empty;
	Node* head;
	Node* tail;
	Node* current;
} LList;

void msgError(const char* error) {
	printf("Error: %s \n", error);
}

void initLList(LList* list) {
	list->empty = true;
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

void append(Recurso* it, LList* list) {	
	Node* temp = (Node*)malloc(sizeof(Node));	
	temp->val = it;
	if(list->size == 0) {
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
		list->current = temp->next;
	}
}
void prev(LList* list) {
	if(list->current == list->head) {
		msgError("Inicio da Lista!");
	}
	else {
		Node* temp = list->current;
		for(list->current = list->head; list->current->next != temp; next(list)) {} 
	}
	
}
void begin(LList* list) {
	list->current = list->head;
}
void end(LList* list) {
	list->current = list->tail;
}
void moveAt(int pos, LList* list) {
	int i = 0;
	if(pos < 1 || pos > list->size) {
		msgError("Fora de alcance!");
	}
	else {
		Node* temp = list->current;
		for(list->current = list->head, i = 0; i < pos; next(list), i++) {}
	}
}

Recurso* remove(LList* list) {
	Recurso* num = (Recurso*)malloc(sizeof(Recurso));
	
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
		else if (list->current == list->tail) {
			prev(list);
			list->tail = list->current;
			list->tail->next = NULL;
			list->current->next = NULL;
		}
		else {
			prev(list);
			list->current->next = temp->next;
		}
		list->size--;
	}
	if(list->size == 0) {
		list->empty = true;
	}

	return num;
}

/* End LList */

typedef struct 
{
	char* nome;
	char* email;
	LList* historicoRecurso;
	char* funcao;
	short acesso;
	bool emAndamento = false;
} Usuario;

void alocar(LList* emProcesso, LList* alocado) {
	Recurso* recurso = (Recurso*)malloc(sizeof(Recurso));

	printf("Identificação do Recurso\n>> ");
	scanf("%s", &recurso->indentificacao);
	getchar();
	printf("Data e Hora início (dd/mm/aaaa 00:00)\n>> ");
	scanf("%d/%d/%d %d:%d", &recurso->inicio->dia, &recurso->inicio->mes, &recurso->inicio->ano,
							 &recurso->inicio->hora->hora, &recurso->inicio->hora->minutos);
	getchar();
	printf("Data e Hora término (dd/mm/aaaa 00:00)\n>> ");
	scanf("%d/%d/%d %d:%d", &recurso->fim->dia, &recurso->fim->mes, &recurso->fim->ano,
							 &recurso->fim->hora->hora, &recurso->fim->hora->minutos);
	getchar();
	printf("Responsável\n>> ");
	scanf("%s", &recurso->responsavel);
	getchar();

	append(recurso, alocado);
}

void mostrarRecursos(Recurso* recurso) {
	printf("Identificação: %s\n", recurso->indentificacao);
	printf("Data e Hora de inicio: %d/%d/%d %d:%d\n", );
	printf("Data e Hora de término: %d/%d/%d %d:%d\n", );
	printf("Responsável: %s\n", );
	printf("Status: %s\n", );

	printf("ATIVIDADE\n");
	printf("Título: \n");
	printf("Descrição: \n");
	printf("Tipo: \n");
	//Resto das atividades

}

void verificarAlocacoes(LList* alocado, LList* emAndamento, LList* usuario) {
	int entrada = 0;

	printf("Alocações pendentes que precisão da sua atenção!\n");
	printf("\n");

	begin(alocado);
	for(int i = 0; i < alocado->size; i++) {
		printf("%d- %s\n", i, alocado->current->val->identificacao);
		next(alocado);
	}
	printf(">> ");

	scanf("%d", &entrada);
	getchar();

	moveAt(entrada, alocado);

	mostrarRecursos(alocado->current);
	/*  $ Procurar recursos na lista 'alocado' como responsável este usuário
		$ Dar a opção de confirmar alocação, se o membro 'emAndamento' estiver false
		$ Quando confirmada:
			& Tirar o recurso da lista 'alocado' e colocar na lista 'emAndamento'
			& Colocar o membro emAndamento do usuario como 'true'
			& Isso quer dizer que o usuario já possui um recurso em Andamento e não poderá pegar outro
		$ Se passar o dia e a hora da alocação o recurso vai para o 'Lixo'
	*/
}

void concluirAlocacoes(LList* emAndamento, LList* concluido) {

}

void menuAlocar(LList* emProcesso, LList* alocado, LList* emAndamento, LList* concluido, LList* usuario) {
	int entrada = 0;
	bool run = true;

	while(run) {
		printf("1- Iniciar alocações\n");
		printf("2- Confirmar alocações\n");
		printf("3- Concluir alocações\n");
		printf("4- Voltar\n>> ");
		scanf("%d", &entrada);
		getchar();

		switch(entrada) {
			case 1:
				alocar(emProcesso, alocado);
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

void cadastrarUsuario() {

}

bool menuPrincipal() {
	bool run = true;
	int entrada;
	LList* emProcesso = (LList*)malloc(sizeof(LList));
	LList* alocado = (LList*)malloc(sizeof(LList));
	LList* emAndamento = (LList*)malloc(sizeof(LList));
	LList* concluido = (LList*)malloc(sizeof(LList));
	LList* usuario = (LList*)malloc(sizeof(LList));

	initLList(emProcesso);
	initLList(alocado);
	initLList(emAndamento);
	initLList(concluido);
	initLList(usuario);

	printf("1- Alocar um Recurso\n");
	printf("2- Consulta\n");
	printf("3- Relatórios\n");
	printf("4- Cadastrar novo usuário\n");
	printf("5- Sair\n>> ");
	scanf("%d", &entrada);

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
			cadastrarUsuario();
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
	char* user, password;
	//Usuario* usuario = (Usuario*)malloc(sizeof(Usuario));
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
		printf("***LOGIN***\nUsuário:\n>> ");
		scanf("%s", user);
		getchar();
		printf("Senha:\n>> ");
		scanf("%s", password);
		getchar();

		/*Verificar o login*/
		
		//if /*Se o login estiver correto*/ 
		//	runLogin = false;
		//else /*Se o login estiver errado*/
		
	}
	
	while(run) {
		run = menuPrincipal();
	}

	return 0;
}
