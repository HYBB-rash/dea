#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <csignal>
#include <sys/param.h>
#include <sys/stat.h>
#include <ctime>
#include <syslog.h>
#include "Tip/tip.h"
#include "Report/report.h"
#include "Mail/mail.h"

int init_daemon(void) {
    int pid;
    int i;

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();
    if (pid > 0) {
        exit(0);
    } else if (pid < 0) {
        return -1;
    }
    setsid();

    pid = fork();
    if (pid > 0) {
        exit(0);
    } else if (pid < 0) {
        return -1;
    }

    for (i = 0; i < NOFILE; close(i ++));

    chdir("/");

    signal(SIGCHLD,SIG_IGN);
    return 0;
}

int main() {
    time_t now;
    init_daemon();
    int cnt = 0;
    std::map<std::string, bool> mail = initMemo();
    while (true) {
        sleep(1);
        cnt ++;
        if (cnt % 15 * 60 == 1) {
            report("User tip long use \n");
            tip();
        }
        else if (cnt % 2) {
            const std::string &string = newMail(mail);
            if (string != "") {
                tip("You have a new mail name :" + string);
                report("New mail name:" + string + "\n");
            }
        }
        cnt %= 10007;
    }
}

//int main () {
//    tip();
//    report();
//    std::map<std::string, bool> map = initMemo();
//    const std::string &string = newMail(map);
//    std::cout << string << "this this" << std::endl;
//    return 0;
//}
