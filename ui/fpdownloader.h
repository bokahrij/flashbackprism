#pragma once
#include <lqtutils_net.h>
#include <QNetworkReply>

class FPDownloader : public lqt::Downloader {
    Q_OBJECT
public:
    FPDownloader(const QString &url, QByteArray *output, QObject *parent = nullptr)
        : lqt::Downloader(url, output, parent) {}

protected:
    void onReplyCreated(QNetworkReply *reply) override {
        // Call base implementation if it exists
        lqt::Downloader::onReplyCreated(reply);

        // Accept self-signed certificates
        QObject::connect(reply, &QNetworkReply::sslErrors,
                         reply, [reply](const QList<QSslError> &errors) {
            qWarning() << "Ignoring SSL errors:" << errors;
            reply->ignoreSslErrors();
        });
    }
};
