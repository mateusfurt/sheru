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
    int tam, valido, i, teste;
    char texto[600], args[3][605], conteudo[5000];
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
        
        if (strcmp(args[0], "ls") == 0 && tam == 1)
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
        if (strcmp(args[0], "ls") == 0 && strcmp(args[1], "-a") == 0 && tam == 2)
        {
            /*CHAMADA DE SISTEMA OPENDIR*/
            DIR *dir = opendir(getcwd(buf, size));
            if (dir == NULL)
            {
                printf("chamada de sistema falhou\n");
            }
            /*CHAMADA DE SISTEMA READDIR*/
            while ((entry = readdir(dir)) != NULL) {
                
                printf("%s ", entry->d_name);
            }
            printf("\n");
            closedir(dir);
            valido = 1;
        }
        if (strcmp(args[0], "ls") == 0 && (strcmp(args[1], "-l") == 0 || strcmp(args[2], "-l") == 0))
        {
            /*CHAMADA DE SISTEMA OPENDIR*/
            DIR *dir = opendir(getcwd(buf, size));
            if (dir == NULL)
            {
                printf("chamada de sistema falhou\n");
            }
            /*CHAMADA DE SISTEMA READDIR*/
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(args[1], "-a") == 0 || strcmp(args[2], "-a") == 0)
                {
                    strcpy(caminho, getcwd(buf, size));
                    strcat(caminho, "/");
                    strcat(caminho, entry->d_name);
                    struct stat file_stat;
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
                    strcpy(caminho, getcwd(buf, size));
                    strcat(caminho, "/");
                    strcat(caminho, entry->d_name);
                    struct stat file_stat;
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
        if(strcmp(args[0], "cat") == 0){
            int arquivo;
            printf("gato");
            strcpy(caminho, getcwd(buf, size));
            strcat(caminho, "/");
            strcat(caminho, args[1]);
            printf("%s\n", caminho);
            arquivo = open (caminho, O_RDONLY);
            if (arquivo < 0){
                printf("erro ao abrir arquivo\n");
            }else
            {
                read(arquivo, conteudo, 5000);
                printf("%s\n", conteudo);
            }
            valido = 1;
        }
        if (valido == 0)
        {
            printf("%s: comando nao encontrado\n", args[0]);
            
        }
        
    }
    

    return 0;
}
