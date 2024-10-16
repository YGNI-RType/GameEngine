/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-1-rtype-basile.fouquet
** File description:
** net_ftp
*/

#pragma once

#include "msg.hpp"

#include <string>
#include <vector>

namespace Network {

class FileService {
public:
    FileService(const std::string &filename, uint8_t priority = -1);
    ~FileService();

    void openFile(const std::string &filename);
    void closeFile(void);

    void writeFile(const TCPMessage &msg);
    bool readFile(TCPMessage &msg); /* store the chunk inside */

    static uint8_t determinePriority(const std::string &filename); /* add any other information */

private:
    std::string m_filePath;

    /* 1 - 10, it's how many time the server loops back to that same file (1 loop = N Chunk of file, and move on to the
     * other pending list, rotating everything) */
    uint8_t m_priority;

    // speed calculation
    double m_completion;
    double m_speed;

    int m_fd;
    size_t m_fileSize;
};

/* upload / download files */
class FTPService {
public:
    FTPService(bool isServer);
    ~FTPService() = default;

    void uploadFile(const std::string &filename);
    void downloadFile(const std::string &filename);

    void addNewFileService(const std::string &filename);

private:
    bool m_isServer;
    std::string m_rootFilePath; /* where to put data (depends if client or server)*/

    std::vector<FileService>
        m_pendingServices; /* all the download / upload of files (TODO : may be concurrent downloads) */
                           /* todo : add a rate limit for any user to not pass */
    /* todo : add a priority system, certain files are most likely to be complemted, however with multithreads it's ok
     */
    /* should the ftp service be a seperated thread ? Like only one instance across multiple server in one process ?
     * Like it will tell if a certain client has finished all download services and continue normal process to join the
     * game ? */

    /* TODO : add a checking for the file prior to everything (is the size allowed, is the mime type authorized, don't
     * allow the client to upload everytime, add a cooldown etc...)*/

    /* TODO : make windows / linux behavior via classes to get necesary information, get it through a custom rate of tcp
     * socket */
    /* clients cna send profile pictures and server may give custom sounds based on game (purity) */
};
} // namespace Network
