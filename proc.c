
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
int gval = 10;
//进程
/*
int main(int argc, char *argv[])
{
	pid_t pid;
	int lval = 20;
	gval++, lval += 5;
	pid = fork();
	if (pid == 0)
		gval += 2, lval += 2;
	else
		gval -= 2, lval -= 2;

	if (pid == 0)
		printf("Child process:[%d,%d]\n", gval, lval);
	else
		printf("parent process:[%d,%d]\n", gval, lval);
	return 0;
}
*/
//僵尸进程
/*
int main(int argc, char*argv[])
{
	pid_t pid = fork();
	if (pid == 0)
		puts("Hi,I am a child process");
	else
	{
		pfintf("Child Prodess ID: %d \n", pid);
		sleep(30);
	}
	if (pid == 0)
		puts("End child process");
	else
		puts("End parent process");
	return 0;
 }
 */
//利用wait函数摧毁僵尸进程
/*
int main(int argc, char *argv[])
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
		return 3;
	else
	{
		printf("Child PID:%d\n", pid);
		pid = fork();
		if (pid == 0)
			exit(7);
		else
		{
			printf("Child PID :%d\n", pid);
			wait(&status);
			if (WIFEXITED(status))
				printf("Child send one:%d\n", WEXITSTATUS(status));

			wsit(&status);
			if (WIFEXITED(status))
				printf("Child send two :%d\n", WEXITSTATUS(status));
			sleep(30);
		}
	}
	return 0;
 }
 */
//使用waitpid函数销毁僵尸进程
/*
int main(int argc,char *argv[])
	{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		sleep(15);
		return 24;
	}
	else
	{
		while (!waitpid(-1, &status, WNOHANG))
		{
			sleep(3);
			puts("sleep3sec.");
         }
			if (WIFEXITED(status))
				printf("Child send %d \n", WEXITSTATUS(status));
	}	
	return 0;
}
*/
//alarm信号处理

void timeout(int sig)
{
	if (sig == SIGALRM)
		puts("Time out!");
	alarm(2);
}
void keycontrol(int sig)
{
	if (sig == SIGINT)
		puts("CTRL+C pressed");
}
/*
int main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);
	alarm(2);

	for (i = 0; i < 3; i++)
	{
		puts("wait......");
		sleep(100);
	}
	return 0;
}
*/
//利用sigaction函数进行信号处理
/*
void timeout(int  sig)
{
	if (sig = SIGALRM)
		puts("Time out !");
	alarm(2);
}

struct sigaction
{
	void(*sa_handler)(int);
	sigset_t sa_mask;
	int sa_flags;
};
/*
int main(int argc, char *argv[])
{
	int i;
	struct sigaction act;
	act.sa_handler = timeout;
	sifemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sifaction(SIGALRM, &act, 0);

	alarm(2);

	for (i = 0; i < 3; ++i)
	{
		puts("wait......");
		sleep(100);
	}
	return 0;
}
*/
//利用信号处理技术消灭僵尸进程
/*
void read_childproc(int)
{
	int status;
	pid_t id = waitpid(-1, &sstatus, WNOHANG);
	if (WIFXITED(status))
	{
		printf("Removed proc id:%d \n", id);
		printf("Child wend: %d\n", WEXITSTATUS);
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler = read_childproc;
	sigemptuset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD, &act, 0);

	pid = fork();
	if (pid == 0)
	{
		puts("Hi!I'm child process");
		sleep(10);
		return 12;
	}
	else
	{
		printf("Child proc id: %d \n", pid);
		pid = fork();
		if (pid == 0)
		{
			puts("Hi!I'm child process");
			sleep(10);
			exit(24);
		}
		else
		{
			int i;
			printf("Child proc id:%d\n", pid);
			for (i = 0; i < 5; ++i)
			{
				puts("Wait......");
				sleep(5);
			}
		}
	}
	return 0;
}
*/