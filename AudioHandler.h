#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "Settings.h"

class AudioHandler : public QObject
{
    Q_OBJECT

public:
    explicit AudioHandler(Settings* settings, QObject* parent = nullptr);
    ~AudioHandler();

    void playAudioFile(const QString& filePath);
    void playAudioFilesInFolder(const QString& folderPath);

private:
    QMediaPlayer* player;
    QAudioOutput* audioOutput;
    Settings* settings;

private slots:
    void handleMediaStateChanged(QMediaPlayer::MediaStatus state);
    void handlePositionChanged(qint64 position);
    void handleError(QMediaPlayer::Error error);
};

#endif // AUDIOHANDLER_H
