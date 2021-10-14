#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QColor>
#include <QColorDialog>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    on_actionNew_triggered();

    //init settings
    ui->textEdit->setFont(QFont("Arial",11,2,false));
    ui->actionSave->setDisabled(true);
    i=0;
    isSaved = false;

    wrap = false;
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    filePath = "./NewFile.txt";           //current file's path
    QFile file(filePath);
    QFileInfo fInfo(file);

      while(fInfo.exists()){

        filePath = "./NewFile("+QString::number(i+1)+").txt" ;
        fInfo.setFile(filePath);
        i++;
        if(!fInfo.exists())
            break;
     }

    ui->textEdit->setText("");
    this->setWindowTitle("*"+fInfo.fileName());
}

void MainWindow::on_actionOpen_triggered()
{
    //open file dialog
    QString sel_file = QFileDialog::getOpenFileName(this,"Open File");
    filePath= sel_file;
    QFile file(filePath);
    //open file as text in read mode
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","file can not be opened !");
        return;
    }

    QTextStream is(&file);
    QString fileContent = is.readAll();
    //set content to text edit
    ui->textEdit->setText(fileContent);
    file.close();

    QFileInfo fInfo(sel_file);
    this->setWindowTitle(fInfo.fileName());

}

void MainWindow::on_actionSave_triggered()
{

    //save file to current path
    QFile file(filePath);


    //open file as text in write mode
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","file can not be opened !");
        return;
    }

    QTextStream os(&file);
    QString currentContent = ui->textEdit->toPlainText();
    os<<currentContent;
    file.flush();
    file.close();

    QFileInfo fInfo(filePath);
    this->setWindowTitle(fInfo.fileName());

    ui->actionSave->setDisabled(true);
    setStatusBar(QString("Saved"));
}

void MainWindow::on_actionSave_As_triggered()
{
    //Open File Dialog
    QString fileName = QFileDialog::getSaveFileName(this,"Save As");
    //update file path
    filePath = fileName;

    QFile file(fileName);

    //open file as text in write mode
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","file can not be opened !");
        return;
    }

    QTextStream os(&file);
    QString currentContent = ui->textEdit->toPlainText();
    os<<currentContent;
    file.flush();
    file.close();


    QFileInfo fInfo(filePath);
    this->setWindowTitle(fInfo.fileName());
}

void MainWindow::on_actionCut_triggered()
{
  ui->textEdit->cut();
   ui->actionCut->setDisabled(true);
}

void MainWindow::on_actionCopy_triggered()
{
  ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
  ui->textEdit->paste();
   ui->actionCut->setEnabled(true);
}

void MainWindow::on_actionUndo_triggered()
{
  ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
 ui->textEdit->redo();
}


//if cursor pos changed
void MainWindow::on_textEdit_cursorPositionChanged()
{
    ui->actionSave->setEnabled(true);
    isSaved = false;
    if(!isSaved){
        if(this->windowTitle().at(0) != '*')
        {
        this->setWindowTitle("*" + this->windowTitle());
        isSaved = true;
        }
    }


    setStatusBar(QString("Unsaved"));


}

//Set text to statusbar
void MainWindow::setStatusBar(const QString& status){

    const  QTextCursor& tcur  = ui->textEdit->textCursor();
     int lineno = tcur.blockNumber();
     int colno = tcur.columnNumber();
     int lineno2 = ui->textEdit->document()->lineCount();


     //show position in status bar
     ui->statusBar->showMessage("Line:" + QString::number(lineno2)+
                                "\t\t Col:"+  QString::number(colno)
                                +"\t\t\t Status:" + status);

}

//font dialog
void MainWindow::on_actionFont_triggered()
{
    bool selected;
    QFont f= QFontDialog::getFont(&selected,this);

    if(selected){
        ui->textEdit->setFont(f);
    }else
        return;


}

//Color dialog
void MainWindow::on_actionColor_triggered()
{

   QColor c =  QColorDialog::getColor(Qt::black,this,"Choose Color");

   if(c.isValid())
   ui->textEdit->setTextColor(c);
   update();

}

void MainWindow::on_actionBackground_triggered()
{

    QColor c =  QColorDialog::getColor(Qt::white,this);

    if(c.isValid()){

    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base,c);
    ui->textEdit->setPalette(pal);
    update();

    }
}

void MainWindow::on_actionWrap_triggered()
{
    if(wrap == false){
      ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
      wrap = true;

      setStatusBar(QString("Unsaved"));
      return;
    }
    if(wrap == true){
         ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
        wrap = false;
          setStatusBar(QString("Unsaved"));
        return;
    }



}


