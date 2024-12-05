#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void runfsh();
char *readInput();
char **splitInput(char *input);
int launchCommand(char **args);
int numBuilt();
int fshcd(char **args);
int fshexit(char **args);
int execCommand(char **args);

char *builtComsList[] = {"cd","exit"};
int (*builtComs[]) (char **) = { &fshcd, &fshexit};

int main(int argc, char **argv)
{	
	runfsh();

	return 0;
}

void runfsh(){
	char *input;
	char **args;
	int status;

	do{
		printf("fsh> ");
		input = readInput();
		args = splitInput(input);
		status = execCommand(args);

		free(input);
		free(args);
	}
	while (status == 1);
}

char *readInput(){
	ssize_t memSize = 0;
	char *input = NULL;

	if (getline(&input, &memSize, stdin) == -1){
		if (feof(stdin)){
			exit;
		}
		else
		{
			perror("getline");
			exit;
		}
	}
	
	return input;
}

char **splitInput(char *input)
{
	int memSize = 32, pos = 0;
	char **tokens = malloc(memSize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "fsh: malloc error\n");
		exit;
	}

	token = strtok(input, " \t\r\n\a");
	while (token != NULL) 
	{
		tokens[pos] = token;
		pos+=1;

		if (pos >= memSize)
		{
			memSize += 32;
			tokens = realloc(tokens, memSize * sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr, "fsh: realloc error\n");
				exit;
			}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[pos] = NULL;
	return tokens;
}

int execCommand(char **args)
{
	int i;

	if (args[0] == NULL)
	{
		return 1;
	}

	for (i = 0; i < numBuilt(); i++)
	{
		if (strcmp(args[0], builtComsList[i]) == 0)
		{	
			return(*builtComs[i])(args);
		}
	}

	return launchCommand(args);

}

int launchCommand(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("fsh");
		}
		exit;
	}
	else if (pid < 0)
	{
		perror("fsh");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int numBuilt()
{
	return sizeof(builtComsList) / sizeof(builtComsList[0]);
}

int fshcd(char **args)
{
	// cwd
	char* cwd;
	char buff[PATH_MAX + 1];
	cwd = getcwd( buff, PATH_MAX + 1 );
	// split into tokens
	char* delim =  "/";
	char* token = strtok(cwd, delim);
	// length of tokens array
        items = strlen(token);
	
	// take first non-null token as root
	basedir = token[1];

	if (args[0] == NULL) {
		// go to root
		pwd = basedir;
	} else if (args[0] == "..") {
		// navigate back one directory
		if (items > 1) { 
    			token[items - 1] = '\0';
			backdir = token;
		} else {
			return 1;
		}
	} else {
		// enter the given directory
		items = strltn(token) + 1;
		token[items] = args;
		cwd = token;
	}
	return 1;
}

int fshls() {
	// get curr dir
        char* cwd;
        char buff[PATH_MAX + 1];
        cwd = getcwd( buff, PATH_MAX + 1 );
        // split into tokens
        char* delim =  "/";
        char* token = strtok(cwd, delim);
        items = strlen(token);

	// read dir items
	dir = token[items - 1];
	while ((ditem = readdir(dir)) != NULL) {
		// make sure dir != empty
		if (ditem->d_type !=  DT_DIR) {
		// print out non directories in black
			printf("%s\t", dir->d_name);
		} else {
		// print out directories in blue
			printf("%s%s/t", "\033[0;34m", dir ->d_name);
			printf("\033[0m");
		}
	}
}

int fshexit(char **args)
{
	return 0;
}

