/*
 * Bittorrent Client using Qt4 and libtorrent.
 * Copyright (C) 2010  Christophe Dumez, Arnaud Demaiziere
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * Contact: chris@qbittorrent.org, arnaud@qbittorrent.org
 */

#ifndef RSSMANAGER_H
#define RSSMANAGER_H

#include <QTimer>

#include "rssfolder.h"

class DownloadThread;

class RssManager: public RssFolder {
  Q_OBJECT
private:
  explicit RssManager();
  static RssManager* m_instance;

public:
  static RssManager* instance();
  static void drop();
  ~RssManager();
  inline DownloadThread* rssDownloader() const { return m_rssDownloader; }
  static void insertSortElem(QList<RssArticle> &list, const RssArticle &item);
  static QList<RssArticle> sortNewsList(const QList<RssArticle>& news_list);

public slots:
  void loadStreamList();
  void saveStreamList() const;
  void forwardFeedInfosChanged(const QString &url, const QString &aliasOrUrl, uint nbUnread);
  void forwardFeedIconChanged(const QString &url, const QString &icon_path);
  void moveFile(RssFile* file, RssFolder* dest_folder);
  void updateRefreshInterval(uint val);

signals:
  void feedInfosChanged(const QString &url, const QString &display_name, uint nbUnread);
  void feedIconChanged(const QString &url, const QString &icon_path);

private:
  QTimer m_refreshTimer;
  uint m_refreshInterval;
  DownloadThread *m_rssDownloader;

};

#endif // RSSMANAGER_H
