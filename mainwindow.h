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
private:
    void show_libs();
    void show_volumes();
    void show_dir(QString path,int tab_index = 0);
    QDir home_dir = QDir::homePath();
    QDir current_dir;
    QVector<QString>copy_files_paths;
    QVector<QString>saved_paths;
    Ui::MainWindow *ui;
    void make_listwidget();
    QVector<QListWidget*>list_widget_vec;
    QVector<QString>vec_tab_path;
public:
    MainWindow(QWidget *parent = nullptr,QString dir = "");
    ~MainWindow();

private slots:
    void context_menu(const QPoint& pos);
    void custom_context_shortcut(const QPoint& pos);
    void on_listWidget_files_itemDoubleClicked(QListWidgetItem *item);

    void on_lineEdit_path_returnPressed();

    void on_pushButton_go_clicked();

    void on_listWidget_libs_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_make_folder_clicked();

    void on_pushButton_make_file_clicked();

    void on_pushButton_addcustom_clicked();

    void on_listWidget_custom_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_files_customContextMenuRequested(const QPoint &pos);
    void on_pushButton_copy_clicked();

    void on_pushButton_paste_clicked();

    void on_pushButton_move_clicked();

    void on_pushButton_pastemove_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_rename_clicked();

    void on_lineEdit_search_textChanged(const QString &arg1);


    void on_pushButton_save_custom_clicked();

    void on_pushButton_custom_refresh_clicked();

    void on_pushButton_custom_delete_clicked();


    void on_listWidget_disks_itemDoubleClicked(QListWidgetItem *item);
    void on_tabWidget_tabBarDoubleClicked(int index);
    void on_tabWidget_currentChanged(int index);
};
#endif // MAINWINDOW_H
