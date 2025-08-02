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
MainWindow::MainWindow(QWidget *parent,QString dir)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::on_pushButton_custom_refresh_clicked();
    current_dir.setPath(dir);
    ui->lineEdit_path->setText(current_dir.path());
    show_volumes();
    show_libs();
    make_listwidget();
    ui->tabWidget->addTab(list_widget_vec[0],"Tab");
    show_dir(current_dir.path());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make_listwidget(){
    QListWidget *listwidget = new QListWidget(centralWidget());
    listwidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    connect(listwidget,&QListWidget::itemDoubleClicked,this,&MainWindow::on_listWidget_files_itemDoubleClicked);
    list_widget_vec.push_back(listwidget);
    vec_tab_path.push_back("");
}

void MainWindow::on_listWidget_files_itemDoubleClicked(QListWidgetItem *item)
{
    QString item_name = "/" + item->text();
    QFileInfo info(current_dir.absolutePath() + item_name);
    QUrl fileurl = QUrl::fromLocalFile(info.absoluteFilePath());
    if(info.isDir()){
        show_dir(item->text(),ui->tabWidget->currentIndex());
    }else{
        QDesktopServices::openUrl(fileurl);
    }
}

void MainWindow::show_dir(QString path,int tab_index){
    current_dir.cd(path);
    vec_tab_path[tab_index] = current_dir.path();
    ui->lineEdit_path->setText(vec_tab_path[tab_index]);
    list_widget_vec[tab_index]->clear(); //ui->listWidget_files->clear();
    list_widget_vec[tab_index]->setIconSize(QSize(32,32));

    QFileInfoList file_list = current_dir.entryInfoList(QDir::NoFilter,QDir::SortFlag::DirsFirst | QDir::SortFlag::Name | QDir::SortFlag::IgnoreCase).toList();
    foreach(auto copy, file_list){
        if(copy.fileName() != "."){
            QFileInfo info(current_dir.path()+ "/" + copy.fileName());
            QListWidgetItem *item = new QListWidgetItem(copy.fileName());
            if(info.isDir()){
                item->setIcon(QIcon::fromTheme("folder"));
            }else if(info.isFile()){
                item->setIcon(QIcon::fromTheme("text-x-generic"));
            }
            list_widget_vec[tab_index]->addItem(item);
            //list_widget_vec[tab_index]->sortItems(Qt::SortOrder::AscendingOrder);
        }
    }

}

void MainWindow::show_libs(){
    QString home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString documentos_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString downloads_path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString pics_path = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    QString musics_path = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QListWidgetItem *item1 = new QListWidgetItem(QIcon::fromTheme("folder"),home_path);
    QListWidgetItem *item2 = new QListWidgetItem(QIcon::fromTheme("folder"),documentos_path.replace(QDir::homePath(),""));
    QListWidgetItem *item3 = new QListWidgetItem(QIcon::fromTheme("folder"),downloads_path.replace(QDir::homePath(),""));
    QListWidgetItem *item4 = new QListWidgetItem(QIcon::fromTheme("folder"),pics_path.replace(QDir::homePath(),""));
    QListWidgetItem *item5 = new QListWidgetItem(QIcon::fromTheme("folder"),musics_path.replace(QDir::homePath(),""));
    ui->listWidget_libs->setIconSize(QSize(32,32));
    ui->listWidget_libs->addItem(item1);
    ui->listWidget_libs->addItem(item2);
    ui->listWidget_libs->addItem(item3);
    ui->listWidget_libs->addItem(item4);
    ui->listWidget_libs->addItem(item5);
}

void MainWindow::show_volumes(){
    ui->listWidget_disks->setIconSize(QSize(32,32));
    foreach(auto copy, QStorageInfo::mountedVolumes()){
        if(copy.device().contains("dev/sd")){
            QListWidgetItem *item = new QListWidgetItem(QIcon::fromTheme("drive-harddisk"),copy.rootPath());
            ui->listWidget_disks->addItem(item);
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
        show_dir(dir_path,ui->tabWidget->currentIndex());
    }else{
        QMessageBox::about(this,"","Unknown dir:" + dir_path);
    }
}


void MainWindow::on_listWidget_libs_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text() != QDir::homePath()){
        show_dir(QDir::homePath() + item->text(),ui->tabWidget->currentIndex());
    }else{
        show_dir(QDir::homePath(),ui->tabWidget->currentIndex());
    }

}


void MainWindow::on_pushButton_make_folder_clicked()
{
    bool ok;
    QString folder_name = QInputDialog::getText(nullptr,"Create folder","Folder:",QLineEdit::Normal,"name",&ok);

    if(ok && !folder_name.isEmpty()){
        current_dir.mkdir(folder_name);
        show_dir(current_dir.path(),ui->tabWidget->currentIndex());
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
        show_dir(current_dir.path(),ui->tabWidget->currentIndex());
    }
}


