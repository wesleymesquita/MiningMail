#include<boost/filesystem.hpp>

#include "UserMailDataset.h"
#include "Logger.h"

namespace bfs = boost::filesystem;

void UserMailDataset::loadFromLocalPath(const std::string& localPath) {
    bfs::path lpath(localPath);
    std::vector<bfs::path> folders;
    if (bfs::exists(lpath)) {
        if (bfs::is_directory(lpath)) {
            auto it = bfs::directory_iterator(lpath);
            while (it != bfs::directory_iterator()) {
                if (bfs::is_directory(it->path())) {
                    folders.push_back(it->path());

                }
                it++;
            }
            for (auto f : folders) {
                auto mail_it = bfs::directory_iterator(f);
                Mail mail(mail_it->path().string().c_str());
                emails.push_back(std::move(mail));
            }

        } else {
            Mail mail(lpath.string().c_str());
            emails.push_back(std::move(mail));
        }
    } else {
        std::stringstream sstr("Could not find ");
        sstr << localPath << " .Verify base dir";
        Logger::log(__FUNCTION__, sstr.str().c_str());
    }
}
