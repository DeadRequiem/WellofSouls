#include "Settings.h"

Settings::Settings(QObject* parent)
    : QObject(parent), m_volume(1.0) // Default volume to 100%
{
    // Add any other initializations here
}

Settings::~Settings()
{
}

void Settings::setVolume(qreal volume)
{
    m_volume = volume;
}

qreal Settings::volume() const
{
    return m_volume;
}
