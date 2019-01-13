#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

static char *sh = "/bin/sh";
static char *argv[] = {"-c sh", 0};
static char *envp[] = {0};

int main(){
	sigset_t s;
	int status;

	if(getpid() != 1)
		return 1;

	sigfillset(&s);
	sigprocmask(SIG_BLOCK, &s, 0);

	if(fork())
		for(;;)
			waitpid(-1, &status, 0);

	sigprocmask(SIG_UNBLOCK, &s, 0);

	setsid();
	setpgid(0, 0);
	return execve(sh, argv, envp);
}

