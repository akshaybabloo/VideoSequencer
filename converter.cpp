//
// Created by Akshay Raj Gollahalli on 27/10/21.
//

#include "converter.h"
#include <QDebug>
#include <QMessageBox>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/pixdesc.h>
#include <libavcodec/avcodec.h>
}

Converter::Converter(QObject *parent, QList<QString> *filePaths) : QObject(parent) {
    _filePaths = filePaths;
}

void Converter::loadVideo() {
}

Converter::~Converter() {
    delete _filePaths;
}

void Converter::convertToFrames() {
    int ret;
    AVFormatContext *avctx = nullptr;
    ret = avformat_open_input(&avctx, "/Users/akshayrajgollahalli/Downloads/add-tablecontroler.mov", nullptr, nullptr);
    if (ret < 0) {
        QMessageBox msgBox;
        msgBox.setText("Failed to open file");
        msgBox.exec();
    }
    qDebug() << ret;

    // retrive input stream information
    ret = avformat_find_stream_info(avctx, nullptr);
    if (ret < 0) {
        qDebug() << "fail to avformat_find_stream_info: ret=" << ret;
        QMessageBox msgBox;
        msgBox.setText("Unable to detect video format");
        msgBox.exec();
    }
    qDebug() << ret;

    // find primary video stream
    AVCodec* vcodec = nullptr;
    ret = av_find_best_stream(avctx, AVMEDIA_TYPE_VIDEO, -1, -1, &vcodec, 0);
    if (ret < 0) {
        qDebug() << "fail to av_find_best_stream: ret=" << ret;
        QMessageBox msgBox;
        msgBox.setText("Unable to get best stream");
        msgBox.exec();
    }
    qDebug() << ret;

    const int vstrm_idx = ret;
    AVStream* vstrm = avctx->streams[vstrm_idx];

//    // open video decoder context
//    ret = avcodec_open2(avcodec_alloc_context3(vcodec), vcodec, nullptr);
//    if (ret < 0) {
//        qDebug() << "fail to avcodec_open2: ret=" << ret;
//    }
//    qDebug() << ret;

    qDebug()
        << "infile: " << "/Users/akshayrajgollahalli/Downloads/add-tablecontroler.mov" << "\n"
        << "format: " << avctx->iformat->name << "\n"
        << "vcodec: " << vcodec->name << "\n"
        << "size:   " << vstrm->codecpar->width << 'x' << vstrm->codecpar->height << "\n"
        << "fps:    " << av_q2d(vstrm->avg_frame_rate) << " [fps]\n"
        << "length: " << av_rescale_q(vstrm->duration, vstrm->time_base, {1,1000}) / 1000.0 << " [sec]\n"
        << "pixfmt: " << av_get_pix_fmt_name(vstrm->codec->pix_fmt) << "\n"
        << "frame:  " << vstrm->nb_frames << "\n";
}
