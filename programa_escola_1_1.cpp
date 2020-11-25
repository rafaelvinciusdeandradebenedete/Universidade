#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "listaagenda.h"
#include <dirent.h>

typedef struct
{
	char nome[50];
	char periodo[1];
	char curso[20];
	char Horarios[30]; 
}reg;


int tamarq(FILE *arq)
 {
 	fseek(arq,0,SEEK_END);
 	return ftell(arq)/sizeof(reg);
 }

void relatorioord(FILE *arq)
{
	int x=0,y=0,h=0;
	char pessoa[50],periodo[2],curso[30],cont[2],status[2];
	arq=fopen("RelatorioOrdenado.txt","w");
	fprintf(arq,"     Nome                        Curso          Periodo        Status\n");
    fclose(arq);
	DIR *dir;
	char nome[260],nomeaux[50];
    struct dirent *lsdir;
	char aux[50]="./alunos/",aux2[50]="./alunos/";
    dir = opendir("./alunos/");
	setlocale(LC_ALL," ");
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        strcpy(nome,lsdir->d_name);
        strcpy(aux,aux2);
        strcat(aux,nome);
        
        arq=fopen(aux,"rb+");
        x=0;
        while (fscanf(arq, "%s", &nomeaux) == 1)
        {
        	cont[0]=nomeaux[0];
        	if(cont[0]=='/')
        	{
        		x++;
			}
			if(x==0)
			{
				strcpy(pessoa,nomeaux);
				x++;
			}
			if(y==1)
			{
				strcat(pessoa," ");
				strcat(pessoa,nomeaux);
			}
			if(x==1)
			{
				y=1;
			}
			if(x==2)
			{
				y=0;
			}
			if(x==2 && cont[0]!='/')
			{
				strcpy(curso,nomeaux);
			}
			if(x==3 && cont[0]!='/')
			{
				x++;
				strcpy(periodo,nomeaux);
			}
			if(x==7 && cont[0]!='/')
			{
				strcpy(status,nomeaux);
			}
			if(x==6)
			{
				x++;
			}
			if(x==5)
			{
				x++;
			}
			if(x==4)
			{
				x++;
			}
			
		}
		fclose(arq);
		arq=fopen("RelatorioOrdenado.txt","rb+");
		
		if(h==2)
		{
			fseek(arq,2,SEEK_END);
			fputs(pessoa,arq);
        	fseek(arq,2,SEEK_END);
        	fputs("\t\t\t",arq);
        	fputs(curso,arq);
        	fseek(arq,2,SEEK_END);
        	fputs("\t",arq);
            fputs(periodo,arq);
            fseek(arq,2,SEEK_END);
            fputs("\t\t",arq);
        	fputs(status,arq);
            fputc('\n',arq);
		}
        else
        {
        	h++;
		}
		fclose(arq);
		printf("\n");
		
    }
    closedir(dir);
	
}


