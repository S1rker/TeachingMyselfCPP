#include "loginScreen.h"
#include "Authentication.h"
#include "signUpDialog.h"

#include <vector>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

LoginScreen::LoginScreen(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Log in");
    setFixedWidth(320);

    m_user = new QLineEdit;
    m_user->setPlaceholderText("Username");

    m_pass = new QLineEdit;
    m_pass->setPlaceholderText("Password");
    m_pass->setEchoMode(QLineEdit::Password);

    m_error = new QLabel;
    m_error->setStyleSheet("color: #c0392b;");
    m_error->hide();

    auto *loginBtn = new QPushButton("Log in");
    loginBtn->setDefault(true);   // Enter key triggers it

    auto *signUpBtn = new QPushButton("Create account");
    signUpBtn->setFlat(true);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_user);
    layout->addWidget(m_pass);
    layout->addWidget(m_error);
    layout->addWidget(loginBtn);
    layout->addWidget(signUpBtn);
    
    
    
    connect(loginBtn, &QPushButton::clicked, this, &LoginScreen::tryLogin);
    connect(m_pass, &QLineEdit::returnPressed, this, &LoginScreen::tryLogin);
    connect(signUpBtn, &QPushButton::clicked, this, [this] {
    SignUpDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        m_user->setText(dlg.username());   // prefill
        m_pass->clear();
        m_pass->setFocus();
        m_error->setStyleSheet("color: #27ae60;");
        m_error->setText("Account created. Please log in.");
        m_error->show();
    }
});
}

QString LoginScreen::username() const { return m_user->text(); }

void LoginScreen::tryLogin() {
    if (authenticate(m_user->text(), m_pass->text())) {
        accept();                 // makes exec() return QDialog::Accepted
    } else {
        m_error->setText("Invalid username or password.");
        m_error->show();
        m_pass->clear();
        m_pass->setFocus();
    }
}

bool LoginScreen::authenticate(const QString &user, const QString &password) {
    // PLACEHOLDER: replace with a real check (see notes below)
    Authentication Auth;
    if (Auth.loginCheck(user.toStdString(), password.toStdString()))
        return true;
    else
        return false;
}

std::vector<std::string> LoginScreen::roomAuthenticate(const QString &user)
{
    Authentication Auth;
    return Auth.roomBuild(user.toStdString());
}