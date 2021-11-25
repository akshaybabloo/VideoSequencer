//
// Created by Akshay Raj Gollahalli on 27/10/21.
//

#ifndef VIDEOSEQUENCER_CONVERTER_H
#define VIDEOSEQUENCER_CONVERTER_H

#include <QObject>
#include <opencv2/opencv.hpp>

using namespace cv;

class Converter : public QObject {

Q_OBJECT

public:
    explicit Converter(QObject *parent, QList<QString> *filePaths);
    void loadVideo();
    void convertToFrames();
    virtual ~Converter();

private:
    QList<QString> *_filePaths;


};


#endif //VIDEOSEQUENCER_CONVERTER_H
