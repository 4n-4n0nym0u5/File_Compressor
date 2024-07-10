#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Huffman.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_encodeButton_clicked();
    void on_decodeButton_clicked();
    void on_Button_clicked();

private:
    Ui::MainWindow *ui;
    HuffmanCompressor compressor;
};

#endif // MAINWINDOW_H
