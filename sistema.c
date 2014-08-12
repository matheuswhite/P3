#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BASICO 1
#define INTERMEDIARIO 2
#define AVANCADO 3
#define TOTAL 4

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

UNode* UNode_new();
void initUNode();
ULList* ULList_new();
void initULList(ULList* list);
void append(Usuario* it, ULList* list);
void next(ULList* list);
void prev(ULList* list);
void begin(ULList* list);
void end(ULList* list);
void moveAt(int pos, ULList* list);
Usuario* removeU(ULList* list);
bool findU(ULList* list, char* id);


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

Node* Node_new();
void initNode();
LList* LList_new();

void initLList(LList* list);
void appendR(Recurso* it, LList* list);
void nextR(LList* list);
void prevR(LList* list);
void beginR(LList* list);
void endR(LList* list);
void moveAtR(int pos, LList* list);
Recurso* removeR(LList* list);
bool findR(LList* list, char* id);

/**********************************************/
/***********Linked*List*Recursos***************/
/**********************************************/

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
	LList* historicoRecurso;
	char* funcao;
	int acesso;
	bool emAndamento;
}Usuario;

typedef struct {
	char* identificacao;
	char** participantes;
	char** materialApoio;
	char* tipo
	DataHora* inicio;
	DataHora* fim;
	Usuario* responsavel;
	char* status;
}Recurso;

/**********************************************/
/*******************Structs********************/
/**********************************************/

void msgError(const char* error) {
    printf("Error: %s \n", error);
}

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
    recurso->inicio->hora->minuto = min;

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
    recurso->fim->hora->minuto = min;

	
	printf("Responsável\n>> ");
	fgets(aux_s, sizeof(aux_s), stdin);

	if (!(findU(usuarios, aux_s))) {
		printf("Usuario não cadastrado!\n");
		cadastrarUsuario(usuarios);
	}

    //fazer
    recurso->responsavel = usuarios->current

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
}

void concluirAlocacoes(LList* emAndamento, LList* concluido, ULList* usuarios) {
    int entrada = 0;
    char* aux_s;
    Atividade* ativ = Atividade_new(); 
    
    printf("Escolha um recurso:\n\n");
    
    beginR(emAndamento);
	for(int i = 0; i < getSizeR(emAndamento); i++) {
		printf("%d- %s\n", i, getId(getCurrentR(emAndamento)));
		nextR(emAndamento);
	}
	printf(">> ");
	
	scanf("%d", &entrada);
	getchar();

	moveAtR(entrada, emAndamento);

	mostrarRecursos(getCurrentR(emAndamento));

    /*char* titulo;
	char** participantes;
	char* info;
	char** materialApoio;
	int numMaterial;
	int numParticipantes;
	char* tipo;*/

    printf("Cadastrar atividade\n");
    printf("Titulo\n>> ");
    fgets(aux_s*, sizeof(aux_s), stdin);
    
    printf("Descricao\n>> ");
    fgets(aux_s, sizeof(aux_s), stdin);
    
    printf("Tipo da atividade\n>> ");
    fgets();
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

