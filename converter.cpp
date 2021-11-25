//
// Created by Akshay Raj Gollahalli on 27/10/21.
//

#include "converter.h"
#include <QDebug>
#include <QMessageBox>

Converter::Converter(QObject *parent, QList<QString> *filePaths) : QObject(parent) {
    _filePaths = filePaths;
}

void Converter::loadVideo() {
}

Converter::~Converter() {
    delete _filePaths;
}

void Converter::convertToFrames() {

    Vide

}
