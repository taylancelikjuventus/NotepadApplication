#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setStatusBar(const QString& status);
    
private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_textEdit_cursorPositionChanged();

    void on_actionFont_triggered();

    void on_actionColor_triggered();

    void on_actionBackground_triggered();

    void on_actionWrap_triggered();

    void on_actionWrap_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    QString filePath;
    int i;
     bool isSaved;
     bool wrap;
};

#endif // MAINWINDOW_H
