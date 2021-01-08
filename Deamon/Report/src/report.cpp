//
// Created by hyong on 1/5/21.
//

#include "../report.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctime>

void report() {
    report("nothing");
}

void report(const std::string& message) {
    time_t now;
    time(&now);
    int fd = open("/tmp/20181389.log", O_RDWR | O_APPEND);
    if (fd == -1) {
        printf("error is %s\n", strerror(errno));
    } else {
        printf("success fd = %d\n", fd);
        std::string str = ctime(&now);
        std::string buffer = "SystemTime:\t" + str +
                             "\t\t\n20181389 System status\n";
        write(fd, message.c_str(), strlen(message.c_str()));
        write(fd, buffer.c_str(), strlen(buffer.c_str()));
        close(fd);
    }
}