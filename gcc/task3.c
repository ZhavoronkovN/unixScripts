#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>

#define PERMS 0666
#define MAX_SIZE 100

void print_help(void){
	printf("%s\n%s\n%s\n%s\n%s\n","Task 3",
			"Usage : task3 DIRECTORY",
			"1) Prints files were changed last hour",
			"2) Prints 10 the oldest files",
			"3) Copies 10 the freshest into directory backup");
	return;
}

char ** file_arr;
int files_cnt;

int workDir(char * dir_name){
	DIR * dir = opendir(dir_name);
	if(!dir){
		printf("Cant open \"%s\"\n",dir_name);
		perror("");
		return 1;
	}
	struct dirent *dirent_f;
	while((dirent_f=readdir(dir))!=NULL){
			if(strchr((*dirent_f).d_name,'.')!=(*dirent_f).d_name){
				char * file = malloc(MAX_SIZE*sizeof(char));
				memcpy(file,dir_name,strlen(dir_name)+1);
				strcat(strcat(file,"/"),(*dirent_f).d_name);
				struct stat f_stat;
				lstat(file,&f_stat);
				if((f_stat.st_mode&S_IFMT)==S_IFDIR){
					char * next_dir = malloc(MAX_SIZE*sizeof(char));
					memcpy(next_dir,file,strlen(file)+1);
					workDir(next_dir);
				}
				else{
					if(strchr(file,'.')!=NULL){
						memcpy(file_arr[files_cnt++],file,strlen(file)+1);
					}
				}
				free(file);
			}
		}
	closedir(dir);
	free(dir_name);
	return 0;
}

int comp(const void * a,const void * b){
	struct stat stat_a;
	struct stat stat_b;
	const char * f1 = *(const char**)a;
	const char * f2 = *(const char**)b;
	lstat(f1,&stat_a);
	lstat(f2,&stat_b);
	double diff = difftime(stat_a.st_mtime,stat_b.st_mtime);
	if(diff==0){
		return 0;
	}
	else if(diff<0){
		return 1;
	}
	else{
		return -1;
	}
}

char * file_name(char * path){
	char * res = malloc(MAX_SIZE* sizeof(char*));
	int cnt=0;
	char * m = strrchr(path,'/');
	for(char* i = m; *i != '\0';i++){
		res[cnt++]=*i;
	}
	res[cnt]='\0';
	return res;
}

int cp(char * file,char * dest){
	char buf[4096];
	int f1,f2,n;
	char * dest_file = malloc((strlen(file)+strlen(dest)+3)*sizeof(char));
	memcpy(dest_file,dest,strlen(dest)+1);
	strcat(strcat(dest_file,"/"),file_name(file));
	if((f1 = open(file,O_RDONLY,0))==-1)
		return 0;
	if((f2 = creat(dest_file, PERMS))==-1)
		return 0;
	while((n=read(f1,buf,4096))>0)
		if(write(f2,buf,n)!=n)
			return 0;
	return 1;
}

void part1(void){
	printf("Files where changed last hour :\n");
	for(int i = 0;i<files_cnt;i++){
		struct stat stat_f;
		lstat(file_arr[i],&stat_f);
		if(difftime(time(NULL),stat_f.st_mtime)<=3600){
			printf("%s\n",file_arr[i]);
		}
	}
}

void part2(void){
	printf("The oldest files :\n");
	void * temp = file_arr[0];
	char * ctemp = temp;
	qsort(file_arr,files_cnt-1,sizeof(char*),comp);
	off_t size = 0;
	struct stat file_stat;
	if(files_cnt-1<10){
		for(int i = files_cnt-1; i >-1;i--){
			lstat(file_arr[i],&file_stat);
			size+=file_stat.st_size;
			printf("%s\n",file_arr[i]);
		}
	}
	else{
		for(int i =0;i<10;i++){
			lstat(file_arr[i],&file_stat);
			size+=file_stat.st_size;
			printf("%s\n",file_arr[i]);
		}
	}
	printf("Their size : \t%ld bytes\n",size);
}

void part3(char * dir_name){
	int backup_exists=0;
	DIR * dir = opendir(dir_name);
	if(!dir){
		printf("Cant open \"%s\"\n",dir_name);
		perror("");
	}
	struct dirent *dirent_f;
	while((dirent_f=readdir(dir))!=NULL){
		if(strchr((*dirent_f).d_name,'.')!=(*dirent_f).d_name){
			char * file = malloc(MAX_SIZE*sizeof(char));
			memcpy(file,dir_name,strlen(dir_name)+1);
			strcat(strcat(file,"/"),(*dirent_f).d_name);
			struct stat f_stat;
			lstat(file,&f_stat);
			if((f_stat.st_mode&S_IFMT)==S_IFDIR){
				if(!strcmp((*dirent_f).d_name,"backup")){
					backup_exists=1;
				}
			}
			free(file);
		}
	}
	closedir(dir);
	char * path = malloc((strlen(dir_name)+1)*sizeof(char));
	memcpy(path,dir_name,strlen(dir_name)+1);
	strcat(strcat(path,"/"),"backup");
	if(!backup_exists){
		char * command = malloc((strlen(path)+7)*sizeof(char));
		memcpy(command,"mkdir ",6);
		strcat(command,path);
		system(command);
		free(command);
	}
	dir = opendir(path);
	if(files_cnt-1<10){
		for(int i = files_cnt-1; i >-1;i--){
			if(!cp(file_arr[i],path)){
				printf("Error in copying %s\n",file_arr[1]);
			}
		}
	}
	else{
		for(int i =0;i<10;i++){
			if(!cp(file_arr[i],path)){
				printf("Error in copying %s\n",file_arr[1]);
			}
		}
	}
	closedir(dir);
}

int main(int argc, char * argv[]){
	for(int i=1;i<argc;i++){
		if(!strcmp(argv[i],"-h")||!strcmp(argv[i],"--help")){
			print_help();
			exit(0);
		}
	}
	if(argc<2)
	{
		printf("%s\n","Error : too few arguments \nType -h or --help for help");
		exit(1);
	}
	else if (argc>2){
		printf("%s\n","Error : too much arguments \nType -h or --help for help");
		exit(2);
	}
	file_arr=malloc(MAX_SIZE * 2 * sizeof(char*));
	for(int i = 0; i < MAX_SIZE * 2; i++){
		file_arr[i]=malloc(MAX_SIZE*sizeof(char));
	}
	files_cnt=0;
	char * dir = malloc((strlen(argv[1])+1)*sizeof(char*));
	memcpy(dir,argv[1],strlen(argv[1])+1);
	workDir(dir);
	part1();
	part2();
	part3(argv[1]);
	return 0;
}
