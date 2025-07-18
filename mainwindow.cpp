#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFile"
#include "QDir"
#include "QDirListing"
#include "QFileInfo"
#include "QMessageBox"
#include "QUrl"
#include "QDesktopServices"
#include "QThread"
#include "QStorageInfo"
#include "QStandardPaths"
#include "QVector"
#include "QInputDialog"
#include "qmenu.h"
#include "QProcess"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_path->setText(current_dir.path());

    show_dir("");
    show_volumes();
    show_libs();

    this->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_files_itemDoubleClicked(QListWidgetItem *item)
{
    QString item_name = "/" + item->text();
    QFileInfo info(current_dir.absolutePath() + item_name);
    QUrl fileurl = QUrl::fromLocalFile(info.absoluteFilePath());
    if(info.isDir()){
        show_dir(item->text());
    }else{
        QDesktopServices::openUrl(fileurl);
    }
}

void MainWindow::show_dir(QString path){
    current_dir.cd(path);
    ui->lineEdit_path->setText(current_dir.path());
    ui->listWidget_files->clear();
    foreach(auto copy, current_dir.entryList()){
        if(copy != "."){
            QFileInfo info(current_dir.path()+ "/" + copy);
            QListWidgetItem *item = new QListWidgetItem(copy);
            if(info.isDir()){
                item->setIcon(QIcon(":/assets/imagens/folder2.png"));
                //ui->listWidget_files->addItem()
            }else if(info.isFile()){
                item->setIcon(QIcon(":/assets/imagens/file2.ico"));
            }
            ui->listWidget_files->addItem(item);
        }
    }


}

void MainWindow::show_libs(){
    QString home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString documentos_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString downloads_path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString pics_path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString musics_path = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    ui->listWidget_libs->addItem(home_path);
    ui->listWidget_libs->addItem(documentos_path);
    ui->listWidget_libs->addItem(downloads_path);
    ui->listWidget_libs->addItem(pics_path);
    ui->listWidget_libs->addItem(musics_path);
}

void MainWindow::show_volumes(){
    foreach(auto copy, QStorageInfo::mountedVolumes()){
        QString device = copy.device();
        if(device.startsWith("/dev/sd")){
            ui->listWidget_disks->addItem(copy.device());
        }
    }
}

void MainWindow::on_lineEdit_path_returnPressed()
{
    QString dir_path = ui->lineEdit_path->text();
    current_dir.setPath(dir_path);
    QFileInfo info(current_dir.path());
    if(info.isDir()){
        show_dir(dir_path);
    }else{
        QMessageBox::about(this,"","Unknown dir:" + dir_path);
    }
}


void MainWindow::on_pushButton_go_clicked()
{
    QString dir_path = ui->lineEdit_path->text();
    current_dir.setPath(dir_path);
    QFileInfo info(current_dir.path());
    if(info.isDir()){
        show_dir(dir_path);
    }else{
        QMessageBox::about(this,"","Unknown dir:" + dir_path);
    }
}


void MainWindow::on_listWidget_libs_itemDoubleClicked(QListWidgetItem *item)
{
    show_dir(item->text());
}


void MainWindow::on_pushButton_make_folder_clicked()
{
    bool ok;
    QString folder_name = QInputDialog::getText(nullptr,"Create folder","Folder:",QLineEdit::Normal,"name",&ok);
    if(ok && !folder_name.isEmpty()){
        current_dir.mkdir(folder_name);
        show_dir(current_dir.path());
    }
}


void MainWindow::on_pushButton_make_file_clicked()
{
    bool exist = false;
    QString file_name = QInputDialog::getText(this,"Create File","name:");
    foreach(auto copy,current_dir.entryList()){
        if(copy == file_name){
            QMessageBox::about(this,"Error","Arquivo ja existe");
            exist = true;
            break;
        }
    }

    if(!exist){
        QString full_path = current_dir.path() + "/" + file_name;
        QFile file(full_path);
        file.open(QIODevice::ReadWrite);
        file.close();
        show_dir(current_dir.path());
    }
}


void MainWindow::on_pushButton_clicked()
{
    QString current_file = ui->listWidget_files->currentItem()->text();
    QString full_path = current_dir.path() + "/" + current_file;
    bool excluir = QMessageBox::question(this,"Deseja excluir","Deseja realmente excluir:" + current_file);
    if(excluir){
        QFileInfo info(full_path);
        if(info.isDir()){
            current_dir.setPath(full_path);
            current_dir.removeRecursively();
            current_dir.cdUp();
        }else{
            current_dir.remove(current_file);
        }
    }
    show_dir(current_dir.path());
}


