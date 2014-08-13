#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BASICO 1
#define INTERMEDIARIO 2
#define AVANCADO 3
#define TOTAL 4
#define STRING_SIZE 256
#define ROWS 30

/**********************************************/
/*******************Structs********************/
/**********************************************/

typedef struct {
    char* hora;
    char* minutos;
}Hora;

typedef struct {
    char* dia;
    char* mes;
    char* ano;
    Hora* hora;
}DataHora;

typedef struct {
    char* nome;
    char* email;
    char* funcao;
    int acesso;
    bool emAndamento;
}Usuario;

typedef struct {
    char* identificacao;
    char** participantes;
    char** materialApoio;
    char* tipo;
    DataHora* inicio;
    DataHora* fim;
    Usuario* responsavel;
    char* status;
    char* tituloAtiv;
    char* descricao;
}Recurso;

void msgError(const char* error) {
    printf("Error: %s \n", error);
}

void initUsuario(Usuario* user) {
    user->nome = (char*)malloc(STRING_SIZE * sizeof(char));
    user->email = (char*)malloc(STRING_SIZE * sizeof(char));
    user->funcao = (char*)malloc(STRING_SIZE * sizeof(char));

    user->emAndamento = false;
    user->acesso = 0;
}

Usuario* Usuario_new() {
    Usuario* user = (Usuario*)malloc(sizeof(Usuario));
    initUsuario(user);
    return user;
}

void initHora(Hora* hora) {
    hora->hora = (char*)malloc(3 * sizeof(char));
    hora->minutos = (char*)malloc(3 * sizeof(char));
}

Hora* Hora_new() {
    Hora* hora = (Hora*)malloc(sizeof(Hora));
    initHora(hora);
    return hora;
}

void initDataHora(DataHora* data) {
    data->dia = (char*)malloc(3 * sizeof(char));
    data->mes = (char*)malloc(3 * sizeof(char));
    data->ano = (char*)malloc(5 * sizeof(char));
    data->hora = Hora_new();
}

DataHora* DataHora_new() {
    DataHora* data = (DataHora*)malloc(sizeof(DataHora));
    initDataHora(data);
    return data;
}

void initRecurso(Recurso* rec) {
    rec->identificacao = (char*)malloc(STRING_SIZE * sizeof(char));
    rec->responsavel = (Usuario*)malloc(sizeof(Usuario));
    rec->status = (char*)malloc(STRING_SIZE * sizeof(char));
    rec->descricao = (char*)malloc(STRING_SIZE * sizeof(char));
    rec->tituloAtiv = (char*)malloc(STRING_SIZE * sizeof(char));
    rec->tipo = (char*)malloc(STRING_SIZE * sizeof(char));

    rec->materialApoio = (char**)malloc(ROWS * sizeof(char*));
    int i, j;
    for (i = 0; i < ROWS; i++) {
        rec->materialApoio[i] = (char*)malloc(STRING_SIZE * sizeof(char));
    }

    rec->participantes = (char**)malloc(ROWS *sizeof(char*));
    for (j = 0; j < ROWS; j++) {
        rec->participantes[j] = (char*)malloc(STRING_SIZE * sizeof(char));
    }

    rec->inicio = DataHora_new();
    rec->fim = DataHora_new();

    rec->status = (char*)"Em andamento";
}

Recurso* Recurso_new() {
    Recurso* rec = (Recurso*)malloc(sizeof(Recurso));
    initRecurso(rec);
    return rec;
}

/**********************************************/
/*******************Structs********************/
/**********************************************/

/**********************************************/
/***********Linked*List*Usuarios***************/
/**********************************************/

struct userelement{
    Usuario* val;
    struct userelement* next;
};

typedef struct userelement UNode;

typedef struct {
    int size;
    bool empty;
    UNode* head;
    UNode* tail;
    UNode* current;
}ULList;

void initUNode(UNode* user) {
    user->val = Usuario_new();
    user->next = 0;
}

