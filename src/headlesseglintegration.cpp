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
#include "headlessoffscreensurface.h"
#include "headlesseglscreen.h"

#include <qpa/qplatformwindow.h>
#include <qpa/qplatformbackingstore.h>
#include <qpa/qwindowsysteminterface.h>
#include <qpa/qplatformnativeinterface.h>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtGui/private/qgenericunixfontdatabase_p.h>
#include <QtGui/private/qgenericunixeventdispatcher_p.h>
#else
#include <QtFontDatabaseSupport/private/qgenericunixfontdatabase_p.h>
#include <QtEventDispatcherSupport/private/qgenericunixeventdispatcher_p.h>
#endif

#include <QtGui/QSurfaceFormat>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOffscreenSurface>

// this is where EGL headers are pulled in, make sure it is last
#include "headlesseglcontext.h"

#ifndef EGL_PLATFORM_SURFACELESS_MESA
#define EGL_PLATFORM_SURFACELESS_MESA 0x31DD
#endif

HeadlessEglIntegration::HeadlessEglIntegration(const QStringList &parameters)
    : QPlatformIntegration()
    , m_parameters(parameters)
    , m_fontDatabase(new QGenericUnixFontDatabase())
    , m_nativeInterface(new QPlatformNativeInterface())
{
}

HeadlessEglIntegration::~HeadlessEglIntegration()
{
    QWindowSystemInterface::handleScreenRemoved(m_screen);
    delete m_fontDatabase;
    delete m_nativeInterface;
    eglTerminate(m_dpy);
}

bool HeadlessEglIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case OpenGL: return true;
    case ThreadedOpenGL: return true;
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
    EGLConfig config = EGL_NO_CONFIG_KHR;
    return new HeadlessEglContext(context->format(), m_dpy, &config);
}

QPlatformOffscreenSurface *HeadlessEglIntegration::createPlatformOffscreenSurface(QOffscreenSurface *surface) const
{
    return new HeadlessOffscreenSurface(surface->requestedFormat(), surface);
}

QPlatformFontDatabase *HeadlessEglIntegration::fontDatabase() const
{
    return m_fontDatabase;
}

QAbstractEventDispatcher *HeadlessEglIntegration::createEventDispatcher() const
{
    return createUnixEventDispatcher();
}

QPlatformNativeInterface *HeadlessEglIntegration::nativeInterface() const
{
    return m_nativeInterface;
}

void HeadlessEglIntegration::initialize()
{
    QPlatformIntegration::initialize();

    if (q_hasEglExtension(EGL_NO_DISPLAY, "EGL_EXT_platform_base")) {
        if (q_hasEglExtension(EGL_NO_DISPLAY, "EGL_KHR_platform_surfaceless") ||
                q_hasEglExtension(EGL_NO_DISPLAY, "EGL_EXT_platform_surfaceless") ||
                q_hasEglExtension(EGL_NO_DISPLAY, "EGL_MESA_platform_surfaceless")) {
            static PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplay = nullptr;
            if (!eglGetPlatformDisplay) {
                eglGetPlatformDisplay = (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
            }
            m_dpy = eglGetPlatformDisplay(EGL_PLATFORM_SURFACELESS_MESA, EGL_DEFAULT_DISPLAY, nullptr);
        } else {
            qFatal("The EGL implementation does not support the surfaceless platform");
            return;
        }
    } else {
        qFatal("The EGL implementation does not support the required platform extensions");
    }

    if (Q_UNLIKELY(m_dpy == EGL_NO_DISPLAY)) {
        qFatal("Could not open EGL display: error = 0x%x", eglGetError());
    }
    EGLint major, minor;
    if (Q_UNLIKELY(!eglInitialize(m_dpy, &major, &minor))) {
        qFatal("Could not initialize EGL display: error = 0x%x", eglGetError());
    }

    m_screen = new HeadlessEglScreen;
    QWindowSystemInterface::handleScreenAdded(m_screen);
}
