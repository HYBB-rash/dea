//
// Created by hyong on 1/5/21.
//
#include "../mail.h"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>
const std::string mailDir = "/var/spool/mail/hyong";

std::map<std::string, bool> initMemo() {
    std::map<std::string, bool> memo;
    DIR *dir;
    struct dirent *p;
    dir = opendir(mailDir.c_str());
    while ((p = readdir(dir)) != nullptr) {
        std::cout << p->d_name << std::endl;
        std::string addr = p->d_name;
        memo[addr] = true;
    }
    return memo;
}

std::string newMail(std::map<std::string, bool> &memo) {
    DIR *dir;
    struct dirent *p;
    dir = opendir(mailDir.c_str());
    std::string newMailString;
    while ((p = readdir(dir)) != nullptr) {
        std::cout << p->d_name << std::endl;
        std::string addr = p->d_name;
        if (!memo[addr]) {
            newMailString = addr;
            memo[addr] = true;
        }
    }
    return newMailString;
}