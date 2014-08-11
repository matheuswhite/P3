#include "Recursos.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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
	ativ->info   = "";
	ativ->tipo   = "";
	ativ->titulo = "";
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
	char hora[2];
	char minutos[2];
};

void setHora(Hora* hora, char* h) {
	hora->hora = h;
}

void setMinutos(Hora* min, char* m) {
	min->minutos = m;
}
/* END HORA */

/* BEGIN DATAHORA */
struct datahora {
	char dia[2];
	char mes[2];
	char ano[4];
	Hora* hora;
};

void setDia(DataHora* data, char* d) {
	data->dia = d;
}

void setMes(DataHora* data, char* m) {
	data->mes = m;
}

void setAno(DataHora* data, char* a) {
	data->ano = a;
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
	rec->status = "Em andamento";
	rec->identificacao = "Vazio";
	rec->responsavel = "Vazio";
	rec->inicio->dia = "00";
	rec->inicio->mes = "00";
	rec->inicio->ano = "0000";
	rec->inicio->hora->hora = "00";
	rec->inicio->hora->minutos = "00";
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
	short acesso;
	bool emAndamento;
};

Usuario* Usuario_new() {
	Usuario* user = malloc(sizeof(Usuario));
	//init Usuario
	return user;
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
	Node* temp = (Node*)malloc(sizeof(Node));
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
	Recurso* num = (Recurso*)malloc(sizeof(Recurso));

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
/* END LLIST(RECURSO) */