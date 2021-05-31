//
// Created by muhammadahmedmemon on 5/30/21.
//

#ifndef IMAGEDOWNLOADER_DOWNLOADMANAGER_H
#define IMAGEDOWNLOADER_DOWNLOADMANAGER_H

#include "curl/curl.h"
#include "vector"
#include "thread"
#include "sstream"
#include "curl/curl.h"

class DownloadManager {
private:
   //CURL *curl_handle;
   // CURL *handle[3];
    std::vector<std::thread> listofThreads;
    std::stringstream pagefilename;
    //std::vector<
    FILE *pagefile;
private:
    static int progress_func(void* ptr, double TotalToDownload, double NowDownloaded,
                      double TotalToUpload, double NowUploaded);
    void downloadFile(std::string url,std::string fname);
public:
    int Initialize(int argc, char **argv);
    DownloadManager() = default;
    DownloadManager(int argc, char *argv[]);
};


#endif //IMAGEDOWNLOADER_DOWNLOADMANAGER_H
