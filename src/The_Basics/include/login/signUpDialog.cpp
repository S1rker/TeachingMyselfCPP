#include "signUpDialog.h"
#include "Authentication.h"
#include <iostream>

#include <QDir>
#include <QStandardPaths>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QVBoxLayout>

SignUpDialog::SignUpDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Create account");
    setFixedWidth(320);

    m_user = new QLineEdit;
    m_user->setPlaceholderText("Username (letters, numbers, _ . -)");

    m_pass = new QLineEdit;
    m_pass->setPlaceholderText("Password (8+ characters)");
    m_pass->setEchoMode(QLineEdit::Password);

    m_confirm = new QLineEdit;
    m_confirm->setPlaceholderText("Confirm password");
    m_confirm->setEchoMode(QLineEdit::Password);

    m_error = new QLabel;
    m_error->setStyleSheet("color: #c0392b;");
    m_error->setWordWrap(true);
    m_error->hide();

    auto *createBtn = new QPushButton("Create account");
    createBtn->setDefault(true);
    auto *cancelBtn = new QPushButton("Back to login");

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_user);
    layout->addWidget(m_pass);
    layout->addWidget(m_confirm);
    layout->addWidget(m_error);
    layout->addWidget(createBtn);
    layout->addWidget(cancelBtn);

    connect(createBtn, &QPushButton::clicked, this, &SignUpDialog::trySignUp);
    connect(m_confirm, &QLineEdit::returnPressed, this, &SignUpDialog::trySignUp);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

QString SignUpDialog::username() const { return m_user->text().trimmed(); }

void SignUpDialog::showError(const QString &msg) {
    m_error->setText(msg);
    m_error->show();
}

void SignUpDialog::trySignUp() {
    static const QRegularExpression validName("^[A-Za-z0-9_.-]{3,32}$");
    const QString user = username();

    if (!validName.match(user).hasMatch())
        return showError("Username must be 3-32 characters: letters, numbers, _ . -");
    if (m_pass->text().size() < 8)
        return showError("Password must be at least 8 characters.");
    if (m_pass->text() != m_confirm->text())
        return showError("Passwords don't match.");
    Authentication Auth;
    if (Auth.regCheck(user.toStdString(), m_pass->text().toStdString()))
        return showError("That username is already taken.");

    accept();
}