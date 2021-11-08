#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>  /* Funcao exit    */
#include <ctype.h>   /* Funcao toupper */

#define FICH "Dados.Dat"  /* Ficheiro  com os Dados */

#define OP_INSERIR   '1'
#define OP_ALTERAR   '2'
#define OP_APAGAR    '3'
#define OP_LISTAR    '4'
#define OP_PESQUISAR '5'

#define OP_SAIR      '0'

#define OP_PESQ_IDADE '1'
#define OP_PESQ_NOME  '2'

char *MainMenu[]={
   "1. Inserir Registo",
   "2. Alterar Registo",
   "3. Apagar Registo",
   "4. Listar Registos",
   "5. Pesquisas",
   "0. Sair",
   NULL   /* Acabaram as Opçoes */
  };

char *PesqMenu[]={
   "1. Pesquisar por Intervalo de Idades",
   "2. Pesquisar por Nome",
   "0. Voltar",
   NULL   /* Acabaram as Opçoes */
  };

FILE *fp;  /* Variavel Global pois e' util ao longo do prog. */

typedef struct
{
  char Nome[30+1];
  int Idade;
  float Salario;
  char Status; /* '*' Indica que o registo esta apagado */
} PESSOA;


void Mensagem(char *msg);


/* Le os dados de um registo introduzidos pelo utilizador */

void Ler_Pessoa(PESSOA *p)
{
  printf("Nome    : "); gets(p->Nome);
  printf("Idade   : "); scanf("%d",&p->Idade);
  printf("Salario : "); scanf("%f",&p->Salario);
  p->Status=' ';
  fflush(stdin);
}

/* Mostra no ecra, os dados existente no registo */

void Mostrar_Pessoa(PESSOA p)
{
  printf("%-30s  %3d  %10.2f\n",p.Nome,p.Idade,p.Salario);
}

/* Adiciona uma Pessoa ao Ficheiro */
void Adicionar_Pessoa(PESSOA p)
{
  fseek(fp, 0L, SEEK_END);
  if (fwrite(&p,sizeof(p),1,fp)!=1)
   Mensagem("Adicionar Pessoa: Falhou a escrita do Registo");
}

/* Coloca um mensagem no ecran */
void Mensagem(char *msg)
{
  printf(msg);
	getchar();
}

/*
 * Verifica se o Ficheiro ja existe. Se nao existir cria-o
 * Se ja existir, abre-o em Modo de Leitura e Escrita (r+b)
 */

void Inic()
{
  fp=fopen(FICH,"r+b"); /* Tentar Abrir */
  if (fp==NULL)
   {
    fp =fopen(FICH,"w+b");   /* Criar o Ficheiro */
    if (fp==NULL)
      {
       fprintf(stderr,"ERRO FATAL: Impossível Criar o Ficheiro de Dados\n");
       exit(1);
      }
   }
}

/*
 * Faz um Menu Simples com as opçoes do vector de Strings.
 * Selecciona a Opçao, usando o 1º carácter de cada string.
 * Devolve o primeiro carácter da opçao
 */
char Menu(char *Opcoes[])
{  int i;
  char ch;

  while (1)
  {  /* Cls */
   printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    for (i=0; Opcoes[i]!=NULL; i++)
     printf("\t\t%s\n\n",Opcoes[i]);

    printf("\n\n\t\tOpcao: ");
    ch = getchar(); fflush(stdin);
    for (i=0; Opcoes[i]!=NULL; i++)
     if (Opcoes[i][0]==ch)
      return ch;
   }
}

void Inserir_Pessoa()
{ PESSOA x;
  Ler_Pessoa(&x);
  Adicionar_Pessoa(x);
}

void Alterar_Pessoa()
{ PESSOA x;
  long int n_reg;
  printf("Qual o Nº do Registo: ");
  scanf("%ld", & n_reg);fflush(stdin);
  if (fseek(fp,(n_reg-1)*sizeof(PESSOA),SEEK_SET)!=0)
   {
    Mensagem("Registo Inexistente ou Problemas no posicionamento!!!");
    return;
   }
  if (fread(&x,sizeof(PESSOA),1,fp)!=1)
   {
    Mensagem("Problemas na Leitura do Registo!!!");
    return;
   }

  if (x.Status=='*')
   {
    Mensagem("Um Registo Apagado nao pode ser alterado!!!\n\n");
    return;
   }

  printf("\n\nDados Actuais\n\n");
  Mostrar_Pessoa(x);
  printf("\n\nNovos Dados\n\n");
  Ler_Pessoa(&x);

  // Recuar um Registo no Ficheiro
  fseek(fp,-(long) sizeof(PESSOA),SEEK_CUR);
  // Reescrever o Registo;
  fwrite(&x,sizeof(PESSOA),1,fp);
  fflush(fp); /* Despejar os Dados no Disco Rigido */
}

