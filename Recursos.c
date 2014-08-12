#include "Recursos.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define ROWS 30
#define STRING_SIZE 256

/* BEGIN ATIVIDADE */
struct atividade {
	char* titulo;
	char** participantes;
	char* info;
	char** materialApoio;
	int numMaterial;
	int numParticipantes;
	char* tipo;
};

Atividade* Atividade_new() {
	Atividade* ativ = malloc(sizeof(Atividade));
	init_Atividade(ativ);
	return ativ;
}

void init_Atividade(Atividade* ativ) {
	ativ->tipo = malloc(STRING_SIZE * sizeof(char));
	ativ->info = malloc(STRING_SIZE * sizeof(char));
	ativ->titulo = malloc(STRING_SIZE * sizeof(char));

	ativ->materialApoio = (char**)malloc(ROWS * sizeof(char*));
	for (size_t i = 0; i < ROWS; i++) {
		ativ->materialApoio[i] = (char*)malloc(STRING_SIZE * sizeof(char));
	}

	ativ->participantes = (char**)malloc(sizeof(char*));
	for (size_t i = 0; i < ROWS; i++) {
		ativ->participantes[i] = (char*)malloc(STRING_SIZE * sizeof(char));
	}

	ativ->info   = "Vazio";
	ativ->tipo   = "vazio";
	ativ->titulo = "Vazio";

	ativ->numMaterial = 0;
	ativ->numParticipantes = 0;
}

void setTitulo(Atividade* ativ, char* titulo) {
	ativ->titulo = ativ;
}

void setInfo(Atividade* ativ, char* info) {
	ativ->info = info;
}

void setTipo(Atividade* ativ, char* tipo) {
	ativ->tipo = tipo;
}

void setNumParticipantes(Atividade* ativ, int num) {
	ativ->numParticipantes = num;
}

void setNumMaterial(Atividade* ativ, int num) {
	ativ->numMaterial = num;
}

void setParticipantes(Atividade* ativ, char* participantes[]) {
	for (int i = 0; i < ativ->numParticipantes; i++) {
		ativ->participantes[i] = participantes[i];
	}
}
void setMaterial(Atividade* ativ, char* materiais[]) {
	for (int i = 0; i < ativ->numMaterial; i++) {
		ativ->materialApoio[i] = materiais[i];
	}
}
/* END ATIVIDADE */

/* BEGIN HORA */
struct hora {
	char* hora;
	char* minutos;
};

Hora* Hora_new() {
	Hora* hora = (Hora*)malloc(sizeof(Hora));
	initHora(hora);
	return hora;
}

void setHora(Hora* hora, char* h) {
	hora->hora = h;
}

void setMinutos(Hora* min, char* m) {
	min->minutos = m;
}

void initHora(Hora* hora) {
	hora->hora = (char*)malloc(3 * sizeof(char));
	hora->minutos = (char*)malloc(3 * sizeof(char));
	
	hora->hora = "00";
	hora->minutos = "00";
}
/* END HORA */

/* BEGIN DATAHORA */
struct datahora {
	char* dia;
	char* mes;
	char* ano;
	Hora* hora;
};

DataHora* DataHora_new() {
	DataHora* data = (DataHora*)malloc(sizeof(DataHora));
	initDataHora(data);
	return data;
}

void setDia(DataHora* data, char* d) {
	data->dia = d;
}

void setMes(DataHora* data, char* m) {
	data->mes = m;
}

void setAno(DataHora* data, char* a) {
	data->ano = a;
}

void initDataHora(DataHora* data) {
	data->dia = (char*)malloc(3 * sizeof(char));
	data->mes = (char*)malloc(3 * sizeof(char));
	data->ano = (char*)malloc(5 * sizeof(char));
	data->hora = Hora_new();

	data->dia = "00";
	data->mes = "00";
	data->ano = "0000";
}
/* END DATAHORA */

