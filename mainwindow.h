#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdir.h>
#include <qlistwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_files_itemDoubleClicked(QListWidgetItem *item);

    void on_lineEdit_path_returnPressed();

    void on_pushButton_go_clicked();

    void on_listWidget_libs_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_make_folder_clicked();

    void on_pushButton_make_file_clicked();

    void on_pushButton_clicked();

    void on_pushButton_addcustom_clicked();

    void on_listWidget_custom_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_files_customContextMenuRequested(const QPoint &pos);
    void on_pushButton_copy_clicked();

    void on_pushButton_paste_clicked();

    void on_pushButton_move_clicked();

    void on_pushButton_pastemove_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_search_textChanged(const QString &arg1);


private:
    void show_libs();
    void show_volumes();
    void show_dir(QString path);
    QDir home_dir = QDir::homePath();
    QDir current_dir = home_dir.absolutePath();
    QString copy_file_path;
    QString copy_file_name;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
