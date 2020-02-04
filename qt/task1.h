#ifndef TASK1_H
#define TASK1_H

#include <QObject>
#include <QtSql>
#include <QDir>
#include <QStandardPaths>
#include <QFileInfo>
#include <QDateTime>

class Task1 : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool SafeModeOn READ SafeModeOn WRITE setSafeModeOn)
    bool safeModeOn;
    bool toRemove;
    bool connectToDb(const QString& dataBaseType,
    const QString& dataBaseName,
    const QString& dataBaseUser = "",
    const QString& dataBasePassword = "",
    const QString& dataBaseHost = "");
    bool insertToDb(const QString& table,const QString& columns,QStringList values);
    bool createTable(const QString& tableName,QStringList columns,const QString& otherParams="");
    bool removeFilesFromDirectoryUnsafe(const QString& directory,const QString& fileType);
    bool removeFilesFromDirectorySafe(const QString& directory, const QString& fileType);
    bool logRemoving(const QString& file, bool isRemoved);
    QString cover(QString str);
public:
    explicit Task1(QObject *parent = nullptr);
    virtual ~Task1(){}
    void setSafeModeOn(bool newMode);
    bool SafeModeOn();
    bool removeFilesFromDirectory(const QString& directory,const QString& fileType);
    bool execQuery(const QString& query);
    int currentUserId;
    bool connectedToDb;
signals:
    void writeMessage(const QString& message);
    void removeAccepted();
    void removeRejected();
    void askForRemove(const QString& file);
public slots:
    void slotStartLogging();
    void slotStartRemoving(const QString& directory,const QString& fileType);
    void slotRemoveAccepted();
    void slotRemoveRejected();
};

#endif // TASK1_H