void MainWindow::on_pushButton_addcustom_clicked()
{
    QString path = QInputDialog::getText(this,"Add a custom path","path:");
    QFileInfo info(path);
    if(info.isDir()){
        saved_paths.push_back(path);
        ui->listWidget_custom->addItem(path);
    }else if(!info.isDir() or path == ""){
        QMessageBox::about(this,"Error","Not a dir:"+path);
    }
}

void MainWindow::on_pushButton_save_custom_clicked()
{
    QString home_path = QDir::homePath();
    QString save_name = home_path + "/whale_save.data";
    QMessageBox::about(this,"",save_name);
    QFile custom_save_file(save_name);
    custom_save_file.open(QIODeviceBase::ReadWrite | QIODeviceBase::Append);
    if(custom_save_file.isOpen()){
        foreach(auto copy,saved_paths){
            custom_save_file.write(copy.toUtf8() + "\n");
        }
    }
    custom_save_file.close();
}

void MainWindow::on_pushButton_custom_refresh_clicked()
{
    QString home_path = QDir::homePath();
    QString saved_path = home_path + "/whale_save.data";
    QFile saved_file(saved_path);
    QVector<QString>data;
    saved_file.open(QIODeviceBase::ReadOnly);
    if(saved_file.isOpen()){
        while(!saved_file.atEnd()){
            data.push_back(saved_file.readLine().replace("\n",""));
        }
        saved_file.close();
    }
    ui->listWidget_custom->clear();
    foreach(auto copy,data){
        ui->listWidget_custom->addItem(copy);
    }

}


void MainWindow::on_listWidget_custom_itemDoubleClicked(QListWidgetItem *item)
{
    show_dir(item->text());
}


void MainWindow::on_listWidget_files_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Copy", this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
    contextMenu.addAction(&action1);

    contextMenu.exec(pos);
}



void MainWindow::on_pushButton_copy_clicked()
{
    QString current_file = ui->listWidget_files->currentItem()->text();
    QString full_path = current_dir.path() + "/" + current_file;
    QFileInfo info(full_path);

    QMessageBox::about(this,"",full_path);
    copy_file_path = full_path;
    copy_file_name = current_file;
    ui->pushButton_paste->setEnabled(true);
}


void MainWindow::on_pushButton_paste_clicked()
{
    QString copy_full = copy_file_path;
    QString dest = current_dir.path();
    QMessageBox::about(this,"","copy:" + copy_full + "\n" + "dest:"+dest);
    QProcess process;
    QStringList args = {"-r",copy_full,dest};
    process.start("cp",args);
    if(process.waitForFinished()){
        show_dir(current_dir.path());
    }
}


void MainWindow::on_pushButton_move_clicked()
{
    QString current_file = ui->listWidget_files->currentItem()->text();
    QString full_path = current_dir.path() + "/" + current_file;
    QFileInfo info(full_path);

    QMessageBox::about(this,"",full_path);
    copy_file_path = full_path;
    copy_file_name = current_file;
    ui->pushButton_pastemove->setEnabled(true);
}


void MainWindow::on_pushButton_pastemove_clicked()
{
    QString copy_full = copy_file_path;
    QString dest = current_dir.path();
    QMessageBox::about(this,"","copy:" + copy_full + "\n" + "dest:"+dest);
    QProcess process;
    QStringList args = {"-f",copy_full,dest};
    process.start("mv",args);
    if(process.waitForFinished()){
        show_dir(current_dir.path());
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString rename = QInputDialog::getText(this,"Rename to","new name:");
    if(rename != ""){
        QString current_file = ui->listWidget_files->currentItem()->text();
        QString full_path = current_dir.path() + "/" + current_file;
        QString full_path_rename = current_dir.path() + "/" + rename;
        QProcess process;
        QStringList args = {full_path,full_path_rename};
        process.start("mv",args);
        if(process.waitForFinished()){
            show_dir(current_dir.path());
        }
    }
}


void MainWindow::on_lineEdit_search_textChanged(const QString &arg1)
{
    QString search_text = arg1;
    ui->listWidget_files->clear();
    foreach(auto copy,current_dir.entryList()){
        if(copy.contains(search_text)){
            ui->listWidget_files->addItem(copy);
        }
    }
}

void MainWindow::on_pushButton_custom_delete_clicked()
{
    QListWidgetItem *item = ui->listWidget_custom->currentItem();
    if(item){
        QListWidgetItem *deleted_item = ui->listWidget_custom->takeItem(ui->listWidget_custom->row(item));
        delete deleted_item;
    }
}

