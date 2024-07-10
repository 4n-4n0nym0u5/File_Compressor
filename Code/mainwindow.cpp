#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

unsigned long a,b,e;
string outputFilePath;
string inputFilePath;
void return_size(unsigned long size)
{
    a=size;
}
void return_compSize(unsigned long compSize)
{
    b=compSize;
}
void return_effiSize(double effiSize)
{
    e=effiSize;
}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->encodeButton, &QPushButton::clicked, this, &MainWindow::on_encodeButton_clicked);
    connect(ui->decodeButton, &QPushButton::clicked, this, &MainWindow::on_decodeButton_clicked);
    //ui->label->setText("<html><head/><body><p><span style=\"font-weight:700; font-style:italic; color:#3c50aa;\">Welcome to the File Compressor</span></p></body></html>");
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_encodeButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Select a file to compress");
    if (!fileName.isEmpty()) {
        QString outputPath = QFileDialog::getSaveFileName(this, "Choose output file path");
        if (!outputPath.isEmpty()) {
            std::string inputFilePath = fileName.toStdString();
            std::string outputFilePath = outputPath.toStdString();
            compressor.encodeFile(inputFilePath, outputFilePath);
            QMessageBox::information(this, "File Compressed", "File compressed successfully!");
            QString fileSizeString = QString::number(a);
            QString compSize = QString::number(b);
            QString effiSize = QString::number(e);
            QString input = QString::fromStdString(inputFilePath);
            QString output = QString::fromStdString(outputFilePath);
            ui->label->setText("<html><head/><body><p><span style=\"font-weight:700; font-style:italic; color:#3c50aa;\">Welcome to the File Compressor</span></p>" "<p>Size of original File: " + fileSizeString + "</p>" "<p>Size of Compressed File: " + compSize + "</p>" "<p> Path of Original File:" + input + "</p>" "<p>Path of Compressed File: " + output+ "</p>" "<p>Efficiency: " + effiSize + "</p></body></html>");
            // QMessageBox::information(this,"File Size", "Size of original file: "+fileSizeString+"\n Size of Compressed File: "+compSize+"\n Path of Original File: "+input+"\n Path of Compressed File: "+output+"\n Efficiency: "+effiSize);


        }
    }
    disconnect(ui->encodeButton, &QPushButton::clicked, this, &MainWindow::on_encodeButton_clicked);
}

void MainWindow::on_decodeButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select an encoded file(.tfs) to decompress");
    if (!fileName.isEmpty()) {
        QString outputPath = QFileDialog::getSaveFileName(this, "Choose output file");
        if (!outputPath.isEmpty()) {
            std::string inputFilePath = fileName.toStdString();
            std::string outputFilePath = outputPath.toStdString();
            compressor.decodeFile(inputFilePath, outputFilePath);
            QMessageBox::information(this, "File Decompressed", "File decompressed successfully!");
        }
    }
    disconnect(ui->decodeButton, &QPushButton::clicked, this, &MainWindow::on_decodeButton_clicked);
}
