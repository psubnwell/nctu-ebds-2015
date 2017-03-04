#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/type.h>
#include <unistd.h>
#include <cctype>
using namespace std;

char *sl_arg[64]; // = {"ls","-1".NULL};
char *output;

void real_run(){
	int pipe_out[2];
	if (pipe(pipe_out)==-1){
		puts("pipe build err\n");
		exit(-1);
	}

	pid_t pid;

	if ((pid=fork())<0){
		puts("fork build err\n");
		exit(-1);
	}
	else if (pid==0){
		close(pipe_out[0]);
		dup2(pipe_out[1],STDOUT_FILENO);
		close(pipe_out[1]);
		execvp(sl_arg[0],sl_arg);
		cout << "wrong cmd" <<endl;
		exit(-1);
	}
	else {
		close(pipe_out[1]);
		char tt[1024];
		int k1 = read(pipe_out[0],tt,1023);
		tt[k1]='\0';
		output = tt;
		close(pipe_out[0]);
	}
}

int main(){
	char *data;

	cout << "ContentType:text/html;\n\n";
	cout << "<html><body>" <<endl;
	cout << "<form action=\"\" method=\"get\">" <<endl;
	cout << "<input type=\"text\" name=\"id\"/>" <<endl;
	cout << "<input type=\"submit\"/>" <<endl;
	cout << "</form>" <<endl; 

	data = getenv("QUERY_STRING");

	int i=3;
	int k=0;
	int m=0;
	char cmd[5][64];

	while (data[i]!='\0'){
		if (data[i]!='+'){
			//sl_arg[0][k] = data[i];

			cmd[m][k] = data[i];
			//cout << data[i];
			i++;
			k++;
		}
		else{
			cmd[m][k] = '\0';
			k=0;
			i++;
			m++;
			//cout << " ";
		}
	}
	cmd[m][k] = '\0';

	for (i=0; i<=m; i++){
		sl_arg[i] = new char [64];
		sl_arg[i] = cmd[i];
	}

	sl_arg[i] = NULL;

	real_run();
	cout << output << endl;
	cout << "</body></html>" <<endl;
}