//
// Created by Akshay Raj Gollahalli on 27/10/21.
//

#ifndef VIDEOSEQUENCER_CONVERTER_H
#define VIDEOSEQUENCER_CONVERTER_H

#include <QObject>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


class Converter : public QObject {

    Q_OBJECT

public:
    explicit Converter(QObject *parent, QList<QString> *filePaths);
    void loadVideo();
    void convertToFrames();
    virtual ~Converter();

private:
    AVCodecContext *c = nullptr;
    AVFrame *frame = nullptr;
    AVPacket *packet = nullptr;
    QList<QString> *_filePaths;


};



#endif //VIDEOSEQUENCER_CONVERTER_H
