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

#include <QtGlobal>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtGui/private/qeglpbuffer_p.h>
#include <QtGui/private/qeglplatformcontext_p.h>
#include <QtGui/private/qeglconvenience_p.h>
#else
#include <QtEglSupport/private/qeglpbuffer_p.h>
#include <QtEglSupport/private/qeglplatformcontext_p.h>
#include <QtEglSupport/private/qeglconvenience_p.h>
#endif

class HeadlessEglContext : public QEGLPlatformContext
{
public:
    HeadlessEglContext(const QSurfaceFormat &format, EGLDisplay display, EGLConfig *config);

    EGLSurface eglSurfaceForPlatformSurface(QPlatformSurface *surface) override;
};
