//
// Created by muhammadahmedmemon on 5/30/21.
//

#include "../include/Application.h"

Application::Application(int argc, char *argv[]) {
    m_DownloadManager = new DownloadManager(argc,argv);
}
