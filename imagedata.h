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
    const QString &getFrameDuration() const;
    void setFrameDuration(const QString &duration);
    const QString &getFileName() const;
    void setFileName(const QString &fileName);
    const QString &getVideoDuration() const;
    void setVideoDuration(const QString &videoDuration);

private:
    Mat _frame;
    QString _frameDuration;
    QString _fileName;
    QString _videoDuration;

};


#endif //VIDEOSEQUENCER_IMAGEDATA_H
