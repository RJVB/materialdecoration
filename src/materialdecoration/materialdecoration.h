/****************************************************************************
**
** Copyright (C) 2014 Robin Burchell <robin.burchell@viroteck.net>
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2017 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
** Copyright (C) 2017 Michael Spencer <sonrisesoftware@gmail.com>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QBitmap>
#include <QtGui/QCursor>
#include <QtGui/QLinearGradient>
#include <QtGui/QPainter>
#include <QtGui/QPalette>

#include <QtGui/qpa/qwindowsysteminterface.h>

#include <QtWaylandClient/private/qwaylandabstractdecoration_p.h>
#include <QtWaylandClient/private/qwaylanddecorationplugin_p.h>
#include <QtWaylandClient/private/qwaylandshellsurface_p.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>

QT_BEGIN_NAMESPACE

namespace QtWaylandClient
{

enum Button
{
    None,
    Close,
    Maximize,
    Minimize
};

class Q_WAYLAND_CLIENT_EXPORT QWaylandMaterialDecoration : public QWaylandAbstractDecoration
{
    Q_OBJECT

public:
    QWaylandMaterialDecoration();

public Q_SLOTS:
    void setBackgroundColor(QColor color) { m_backgroundColor = color; }

    void setTextColor(QColor color) { m_textColor = color; }

    void setIconColor(QColor color) { m_iconColor = color; }

protected:
    QMargins margins() const override;
    void paint(QPaintDevice *device) override;
    bool handleMouse(QWaylandInputDevice *inputDevice, const QPointF &local, const QPointF &global,
                     Qt::MouseButtons b, Qt::KeyboardModifiers mods) override;
    bool handleTouch(QWaylandInputDevice *inputDevice, const QPointF &local, const QPointF &global,
                     Qt::TouchPointState state, Qt::KeyboardModifiers mods) override;

private:
    void processMouseTop(QWaylandInputDevice *inputDevice, const QPointF &local, Qt::MouseButtons b,
                         Qt::KeyboardModifiers mods);
    void processMouseBottom(QWaylandInputDevice *inputDevice, const QPointF &local,
                            Qt::MouseButtons b, Qt::KeyboardModifiers mods);
    void processMouseLeft(QWaylandInputDevice *inputDevice, const QPointF &local,
                          Qt::MouseButtons b, Qt::KeyboardModifiers mods);
    void processMouseRight(QWaylandInputDevice *inputDevice, const QPointF &local,
                           Qt::MouseButtons b, Qt::KeyboardModifiers mods);
    bool clickButton(Qt::MouseButtons b, Button btn);

    QRectF closeButtonRect() const;
    QRectF maximizeButtonRect() const;
    QRectF minimizeButtonRect() const;

    int dp(int dp) const;
    qreal pixelDensity() const;

    QBitmap buttonIcon(const QString &name) const;

    Button m_clicking;
    QColor m_backgroundColor;
    QColor m_iconColor;
    QColor m_textColor;
    QStaticText m_windowTitle;
};
}