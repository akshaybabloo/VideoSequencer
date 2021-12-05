//
// Created by Akshay Raj Gollahalli on 27/10/21.
//

#include "converter.h"
#include "imagedata.h"
#include <QDebug>
#include <QMessageBox>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

Converter::Converter(QObject *parent, QList<QString> *filePaths) : QObject(parent) {
    _filePaths = filePaths;
}

void Converter::loadVideo() {
}

Converter::~Converter() {
    delete _filePaths;
}

QList<ImageData *> Converter::convertToFrames() {
    QList<ImageData*> imageData;

    for (const QString& filePath: *_filePaths) {
        qDebug() << filePath;
        std::vector<int> frameIndexes;
        Mat frame;

        VideoCapture capture(filePath.toStdString());

        if(!capture.isOpened()) {
            qDebug() << "unable to open video";
            return imageData;
        }

        int frameCount = int(capture.get(cv::CAP_PROP_FRAME_COUNT));
        auto fps = capture.get(cv::CAP_PROP_FPS);
        auto durationMinutes = QString::number((frameCount/fps)/60.0);
        int nthFrame = int((frameCount-10)/10);

        boost::push_back(frameIndexes, boost::irange(1, frameCount, nthFrame));

        qDebug()
                << "fps = " << fps << "\n"
                << "number of frames = " << frameCount << "\n"
                << "duration = " << durationMinutes
                << "frames = " << frameIndexes;

        for (int index : frameIndexes) {
            capture.set(cv::CAP_PROP_POS_FRAMES, index);
            capture >> frame;

            auto data = new ImageData(nullptr);
            data->setFrame(frame);
            data->setDuration(QString(""));

            imageData.append(data);
//            qDebug() << frame.data;
//            imwrite(QString("test%1.png").arg(index).toStdString(), frame);
//            qDebug() << QString("test%1.png").arg(index);
        }

        capture.release();
    }

    return imageData;

}
