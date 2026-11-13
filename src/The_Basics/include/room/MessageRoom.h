#pragma once
#include <QWidget>
#include <QString>

class QVBoxLayout;
class QHBoxLayout;
class QTextEdit;
class QLineEdit;


class Room : public QWidget {
    Q_OBJECT
public:
    explicit Room(const QString &name, const QString &username, QWidget *parent = nullptr);

    QString name() const { return m_name; }
    QString username() const { return m_username; }

    // Optional hooks subclasses can override
    virtual void onEnter() {}   // called when the room becomes visible
    virtual void onLeave() {}   // called when the user switches away

public slots:
    void addMessage(const QString &message);

private:
    QString m_name;
    QString m_username;
    QVBoxLayout *m_roomLayout = nullptr;
    QHBoxLayout *m_messageLayout = nullptr;
    QLineEdit *m_textInput = nullptr;
    QTextEdit *m_textDisplay = nullptr;
};