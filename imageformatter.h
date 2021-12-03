//
// Created by em8273 on 30/11/2021.
//

#ifndef VIDEOSEQUENCER_IMAGEFORMATTER_H
#define VIDEOSEQUENCER_IMAGEFORMATTER_H


#include <QObject>

class ImageFormatter : public QObject {
Q_OBJECT

public:
    explicit ImageFormatter(QObject *parent);
};


#endif //VIDEOSEQUENCER_IMAGEFORMATTER_H
