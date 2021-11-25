#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "converter.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMimeDatabase>
#include <numeric>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setAcceptDrops(true);

    connect(ui->clearButton, &QPushButton::released, this, &MainWindow::clearList);
    connect(ui->convertButton, &QPushButton::released, this, &MainWindow::convert);

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    QMimeDatabase db;

            foreach (const QUrl &url, event->mimeData()->urls()) {
            QString filePath = url.toLocalFile();
            qDebug() << "Dropped file:" << filePath;
            QMimeType type = db.mimeTypeForFile(filePath);
            qDebug() << "Mime type:" << type.name();
            new QListWidgetItem(filePath, ui->listWidget);
        }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::clearList() {
    ui->listWidget->clear();
}

void MainWindow::convert() {
    QList<QString> filePaths;

    for (int index: range(0, ui->listWidget->count())) {
        filePaths.append(ui->listWidget->item(index)->text());
    }

    auto converter = new Converter(nullptr, &filePaths);
    converter->convertToFrames();

}

