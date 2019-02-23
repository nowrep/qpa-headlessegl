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

#include "headlesseglbackingstore.h"

HeadlessEglBackingStore::HeadlessEglBackingStore(QWindow *window)
    : QPlatformBackingStore(window)
{
}

QPaintDevice *HeadlessEglBackingStore::paintDevice()
{
    qWarning("HeadlessEglBackingStore::paintDevice not supported");
    return &m_image;
}

void HeadlessEglBackingStore::flush(QWindow *window, const QRegion &region, const QPoint &offset)
{
    Q_UNUSED(window);
    Q_UNUSED(region);
    Q_UNUSED(offset);
    qWarning("HeadlessEglBackingStore::flush not supported");
}

void HeadlessEglBackingStore::resize(const QSize &size, const QRegion &staticContents)
{
    Q_UNUSED(size);
    Q_UNUSED(staticContents);
    qWarning("HeadlessEglBackingStore::resize not supported");
}