UNode* UNode_new() {
    UNode* user = (UNode*)malloc(sizeof(UNode));
    initUNode(user);
    return user;
}

void initULList(ULList* list) {
    list->empty = true;
    list->size = 0;
    list->head = 0;
    list->tail = 0;
    list->current = 0;
}

ULList* ULList_new() {
    ULList* list = (ULList*)malloc(sizeof(ULList));
    initULList(list);
    return list;
}

void append(Usuario* it, ULList* list) {
    UNode* temp = UNode_new();
    temp->val = it;
    if (list->size == 0) {
        temp->next = 0;
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
    if (list->current->next == 0) {
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
            temp->next = 0;
        }
        else if (list->current == list->tail) {
            prev(list);
            list->tail = list->current;
            list->tail->next = 0;
            list->current->next = 0;
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

Usuario* findU(ULList* list, char* id) {

    begin(list);
    int i;
    for (i = 0; i < list->size; i++)
    {
        if (strcmp(list->current->val->nome, id) == 0) {
            return list->current->val;
        }
        next(list);
    }

    return 0;
}

/**********************************************/
/***********Linked*List*Usuarios***************/
/**********************************************/

/**********************************************/
/***********Linked*List*Recursos***************/
/**********************************************/

struct element{
    Recurso* val;
    struct element* next;
};

typedef struct element Node;

typedef struct{
    int size;
    bool empty;
    Node* head;
    Node* tail;
    Node* current;
}LList;

void initNode(Node* rec) {
    rec->val = Recurso_new();
    rec->next = 0;
}

Node* Node_new() {
    Node* rec = (Node*)malloc(sizeof(Node));
    initNode(rec);
    return rec;
}

void initLList(LList* list) {
    list->empty = true;
    list->size = 0;
    list->head = 0;
    list->tail = 0;
    list->current = 0;
}

LList* LList_new() {
    LList* list = (LList*)malloc(sizeof(LList));
    initLList(list);
    return list;
}

void appendR(Recurso* it, LList* list) {
    Node* temp = Node_new();
    temp->val = it;
    if (list->size == 0) {
        temp->next = 0;
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

void nextR(LList* list) {
    if (list->current->next == 0) {
        msgError("Final da Lista!");
    }
    else {
        Node* temp = list->current;
        list->current = temp->next;
    }
}

void prevR(LList* list) {
    if (list->current == list->head) {
        msgError("Inicio da Lista!");
    }
    else {
        Node* temp = list->current;
        for (list->current = list->head; list->current->next != temp; nextR(list)) {}
    }

}

void beginR(LList* list) {
    list->current = list->head;
}

void endR(LList* list) {
    list->current = list->tail;
}

void moveAtR(int pos, LList* list) {
    int i = 0;
    if (pos < 1 || pos > list->size) {
        msgError("Fora de alcance!");
    }
    else {
        Node* temp = list->current;
        for (list->current = list->head, i = 0; i < pos; nextR(list), i++) {}
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
            temp->next = 0;
        }
        else if (list->current == list->tail) {
            prevR(list);
            list->tail = list->current;
            list->tail->next = 0;
            list->current->next = 0;
        }
        else {
            prevR(list);
            list->current->next = temp->next;
        }
        list->size--;
    }
    if (list->size == 0) {
        list->empty = true;
    }

    return num;
}

Recurso* findR(LList* list, char* id) {
    beginR(list);
    int i;
    for (i = 0; i < list->size; i++)
    {
        if (strcmp(list->current->val->identificacao, id) == 0) {
            return list->current->val;
        }
        nextR(list);
    }

    return 0;
}

/**********************************************/
/***********Linked*List*Recursos***************/
/**********************************************/

void cadastrarUsuario(ULList* list) {
    int entrada;
    char aux_s2[256];
    Usuario* user = Usuario_new();
    bool run = false;

    printf("Usuários existentes:\n");

    if (list->size == 0) {
        printf("Sem usuários cadastrados\n");
    }
    else {
        begin(list);
        int i;
        for (i = 0; i < list->size; i++)
        {
            user = list->current->val;
            printf("%d- %s\n", i, user->nome);
            next(list);
        }
        printf("\n");
    }

    user = 0;

    getchar();
    printf("Nome do Usuário\n>> ");
    fgets(aux_s2, sizeof(aux_s2), stdin);

    user->nome = aux_s2;
    /*problema*/
    //strcpy(user->nome, aux_s);

    printf("E-mail\n>> ");
    fgets(aux_s2, sizeof(aux_s2), stdin);

    user->email = aux_s2;

    printf("Função do Usuário\n1- Aluno de Graduação\t4- Professor\n2- Aluno de Mestrado\t5- Pesquisador\n3- Aluno de Doutorado\t6- Administrador\n>> ");
    scanf("%d", &entrada);
    getchar();

    switch (entrada)
    {
    case 1:
        user->funcao = (char*)"Aluno de Graduação";
        user->acesso = BASICO;
        break;
    case 2:
        user->funcao = (char*)"Aluno de Mestrado";
        user->acesso = BASICO;
        break;
    case 3:
        user->funcao = (char*)"Aluno de Doutorado";
        user->acesso = BASICO;
        break;
    case 4:
        user->funcao = (char*)"Professor";
        user->acesso = AVANCADO;
        break;
    case 5:
        user->funcao = (char*)"Pesquisador";
        user->acesso = INTERMEDIARIO;
        break;
    case 6:
        user->funcao = (char*)"Administrador";
        user->acesso = TOTAL;
        break;
    default:
        break;
    }

    append(user, list);
}

void alocar(LList* emProcesso, LList* alocado, ULList* usuarios) {
    Recurso* recurso = Recurso_new();
    Usuario* user = Usuario_new();
    char aux_s[256];
    char dia[3];
    char mes[3];
    char ano[5];
    char hora[3];
    char min[3];

    printf("Identificação do Recurso (sem espaços)\n>> ");
    fgets(aux_s, sizeof(aux_s), stdin);

    recurso->identificacao = aux_s;

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


    recurso->inicio->dia = dia;
    recurso->inicio->mes = mes;
    recurso->inicio->ano = ano;
    recurso->inicio->hora->hora = hora;
    recurso->inicio->hora->minutos = min;

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

    recurso->fim->dia = dia;
    recurso->fim->mes = mes;
    recurso->fim->ano = ano;
    recurso->fim->hora->hora = hora;
    recurso->fim->hora->minutos = min;


    printf("Responsável\n>> ");
    fgets(aux_s, sizeof(aux_s), stdin);

    user = findU(usuarios, aux_s);

    if (user == 0) {
        printf("Usuario não cadastrado!\n");
        cadastrarUsuario(usuarios);
    }
    else {
        recurso->responsavel = user;
    }

    appendR(recurso, alocado);
}

void mostrarRecursos(Recurso* rec) {
	/*char* identificacao; v
    char** participantes;
    char** materialApoio;
    char* tipo;
    DataHora* inicio; v
    DataHora* fim; v
    Usuario* responsavel; v
    char* status; v
    char* tituloAtiv; v
    char* descricao; v*/
	
	int i;
    printf("Identificação: %s\n", rec->identificacao);
    printf("Data e Hora de inicio: %s/%s/%s %s:%s\n", rec->inicio->dia, rec->inicio->mes, rec->inicio->ano,
           rec->inicio->hora->hora, rec->inicio->hora->minutos);
    printf("Data e Hora de término: %s/%s/%s %s:%s\n", rec->fim->dia, rec->fim->mes, rec->fim->ano,
           rec->fim->hora->hora, rec->fim->hora->minutos);
    printf("Responsável: %s\n", rec->responsavel);
    printf("Status: %s\n", rec->responsavel);
	printf("Titulo da Atividade: %s\n", rec->tituloAtiv);
	printf("Descricao: %s\n", rec->descricao);
	printf("Tipo de Atividade: %s\n", rec->tipo);
	
	printf("Participantes\n");
	for(i = 0; i < 30; i++) {
		printf("%d- %s\n", i, rec->participantes[i]);
	}
	
	printf("Materiais de apoio\n");
	for(i = 0; i < 30; i++) {
		printf("%d- %s\n", i, rec->materialApoio[i]);
	}
}

void mostrarUsuario(Usuario* user) {
	printf("Nome: %s\n", user->nome);
    printf("Email: %s\n", user->email);
    printf("Função: %s\n", user->funcao);
}

void verificarAlocacoes(LList* alocado, LList* emAndamento, ULList* usuario) {
    int entrada = 0;
    char* aux_s;
    char* responsavel;
    bool runChoice = false;
    Recurso* rec = Recurso_new();
    Usuario* user = Usuario_new();

    printf("Alocações pendentes que precisão da sua atenção!\n");
    printf("\n");

    beginR(alocado);
    int i;
    for(i = 0; i < alocado->size; i++) {
        printf("%d- %s\n", i, alocado->current->val->identificacao);
        nextR(alocado);
    }
    printf(">> ");

    scanf("%d", &entrada);
    getchar();

    moveAtR(entrada, alocado);

    mostrarRecursos(alocado->current->val);


    while (runChoice) {
        printf("Confimar esta alocação?\n1- Sim\t2- Não\n>> ");
        scanf("%d", &entrada);

        if (entrada == 1) {
            rec = removeR(alocado);
            user = rec->responsavel;
            user = findU(usuario, user->nome);
            if (user != 0) {
                if (!(user->emAndamento)) {
                    user->emAndamento = true;
                    rec->status = (char*)"Em Andamento";
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
}

void concluirAlocacoes(LList* emAndamento, LList* concluido, ULList* usuarios) {
    int entrada = 0;
    char aux_s[STRING_SIZE];
    Recurso* rec = Recurso_new();
    Usuario* user = Usuario_new();

    printf("Escolha um recurso:\n\n");

    beginR(emAndamento);
    int i;
    for(i = 0; i < emAndamento->size; i++) {
        printf("%d- %s\n", i, emAndamento->current->val->identificacao);
        nextR(emAndamento);
    }
    printf(">> ");

    scanf("%d", &entrada);
    getchar();

    moveAtR(entrada, emAndamento);

    rec = emAndamento->current->val;

    mostrarRecursos(rec);

    user = findU(usuarios, rec->responsavel->nome);

    printf("Cadastrar atividade\n");
    printf("Titulo da Atividade\n>> ");
    fgets(aux_s, sizeof(aux_s), stdin);
    getchar();

    rec->tituloAtiv = aux_s;

    printf("Descricao\n>> ");
    fgets(aux_s, sizeof(aux_s), stdin);
    getchar();

    rec->descricao = aux_s;

    if(user == 0) {
        msgError("Usuario não cadastrado");
    }
    else {
        if(user->acesso == BASICO) {
            msgError("Este usuario não pode alocar salas");
        }
        else {
            if(user->acesso == AVANCADO) {
                printf("Tipo da atividade\n1- Aula\n2- Apresentações\n3- Laboratório\n>> ");
                scanf("%d", &entrada);
                getchar();

                switch (entrada) {
                case 1:
                    rec->tipo = (char*)"Aula";
                    break;
                case 2:
                    rec->tipo = (char*)"Apresentação";
                    break;
                case 3:
                    rec->tipo = (char*)"Laboratório";
                    break;
                default:
                    break;
                }
            }
            else {
                rec->tipo = (char*)"Apresentação";
            }
        }
    }

    printf("Numero de participantes\n>> ");
    scanf("%d", &entrada);
    getchar();

    printf("Participantes:\n");
    int j;
    for(j = 0; j < entrada; j++) {
        printf("%d- ", j);
        fgets(aux_s, sizeof(aux_s), stdin);
        getchar();

        rec->participantes[j] = aux_s;
    }

    printf("Numero de materiais de apoio\n>> ");
    scanf("%d", &entrada);
    getchar();

    printf("Materiais:\n");
    int k;
    for(k = 0; k < entrada; k++) {
        printf("%d- ", k);
        fgets(aux_s, sizeof(aux_s), stdin);
        getchar();

        rec->materialApoio[k] = aux_s;
    }

    rec->status = (char*)"Concluído";

    appendR(rec, concluido);
}

void menuAlocar(LList* emProcesso, LList* alocado, LList* emAndamento, LList* concluido , ULList* usuario) {
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
            alocar(emProcesso, alocado, usuario);
            break;
        case 2:
            verificarAlocacoes(alocado, emAndamento, usuario);
            break;
        case 3:
            concluirAlocacoes(emAndamento, concluido, usuario);
            break;
        case 4:
            run = false;
            break;
        default:
            break;
        }
    }

}

void consulta(LList* emProcesso, LList* alocado, LList* emAndamento, LList* concluido , ULList* usuario) {
	int entrada = 0;
	Recurso* rec = Recurso_new();
	Usuario* user = Usuario_new();
	
	printf("Consulta:\n1- Por usuario\t2- Por recurso");
	scanf("%d", &entrada);
	getchar();
	
	if(entrada == 1) {
		begin(usuario);
		int i;
		for(i = 0; i < usuario->size; i++) {
			printf("%d- %s\n", i, usuario->current->val->identificacao);
			next(usuario);
		}
		
		printf(">> ");

		scanf("%d", &entrada);
		getchar();
		
		moveAt(entrada, user);
		user = user->current->val;
		
		mostrarUsuario(user);
	}
	else if (entrada == 2) {
		printf("Escolha um recurso:\n\n");

		beginR(emAndamento);
		beginR(emProcesso);
		beginR(alocado);
		beginR(concluido);
		int i,j,k,l;
		for(i = 0; i < emAndamento->size; i++) {
			printf("%d- %s\n", i, emAndamento->current->val->identificacao);
			nextR(emAndamento);
		}
		for(j = i; j < emProcesso->size; j++) {
			printf("%d- %s\n", j, emProcesso->current->val->identificacao);
			nextR(emProcesso);
		}
		for(k = j; k < alocado->size; k++) {
			printf("%d- %s\n", k, alocado->current->val->identificacao);
			nextR(alocado);
		}
		for(l = k; l < concluido->size; l++) {
			printf("%d- %s\n", l, concluido->current->val->identificacao);
			nextR(concluido);
		}
		
		printf(">> ");

		scanf("%d", &entrada);
		getchar();
		
		if(entrada < emAndamento->size) {
			moveAtR(entrada, emAndamento);
			rec = emAndamento->current->val;
		}
		else if(entrada >= emAndamento->size && entrada < emProcesso->size) {
			moveAtR(entrada, emProcesso);
			rec = emProcesso->current->val;
		}
		else if(entrada >= emProcesso->size && entrada < alocado->size) {
			moveAtR(entrada, alocado);
			rec = alocado->current->val;
		}
		else if(entrada >= alocado->size) {
			moveAtR(entrada, concluido);
			rec = concluido->current->val;
		}
		
		mostrarRecursos(rec);
	}
}

void relatorios(LList* emProcesso, LList* alocado, LList* emAndamento, LList* concluido , ULList* usuario) {

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
    scanf("%d", &entrada);

    switch(entrada) {
    case 1:
        menuAlocar(emProcesso, alocado, emAndamento, concluido, usuario);
        break;
    case 2:
        consulta(emProcesso, alocado, emAndamento, concluido, usuario);
        break;
    case 3:
        relatorios(emProcesso, alocado, emAndamento, concluido, usuario);
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
    bool run = true;

    while(run) {
        run = menuPrincipal();
    }

    return 0;
}

