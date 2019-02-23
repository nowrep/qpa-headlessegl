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

#include <qpa/qplatformintegrationplugin.h>
#include "headlesseglintegration.h"

class HeadlessEglIntegrationPlugin : public QPlatformIntegrationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformIntegrationFactoryInterface_iid FILE "headlessegl.json")
public:
    using QPlatformIntegrationPlugin::create;
    QPlatformIntegration *create(const QString &system, const QStringList &paramList) override;
};

QPlatformIntegration *HeadlessEglIntegrationPlugin::create(const QString &system, const QStringList &paramList)
{
    Q_UNUSED(paramList)
    if (system.compare(QLatin1String("headlessegl"), Qt::CaseInsensitive) == 0) {
        return new HeadlessEglIntegration;
    }
    return nullptr;
}

#include "main.moc"
