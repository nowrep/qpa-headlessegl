#pragma once

#include <qpa/qplatformoffscreensurface.h>

class HeadlessOffscreenSurface : public QPlatformOffscreenSurface
{
public:
    HeadlessOffscreenSurface(const QSurfaceFormat &format, QOffscreenSurface *offscreenSurface);

    QSurfaceFormat format() const override;
    bool isValid() const override;

private:
    QSurfaceFormat m_format;
};
