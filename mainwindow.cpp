#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("note1 - CorPad");
    this->setCentralWidget(ui->note);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCopy_triggered()
{
    ui->note->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->note->cut();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->note->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::currentPath(), "Text files (*.txt)");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName.split("/").back().split(".txt").front() + " - CorPad");
    QTextStream in(&file);
    QString text = in.readAll();
    ui->note->setText(text);
    file.close();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->note->paste();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "warning", "Cannot access printer");
        return;
    }
    ui->note->print(&printer);
}

void MainWindow::on_actionRedo_triggered()
{
    ui->note->redo();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file (currentFile);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save current file");
        return;
    }
    QTextStream out(&file);
    QString text = ui->note->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as...");
    QFile file (fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->note->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->note->undo();
}