void Apagar_Pessoa()
{ PESSOA x;
  long int n_reg;
  char resp;

  printf("Qual o Nº do Registo: ");
  scanf("%ld", & n_reg);fflush(stdin);
  if (fseek(fp,(n_reg-1)*sizeof(PESSOA),SEEK_SET)!=0)
   {
    Mensagem("Registo Inexistente ou Problemas no posicionamento!!!");
    return;
   }
  if (fread(&x,sizeof(PESSOA),1,fp)!=1)
   {
    Mensagem("Problemas na Leitura do Registo!!!");
    return ;
   }

  if (x.Status=='*')
   {
    Mensagem("Registo ja esta Apagado!!!\n\n");
    return;
   }

  printf("\n\nDados Actuais\n\n");
  Mostrar_Pessoa(x);
  printf("\n\nApagar o Registo (s/n)???: "); resp = getchar();
  fflush(stdin);
  if (toupper(resp)!='S') return;

  x.Status='*';
  // Recuar um Registo no Ficheiro
  fseek(fp,-(long) sizeof(PESSOA),SEEK_CUR);
  // Reescrever o Registo;
  fwrite(&x,sizeof(PESSOA),1,fp);
  fflush(fp); /* Despejar os Dados no Disco Rigido */
}

void Listar()
{ long int N_Linhas =0;
  PESSOA reg;
  rewind(fp);
  while(1)
   {
    if (fread(&reg,sizeof(reg),1,fp)!=1) break;/* Sair do Ciclo */
    if (reg.Status=='*') continue ;  /* Passa ao proximo */
    Mostrar_Pessoa(reg);
    N_Linhas++;
    if (N_Linhas%20==0)
      Mensagem("PRIMA <ENTER> para continuar . . . ");
   }
 Mensagem("\n\nPRIMA <ENTER> para continuar . . . "); /* No fim da Listagem */
}

void Pesquisar_Idades(int ini, int fim)
{ PESSOA reg;
  rewind(fp);

  while (fread(&reg,sizeof(PESSOA),1,fp))
   if (reg.Status!='*' && reg.Idade>=ini && reg.Idade<=fim)
    Mostrar_Pessoa(reg);

 Mensagem("\n\nPRIMA <ENTER> para continuar . . . "); /* No fim da Listagem */
}

void Pesquisar_Nome(char *s)
{ PESSOA reg;
  rewind(fp);

  while (fread(&reg,sizeof(PESSOA),1,fp))
   if (reg.Status!='*' && strstr(reg.Nome,s))
    Mostrar_Pessoa(reg);

 Mensagem("\n\nPRIMA <ENTER> para continuar . . . "); /* No fim da Listagem */
}



main()
{
	char  Opcao;
	Inic();
	while ((Opcao=Menu(MainMenu))!=OP_SAIR)
	 switch(Opcao)
    {  case OP_INSERIR: Inserir_Pessoa(); break;
      case OP_ALTERAR: Alterar_Pessoa(); break;
      case OP_APAGAR:  Apagar_Pessoa(); break;
      case OP_LISTAR:  Listar(); break;
      case OP_PESQUISAR:
				while((Opcao=Menu(PesqMenu))!=OP_SAIR)
					switch (Opcao)
           {
            case OP_PESQ_IDADE:
              { int n1,n2;
               printf("Qual o intervalo de Idades: ");
               scanf("%d%d",&n1,&n2);fflush(stdin);
               Pesquisar_Idades(n1,n2);
                      break;
              }
            case OP_PESQ_NOME:
              { char string[BUFSIZ+1];
               printf("Qual o Nome a Procurar: ");
               gets(string);fflush(stdin);
               Pesquisar_Nome(string);
              }
           }
    }
}
