#ifndef RECURSOS_H
#define RECURSOS_H

/* BEGIN STRUCTS */
typedef struct hora Hora;
typedef struct datahora DataHora;
typedef struct atividade Atividade;
typedef struct recurso Recurso;
typedef struct usuario Usuario;
typedef struct element Node;
typedef struct linkedlist LList;
typedef struct userlinkedlist ULList;
typedef struct userelement UNode;
/* END STRUCTS */

/* BEGIN USUARIO */
Usuario* Usuario_new();
/* END USUARIO */

/* BEGIN ATIVIDADE */
Atividade* Atividade_new();
void init_Atividade(Atividade* ativ);
void setTitulo(Atividade* ativ, char* titulo);
void setInfo(Atividade* ativ, char* info);
void setTipo(Atividade* ativ, char* tipo);
void setNumParticipantes(Atividade* ativ, int num);
void setNumMaterial(Atividade* ativ, int num);
void setParticipantes(Atividade* ativ, char* participantes[]);
void setMaterial(Atividade* ativ, char* materiais[]);
/* END ATIVIDADE */

/* BEGIN HORA */
void setHora(Hora* hora, char* h);
void setMinutos(Hora* min, char* m);
/* END HORA */

/* BEGIN DATAHORA */
void setDia(DataHora* data, char* d);
void setMes(DataHora* data, char* m);
void setAno(DataHora* data, char* a);
/* END DATAHORA */

/* BEGIN RECURSO */
Recurso* Recurso_new();
void initRecurso(Recurso* rec);
void setId(Recurso* rec, char* id);
void setResponsavel(Recurso* rec, char* resp);
void setStatus(Recurso* rec, char* stats);
Hora* getHora(DataHora* data);
DataHora* getInicio(Recurso* rec);
DataHora* getFim(Recurso* rec);
Atividade* getAtividade(Recurso* rec);
/* END RECURSO */

/* BEGIN LLIST(RECURSO) */
LList* LList_new();
void msgError(const char* error);
void initLList(LList* list);
void append(Recurso* it, LList* list);
void next(LList* list);
void prev(LList* list);
void begin(LList* list);
void end(LList* list);
void moveAt(int pos, LList* list);
Recurso* removeR(LList* list);
/* END LLIST(RECURSO) */

#endif // RECURSOS_H