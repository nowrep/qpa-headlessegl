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

#include "headlesseglscreen.h"

HeadlessEglScreen::HeadlessEglScreen()
    : QPlatformScreen()
{
}

QRect HeadlessEglScreen::geometry() const
{
    return QRect(0, 0, 640, 480);
}

int HeadlessEglScreen::depth() const
{
    return 32;
}

QImage::Format HeadlessEglScreen::format() const
{
    return QImage::Format_ARGB32_Premultiplied;
}
