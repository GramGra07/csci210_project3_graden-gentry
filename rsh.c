#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12
#define ARGLEN 20

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	// return 1 if cmd is one of the allowed commands
	// return 0 otherwise
	for (int i = 0; i < N; i++){
		if (strcmp(cmd,allowed[i])== 0) {return 1;}
	}
	
	return 0;
}

int main() {
    char line[256];

    pid_t pid;
    int status;
    posix_spawnattr_t attr;
    posix_spawnattr_init(&attr);

    while (1) {
	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;
	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';
	
	//chop with strtok
	char cmd[256];
	strcpy(cmd, line);
	char *token;
	token = strtok(cmd, " ");
	int tokenLen = 0;
	
	char *args[22] = {NULL};
	while (token != NULL && tokenLen < 21) {
		args[tokenLen] = token;
		token = strtok(NULL, " ");	tokenLen++;
   	}
	args[tokenLen] = NULL;
	if (tokenLen == 0) continue;
	// this code works
	//if (isAllowed(line))
	if (isAllowed(args[0])){
		if (strcmp(args[0],"exit")==0){ 
			posix_spawnattr_destroy(&attr);
			return 0;
		}
		if (strcmp(args[0],"help")==0){
			printf("The allowed commands are:\n");
			for (int i = 0; i < N; i++){
				printf("%d: %s\n",i+1,allowed[i]);
			}
			continue;
		}
		if (strcmp(args[0],"cd") == 0){
			if (tokenLen > 2){
				printf("-rsh: cd: too many arguments\n");
			}else{
				if (tokenLen == 2) chdir(args[1]);
			}
			continue;
		}

		// add spawns

		if (posix_spawnp(&pid, args[0], NULL, &attr, args, environ) == 0) {
			waitpid(pid, &status, 0);
		}else{
			perror("spawn failed");
		}
		
	}else{
		printf("NOT ALLOWED!\n");
	}
    }
    posix_spawnattr_destroy(&attr);
    return 0;
}
