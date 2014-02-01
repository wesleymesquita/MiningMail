/* 
 * File:   MailStorage.h
 * Author: wesley
 *
 * Created on 1 de Janeiro de 2014, 20:47
 */

#ifndef MAILSTORAGE_H
#define	MAILSTORAGE_H

#include<vector>
#include<boost/filesystem.hpp>


namespace mm {
    namespace fs = boost::filesystem;

    class MailStorage {
    public:
        MailStorage(const std::string& rootDir);
        virtual ~MailStorage();
        void loadUsers();
    private:
        fs::path rootDir;
        std::vector<std::string> users;
    };
};
#endif	/* MAILSTORAGE_H */

