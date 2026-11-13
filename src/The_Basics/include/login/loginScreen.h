#pragma once
#include <QDialog>
#include <QString>

class QLineEdit;
class QLabel;


class LoginScreen : public QDialog {
    Q_OBJECT
    public:
        explicit LoginScreen(QWidget *parent = nullptr);
        QString username() const;
        std::vector<std::string> roomAuthenticate(const QString &user);

    private:
        void tryLogin();
        bool authenticate(const QString &user, const QString &password);
        

        QLineEdit *m_user;
        QLineEdit *m_pass;
        QLabel *m_error;
        
};