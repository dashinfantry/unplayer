/*
 * Unplayer
 * Copyright (C) 2015-2019 Alexey Rochev <equeim@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UNPLAYER_ALBUMSMODEL_H
#define UNPLAYER_ALBUMSMODEL_H

#include <vector>

#include <QAbstractListModel>
#include <QQmlParserStatus>

#include "librarytrack.h"

namespace unplayer
{
    struct Album
    {
        QString artist;
        QString displayedArtist;
        QString album;
        QString displayedAlbum;
        int year;
        int tracksCount;
        int duration;
    };

    class AlbumsModel : public QAbstractListModel, public QQmlParserStatus
    {
        Q_OBJECT
        Q_INTERFACES(QQmlParserStatus)
        Q_PROPERTY(bool allArtists READ allArtists WRITE setAllArtists NOTIFY allArtistsChanged)
        Q_PROPERTY(QString artist READ artist WRITE setArtist)
        Q_PROPERTY(bool sortDescending READ sortDescending WRITE setSortDescending)
        Q_PROPERTY(SortMode sortMode READ sortMode WRITE setSortMode NOTIFY sortModeChanged)
    public:
        enum Role
        {
            ArtistRole = Qt::UserRole,
            DisplayedArtistRole,
            UnknownArtistRole,
            AlbumRole,
            DisplayedAlbumRole,
            UnknownAlbumRole,
            YearRole,
            TracksCountRole,
            DurationRole
        };
        Q_ENUM(Role)

        enum SortMode
        {
            SortAlbum,
            SortYear,
            SortArtistAlbum,
            SortArtistYear
        };
        Q_ENUM(SortMode)

        ~AlbumsModel() override;
        void classBegin() override;
        void componentComplete() override;

        QVariant data(const QModelIndex& index, int role) const override;
        int rowCount(const QModelIndex& parent) const override;

        bool allArtists() const;
        void setAllArtists(bool allArtists);

        const QString& artist() const;
        void setArtist(const QString& artist);

        bool sortDescending() const;
        void setSortDescending(bool descending);
        SortMode sortMode() const;
        void setSortMode(SortMode mode);

        Q_INVOKABLE std::vector<unplayer::LibraryTrack> getTracksForAlbum(int index) const;
        Q_INVOKABLE std::vector<unplayer::LibraryTrack> getTracksForAlbums(const std::vector<int>& indexes) const;
        Q_INVOKABLE QStringList getTrackPathsForAlbum(int index) const;
        Q_INVOKABLE QStringList getTrackPathsForAlbums(const std::vector<int>& indexes) const;

        Q_INVOKABLE void removeAlbum(int index, bool deleteFiles);
        Q_INVOKABLE void removeAlbums(std::vector<int> indexes, bool deleteFiles);

    protected:
        QHash<int, QByteArray> roleNames() const override;

    private:
        void execQuery();

        std::vector<Album> mAlbums;

        bool mAllArtists = true;
        QString mArtist;

        bool mSortDescending = false;
        SortMode mSortMode = SortAlbum;

    signals:
        void allArtistsChanged();
        void sortModeChanged();
    };
}

#endif // UNPLAYER_ALBUMSMODEL_H
