//
// Created by muhammadahmedmemon on 5/30/21.
//

#ifndef IMAGEDOWNLOADER_APPLICATION_H
#define IMAGEDOWNLOADER_APPLICATION_H

#include "DownloadManager.h"
class Application {
public:
    Application() = default;
    Application(int argc, char *argv[]);

private:
    DownloadManager *m_DownloadManager;
};


#endif //IMAGEDOWNLOADER_APPLICATION_H
