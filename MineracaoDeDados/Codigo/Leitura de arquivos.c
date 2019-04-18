#include <stdio.h>
#include <stdlib.h>
#include <locale.h> 

/*Criação da estrutura de uma arvore */

struct No {
       char chave[50];
       struct No *esq, *dir;
};

typedef struct No *Arvore;

/*Objetivo da função é inserir elementos na árvore*/

Arvore inserir (char chaveAuxiliar[], Arvore arvore)
{      
       if (arvore == NULL) //Arvore nula, cria nova arvore
       {  arvore = (struct No *) malloc(sizeof (struct No));            
          strcpy(arvore->chave, chaveAuxiliar);/*copiar o valor da chave 
		                                        auxiliar na chave da arvore*/
          arvore->esq = NULL;
          arvore->dir = NULL;
		}             
       else if (chaveAuxiliar < arvore->chave) //chave da func < que a chave da arvore
       {       
	   	   arvore->esq = inserir(chaveAuxiliar, arvore->esq);
	   }
       else if (chaveAuxiliar > arvore->chave) //chave da func > que a chave da arvore
       {       
	   	   arvore->dir = inserir(chaveAuxiliar, arvore->dir);
	   }       
       else //chave da func == a chave da arvore
       {       
	   	   printf("Chave já existe");     
	   }
       
       return arvore;
}

/*Objetivo da função é pesquisarr elementos na arvore*/

int pesquisar (char ChaveAuxiliar[], Arvore arvore)
{      
       if (arvore == NULL)
       {  return -1; } //n achou
       else if (strcmp(ChaveAuxiliar, arvore->chave) < 0)
       {       return (pesquisar(ChaveAuxiliar, arvore->esq));	}
       else if (strcmp(ChaveAuxiliar, arvore->chave) > 0)
       {       return (pesquisar(ChaveAuxiliar, arvore->dir));	}       
       else 
       {       return 1;  //achou   }
}
}

/*Objetivo da função é processar as StopWords e inseri-las em uma arvore
 binária para otimizar a busca*/
 
 Arvore CarregarStopWords (char NomeArquivo[])
{
	FILE *file;
	char palavra[20];

    Arvore aux = NULL;

    file = fopen(NomeArquivo, "r");
	if (file == NULL)
	{ 
        printf("\n Não foi possivel abrir o arquivo '%s' \n\n", NomeArquivo); 
        system("pause");
    }
    else
    {
        while (!feof(file))
        {     
			fscanf(file," %s ", &palavra);
			//printf("%s \n", palavra); //mostrar as palavras processadas        
    		aux = inserir(palavra, aux);
        }
        
    }
	fclose(file);
    return aux;
}

/*Objetivo da função é remover as StopWords dos textos*/

void removeStopWords(char NomeArquivo[],char NomeNovoArquivo[], Arvore stopWords){
	
	FILE *file;
	FILE *file2;
	file = fopen(NomeArquivo, "r");
	char palavra[20];
	
	if (file == NULL)
	{ 
        printf("\n Não foi possivel abrir o arquivo '%s' \n\n", NomeArquivo); 
        system("pause");
    }
    else
    {
    	file2 = fopen(NomeNovoArquivo, "w");
        while (!feof(file))
        {     
			fscanf(file," %s ", &palavra);
			
			if (pesquisar(palavra, stopWords) == 1)
			{
				printf("");
			}
			else if(pesquisar(palavra,stopWords) == -1)
			{
				fputs(palavra, file2);
			}
			
			
        } 
    }
	
	fclose(file);
	fclose(file2);
}

int main()
{
	setlocale(LC_ALL,"portuguese");
	
	Arvore a;
	a= CarregarStopWords("palavras1.txt");
	removeStopWords("texto.txt","arqv1.txt",a);
	return 0;
}