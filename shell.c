#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
void ls(char arr[])
{
  int i;
  char *ptr=arr;
  char a[],b[]
  //printf("\nhello\n");
  sscanf(ptr,"%s %s ",a,b);
  printf("%s",a);
}
int main(int argc,char *argv[])
{
  char line[1024];
  int s;
  while(1)
  {
   // line="\0";        
    printf("$: ");

    if(!fgets(line, 1024, stdin))
      break;
    s=strcmp("exit\n",line);
    printf("%d",s);
    if(!strcmp("ls\n",line))
        ls(line);
    if(s==0)
      break;            //printf("\n\n cmd: %s\n\n",line);    
    system(line);



  }

  return 0;
}
~     
