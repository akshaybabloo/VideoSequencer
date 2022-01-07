//
// Created by em8273 on 3/12/2021.
//

#include "imagedata.h"


ImageData::ImageData(QObject *parent) : QObject{parent} {

}

const QList<QImage> &ImageData::getFrames() const {
    return _frame;
}

void ImageData::appendFrame(const QImage &frame) {
    this->_frame.append(frame);
}

const QString &ImageData::getFrameDuration() const {
    return _frameDuration;
}

void ImageData::setFrameDuration(const QString &duration) {
    this->_frameDuration = duration;
}

const QString &ImageData::getFileName() const {
    return _fileName;
}

void ImageData::setFileName(const QString &fileName) {
    _fileName = fileName;
}

const QString &ImageData::getVideoDuration() const {
    return _videoDuration;
}

void ImageData::setVideoDuration(const QString &videoDuration) {
    _videoDuration = videoDuration;
}