/* BEGIN RECURSOS */
struct recurso {
	char* identificacao;
	DataHora* inicio;
	DataHora* fim;
	char* responsavel;
	char* status;
	Atividade* atividade;
};

void initRecurso(Recurso* rec) {
	rec->identificacao = (char*)malloc(STRING_SIZE * sizeof(char));
	rec->responsavel = (char*)malloc(STRING_SIZE * sizeof(char));
	rec->status = (char*)malloc(STRING_SIZE * sizeof(char));

	rec->inicio = DataHora_new();
	rec->fim = DataHora_new();

	rec->atividade = Atividade_new();
	
	rec->status = "Em andamento";
	rec->identificacao = "Vazio";
	rec->responsavel = "Vazio";
}

Recurso* Recurso_new() {
	Recurso* rec = malloc(sizeof(Recurso));
	initRecurso(rec);
	return rec;
}

void setId(Recurso* rec, char* id){
	rec->identificacao = id;
}

void setResponsavel(Recurso* rec, char* resp) {
	rec->responsavel = resp;
}

void setStatus(Recurso* rec, char* stats) {
	rec->status = stats;
}

Hora* getHora(DataHora* data) {
	return data->hora;
}

DataHora* getInicio(Recurso* rec) {
	return rec->inicio;
}

DataHora* getFim(Recurso* rec) {
	return rec->fim;
}

Atividade* getAtividade(Recurso* rec) {
	return rec->atividade;
}
/* END RECURSOS */

/* BEGIN USUARIO */
struct usuario {
	char* nome;
	char* email;
	LList* historicoRecurso;
	char* funcao;
	int acesso;
	bool emAndamento;
};

Usuario* Usuario_new() {
	Usuario* user = malloc(sizeof(Usuario));
	initUsuario(user);
	return user;
}

char* getNome(Usuario* user) {
	return user->nome;
}

void initUsuario(Usuario* user) {
	user->nome = (char*)malloc(STRING_SIZE * sizeof(char));
	user->email = (char*)malloc(STRING_SIZE * sizeof(char));
	user->funcao = (char*)malloc(STRING_SIZE * sizeof(char));
	user->historicoRecurso = LList_new();
	
	user->emAndamento = false;
	user->acesso = 0;
	user->funcao = "Vazio";
	user->email = "Vazio";
	user->nome = "Vazio";
}

void setNome(Usuario* user, char* nome) {
	user->nome = nome;
}

void setemail(Usuario* user, char* email) {
	user->email = email;
}

void setFuncao(Usuario* user, char* func) {
	user->funcao = func;
}

void setAcesso(Usuario* user, int acess) {
	user->acesso = acess;
}
/* END USUARIO */

/* BEGIN LLIST(RECURSO) */
struct element{
	Recurso* val;
	struct element* next;
};

struct linkedlist {
	int size;
	bool empty;
	Node* head;
	Node* tail;
	Node* current;
};

void msgError(const char* error) {
	printf("Error: %s \n", error);
}

Node* Node_new() {
	Node* rec = (Node*)malloc(sizeof(Node));
	initNode(rec);
	return rec;
}

void initNode(Node* rec) {
	rec->val = Recurso_new();
	rec->next = NULL;
}

LList* LList_new() {
	LList* list = malloc(sizeof(LList));
	initLList(list);
	return list;
}

