#include "MessageRoom.h"

#include <QLabel>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

Room::Room(const QString &name, const QString &username, QWidget *parent)
    : QWidget(parent), m_name(name), m_username(username)
{
    m_roomLayout = new QVBoxLayout(this);
    m_roomLayout->setContentsMargins(0, 0, 0, 0);
    m_roomLayout->setSpacing(0);

    auto *page = new QLabel("Welcome to the " + m_name);
    page->setAlignment(Qt::AlignTop);
    page->setMargin(10);

    m_textDisplay = new QTextEdit(this);
    m_textDisplay->setPlaceholderText("");
    m_textDisplay->setReadOnly(true);
    m_textDisplay->setAutoFillBackground(true);

    auto *messageBar = new QWidget(this);
    m_messageLayout = new QHBoxLayout(messageBar);
    m_messageLayout->setAlignment(Qt::AlignBottom);

    m_textInput = new QLineEdit(this);
    m_textInput->setPlaceholderText("type message.");
    m_textInput->setStyleSheet("border: 1px solid gray; width: 25px; height:25px;");

    auto *textBtn = new QPushButton("Enter", this);

    m_messageLayout->addWidget(m_textInput);
    m_messageLayout->addWidget(textBtn);

    m_roomLayout->addWidget(page);
    m_roomLayout->addWidget(m_textDisplay);
    m_roomLayout->addWidget(messageBar);

    connect(textBtn, &QPushButton::clicked, this, [this] {
        addMessage(m_textInput->text());
    });

    connect(m_textInput, &QLineEdit::returnPressed, this, [this] {
        addMessage(m_textInput->text());
    });
}

void Room::addMessage(const QString &message)
{
    /*
     text format for the messages I want it look this
     name of user
     message
     (empty line)
     then repeat for every message that gets inputed.
     */
    const QString trimmedMessage = message.trimmed();
    if (trimmedMessage.isEmpty()) {
        return;
    }

    const QString author = this->m_username;
    m_textDisplay->append(author + " said");
    m_textDisplay->append(trimmedMessage);
    m_textDisplay->append("");
    m_textInput->clear();
}