int main(void)
{	
	
	reg aluno;
	int op;
	void cadastrar(FILE *);
	void cadastrarcurso(FILE *);
	void horarios(FILE *);
	void consultar(FILE *);
	void excluir(FILE *);
	int tamarq(FILE *);
	FILE *arq;
	
	setlocale(LC_ALL,"");
	
	arq = fopen("./alunos","rb+");
	   if (arq==0)
	   {
	   	CreateDirectory("alunos",NULL);
	   	
	   }
	fclose(arq);
   
   
   
   arq = fopen("./cursos","rb+");
   if (arq==0)
   {
   	CreateDirectory("cursos",NULL);
   }
   fclose(arq);
	
	
	arq = fopen("dados.dat","rb+");
   if (arq==0)
   {
   	arq= fopen("dados.dat","wb+");
   }

   
	
	do
	{
		system("cls");
		printf("\n===============AGENDA===============\n");
		printf("1.Cadastrar Aluno\n");
		printf("2.Cadastrar Novo Curso\n");
		printf("3.Inserir horarios das aulas\n");
		printf("4.Consultar\n");
		printf("5.Relatório\n");
		printf("6.Excluir\n");
		printf("7.Sair\n");
		printf("======================================\n");
		printf("Opcao:");
		scanf("%i",&op);
		switch(op)
		{
			case 1:
				cadastrar(arq);
				break;
			case 2:
				cadastrarcurso(arq);
				break;
			case 3:
				horarios(arq);
				break;
			case 4:
				consultar(arq);
				break;
			case 5:
				relatorioord(arq);
				break;
			case 6:
				excluir(arq);
				break;
			case 7:fclose(arq);
		}
	}while(op!=7);
}
	void cadastrar(FILE *arq)
	{
		int x,h;
		reg aluno;
		char confirma;
		char nome[50],curso[50],periodo[4];
		char aux[50]="./cursos/",aux2[50]="./alunos/";
		
		fflush(stdin);
		printf("Novo Periodo?<s/n>");
		scanf("%c",&confirma);
		if(toupper(confirma)== 'S')
		{
			h=1;
		}
		fflush(stdin);
		printf("Cadastrando novo Aluno:\n");
		printf("Nome:......");
		gets(aluno.nome);
		strcpy(nome,aluno.nome);
		
		
		printf("Período:..");
		fflush(stdin);
		gets(aluno.periodo);
		strcpy(periodo,aluno.periodo);
		
		printf("Curso:.....");
		gets(aluno.curso);
		strcpy(curso,aluno.curso);
		
		
		printf("\nConfirma <s/n>:");
		scanf("%c",&confirma);
		
		if(toupper(confirma)== 'S')
		{
			printf("\n gravando....\n");
			fseek(arq,0,SEEK_END);
			fwrite(&aluno,sizeof(reg),1,arq);
		}
		
		strcat(nome,".txt");
		strcat(aux2,nome);
	
		arq = fopen(aux2,"wb+");
		
		fputs(aluno.nome, arq);
		fputs(" / ",arq); 
		fputs(aluno.curso, arq);
		fputs(" / ",arq);
		fputs(periodo, arq);
		fputs(" º ",arq);
		
		fclose(arq);
		
		
		strcat(aux,curso);
		strcat(aux,"/");
		strcat(aux,periodo);
		strcat(aux,"/");
		strcat(periodo,".txt");
		strcat(aux,periodo);
		printf("%s",aux);
		arq=fopen(aux,"a");
		fclose(arq);
		if(h==0)
		{
			arq = fopen(aux,"rb+");
		}
		else
		{
			arq=fopen(aux,"wb+");
			fclose(arq);
			arq = fopen(aux,"rb+");
			h=0;
		}
		fseek(arq,0,SEEK_END);
		fputs(aluno.nome,arq);
		fputs(" /",arq);
		fputc('\n',arq);
	
		fclose(arq);
	}
	
	
