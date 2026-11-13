#include "passwordHasher.h"

#include <QByteArray>
#include <QCryptographicHash>
#include <QPasswordDigestor>
#include <QRandomGenerator>
#include <QString>
#include <QStringList>


namespace {
constexpr int kIterations = 200000;
constexpr int kSaltBytes  = 16;
constexpr int kHashBytes  = 32;

QByteArray derive(const std::string& password, const QByteArray& salt, int iterations)
{
    return QPasswordDigestor::deriveKeyPbkdf2(
        QCryptographicHash::Sha256,
        QByteArray::fromStdString(password),
        salt, iterations, kHashBytes);
}

// Compares every byte so timing doesn't reveal where a mismatch occurred
bool constantTimeEqual(const QByteArray& a, const QByteArray& b)
{
    if (a.size() != b.size()) return false;
    unsigned char diff = 0;
    for (int i = 0; i < a.size(); ++i)
        diff |= static_cast<unsigned char>(a[i]) ^ static_cast<unsigned char>(b[i]);
    return diff == 0;
}
}

std::string PasswordHasher::hash(const std::string& password)
{
    QByteArray salt(kSaltBytes, 0);
    for (char& c : salt)
        c = static_cast<char>(QRandomGenerator::system()->bounded(256));

    const QByteArray h = derive(password, salt, kIterations);

    return (QString::number(kIterations) + '$'
            + salt.toBase64() + '$'
            + h.toBase64()).toStdString();
}

bool PasswordHasher::verify(const std::string& password, const std::string& stored)
{
    const QStringList parts = QString::fromStdString(stored).split('$');
    if (parts.size() != 3) return false;

    bool ok = false;
    const int iterations = parts[0].toInt(&ok);
    if (!ok || iterations <= 0) return false;

    const QByteArray salt     = QByteArray::fromBase64(parts[1].toUtf8());
    const QByteArray expected = QByteArray::fromBase64(parts[2].toUtf8());

    return constantTimeEqual(derive(password, salt, iterations), expected);
}