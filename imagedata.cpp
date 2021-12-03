//
// Created by em8273 on 3/12/2021.
//

#include "imagedata.h"


ImageData::ImageData(QObject *parent) : QObject(parent) {

}

const Mat &ImageData::getFrame() const {
    return _frame;
}

void ImageData::setFrame(const Mat &frame) {
    this->_frame = frame;
}

const QString &ImageData::getDuration() const {
    return _duration;
}

void ImageData::setDuration(const QString &duration) {
    this->_duration = duration;
}
