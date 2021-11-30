#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

template <typename T>
std::vector <T> range(T N1, T N2) {
    std::vector<T> numbers(N2-N1);
    iota(numbers.begin(), numbers.end(), N1);
    return numbers;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void clearList();
    void convert();
    void rowsChanged(const QModelIndex &parent, int first, int last);
    void exitApplication(bool checked);

};
#endif // MAINWINDOW_H
