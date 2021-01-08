//
// Created by hyong on 1/5/21.
//

#ifndef DEA_MAIL_H
#define DEA_MAIL_H

#include <map>

extern std::map<std::string, bool> memo;

std::map<std::string, bool> initMemo();

std::string newMail(std::map<std::string, bool> &memo);
#endif //DEA_MAIL_H
