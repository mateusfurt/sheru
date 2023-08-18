#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void tiraenter(char texto[]){
    int tam;
    tam = strlen(texto);
    if(texto[tam-1]=='\n'){
            texto[tam-1]='\0';
        }

}

int main(int argc, char const *argv[])
{
    int tam, valido, i, teste;
    char texto[600], args[3][605];
    char buf[500];
    char caminho[500];
    struct dirent *entry;
    /*CHAMADA DE SISTEMA GETOGIN*/
    char *user = getlogin();
    size_t size = 500;
    /*CHAMADA DE SISTEMA GETCWD*/
    char *getcwd(char *buf, size_t size);
    system("clear");
    printf("\033[1;35m");
    printf("      ::::::::  :::    ::: :::::::::: :::::::::  :::    :::\n");
    printf("    :+:    :+: :+:    :+: :+:        :+:    :+: :+:    :+: \n");
    printf("   +:+        +:+    +:+ +:+        +:+    +:+ +:+    +:+  \n");
    printf("  +#++:++#++ +#++:++#++ +#++:++#   +#++:++#:  +#+    +:+         |\\      _,,,---,,_\n");
    printf("        +#+ +#+    +#+ +#+        +#+    +#+ +#+    +#+    ZZZzz /,`.-'`'    -.  ;-;;,_\n");
    printf("#+#    #+# #+#    #+# #+#        #+#    #+# #+#    #+#          |,4-  ) )-,_. ,\\ (  `'-'\n");
    printf("########  ###    ### ########## ###    ###  ########           '---''(_/--'  `-'\\_)   \n\n");
    printf("Desenvolvido por: Mateus Furtado e Nathalia Noemia\n\n");
    printf("\033[0m");

    while (1)
    {
        valido = 0;
        printf("\033[1;32m");
        /*CHAMADA DE SISTEMA GETCWD*/
        printf("%s@Sheru \033[1;33m ~%s\033[0m$ ", user, getcwd(buf, size));
        printf("\033[0m");
        
        fgets(texto, sizeof(texto), stdin);
        tiraenter(texto);
        char *token = strtok(texto, " ");
        for (i = 0; token != NULL; i++)
        {
            strcpy(args[i], token);
            token = strtok(NULL, " ");
        }
        tam = i;
        //printf("tamanho%d", tam);
        //printf("ESCREVEU: %s\n", texto);
        if (strcmp(texto, "") == 0)
        {
            valido = 1;
        }
        
        if (strcmp(args[0], "ls") == 0)
        {
            /*CHAMADA DE SISTEMA OPENDIR*/
            DIR *dir = opendir(getcwd(buf, size));
            if (dir == NULL)
            {
                printf("chamada de sistema falhou\n");
            }
            /*CHAMADA DE SISTEMA READDIR*/
            while ((entry = readdir(dir)) != NULL) {
                
                if(entry->d_name[0] != '.'){
                    printf("%s ", entry->d_name);
                }
            }
            printf("\n");
            closedir(dir);
            valido = 1;
        }
        if (strcmp(args[0], "cd") == 0 && tam == 1)
        {
            strcpy(caminho, "/home/");
            strcat(caminho, user);
            /*CHAMADA DE SISTEMA CHDIR*/
            if (chdir(caminho) == -1)
            {
                printf("chamada de sistema falhou\n");
            }
            
            valido = 1;
        }
        if (strcmp(args[0], "cd") == 0 && tam == 2)
        {
            if (strcmp(args[1], "/")==0)
            {
                /*CHAMADA DE SISTEMA CHDIR*/
                if (chdir("/") == -1)
            {
                printf("chamada de sistema falhou\n");
            }
            }
            
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            if (chdir(caminho) == -1)
            {
                printf("chamada de sistema falhou\n");
            }
            valido = 1;
        }
        
        
        
        if (strcmp(args[0], "pwd") == 0)
        {
            /*CHAMADA DE SISTEMA GETCWD*/
            if (getcwd(buf, size) == NULL)
            {
                printf("chamada de sistema falhou\n");
            }
            
            printf("%s\n", buf);
            valido = 1;
        }
        
        if (strcmp(args[0], "exit") == 0)
        {
            puts("Saindo...");
            /*CHAMADA DE SISTEMA EXIT*/
            exit(0);
        }
        if (valido == 0)
        {
            printf("%s: comando nao encontrado\n", args[0]);
            
        }
        
    }
    

    return 0;
}
