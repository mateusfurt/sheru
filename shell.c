#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>

void tiraenter(char texto[]){
    int tam;
    tam = strlen(texto);
    if(texto[tam-1]=='\n'){
            texto[tam-1]='\0';
        }

}

int main(int argc, char const *argv[])
{
    int tam, valido, i, teste, j, k;
    char texto[600], args[3][605], conteudo[5000];
    char buf[500];
    char caminho[500];
    struct dirent *entry;
    /*CHAMADA DE SISTEMA GETLOGIN*/
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

        /*##################################################################*/

        fgets(texto, sizeof(texto), stdin);
        tiraenter(texto);
        char *token = strtok(texto, " ");
        for (i = 0; token != NULL; i++)
        {
            strcpy(args[i], token);
            token = strtok(NULL, " ");
        }
        tam = i;
        
        /*##################################################################*/

        if (strcmp(texto, "") == 0)
        {
            valido = 1;
        }

        /*##################################################################*/

        if (strcmp(args[0], "mkdir") == 0 && tam == 2)
        {
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            /*CHAMADA DE SISTEMA MKDIR*/
            if (mkdir(caminho, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) < 0)
            {
                printf("nao foi possivel criar diretorio\n");
            }
            
            valido = 1;
        }

        /*##################################################################*/

        if (strcmp(args[0], "ls") == 0 && tam == 1)
        {
            /*CHAMADA DE SISTEMA OPENDIR e GETCWD*/
            DIR *dir = opendir(getcwd(buf, size));
            if (dir == NULL)
            {
                printf("chamada de sistema falhou\n");
            }else{
                /*CHAMADA DE SISTEMA READDIR*/
                while ((entry = readdir(dir)) != NULL) {
                    
                    if(entry->d_name[0] != '.'){
                        if (entry->d_type == 4)
                        {
                            printf("\033[1;34m");
                        }
                        printf("%s   ", entry->d_name);
                        printf("\033[1;0m");
                    }
                }
                printf("\n");
                /*CHAMADA DE SISTEMA CLOSEDIR*/
                closedir(dir);
            }
            
            valido = 1;
        }

        /*##################################################################*/

        if (strcmp(args[0], "ls") == 0 && strcmp(args[1], "-a") == 0 && tam == 2)
        {
            /*CHAMADA DE SISTEMA OPENDIR e GETCWD*/
            DIR *dir = opendir(getcwd(buf, size));
            if (dir == NULL)
            {
                printf("chamada de sistema falhou\n");
            }else{
                /*CHAMADA DE SISTEMA READDIR*/
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_type == 4)
                        {
                            printf("\033[1;34m");
                        }
                    
                    printf("%s   ", entry->d_name);
                    printf("\033[1;0m");
                }
                printf("\n");
                /*CHAMADA DE SISTEMA CLOSEDIR*/
                closedir(dir);
            }
            
            valido = 1;
        }

        /*##################################################################*/

        if (tam > 1 && strcmp(args[0], "ls") == 0 && (strcmp(args[1], "-l") == 0 || strcmp(args[2], "-l") == 0))
        {
            /*CHAMADA DE SISTEMA OPENDIR e GETCWD*/
            DIR *dir = opendir(getcwd(buf, size));
            if (dir == NULL)
            {
                printf("chamada de sistema falhou\n");
            }else{
                /*CHAMADA DE SISTEMA READDIR*/
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(args[1], "-a") == 0 || strcmp(args[2], "-a") == 0)
                {
                    /*CHAMADA DE SISTEMA GETCWD*/
                    strcpy(caminho, getcwd(buf, size));
                    strcat(caminho, "/");
                    strcat(caminho, entry->d_name);
                    
                    
                    struct stat file_stat;
                    /*CHAMADA DE SISTEMA STAT*/
                    if (lstat(caminho, &file_stat) == 0) {
                        printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
                        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
                        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");

                        printf(" %ld", (long)file_stat.st_nlink);

                        struct passwd *pw = getpwuid(file_stat.st_uid);
                        struct group *gr = getgrgid(file_stat.st_gid);
                        printf(" %s %s", pw->pw_name, gr->gr_name);

                        printf(" %lld", (long long)file_stat.st_size);

                        // Data de modificação
                        char time_str[100];
                        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                        printf(" %s", time_str);

                        printf(" %s ", entry->d_name);

                        printf("\n");
                    }
                }else
                {
                    /*CHAMADA DE SISTEMA GETCWD*/
                    strcpy(caminho, getcwd(buf, size));
                    strcat(caminho, "/");
                    strcat(caminho, entry->d_name);
                    struct stat file_stat;
                    /*CHAMADA DE SISTEMA STAT*/
                    if (lstat(caminho, &file_stat) == 0) {
                        if(entry->d_name[0] != '.'){
                        printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
                        printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
                        printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
                        printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");

                        printf(" %ld", (long)file_stat.st_nlink);

                        struct passwd *pw = getpwuid(file_stat.st_uid);
                        struct group *gr = getgrgid(file_stat.st_gid);
                        printf(" %s %s", pw->pw_name, gr->gr_name);

                        printf(" %lld", (long long)file_stat.st_size);

                        // Data de modificação
                        char time_str[100];
                        strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
                        printf(" %s", time_str);

                        printf(" %s ", entry->d_name);

                        printf("\n");
                    }
                    }
                    
                }
            }
            /*CHAMADA DE SISTEMA CLOSEDIR*/
            closedir(dir);
            }
            valido = 1;
        }

        /*##################################################################*/

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
        
        /*##################################################################*/

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

        /*##################################################################*/

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
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            /*CHAMADA DE SISTEMA CHDIR*/
            if (chdir(caminho) == -1)
            {
                printf("chamada de sistema falhou\n");
            }
            valido = 1;
        }

        /*##################################################################*/

        if (strcmp(args[0], "mv") == 0 && tam == 3)
        {
            int origem, destino;
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[2]);
            /*CHAMADA DE SISTEMA OPEN*/
            destino = open (caminho,  O_WRONLY | O_CREAT | O_TRUNC, 0755);
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            /*CHAMADA DE SISTEMA OPEN*/
            origem = open(caminho, O_RDONLY);
            if (origem<0||destino<0)
            {
                printf("erro ao abrir arquivo\n");
            }else{
                /*CHAMADA DE SISTEMA READ*/
                read(origem, conteudo, 5000);
                /*CHAMADA DE SISTEMA WRITE*/
                write(destino, conteudo, strlen(conteudo));
                /*CHAMADA DE SISTEMA UNLINK*/
                unlink(caminho);
                
                
            }
            /*CHAMADA DE SISTEMA CLOSE*/
            close(destino);
            close(origem);
            valido =1;
        }
        if (strcmp(args[0], "mv") == 0 && tam < 3)
        {
            printf("parametros insuficientes\n");
            valido = 1;
        }
        

        /*##################################################################*/

        if (strcmp(args[0], "rm") == 0 && tam == 2)
        {
            int erro = 0;
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            /*CHAMADA DE SISTEMA UNLINK*/
            
            if (unlink(caminho)<0) erro++;
            /*CHAMADA DE SISTEMA RMDIR*/
            if(rmdir(caminho)<0) erro++;
            if(erro == 2)printf("nao foi possivel remover\n");
            valido = 1;
        }
        if (strcmp(args[0], "rm") == 0 && tam < 2)
        {
            printf("parametros insuficientes\n");
            valido = 1;
        }

        /*##################################################################*/

        if (strcmp(args[0], "cp") == 0 && tam == 3)
        {
            int origem, destino;
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[2]);
            /*CHAMADA DE SISTEMA OPEN*/
            destino = open (caminho,  O_WRONLY | O_CREAT | O_TRUNC, 0755);
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            /*CHAMADA DE SISTEMA OPEN*/
            origem = open(caminho, O_RDONLY);
            if (origem< 0 || destino<0)
            {
                printf("erro ao abrir arquivo\n");
            }else{
                /*CHAMADA DE SISTEMA READ*/
                read(origem, conteudo, 5000);
                write(destino, conteudo, strlen(conteudo));
                /*CHAMADA DE SISTEMA CLOSE*/
                close(destino);
                close(origem);
            }
            valido = 1;
        }
        if (strcmp(args[0], "cp") == 0 && tam < 3)
        {
            printf("parametros insuficientes\n");
            valido = 1;
        }

        /*##################################################################*/

        if(strcmp(args[0], "cat") == 0 && tam == 2){
            int arquivo;
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            /*CHAMADA DE SISTEMA OPEN*/
            arquivo = open(caminho, O_RDONLY);
            if (arquivo < 0){
                printf("erro ao abrir arquivo\n");
            }else
            {
                /*CHAMADA DE SISTEMA READ*/
                read(arquivo, conteudo, 5000);
                printf("%s\n", conteudo);
            }
            /*CHAMADA DE SISTEMA CLOSE*/
            close(arquivo);
            valido = 1;
        }
        if (strcmp(args[0], "cat") == 0 && tam < 2)
        {
            printf("parametros insuficientes\n");
            valido = 1;
        }

        /*##################################################################*/

        if (strcmp(args[0], "sort") == 0 && tam == 2)
        {
            int arquivo, count = 1, menor;
            /*CHAMADA DE SISTEMA GETCWD*/
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            /*CHAMADA DE SISTEMA OPEN*/
            arquivo = open(caminho, O_RDONLY);
            if (arquivo<0)
            {
                printf("erro ao abrir arquivo\n");
            }else
            {
                /*CHAMADA DE SISTEMA READ*/
            read(arquivo, conteudo, 5000);
            for ( i = 0; i < strlen(conteudo); i++)
            {
                if (conteudo[i]=='\n')
                {
                    count++;
                }
                
            }
            char **linhas = (char **)malloc(count * sizeof(char*));
            for(int i = 0; i < count; i++) linhas[i] = (char *)malloc(500 * sizeof(char));;
            for (i = 0; i < count; i++)
            for(int i = 0; i < count; i++) strcpy(linhas[i], " ");
            char *token = strtok(conteudo, "\n");
            for (i = 0; token != NULL; i++)
            {
                strcpy(linhas[i], token); 
                token = strtok(NULL, "\n");
            }
            count = i;  
            /*--*/
            char tmp[500];
            for (i = 0; i < count-1; i++) {
                menor = i;
                for (j = i + 1; j < count; j++) {
                if (strcmp(linhas[j], linhas[menor]) < 0) {
                    menor = j;
                }
                }
                strcpy(tmp, linhas[menor]);
                strcpy(linhas[menor], linhas[i]);
                strcpy(linhas[i], tmp);
            }
            /*--*/
            for (i = 0; i < count; i++)
            {
                printf("%s\n", linhas[i]);
                
            }
            for ( i = 0; i < count; i++)
            {
                free(linhas[i]);
            }
            
            free(linhas);
            }
            
            
            
            /*CHAMADA DE SISTEMA CLOSE*/
            close(arquivo);
            valido = 1;
        }
        if (strcmp(args[0], "sort") == 0 && tam < 2)
        {
            printf("parametros insuficientes\n");
            valido = 1;
        }

        /*##################################################################*/

        if (strcmp(args[0], "exit") == 0)
        {
            puts("Saindo...");
            /*CHAMADA DE SISTEMA EXIT*/
            exit(0);
        }
        
        /*##################################################################*/

        if (valido == 0)
        {
            printf("%s: comando nao encontrado\n", args[0]);
        }   
    }
    return 0;
}
