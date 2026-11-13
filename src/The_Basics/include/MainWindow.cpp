/*
This is the layout for the app here will be scroll 
box which will containt different chat rooms from 
different people they will be labeled with name so
people know who they are talking to at the top of the app
there will be a search feature as will as a method to add new chat rooms
to the right of the scroll box there will be messaging box 
that shows all previous messages and who they where sent by
name at the above the message is where the name will be placed
at the button there will be a text box to add new messages to the chat
I only want one on one chats no need for multiple different people in one chat room
also one text message in the chat no files can be sent and links will just be read as 
normal text.
*/
#include "MainWindow.h"
#include "loginScreen.h"
#include "Authentication.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(const QString &username, QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    m_rooms = new QStackedWidget;
    m_group = new QButtonGroup(this);
    m_group->setExclusive(true);

    // ---- Scrollable button column ----
    auto *sidebarContent = new QWidget;
    m_sidebarLayout = new QVBoxLayout(sidebarContent);
    m_sidebarLayout->setAlignment(Qt::AlignTop);

    m_scroll = new QScrollArea;
    m_scroll->setWidget(sidebarContent);
    m_scroll->setWidgetResizable(true);
    m_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scroll->setFrameShape(QFrame::NoFrame);

    // ---- Search box (above) and add button (below) ----
    m_search = new QLineEdit;
    m_search->setPlaceholderText("Search rooms...");
    m_search->setClearButtonEnabled(true);

    auto *addBtn = new QPushButton("+ Add Room");

    auto *sidebar = new QWidget;
    sidebar->setFixedWidth(200);
    auto *sidebarOuter = new QVBoxLayout(sidebar);
    sidebarOuter->setContentsMargins(6, 6, 6, 6);
    sidebarOuter->addWidget(m_search);
    sidebarOuter->addWidget(m_scroll, 1);
    sidebarOuter->addWidget(addBtn);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(m_rooms, 1);

    // ---- Connections ----
    connect(m_group, &QButtonGroup::idClicked, m_rooms, &QStackedWidget::setCurrentIndex);
    connect(m_search, &QLineEdit::textChanged, this, &MainWindow::applyFilter);
    connect(addBtn, &QPushButton::clicked, this, [this, username] {
        promptForRoom(username);
    });

    LoginScreen loginScreen;
    std::vector<std::string> list = loginScreen.roomAuthenticate(username);

    for (const std::string &room : list) {
        const QString name = QString::fromStdString(room);
        addRoom(new Room(name, username));
    }

    if (QAbstractButton *firstButton = m_group->button(0))
        firstButton->setChecked(true);
}

void MainWindow::addRoom(Room *room) {
    const int id = m_rooms->count();
    m_rooms->addWidget(room);            // stack takes ownership

    auto *btn = new QPushButton(room->name());
    btn->setCheckable(true);
    btn->setMinimumHeight(60);
    m_sidebarLayout->addWidget(btn);
    m_group->addButton(btn, id);

    applyFilter(m_search->text());     // respect any active search
}


void MainWindow::applyFilter(const QString &text) {
    const QString needle = text.trimmed();
    for (QAbstractButton *btn : m_group->buttons())
        btn->setVisible(needle.isEmpty() ||
                        btn->text().contains(needle, Qt::CaseInsensitive));
}



void MainWindow::promptForRoom(const QString &username) {
    bool ok = false;
    const QString name = QInputDialog::getText(this, "New Room", "Room name:", QLineEdit::Normal, "", &ok).trimmed();
    if (!ok || name.isEmpty())
        return;

    // Prevent duplicates (case-insensitive)
    for (QAbstractButton *btn : m_group->buttons()) {
        if (btn->text().compare(name, Qt::CaseInsensitive) == 0) {
            m_search->setText(name);   // just show the existing one
            return;
        }
    }
    Authentication Auth;
    if (!Auth.addRoom(username.toStdString(), name.toStdString())) return;

    m_search->clear();                 // make sure the new room is visible
    addRoom(new Room(name, username));

    // Select it and show its page
    connect(m_rooms, &QStackedWidget::currentChanged, this, [this](int i) {
    if (auto *old = qobject_cast<Room *>(m_rooms->widget(m_current))) old->onLeave();
    m_current = i;
    if (auto *now = qobject_cast<Room *>(m_rooms->widget(i))) now->onEnter();});

}