#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "converter.h"
#include "imageformatter.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMimeDatabase>
#include <numeric>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setAcceptDrops(true);

    ui->convertButton->setDisabled(true);

    connect(ui->clearButton, &QPushButton::released, this, &MainWindow::clearList);
    connect(ui->convertButton, &QPushButton::released, this, &MainWindow::convert);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitApplication);

    connect(ui->listWidget->model(), &QAbstractListModel::rowsInserted, this, &MainWindow::rowsChanged);
    connect(ui->listWidget->model(), &QAbstractListModel::rowsRemoved, this, &MainWindow::rowsChanged);

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
    ui->convertButton->setDisabled(true);
}

void MainWindow::convert() {
    QFileInfoList filePaths;

    for (int index: range(0, ui->listWidget->count())) {
        filePaths.append(QFileInfo(ui->listWidget->item(index)->text()));
    }

    auto converter = new Converter(nullptr, &filePaths);
    auto frames = converter->convertToFrames();

    auto imageFormatter = new ImageFormatter(nullptr);
    for (const auto &frame : frames){
        auto collague = imageFormatter->createImageCollage(frame);
    }



}

void MainWindow::rowsChanged(const QModelIndex &parent, int first, int last) {
    if (ui->listWidget->count() > 0) {
        ui->convertButton->setDisabled(false);
    }
}

void MainWindow::exitApplication(bool checked) {
    QApplication::exit(0);
}

