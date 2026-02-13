#pragma once
#include <lqtutils_net.h>
#include <QNetworkReply>

class FPDownloader : public lqt::Downloader {
    Q_OBJECT
public:
    FPDownloader(const QString &url, QByteArray *output, QObject *parent = nullptr)
        : lqt::Downloader(url, output, parent) {}

protected:
    void onStateChanged() override {
        // Call base implementation
        lqt::Downloader::onStateChanged();

        // When the reply is created, attach SSL handler
        if (m_reply) {
            QObject::connect(m_reply, &QNetworkReply::sslErrors,
                             m_reply, [this](const QList<QSslError> &errors) {
                qWarning() << "Ignoring SSL errors:" << errors;
                m_reply->ignoreSslErrors();
            });
        }
    }
};
