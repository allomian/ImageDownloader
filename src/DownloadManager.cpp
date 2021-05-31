//
// Created by muhammadahmedmemon on 5/30/21.
//

#include "../include/DownloadManager.h"
#include <curl/curl.h>
#include <curl/multi.h>
#include <iostream>
#include <math.h>
#include <algorithm>
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}
DownloadManager::DownloadManager(int argc, char *argv[]) {
    Initialize(argc,argv);
}
int DownloadManager::Initialize(int argc, char **argv){
    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    //curl_handle = curl_easy_init();
    for(int i =0; i < argc ;i++) {
        listofThreads.emplace_back(std::thread([argv,i,argc,this]() {
            if (argc < 2) {
                return 1;
            }
            if (i == 0) {
                return 0;
            }
            std::cout << "Downloading File from thread" <<std::this_thread::get_id() << std::endl;
            pagefilename << "Image" << i << ".jpg";
            FILE *fp;
            CURLcode res;
            CURL *curl_handle;
            curl_handle = curl_easy_init();
            if (curl_handle){
                fp = fopen(pagefilename.str().c_str(), "wb");
                //curl_multi_add_handle()
                curl_easy_setopt(curl_handle, CURLOPT_URL, argv[i]);
                curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
                curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fp);
                curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, false);
                curl_easy_setopt(curl_handle, CURLOPT_PROGRESSFUNCTION, progress_func);

                res = curl_easy_perform(curl_handle);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                curl_easy_cleanup(curl_handle);
                fclose(fp);
            }
        }));
    }
    for(auto &t: listofThreads){
        t.join();
    }
    //curl_easy_cleanup(curl_handle);

    curl_global_cleanup();
}
void DownloadManager::downloadFile(std::string url,std::string fname) {
//    std::cout
//    << std::endl << "Downloading File from url " << url <<std::endl;
//    CURL *curl;
//    FILE *fp;
//    CURLcode res;
//
//    curl_handle = curl_easy_init();
//    if (curl_handle){
//        fp = fopen(fname.c_str(), "wb");
//        //curl_multi_add_handle()
//        curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
//        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
//        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, fp);
//        curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, false);
//        curl_easy_setopt(curl_handle, CURLOPT_PROGRESSFUNCTION, progress_func);
//        res = curl_easy_perform(curl_handle);
//        //curl_easy_cleanup(curl_handle);
//        fclose(fp);
//    }
}
int DownloadManager::progress_func(void *ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload,
                                   double NowUploaded) {
    // ensure that the file to be downloaded is not empty
    // because that would cause a division by zero error later on
    if (TotalToDownload <= 0.0) {
        return 0;
    }

    // how wide you want the progress meter to be
    int totaldotz=40;
    double fractiondownloaded = NowDownloaded / TotalToDownload;
    // part of the progressmeter that's already "full"
    int dotz = (int) round(fractiondownloaded * totaldotz);

    // create the "meter"
    int ii=0;
    std::cout << "[" <<fractiondownloaded*100;
    //printf("%3.0f%% [",fractiondownloaded*100);
    // part  that's full already
    for ( ; ii < dotz;ii++) {
        std::cout << "=";
    }
    // remaining part (spaces)
    for ( ; ii < totaldotz;ii++) {
        printf(" ");
    }
    // and back to line begin - do not forget the fflush to avoid output buffering problems!
    printf("]\r");
    fflush(stdout);
    // if you don't return 0, the transfer will be aborted - see the documentation
    return 0;
}