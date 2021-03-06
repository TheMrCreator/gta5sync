/*****************************************************************************
* gta5sync GRAND THEFT AUTO V SYNC
* Copyright (C) 2016-2017 Syping
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
*****************************************************************************/

#ifndef SNAPMATICPICTURE_H
#define SNAPMATICPICTURE_H

#include <QStringList>
#include <QDateTime>
#include <QObject>
#include <QString>
#include <QImage>
#include <QFile>

struct SnapmaticProperties {
    struct SnapmaticLocation {
        QString area;
        double x;
        double y;
        double z;
    };
    int uid;
    int crewID;
    QStringList playersList;
    uint createdTimestamp;
    QDateTime createdDateTime;
    bool isMeme;
    bool isMug;
    bool isSelfie;
    bool isFromDirector;
    bool isFromRSEditor;
    SnapmaticLocation location;
};

class SnapmaticPicture : public QObject
{
    Q_OBJECT
public:
    explicit SnapmaticPicture(const QString &fileName = "", QObject *parent = 0);
    ~SnapmaticPicture();
    void reset();
    bool readingPictureFromFile(const QString &fileName, bool writeEnabled = true, bool cacheEnabled = false);
    bool readingPicture(bool writeEnabled = true, bool cacheEnabled = true);
    bool isPicOk();
    void clearCache();
    QImage getImage();
    QString getLastStep();
    QString getPictureStr();
    QString getPictureHead();
    QString getPictureTitl();
    QString getPictureDesc();
    QString getPictureSortStr();
    QString getPictureFileName();
    QString getPictureFilePath();
    QString getExportPictureFileName();
    int getContentMaxLength();
    bool setImage(const QImage &picture);
    bool setPictureTitl(const QString &newTitle);
    bool setPictureStream(const QByteArray &picByteArray);
    bool exportPicture(const QString &fileName, bool customFormat = false);
    void setPicFileName(QString picFileName);
    void setPicFilePath(QString picFilePath);
    void updateStrings();

    // ALTERNATIVES
    QString getPictureTitle() { return getPictureTitl(); }
    QString getPictureString() { return getPictureStr(); }
    QString getPictureDescription() { return getPictureDesc(); }
    bool setPictureTitle(const QString &newTitle) { return setPictureTitl(newTitle); }

    // JSON
    bool isJsonOk();
    QString getJsonStr();
    SnapmaticProperties getSnapmaticProperties();
    bool setSnapmaticProperties(SnapmaticProperties newSpJson);

    // VISIBILITY
    bool isHidden();
    bool setPictureHidden();
    bool setPictureVisible();

private:
    QString getSnapmaticHeaderString(const QByteArray &snapmaticHeader);
    QString getSnapmaticJSONString(const QByteArray &jsonBytes);
    QString getSnapmaticTIDEString(const QByteArray &tideBytes);
    QImage cachePicture;
    QString picExportFileName;
    QString picFileName;
    QString picFilePath;
    QString pictureHead;
    QString pictureStr;
    QString lastStep;
    QString sortStr;
    QString titlStr;
    QString descStr;
    bool picOk;
    bool writeEnabled;
    bool cacheEnabled;
    bool isCustomFormat;
    int jpegRawContentSize;

    // PARSE INT
    int snapmaticHeaderLength;
    int snapmaticUsefulLength;
    int snapmaticFileMaxSize;
    int jpegHeaderLineDifStr;
    int jpegPreHeaderLength;
    int jpegPicStreamLength;
    int jsonStreamLength;
    int tideStreamLength;

    // PARSE EDITOR
    int jpegStreamEditorBegin;
    int jsonStreamEditorBegin;
    int jsonStreamEditorLength;
    int titlStreamEditorBegin;
    int titlStreamEditorLength;
    int titlStreamCharacterMax;
    QByteArray rawPicContent;

    // JSON
    void parseJsonContent();
    bool jsonOk;
    QString jsonStr;
    SnapmaticProperties localSpJson;

signals:

public slots:
};

#endif // SNAPMATICPICTURE_H
