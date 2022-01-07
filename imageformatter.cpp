//
// Created by em8273 on 30/11/2021.
//

#include <QImage>
#include <QtConcurrent>
#include <QFuture>
#include <QDebug>
#include "imageformatter.h"

ImageFormatter::ImageFormatter(QObject *parent) : QObject(parent) {

}

QImage ImageFormatter::createImageCollage(ImageData *imageData) {

    QFuture<QImage> future = QtConcurrent::mapped(imageData->getFrames(), ImageFormatter::scaled);
    auto item = future.then([](const QImage& reply){
        qDebug() << reply;
    });

    return {};
}

QImage ImageFormatter::scaled(const QImage &image) {
    if (image.isNull()){
        qDebug()<<image;
        return image;
    }
    return image.scaled(100,100);
}
