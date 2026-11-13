#pragma once
#include <QString>
#include <QWidget>
#include "MessageRoom.h"


class QStackedWidget;
class QVBoxLayout;
class QButtonGroup;
class QLineEdit;
class QScrollArea;

class MainWindow : public QWidget {
    Q_OBJECT
    public:
        explicit MainWindow(const QString &username, QWidget *parent = nullptr);

    private:
        void addRoom(Room *room);
        void applyFilter(const QString &text);
        void promptForRoom(const QString &username);
        void loadRoom();


        QStackedWidget *m_rooms;
        QVBoxLayout *m_sidebarLayout;
        QButtonGroup *m_group;
        QLineEdit *m_search;
        QScrollArea *m_scroll;
        int m_current;
};