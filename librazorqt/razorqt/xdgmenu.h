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


#ifndef XDGMENU_H
#define XDGMENU_H

#include "xdgdesktopfile.h"

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QHash>
#include <QtXml/QDomDocument>


class QDomDocument;
class QDomElement;
/*! @brief The XdgMenu class implements the "Desktop Menu Specification" from freedesktop.org.

 Freedesktop menu is a user-visible hierarchy of applications, typically displayed as a menu.

 Example usage:
@code
    QString menuFile = XdgMenu::getMenuFileName();
    XdgMenu xdgMenu(menuFile);

    bool res = xdgMenu.read();
    if (!res)
    {
        QMessageBox::warning(this, "Parse error", xdgMenu.errorString());
    }

    QDomElement rootElement = xdgMenu.xml().documentElement()
 @endcode

 @sa http://specifications.freedesktop.org/menu-spec/menu-spec-latest.html
 */
class XdgMenu : public QObject
{
Q_OBJECT
friend class XdgMenuItem;

public:
    explicit XdgMenu(const QString& menuFileName, QObject *parent = 0);
    virtual ~XdgMenu();

    bool read();
    void save(const QString& fileName);

    const QDomDocument xml() const { return mXml; }
    QString menuFileName() const { return mMenuFileName; }

    QDomElement findMenu(QDomElement& baseElement, const QString& path, bool createNonExisting);
    QStringList& environments() { return mEnvironments; }

    const QString errorString() const { return mErrorString; }
    const QString logDir() const { return mLogDir; }
    void setLogDir(const QString& directory);

    static QString getMenuFileName(const QString& baseName = "applications.menu");
    
    
signals:

public slots:

protected:
    void simplify(QDomElement& element);
    void mergeMenus(QDomElement& element);
    void moveMenus(QDomElement& element);
    void deleteDeletedMenus(QDomElement& element);

    void processDirectoryEntries(QDomElement& element, const QStringList& parentDirs);
    void processApps(QDomElement& element);
    void deleteEmpty(QDomElement& element);

    bool loadDirectoryFile(const QString& fileName, QDomElement& element);


private:
    QString mMenuFileName;
    QDomDocument mXml;
//    QHash<QString, XdgDesktopFile*> mDesktopFiles;

    void prependChilds(QDomElement& srcElement, QDomElement& destElement);
    void appendChilds(QDomElement& srcElement, QDomElement& destElement);
    QStringList mEnvironments;
    QString mErrorString;
    QString mLogDir;
};


#endif // XDGMENU_H
