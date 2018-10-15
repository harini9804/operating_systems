
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){


  int no_of_options;
  int log_count=0;
  int i;
  pid_t pid;
  char **cmd, **history, *str;
  char *token;
  cmd=(char**)malloc(sizeof(char*)*100);
  history =(char**)malloc(sizeof(char*)*100);

  while(1)
  {

    // printf("\nEnter total no of options: ");
    // scanf("%d",&no_of_options);
    //
    //
    // printf("\nEnter the command to be executed: ");
    // for(int i=0;i<no_of_options;i++)
    // {
    //   cmd[i]=(char*)malloc(sizeof(char)*100);
    //   scanf("%s",cmd[i]);
    // }
    no_of_options=0;
    printf("\nCommand (enter !! for cmd history.)>> ");
    str = (char*)malloc(sizeof(char)*256);
    gets(str);

    if(!strcmp(str,"!!")){

      if(log_count==0){
        printf("\nNo history available.");
      }
      else{
        printf("\nCommand History: \n");
        for(int i=log_count-1;i>=0;i--){
          printf("%s\n",history[i] );
        }
      }


    }
    else if(strlen(str)==2 && str[0]=='!')
    {

      if(log_count==0){
        printf("\nNo history available.");
      }
      else{

        int x = str[1]-'0';
        printf("\nRecent %d logs: \n",x);
        if(x>log_count){
          printf("\nCommand History: \n");
          for(int i=log_count-1;i>=0;i--){
            printf("%s\n",history[i] );
          }
        }
        else{
          printf("\nCommand History: \n");
          for(int i=log_count -1;i>=log_count-x;i--){
            printf("%s\n",history[i] );
          }
        }

      }


    }
    else{

      history[log_count]=(char*)malloc(sizeof(char)*256);
      strcpy(history[log_count],str);
      log_count++;

      token = strtok(str, " ");
      cmd[no_of_options]=(char*)malloc(sizeof(char)*100);
      cmd[no_of_options] = token;
      no_of_options++;
     // Keep printing tokens while one of the
     // delimiters present in str[].
     while (token != NULL) {
         token = strtok(NULL, " ");
         cmd[no_of_options]=(char*)malloc(sizeof(char)*100);
         cmd[no_of_options] = token;
         no_of_options++;
     }

      char * arg=NULL;
      cmd[no_of_options]=arg;
      pid = fork();
      if(pid==0){
        execvp(cmd[0],cmd);
      }

      else if(pid>0)
      {
        wait(NULL);
      }

    }

  }

  return 0;
}
