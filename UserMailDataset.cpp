#include<string>
#include<vector>

#include<boost/filesystem.hpp>

#include "MiningMail.h"
#include "UserMailDataset.h"
#include "Logger.h"

namespace mm {
    namespace bfs = boost::filesystem;

    void UserMailDataset::loadFromLocalPath(const std::string& localPath) {
        bfs::path lpath(localPath);
        std::vector<bfs::path> folders;

        if (bfs::exists(lpath)) {
            if (bfs::is_directory(lpath)) {
                auto it = bfs::directory_iterator(lpath);
                while (it != bfs::directory_iterator()) {
                    loadFromLocalPath(it->path().string());
                    it++;
                }
            } else {
                Mail mail(lpath.string());
                emails.push_back(std::move(mail));
            }
        } else {
            std::stringstream sstr("Could not find ");
            sstr << localPath << " .Verify base dir";
            LOG_MESSAGE("UserMailDataSet", sstr.str().c_str());
        }
    }
};