int cadastrarcurso(FILE *arq)
    {
        int p,x;
        char aux[50]="./cursos/",aux2[50]="./cursos/";
        char curso[30];
        printf("Entre com o novo Curso:");
        fflush(stdin);
        gets(curso);
        printf("entre com a quantidade de períodos:");
        scanf("%i",&p);
        strcat(aux,curso);
        if(CreateDirectory(aux,NULL))
        {
            strcat(aux,"/");
            for(x=0;x<p;x++)
            {
                strcpy(aux2,aux);
                if(x==0)
                {
                    strcat(aux2,"1");
                }
                if(x==1)
                {
                    strcat(aux2,"2");
                }
                if(x==2)
                {
                    strcat(aux2,"3");
                }
                if(x==3)
                {
                    strcat(aux2,"4");
                }
                if(x==4)
                {
                    strcat(aux2,"5");
                }
                if(x==5)
                {
                    strcat(aux2,"6");
                }
                if(x==6)
                {
                    strcat(aux2,"7");
                }
                if(x==7)
                {
                    strcat(aux2,"8");
                }
                if(x==8)
                {
                    strcat(aux2,"9");
                }
                if(x==9)
                {
                    strcat(aux2,"10");
                }
                CreateDirectory(aux2,NULL);
            }
            printf("Diretorio criado com sucesso");
        }
        else
        {
            printf("Erro ao criar novo Curso");
        }
        system("pause");
    }
	
	void criarhorario(FILE *arq,char aux[50])
	{
		reg aluno;
		char x[2],d[2];
		int y=0,dia=0, confirma=0;
		x[0]='s';
		d[0]='s';
		fputs("Segunda-Feira: ",arq);
		while(dia!=5)
		{
			
			if(dia==0 && confirma==0)
			{
				printf("Aulas na Segunda-Feira?<s/n>");
				scanf(" %c",&d[0]);	
			}
			if(dia==1 && confirma==0)
			{
				printf("Aulas na Terça-Feira?<s/n>");
				scanf(" %c",&d[0]);
			}
			if(dia==2 && confirma==0)
			{
				printf("Aulas na Quarta-Feira?<s/n>");
				scanf(" %c",&d[0]);
			}
			if(dia==3 && confirma==0)
			{
				printf("Aulas na Quinta-Feira?<s/n>");
				scanf(" %c",&d[0]);
			}
			if(dia==4 && confirma==0)
			{
				printf("Aulas na Sexta-Feira?<s/n>");
				scanf(" %c",&d[0]);
			}
			
			if(d[0]=='s')
			{
				confirma=1;
				printf("Entre com o horário da %iª aula:",y+1);
				y++;
				fflush(stdin);
				gets(aluno.Horarios);
				fputs(aluno.Horarios,arq);
				fputc(' ',arq);
				printf("Entre com a Materia:");
				fflush(stdin);
				gets(aluno.Horarios);
				fputs(aluno.Horarios,arq);
				fputc(' ',arq);
				printf("Entre com o professor:");
				fflush(stdin);
				gets(aluno.Horarios);
				fputs(aluno.Horarios,arq);
				fputc(' ',arq);
				printf("Adicionar mais um horario?<s/n>");
				scanf(" %c",&x[0]);
				if(x[0]=='s')
				{
					fputs(" / ",arq);
				}
				if(x[0]=='n')
				{
					confirma=0;
					dia++;
					if(dia != 5)
						fputs(" * ",arq);
					y=0;
					fputc('\n',arq);
					if(dia==1)
					{
						fputs("Terça-Feira: ",arq);
					}
					if(dia==2)
					{
						fputs("Quarta-Feira: ",arq);
					}
					if(dia==3)
					{
						fputs("Quinta-Feira: ",arq);
					}
					if(dia==4)
					{
						fputs("Sexta-Feira: ",arq);
					}
				}
			}
			if(d[0]=='n')
			{
				dia++;
				if(dia != 5)
					fputs(" * ",arq);
				y=0;
				fputc('\n',arq);
				if(dia==1)
				{
					fputs("Terça-Feira: ",arq);
				}
				if(dia==2)
				{
					fputs("Quarta-Feira: ",arq);
				}
				if(dia==3)
				{
					fputs("Quinta-Feira: ",arq);
				}
				if(dia==4)
				{
					fputs("Sexta-Feira: ",arq);
				}
			}
		}
	}
	
	void horarios(FILE *arq)
	{
		char aux[50]="./cursos/";
		char periodo[2];
		char curso[30];
		reg aluno;
		fflush(stdin);
		printf("Entre com o Curso:");
		gets(curso);
		fflush(stdin);
		printf("Entre com o Periodo:");
		gets(periodo);
		
		strcat(aux,curso);
		strcat(aux,"/");
		strcat(aux,periodo);
		strcat(aux,"/horarios.txt");
		arq=fopen(aux,"wb+");
		
		criarhorario(arq,&aux[50]);
	
		fclose(arq);
	}
	
