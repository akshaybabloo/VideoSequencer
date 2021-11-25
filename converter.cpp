//
// Created by Akshay Raj Gollahalli on 27/10/21.
//

#include "converter.h"
#include <QDebug>
#include <QMessageBox>

Converter::Converter(QObject *parent, QList<QString> *filePaths) : QObject(parent) {
    _filePaths = filePaths;
}

void Converter::loadVideo() {
}

Converter::~Converter() {
    delete _filePaths;
}

void Converter::convertToFrames() {

    for (const QString& filePath: *_filePaths) {
        qDebug() << filePath;

        VideoCapture capture(filePath.toStdString());

        if(!capture.isOpened()) {
            qDebug() << "unable to open video";
            return;
        }

        auto frameCount = capture.get(cv::CAP_PROP_FRAME_COUNT);
        auto fps = capture.get(cv::CAP_PROP_FPS);

        auto duration = frameCount/fps;

        qDebug()
                << "fps = " << fps << "\n"
                << "number of frames = " << frameCount << "\n"
                << "duration = " << duration;

        capture.release();
    }


}
