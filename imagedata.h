//
// Created by em8273 on 3/12/2021.
//

#ifndef VIDEOSEQUENCER_IMAGEDATA_H
#define VIDEOSEQUENCER_IMAGEDATA_H

#include <opencv2/opencv.hpp>

using namespace cv;

#include <QObject>

class ImageData : public QObject {
Q_OBJECT
public:
    explicit ImageData(QObject *parent);
    const Mat &getFrame() const;
    void setFrame(const Mat &frame);
    const QString &getDuration() const;
    void setDuration(const QString &duration);

private:
    Mat _frame;
    QString _duration;

};


#endif //VIDEOSEQUENCER_IMAGEDATA_H
