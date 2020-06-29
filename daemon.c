#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
    pid_t pid = 0;
    pid_t sid = 0;
    FILE *fp= NULL;
    int i = 0;
    /*Создание нового процесса*/
    pid = fork();
    /*Проверка правильности идентификатора процесса*/
    if (pid < 0)
    {
        printf("fork failed - wrong pid!\n");
        exit(1);
    }
    /*Родительский процесс*/
    if (pid > 0)
    {
       printf("pid of child process %d \n", pid);
        exit(0); //завершение процесса родителя
    }

    umask(0);//права на открытие файла, чтение, запись...
    /*Создание новой сессии, чтобы демон из процесса-ребенка стал лидером группы новых процессов*/
    sid = setsid();
    if(sid < 0)
    {
        exit(1);
    }
    /*Закрытие стандартных файловых дескрипторов*/
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    /*Работа демона в фоне*/
    fp = fopen ("deamonWorks.txt", "w+");
    char test[15]="testing daemon";
    while (i < 10)
    {
        sleep(1);
        fprintf(fp, "%s \n", test);
        i++;
    }
    fclose(fp);
  
    return (0);
}