int confirma(FILE *arq,char nome[50])
{
	int x=0;
	char c,aux[50]="./alunos/";
	strcat(aux,nome);
	strcat(aux,".txt");
	arq=fopen(aux,"rb+");
	while (!feof(arq))
	{
		fscanf(arq,"%c",&c);
		if(c=='*')
		{
			x=1;
		}
	}
	fclose(arq);
	if(x==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void excluir(FILE *arq)
{
	char nome[50],aux[50]="./alunos/";
	fflush(stdin);
	printf("Entre com o nome do aluno a ser deletado:");
	gets(nome);
	strcat(aux,nome);
	strcat(aux,".txt");
	arq=fopen(aux,"rb+");
	fseek(arq,2,SEEK_END);
	fputs(" *",arq);
	fclose(arq);
	printf("Aluno deletado\n");
	system("pause");
}

	
void consultar(FILE *arq)
{
	reg aluno;
	int op,y=0,x=-1,h=0;
	char nome[50],aux[50]="./alunos/",aux2[50]="./alunos/";
	char auxc[50]="./cursos/",auxc2[50]="./cursos/",cont[2];
	char periodos[5],curso[20];
	do
	{
		system("cls");
		printf("\n=============FILTROS===============\n");
		printf("1.Procurar por nome\n");
		printf("2.Procurar por curso\n");
		printf("3.Sair\n");
		printf("=====================================\n");
		printf("Opcao:");
		scanf("%i",&op);
		
		switch(op)
		{
			case 1:
				h=0;
				y=0;
				fflush(stdin);
				
				strcpy(aux,aux2);
				strcpy(auxc,auxc2);
				
				printf("Digite o nome:");
				gets(nome);
				
				if(confirma(arq,nome)==1)
				{
					printf("Aluno Não Matriculado\n");
				}
				else
                {
                    strcat(aux,nome);
                    strcat(aux,".txt");

                       if (!(arq= fopen(aux,"rb+"))){
                        printf("Erro! Impossivel abrir o arquivo!\n");
                      }

                    while (fscanf(arq, "%s", &nome) == 1)
                    {
                        if(h==0)
                        {
                            printf("Nome: ");
                            h=1;
                        }

                        if(h==2)
                        {
                            printf("Curso: ");
                            h=3;
                        }

                        if(h==4)
                        {
                            printf("Periodo: ");
							h=5;                  
						}
                        cont[0]=nome[0];
                        if(cont[0]!='/')
                        {
                            printf("%s ", nome);
                        }

                        if(y==1){
                                strcpy(curso,nome);
                                y=2;
                            }
                            if(y==3){
                                strcpy(periodos,nome);
                                y=4;
                            }
                        if(cont[0] == '/')
                        {
                            h++;
                            printf("\n");
                            y++;
                            if(y==5)
                            {
                                printf("\n\n");
                                printf("\t");
                                y=0;
                            }
                        }  
                    }
                    printf("\n");
					strcat(auxc,curso);
					strcat(auxc,"/");
					strcat(auxc,periodos);
					strcat(auxc,"/");
					strcat(auxc,"horarios.txt");
					fclose(arq);
					arq=fopen(auxc,"rb+");
					printf("\n==========================ESCALAS=============================\n");
					printf("\n  		         |HORÁRIOS|   |MATÉRIAS|  |PROFESSORES|		\n");
					printf("\n*      ");
					while (fscanf(arq, "%s", &nome) == 1){
						cont[0]=nome[0];
						if(cont[0] == '/')
						{
							printf("\n");
							printf("\t  ");
							printf("                  ");
						}
						if(cont[0] == '*')	
						{ 
							
							printf("\n\n");
						}
							if(cont[0]!='/')
                        {
                            printf("%s       ", nome);
                        }

					}
                }
					printf("\n");
					system("pause");
				break;
			case 2:
				fflush(stdin);
				
				strcpy(auxc,auxc2);
				
				printf("Digite o curso:");
				gets(curso);
				printf("Digite o periodos:");
				gets(periodos);
				strcat(auxc,curso);
				strcat(auxc,"/");
				strcat(auxc,periodos);
				strcat(auxc,"/");
				strcat(periodos,".txt");
				strcat(auxc,periodos);
				arq=fopen(auxc,"rb+");
				printf("\tALUNOS:\n");
				printf("\t");
				y=0;
				while (fscanf(arq, "%s", &nome) == 1)
					{	
					cont[0]=nome[0];
					if (cont [0]!='/')
					{
						printf("%s ", nome);
					}
					if(cont[0] == '/')
					{
							printf("\n");
							printf("\t");
					}
					}
				printf("Aperte qualquer botao");
				getchar();
				break;
				}
		}while(op!=3);
	}
