//
// Created by em8273 on 30/11/2021.
//

#ifndef VIDEOSEQUENCER_IMAGEWRITER_H
#define VIDEOSEQUENCER_IMAGEWRITER_H


#include <QObject>

class ImageWriter : public QObject {
Q_OBJECT

public:
    explicit ImageWriter(QObject *parent);
};


#endif //VIDEOSEQUENCER_IMAGEWRITER_H
