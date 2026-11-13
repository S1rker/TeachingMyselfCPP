#pragma once
#include <QDialog>

class QLineEdit;
class QLabel;

class SignUpDialog : public QDialog {
    Q_OBJECT
public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    QString username() const;

private:
    void trySignUp();
    void showError(const QString &msg);

    QLineEdit *m_user;
    QLineEdit *m_pass;
    QLineEdit *m_confirm;
    QLabel *m_error;
};