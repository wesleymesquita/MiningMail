/* 
 * File:   MailDataSet..h
 * Author: wesley
 *
 * Created on 22 de Janeiro de 2014, 19:57
 */

#ifndef USERMAILDATASET__H
#define	USERMAILDATASET__H

#include<string>
#include<vector>
#include<boost/current_function.hpp>
#include "Mail.h"

class UserMailDataset{
public:
    void loadFromLocalPath(const std::string& localPath);
private:
    std::string user;
    std::vector<Mail> emails;
};

#endif	/* USERMAILDATASET__H */

