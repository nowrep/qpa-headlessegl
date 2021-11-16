#include "headlessoffscreensurface.h"

HeadlessOffscreenSurface::HeadlessOffscreenSurface(const QSurfaceFormat &format, QOffscreenSurface *offscreenSurface)
    : QPlatformOffscreenSurface(offscreenSurface)
    , m_format(format)
{
}

QSurfaceFormat HeadlessOffscreenSurface::format() const
{
    return m_format;
}

bool HeadlessOffscreenSurface::isValid() const
{
    return true;
}
