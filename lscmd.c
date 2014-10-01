#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<limits.h>
#include<errno.h>
#include<string.h>
#include<time.h>
#include<sys/utsname.h>
#include<pwd.h>
#include<grp.h>
#define RESET_COLOR "\e[m" 
#define MAKE_GREEN "\e[32m" 
#define MAKE_BLUE "\e[36m"

void perm(struct stat mystat)
{
    printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-");
    printf( (mystat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (mystat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (mystat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (mystat.st_mode & S_IROTH) ? "r" : "-");
    printf( (mystat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (mystat.st_mode & S_IXOTH) ? "x" : "-");
  
}
void pdate(struct stat mystat)
{
  char dm[100];
  struct tm *dt;
  dt=localtime(&mystat.st_mtime);
  strftime(dm,100,"%b %d %H:%M",dt);
  printf("%s\t",dm);
}
void psiz(struct stat mystat)
{
  printf("%d\t",(int)mystat.st_size);
}
void plnk(struct stat mystat)
{
  printf(" %d\t",(int)mystat.st_nlink);  
}
void pug(struct stat mystat)
{
  struct passwd *pwd;
  struct group *grp;
  pwd=getpwuid(mystat.st_uid);
  grp=getgrgid(mystat.st_gid);
  printf("%s\t",pwd->pw_name);
  printf("%s\t  ",grp->gr_name);
  
}

void np(struct dirent *myfile)
{
    printf("%s", (char*)myfile->d_name);
}
void cp(struct dirent *myfile,struct stat mystat)
{
  (S_ISDIR(mystat.st_mode)? printf(MAKE_BLUE"%s   "RESET_COLOR,(char*)myfile->d_name) : (mystat.st_mode & S_IXOTH )? printf(MAKE_GREEN"%s   "RESET_COLOR,(char*)myfile->d_name): printf("%s   ",(char*)myfile->d_name) );
}
int main(int argc, char* argv[])
{
  char* a;
  //struct utsname unm;
  DIR *mydir;
  struct dirent *myfile;
  struct stat mystat;
  char* dir=(char*)get_current_dir_name();
  int f=0;
  /*if(uname(&unm)<0)
  {
    printf("uname error");
    return 0;
  }*/  
  if(argc==2)
  { 
    if(!strcmp(argv[1],"-l"))
      f=1;
    else if(!strcmp(argv[1],"-a"))
      f=2;
    else if(!strcmp(argv[1],"-la"))
      f=3;
    else if(!strcmp(argv[1],"-d"))
      f=4;
    else if(!strcmp(argv[1],"-ld"))
      f=5;
    
  }  
  printf("%d\n",argc);
  mydir = opendir(dir);
  while((myfile = readdir(mydir)) != NULL)
  {
    stat(myfile->d_name, &mystat);
    a=(char*)myfile->d_name;
    if(f==1)
    {
      if(*a!='.')
      {
        //stat(myfile->d_name, &mystat);
        perm(mystat);
        plnk(mystat);
        pug(mystat);
        psiz(mystat);
        pdate(mystat);
        cp(myfile,mystat); 
        printf("\n");
 
      }
    }
    else if(f==3)
    {
      //stat(myfile->d_name, &mystat);
      perm(mystat);
      plnk(mystat);
      pug(mystat);
      psiz(mystat);
      //printf("%s\t",unm.machine);
      pdate(mystat);
      cp(myfile,mystat);
      //np(myfile);
      printf("\n");

    }
    else if(f==2)
    {
      //stat(myfile->d_name, &mystat);
      cp(myfile,mystat);
    }
    else if(f==4)
    {
      if(!strcmp(myfile->d_name,"."))
        cp(myfile,mystat);
    }
    else if(f==5)
    {
      if(!strcmp(myfile->d_name,"."))
      {
        //stat(myfile->d_name, &mystat);
        perm(mystat);
        plnk(mystat);
        pug(mystat);
        psiz(mystat);
        pdate(mystat);
        cp(myfile,mystat); 
        printf("\n");
      }
    }
    else
    {
      if(*a!='.')
      {
        //stat(myfile->d_name, &mystat);
        cp(myfile,mystat);
      }
    }  
  }
  printf("\n");
  closedir(mydir);
}