void MainWindow::on_pushButton_delete_clicked()
{
    if(list_widget_vec[ui->tabWidget->currentIndex()]->currentRow() >= 0){
        QString current_file = list_widget_vec[ui->tabWidget->currentIndex()]->currentItem()->text();
        QString full_path = current_dir.path() + "/" + current_file;
        QMessageBox::StandardButton excluir = QMessageBox::question(this,"Deseja excluir","Deseja realmente excluir:" + current_file);
        if(excluir == QMessageBox::Yes){
            QFileInfo info(full_path);
            if(info.isDir()){
                current_dir.setPath(full_path);
                current_dir.removeRecursively();
                current_dir.cdUp();
            }else{
                current_dir.remove(current_file);
            }
        }
        show_dir(current_dir.path(),ui->tabWidget->currentIndex());
    }
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
    show_dir(item->text(),ui->tabWidget->currentIndex());
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
    copy_files_paths.clear();
    QList selected_items = list_widget_vec[ui->tabWidget->currentIndex()]->selectedItems();
    QString select_files = "";
    if(selected_items.size() > 0){
        foreach(auto copy_item,selected_items){
            QString full_path = current_dir.path() + "/" + copy_item->text();
            select_files += full_path + "\n";
            copy_files_paths.push_back(full_path);
        }
        QMessageBox::about(this,"Selected files",select_files);
        ui->pushButton_paste->setEnabled(true);
    }else{
        QMessageBox::about(this,"error","Select at least one item");
    }
}


void MainWindow::on_pushButton_paste_clicked()
{
    QString dest = current_dir.path();
    foreach(auto copy,copy_files_paths){
        QProcess process;
        QStringList args = {"-r",copy,dest};
        process.start("cp",args);
        if(process.waitForFinished()){
            show_dir(current_dir.path(),ui->tabWidget->currentIndex());
        }
    }
    QMessageBox::about(this,"","paste finished");
}


void MainWindow::on_pushButton_move_clicked()
{
    copy_files_paths.clear();
    QList select_items = list_widget_vec[ui->tabWidget->currentIndex()]->selectedItems();
    if(select_items.size() > 0){
        QString select_files = "";
        foreach(auto copy_item,select_items){
            QString current_file = copy_item->text();
            QString full_path = current_dir.path() + "/" + current_file;
            select_files += full_path + "\n";
            copy_files_paths.push_back(full_path);
        }
        QMessageBox::about(this,"selected files:",select_files);
        ui->pushButton_pastemove->setEnabled(true);
    }else{
        QMessageBox::about(this,"error","Select at least one item from list");
    }
}


void MainWindow::on_pushButton_pastemove_clicked()
{
    QString dest = current_dir.path();
    foreach(auto copy,copy_files_paths){
        QProcess process;
        QStringList args = {"-f",copy,dest};
        process.start("mv",args);
        if(process.waitForFinished()){
            show_dir(current_dir.path(),ui->tabWidget->currentIndex());
        }
    }
    QMessageBox::about(this,"Advice","File move finished");
}


void MainWindow::on_pushButton_rename_clicked()
{
    QString rename = QInputDialog::getText(this,"Rename to","new name:");
    if(rename != ""){
        QString current_file = list_widget_vec[ui->tabWidget->currentIndex()]->currentItem()->text();
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
    list_widget_vec[ui->tabWidget->currentIndex()]->clear();
    foreach(auto copy,current_dir.entryList()){
        if(copy != "."){
            if(copy.contains(search_text)){
                QFileInfo info(current_dir.path()+ "/" + copy);
                QListWidgetItem *item = new QListWidgetItem(copy);
                if(info.isDir()){
                    item->setIcon(QIcon::fromTheme("folder"));
                }else if(info.isFile()){
                    item->setIcon(QIcon::fromTheme("text-x-generic"));
                }
                list_widget_vec[ui->tabWidget->currentIndex()]->addItem(item);
            }
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




void MainWindow::on_listWidget_disks_itemDoubleClicked(QListWidgetItem *item)
{
    show_dir(item->text(),ui->tabWidget->currentIndex());
}


void MainWindow::on_tabWidget_tabBarDoubleClicked(int index)
{
    int newtab_index = index + 1;
    make_listwidget();
    ui->tabWidget->addTab(list_widget_vec[newtab_index],"Tab " + QString::number(newtab_index));
    show_dir(current_dir.path(),newtab_index);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->lineEdit_path->setText(vec_tab_path[index]);
    show_dir(vec_tab_path[index],index);
}

