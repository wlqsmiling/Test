#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static pid_t g_devm_ntp_pid = -1;

// 启动进程
int32_t devm_ntp_restart()
{
    pid_t pid = fork();

	printf("pid is:%ld",pid);
    if (pid > 0)
    {
        g_devm_ntp_pid = pid;
    }
    if (pid < 0)
    {
        exit(-1);
    }
    else if (pid == 0)
    {
        // execl("/usr/sbin/ntpd", "ntp", "-g");
        execl("/usr/sbin/rsyslogd", "/usr/sbin/rsyslogd", "-n", "-iNONE");
        exit(-1);
    }

    return 0;
}

void main() {
	devm_ntp_restart();

	while(1) {
		printf("haha\n");

		sleep(5);
	}
	
}
