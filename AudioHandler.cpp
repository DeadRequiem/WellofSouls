#include "AudioHandler.h"
#include <QDir>
#include <QDebug>

AudioHandler::AudioHandler(Settings* settings, QObject* parent)
    : QObject(parent), settings(settings)
{
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(settings->volume()); // Use volume from settings

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &AudioHandler::handleMediaStateChanged);
    connect(player, &QMediaPlayer::positionChanged, this, &AudioHandler::handlePositionChanged);
    connect(player, &QMediaPlayer::errorOccurred, this, &AudioHandler::handleError);
}

AudioHandler::~AudioHandler()
{
    delete player;
}

void AudioHandler::playAudioFile(const QString& filePath)
{
    qDebug() << "Attempting to play audio file:" << filePath;
    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();
}

void AudioHandler::playAudioFilesInFolder(const QString& folderPath)
{
    QDir dir(folderPath);
    QStringList filters = QStringList() << "*.mp3" << "*.wav" << "*.midi";
    QStringList audioFiles = dir.entryList(filters, QDir::Files);

    foreach (QString audioFile, audioFiles) {
        QString filePath = dir.absoluteFilePath(audioFile);
        playAudioFile(filePath);
        // Add a delay or wait for the playback to finish before playing the next file
    }
}

void AudioHandler::handleMediaStateChanged(QMediaPlayer::MediaStatus state)
{
    switch (state) {
    case QMediaPlayer::LoadedMedia:
        qDebug() << "Media loaded.";
        break;
    case QMediaPlayer::BufferedMedia:
        qDebug() << "Media buffered.";
        break;
    case QMediaPlayer::StalledMedia:
        qDebug() << "Media stalled.";
        break;
    case QMediaPlayer::EndOfMedia:
        qDebug() << "End of media.";
        break;
    default:
        break;
    }
}

void AudioHandler::handlePositionChanged(qint64 position)
{
    qDebug() << "Position changed:" << position;
}

void AudioHandler::handleError(QMediaPlayer::Error error)
{
    qWarning() << "Error occurred:" << error << "-" << player->errorString();
}
