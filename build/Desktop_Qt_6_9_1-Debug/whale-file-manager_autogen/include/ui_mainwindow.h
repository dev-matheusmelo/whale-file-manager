/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCopy;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_addcustom;
    QPushButton *pushButton_custom_delete;
    QPushButton *pushButton_save_custom;
    QPushButton *pushButton_custom_refresh;
    QLabel *label;
    QListWidget *listWidget_custom;
    QLabel *label_libraries;
    QListWidget *listWidget_libs;
    QLabel *label_2;
    QListWidget *listWidget_disks;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_go;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_make_folder;
    QPushButton *pushButton_make_file;
    QLineEdit *lineEdit_search;
    QListWidget *listWidget_files;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_move;
    QPushButton *pushButton_pastemove;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_copy;
    QPushButton *pushButton_paste;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(709, 733);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditCopy));
        actionCopy->setIcon(icon);
        actionCopy->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_6 = new QHBoxLayout(centralwidget);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        pushButton_addcustom = new QPushButton(centralwidget);
        pushButton_addcustom->setObjectName("pushButton_addcustom");
        pushButton_addcustom->setMinimumSize(QSize(50, 41));
        pushButton_addcustom->setMaximumSize(QSize(50, 41));

        horizontalLayout_5->addWidget(pushButton_addcustom);

        pushButton_custom_delete = new QPushButton(centralwidget);
        pushButton_custom_delete->setObjectName("pushButton_custom_delete");
        pushButton_custom_delete->setMinimumSize(QSize(50, 41));
        pushButton_custom_delete->setMaximumSize(QSize(50, 41));

        horizontalLayout_5->addWidget(pushButton_custom_delete);

        pushButton_save_custom = new QPushButton(centralwidget);
        pushButton_save_custom->setObjectName("pushButton_save_custom");
        sizePolicy.setHeightForWidth(pushButton_save_custom->sizePolicy().hasHeightForWidth());
        pushButton_save_custom->setSizePolicy(sizePolicy);
        pushButton_save_custom->setMaximumSize(QSize(16777215, 41));

        horizontalLayout_5->addWidget(pushButton_save_custom);

        pushButton_custom_refresh = new QPushButton(centralwidget);
        pushButton_custom_refresh->setObjectName("pushButton_custom_refresh");
        pushButton_custom_refresh->setMinimumSize(QSize(50, 41));
        pushButton_custom_refresh->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(pushButton_custom_refresh);


        verticalLayout->addLayout(horizontalLayout_5);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        listWidget_custom = new QListWidget(centralwidget);
        listWidget_custom->setObjectName("listWidget_custom");
        listWidget_custom->setMinimumSize(QSize(256, 217));
        listWidget_custom->setMaximumSize(QSize(256, 217));

        verticalLayout->addWidget(listWidget_custom);

        label_libraries = new QLabel(centralwidget);
        label_libraries->setObjectName("label_libraries");

        verticalLayout->addWidget(label_libraries);

        listWidget_libs = new QListWidget(centralwidget);
        listWidget_libs->setObjectName("listWidget_libs");
        listWidget_libs->setMinimumSize(QSize(256, 218));
        listWidget_libs->setMaximumSize(QSize(256, 218));

        verticalLayout->addWidget(listWidget_libs);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        listWidget_disks = new QListWidget(centralwidget);
        listWidget_disks->setObjectName("listWidget_disks");
        listWidget_disks->setMinimumSize(QSize(256, 217));
        listWidget_disks->setMaximumSize(QSize(256, 217));

        verticalLayout->addWidget(listWidget_disks);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEdit_path = new QLineEdit(centralwidget);
        lineEdit_path->setObjectName("lineEdit_path");

        horizontalLayout->addWidget(lineEdit_path);

        pushButton_go = new QPushButton(centralwidget);
        pushButton_go->setObjectName("pushButton_go");

        horizontalLayout->addWidget(pushButton_go);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_make_folder = new QPushButton(centralwidget);
        pushButton_make_folder->setObjectName("pushButton_make_folder");

        horizontalLayout_2->addWidget(pushButton_make_folder);

        pushButton_make_file = new QPushButton(centralwidget);
        pushButton_make_file->setObjectName("pushButton_make_file");

        horizontalLayout_2->addWidget(pushButton_make_file);


        verticalLayout_2->addLayout(horizontalLayout_2);

        lineEdit_search = new QLineEdit(centralwidget);
        lineEdit_search->setObjectName("lineEdit_search");
        lineEdit_search->setStyleSheet(QString::fromUtf8(""));
        lineEdit_search->setClearButtonEnabled(true);

        verticalLayout_2->addWidget(lineEdit_search);

        listWidget_files = new QListWidget(centralwidget);
        listWidget_files->setObjectName("listWidget_files");
        listWidget_files->setMouseTracking(false);
        listWidget_files->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        listWidget_files->setStyleSheet(QString::fromUtf8(""));
        listWidget_files->setDefaultDropAction(Qt::DropAction::MoveAction);
        listWidget_files->setViewMode(QListView::ViewMode::ListMode);

        verticalLayout_2->addWidget(listWidget_files);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_2->addWidget(pushButton_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_move = new QPushButton(centralwidget);
        pushButton_move->setObjectName("pushButton_move");

        horizontalLayout_4->addWidget(pushButton_move);

        pushButton_pastemove = new QPushButton(centralwidget);
        pushButton_pastemove->setObjectName("pushButton_pastemove");

        horizontalLayout_4->addWidget(pushButton_pastemove);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_copy = new QPushButton(centralwidget);
        pushButton_copy->setObjectName("pushButton_copy");

        horizontalLayout_3->addWidget(pushButton_copy);

        pushButton_paste = new QPushButton(centralwidget);
        pushButton_paste->setObjectName("pushButton_paste");
        pushButton_paste->setEnabled(false);

        horizontalLayout_3->addWidget(pushButton_paste);


        verticalLayout_2->addLayout(horizontalLayout_3);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout_6->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Whale File Manager", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        pushButton_addcustom->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pushButton_custom_delete->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pushButton_save_custom->setText(QCoreApplication::translate("MainWindow", "SAVE", nullptr));
        pushButton_custom_refresh->setText(QCoreApplication::translate("MainWindow", "RE", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Rapid Access:", nullptr));
        label_libraries->setText(QCoreApplication::translate("MainWindow", "Libraries:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Devices:", nullptr));
        lineEdit_path->setText(QCoreApplication::translate("MainWindow", "Path", nullptr));
        pushButton_go->setText(QCoreApplication::translate("MainWindow", "GO", nullptr));
        pushButton_make_folder->setText(QCoreApplication::translate("MainWindow", "MAKE FOLDER", nullptr));
        pushButton_make_file->setText(QCoreApplication::translate("MainWindow", "MAKE FILE", nullptr));
        lineEdit_search->setInputMask(QString());
        lineEdit_search->setText(QString());
        lineEdit_search->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "RENAME", nullptr));
        pushButton_move->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
        pushButton_pastemove->setText(QCoreApplication::translate("MainWindow", "Paste move", nullptr));
        pushButton_copy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        pushButton_paste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "DELETE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
