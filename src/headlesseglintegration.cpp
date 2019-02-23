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

#include <QtFontDatabaseSupport/private/qgenericunixfontdatabase_p.h>
#include <QtEventDispatcherSupport/private/qgenericunixeventdispatcher_p.h>
#include <QtEglSupport/private/qeglpbuffer_p.h>

#include <QtGui/QSurfaceFormat>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOffscreenSurface>

HeadlessEglIntegration::HeadlessEglIntegration()
    : QPlatformIntegration()
    , m_fontDatabase(new QGenericUnixFontDatabase())
{
}

HeadlessEglIntegration::~HeadlessEglIntegration()
{
    delete m_fontDatabase;
}

bool HeadlessEglIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case OpenGL: return true;
    case ThreadedOpenGL: return true;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

QPlatformWindow *HeadlessEglIntegration::createPlatformWindow(QWindow *window) const
{
    return nullptr;
}

QPlatformBackingStore *HeadlessEglIntegration::createPlatformBackingStore(QWindow *window) const
{
    return nullptr;
}

QPlatformOpenGLContext *HeadlessEglIntegration::createPlatformOpenGLContext(QOpenGLContext *context) const
{
    return nullptr;
}

QPlatformOffscreenSurface *HeadlessEglIntegration::createPlatformOffscreenSurface(QOffscreenSurface *surface) const
{
    return nullptr;
}

QPlatformFontDatabase *HeadlessEglIntegration::fontDatabase() const
{
    return m_fontDatabase;
}

QAbstractEventDispatcher *HeadlessEglIntegration::createEventDispatcher() const
{
    return createUnixEventDispatcher();
}
