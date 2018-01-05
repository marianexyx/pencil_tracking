/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNONE;
    QAction *action_refreshPorts;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *outputgrid;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *output;
    QLineEdit *commandLine;
    QPushButton *enterButton;
    QGridLayout *toolButtonGrid;
    QPushButton *visual;
    QPushButton *MusicPlayer;
    QSpacerItem *verticalSpacer;
    QComboBox *port;
    QMenuBar *menuBar;
    QMenu *menuTools;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(527, 296);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
        actionNONE = new QAction(MainWindow);
        actionNONE->setObjectName(QStringLiteral("actionNONE"));
        actionNONE->setCheckable(true);
        action_refreshPorts = new QAction(MainWindow);
        action_refreshPorts->setObjectName(QStringLiteral("action_refreshPorts"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        outputgrid = new QGridLayout();
        outputgrid->setSpacing(6);
        outputgrid->setObjectName(QStringLiteral("outputgrid"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        output = new QPlainTextEdit(groupBox);
        output->setObjectName(QStringLiteral("output"));
        output->setReadOnly(true);
        output->setOverwriteMode(false);

        gridLayout_2->addWidget(output, 0, 0, 1, 1);


        outputgrid->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout->addLayout(outputgrid, 0, 0, 1, 1);

        commandLine = new QLineEdit(centralWidget);
        commandLine->setObjectName(QStringLiteral("commandLine"));
        commandLine->setDragEnabled(false);

        gridLayout->addWidget(commandLine, 1, 0, 1, 1);

        enterButton = new QPushButton(centralWidget);
        enterButton->setObjectName(QStringLiteral("enterButton"));

        gridLayout->addWidget(enterButton, 1, 1, 1, 1);

        toolButtonGrid = new QGridLayout();
        toolButtonGrid->setSpacing(6);
        toolButtonGrid->setObjectName(QStringLiteral("toolButtonGrid"));
        visual = new QPushButton(centralWidget);
        visual->setObjectName(QStringLiteral("visual"));

        toolButtonGrid->addWidget(visual, 1, 0, 1, 1);

        MusicPlayer = new QPushButton(centralWidget);
        MusicPlayer->setObjectName(QStringLiteral("MusicPlayer"));

        toolButtonGrid->addWidget(MusicPlayer, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        toolButtonGrid->addItem(verticalSpacer, 3, 0, 1, 1);

        port = new QComboBox(centralWidget);
        port->setObjectName(QStringLiteral("port"));

        toolButtonGrid->addWidget(port, 0, 0, 1, 1);


        gridLayout->addLayout(toolButtonGrid, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 527, 21));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuTools->menuAction());
        menuTools->addAction(action_refreshPorts);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ArduinoManager", nullptr));
        actionNONE->setText(QApplication::translate("MainWindow", "NONE", nullptr));
        action_refreshPorts->setText(QApplication::translate("MainWindow", "Refresh Ports", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Output Console", nullptr));
        commandLine->setText(QString());
        commandLine->setPlaceholderText(QString());
        enterButton->setText(QApplication::translate("MainWindow", "Enter", nullptr));
        visual->setText(QApplication::translate("MainWindow", "Visualize", nullptr));
        MusicPlayer->setText(QApplication::translate("MainWindow", "Music Player", nullptr));
        menuTools->setTitle(QApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
