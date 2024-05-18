#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject* parent = nullptr);
    ~Settings();

    void setVolume(qreal volume);
    qreal volume() const;

private:
    qreal m_volume;
};

#endif // SETTINGS_H
