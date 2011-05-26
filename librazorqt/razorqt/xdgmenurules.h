/* BEGIN_COMMON_COPYRIGHT_HEADER
 *
 * Razor - a lightweight, Qt based, desktop toolset
 * https://sourceforge.net/projects/razor-qt/
 *
 * Copyright: 2010-2011 Razor team
 * Authors:
 *   Alexander Sokoloff <sokoloff.a@gmail.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation;  only version 2 of
 * the License is valid for this program.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * END_COMMON_COPYRIGHT_HEADER */

/*********************************************************************
  See: http://standards.freedesktop.org/desktop-entry-spec

*********************************************************************/

#ifndef XDGMENURULES_H
#define XDGMENURULES_H

#include <QObject>
#include <QDomElement>
#include <QLinkedList>

#include "xdgdesktopfile.h"

class XdgMenuRule : public QObject
{
    Q_OBJECT
public:
    explicit XdgMenuRule(const QDomElement& element, QObject* parent = 0);
    virtual ~XdgMenuRule();

    virtual bool check(const QString& desktopFileId, const XdgDesktopFile& desktopFile) = 0;
};


class XdgMenuRuleOr : public XdgMenuRule
{
    Q_OBJECT
public:
    explicit XdgMenuRuleOr(const QDomElement& element, QObject* parent = 0);

    bool check(const QString& desktopFileId, const XdgDesktopFile& desktopFile);

protected:
    QLinkedList<XdgMenuRule*> mChilds;
};


class XdgMenuRuleAnd : public XdgMenuRuleOr
{
    Q_OBJECT
public:
    explicit XdgMenuRuleAnd(const QDomElement& element, QObject* parent = 0);
    bool check(const QString& desktopFileId, const XdgDesktopFile& desktopFile);
};


class XdgMenuRuleNot : public XdgMenuRuleOr
{
    Q_OBJECT
public:
    explicit XdgMenuRuleNot(const QDomElement& element, QObject* parent = 0);
    bool check(const QString& desktopFileId, const XdgDesktopFile& desktopFile);
};


class XdgMenuRuleFileName : public XdgMenuRule
{
    Q_OBJECT
public:
    explicit XdgMenuRuleFileName(const QDomElement& element, QObject* parent = 0);
    bool check(const QString& desktopFileId, const XdgDesktopFile& desktopFile);
private:
    QString mId;
};


class XdgMenuRuleCategory : public XdgMenuRule
{
    Q_OBJECT
public:
    explicit XdgMenuRuleCategory(const QDomElement& element, QObject* parent = 0);
    bool check(const QString& desktopFileId, const XdgDesktopFile& desktopFile);
private:
    QString mCategory;
};


class XdgMenuRuleAll : public XdgMenuRule
{
    Q_OBJECT
public:
    explicit XdgMenuRuleAll(const QDomElement& element, QObject* parent = 0);
    bool check(const QString& desktopFileId, const XdgDesktopFile& desktopFile);
};



class XdgMenuRules : public QObject
{
    Q_OBJECT
public:
    explicit XdgMenuRules(QObject* parent = 0);
    virtual ~XdgMenuRules();

    void addInclude(const QDomElement& element);
    void addExclude(const QDomElement& element);

    bool checkInclude(const QString& desktopFileId, const XdgDesktopFile& desktopFile);
    bool checkExclude(const QString& desktopFileId, const XdgDesktopFile& desktopFile);

protected:
    QLinkedList<XdgMenuRule*> mIncludeRules;
    QLinkedList<XdgMenuRule*> mExcludeRules;
};

#endif // XDGMENURULES_H