void initLList(LList* list) {
	list->empty = true;
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

void append(Recurso* it, LList* list) {
	Node* temp = Node_new();
	temp->val = it;
	if (list->size == 0) {
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
	if (list->current->next == NULL) {
		msgError("Final da Lista!");
	}
	else {
		Node* temp = list->current;
		list->current = temp->next;
	}
}

void prev(LList* list) {
	if (list->current == list->head) {
		msgError("Inicio da Lista!");
	}
	else {
		Node* temp = list->current;
		for (list->current = list->head; list->current->next != temp; next(list)) {}
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
	if (pos < 1 || pos > list->size) {
		msgError("Fora de alcance!");
	}
	else {
		Node* temp = list->current;
		for (list->current = list->head, i = 0; i < pos; next(list), i++) {}
	}
}

Recurso* removeR(LList* list) {
	Recurso* num = Recurso_new();

	if (list->size == 0) {
		msgError("Lista Vazia!");
	}
	else {
		Node* temp = list->current;
		num = temp->val;
		if (list->current == list->head) {
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
	if (list->size == 0) {
		list->empty = true;
	}

	return num;
}

int getSize(LList* list) {
	return list->size;
}

bool find(LList* list, char* id) {
	bool saida = false;
	
	begin(list);
	for (size_t i = 0; i < getSize(list); i++)
	{
		if (strcmp(list->current->val->identificacao, id) == 0) {
			saida = true;
			i = getSize(list) + 1;
		}
		next(list);
	}

	return saida;
}
/* END LLIST(RECURSO) */

/* BEGIN LLIST(USUARIO) */
struct userelement{
	Usuario* val;
	struct userelement* next;
};

struct userlinkedlist {
	int size;
	bool empty;
	UNode* head;
	UNode* tail;
	UNode* current;
};

UNode* UNode_new() {
	UNode* user = (UNode*)malloc(sizeof(UNode));
	initUNode(user);
	return user;
}

void initUNode(UNode* user) {
	user->val = Usuario_new();
	user->next = NULL;
}

ULList* LList_new() {
	ULList* list = malloc(sizeof(ULList));
	initULList(list);
	return list;
}

void initULList(ULList* list) {
	list->empty = true;
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
}

void append(Usuario* it, ULList* list) {
	UNode* temp = UNode_new();
	temp->val = it;
	if (list->size == 0) {
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

void next(ULList* list) {
	if (list->current->next == NULL) {
		msgError("Final da Lista!");
	}
	else {
		UNode* temp = list->current;
		list->current = temp->next;
	}
}

void prev(ULList* list) {
	if (list->current == list->head) {
		msgError("Inicio da Lista!");
	}
	else {
		UNode* temp = list->current;
		for (list->current = list->head; list->current->next != temp; next(list)) {}
	}

}

void begin(ULList* list) {
	list->current = list->head;
}

void end(ULList* list) {
	list->current = list->tail;
}

void moveAt(int pos, ULList* list) {
	int i = 0;
	if (pos < 1 || pos > list->size) {
		msgError("Fora de alcance!");
	}
	else {
		UNode* temp = list->current;
		for (list->current = list->head, i = 0; i < pos; next(list), i++) {}
	}
}

Usuario* removeU(ULList* list) {
	Usuario* num = Usuario_new();

	if (list->size == 0) {
		msgError("Lista Vazia!");
	}
	else {
		UNode* temp = list->current;
		num = temp->val;
		if (list->current == list->head) {
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
	if (list->size == 0) {
		list->empty = true;
	}

	return num;
}

int getSize(ULList* list) {
	return list->size;
}

Usuario* getVAL(ULList* list) {
	return list->current->val;
}

bool findNome(ULList* list, char* name) {
	bool saida = false;

	begin(list);
	for (size_t i = 0; i < getSize(list); i++)
	{
		if (strcmp(list->current->val->nome, name) == 0) {
			saida = true;
			i = getSize(list) + 1;
		}
		next(list);
	}

	return saida;
}

bool findEmail(ULList* list, char* email) {
	bool saida = false;

	begin(list);
	for (size_t i = 0; i < getSize(list); i++)
	{
		if (strcmp(list->current->val->email, email) == 0) {
			saida = true;
			i = getSize(list) + 1;
		}
		next(list);
	}

	return saida;
}

bool findFuncao(ULList* list, char* func) {
	bool saida = false;

	begin(list);
	for (size_t i = 0; i < getSize(list); i++)
	{
		if (strcmp(list->current->val->funcao, func) == 0) {
			saida = true;
			i = getSize(list) + 1;
		}
		next(list);
	}

	return saida;
}

/* END LLIST(USUARIO) */