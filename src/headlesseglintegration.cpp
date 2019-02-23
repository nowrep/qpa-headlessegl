/* ============================================================
* Qt platform plugin - headlessegl
* Copyright (C) 2019 David Rosca <nowrep@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 3 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */

#include "headlesseglintegration.h"
#include "headlesseglbackingstore.h"
#include "headlesseglscreen.h"

#include <qpa/qplatformwindow.h>
#include <qpa/qplatformbackingstore.h>

#include <QtFontDatabaseSupport/private/qgenericunixfontdatabase_p.h>
#include <QtEventDispatcherSupport/private/qgenericunixeventdispatcher_p.h>

#include <QtGui/QSurfaceFormat>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOffscreenSurface>

// this is where EGL headers are pulled in, make sure it is last
#include "headlesseglcontext.h"

HeadlessEglIntegration::HeadlessEglIntegration(const QStringList &parameters)
    : QPlatformIntegration()
    , m_parameters(parameters)
    , m_fontDatabase(new QGenericUnixFontDatabase())
{
}

HeadlessEglIntegration::~HeadlessEglIntegration()
{
    destroyScreen(m_screen);
    delete m_fontDatabase;
}

bool HeadlessEglIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case OpenGL: return true;
    case ThreadedOpenGL: return true;
    case RasterGLSurface: return true;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

QPlatformWindow *HeadlessEglIntegration::createPlatformWindow(QWindow *window) const
{
    return new QPlatformWindow(window);
}

QPlatformBackingStore *HeadlessEglIntegration::createPlatformBackingStore(QWindow *window) const
{
    return new HeadlessEglBackingStore(window);
}

QPlatformOpenGLContext *HeadlessEglIntegration::createPlatformOpenGLContext(QOpenGLContext *context) const
{
    return new HeadlessEglContext(context->format(), nullptr, m_dpy);
}

QPlatformOffscreenSurface *HeadlessEglIntegration::createPlatformOffscreenSurface(QOffscreenSurface *surface) const
{
    return new QEGLPbuffer(m_dpy, surface->requestedFormat(), surface);
}

QPlatformFontDatabase *HeadlessEglIntegration::fontDatabase() const
{
    return m_fontDatabase;
}

QAbstractEventDispatcher *HeadlessEglIntegration::createEventDispatcher() const
{
    return createUnixEventDispatcher();
}

void HeadlessEglIntegration::initialize()
{
    QPlatformIntegration::initialize();

    m_screen = new HeadlessEglScreen;
    screenAdded(m_screen);

    m_dpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (Q_UNLIKELY(m_dpy == EGL_NO_DISPLAY)) {
        qWarning("Could not open egl display");
        qFatal("EGL error");
    }
    EGLint major, minor;
    if (Q_UNLIKELY(!eglInitialize(m_dpy, &major, &minor))) {
        qWarning("Could not initialize egl display\n");
        qFatal("EGL error");
    }
}
