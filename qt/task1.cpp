#include "task1.h"

Task1::Task1(QObject *parent) : QObject(parent)
{
    toRemove=false;
    this->safeModeOn=false;
    this->currentUserId=-1;
    this->connectedToDb=connectToDb("QSQLITE",
                                    "D:\\Projects\\Qt\\unix\\logTask1.db");
    this->slotStartLogging();
}

void Task1::setSafeModeOn(bool newMode){
    this->safeModeOn=newMode;
    emit writeMessage(QString("Safe mode now is ")+QString(safeModeOn?"on.\n":"off.\n"));
}

bool Task1::SafeModeOn(){
    return this->safeModeOn;
}

QString Task1::cover(QString str){
    return "\'"+str+"\'";
}

bool Task1::connectToDb(const QString& dataBaseType, const QString& dataBaseName, const QString& dataBaseUser, const QString& dataBasePassword, const QString& dataBaseHost){
    QSqlDatabase db = QSqlDatabase::addDatabase(dataBaseType);
    db.setDatabaseName(dataBaseName);
    if(dataBaseUser!="")
        db.setUserName(dataBaseUser);
    if(dataBaseHost!="")
        db.setHostName(dataBaseHost);
    if(dataBasePassword!="")
        db.setPassword(dataBasePassword);
    bool res = db.open();
    return res;
}

bool Task1::insertToDb(const QString& table, const QString& columns, QStringList values){
    if(!connectedToDb){
        return false;
    }
    QSqlQuery query;
    QString queryString = "Insert into %1(%2) values (%3);";
    return query.exec(queryString.arg(table).arg(columns).arg(values.join(",")));
}

bool Task1::createTable(const QString& tableName, QStringList columns, const QString& otherParams){
    if(!connectedToDb){
        return false;
    }
    QSqlQuery query;
    QString queryString = "Create table %1(%2,%3);";
    return query.exec(queryString.arg(tableName).arg(columns.join(",")).arg(otherParams));
}

bool Task1::removeFilesFromDirectoryUnsafe(const QString& directory, const QString& fileType){
    QDir dir(directory);
    auto temp = dir.entryInfoList();
    for(auto i = temp.begin()+2;i != temp.end(); i++){
        if(i->isDir() && i->absoluteFilePath()!=dir.absolutePath()){
            removeFilesFromDirectoryUnsafe(i->absoluteFilePath(),fileType);
        }
        else if(i->isFile() && i->suffix()==fileType){
            bool isRemoved = dir.remove(i->fileName());
            this->logRemoving(i->absoluteFilePath(),isRemoved);
            if(isRemoved == false){
                emit writeMessage("Error in removing " + i->fileName() + "\n");
            }
            else{
                emit writeMessage("Removed " + i->fileName() + "\n");
            }
        }
    }
    return 0;
}

bool Task1::removeFilesFromDirectorySafe(const QString& directory, const QString& fileType){
    QDir dir(directory);
    auto temp = dir.entryInfoList();
    for(auto i = temp.begin()+2;i != temp.end(); i++){
        if(i->isDir() && i->absoluteFilePath()!=dir.absolutePath()){
            removeFilesFromDirectoryUnsafe(i->absoluteFilePath(),fileType);
        }
        else if(i->isFile() && i->suffix()==fileType){
            QEventLoop loop;
            connect(this,&Task1::removeAccepted,&loop,&QEventLoop::quit);
            connect(this,&Task1::removeRejected,&loop,&QEventLoop::quit);
            this->askForRemove(i->absoluteFilePath());
            loop.exec();
            if(toRemove){
                bool isRemoved = dir.remove(i->fileName());
                this->logRemoving(i->absoluteFilePath(),isRemoved);
                if(isRemoved == false){
                    emit writeMessage("Error in removing " + i->fileName() + "\n");
                }
                else{
                    emit writeMessage("Removed " + i->fileName() + "\n");
                }
            }
            else{
                emit writeMessage("Remove of " + i->fileName() + " rejected\n");
                this->logRemoving(i->absoluteFilePath(),toRemove);
            }
        }
    }
    return 0;
}

bool Task1::removeFilesFromDirectory(const QString& directory, const QString& fileType){
    if(this->safeModeOn){
        return this->removeFilesFromDirectorySafe(directory,fileType);
    }
    else{
        return this->removeFilesFromDirectoryUnsafe(directory,fileType);
    }
}

bool Task1::execQuery(const QString &queryString){
    if(!connectedToDb){
        return false;
    }
    QSqlQuery query;
    return query.exec(queryString);
}

void Task1::slotStartLogging(){
    if(this->connectedToDb){
        QString userName = QString("\'%1\'").arg(QDir::home().dirName());
        QString time = QDateTime::currentDateTime().toString();
        if(this->insertToDb("Users","UserName,Time",QStringList({userName,cover(time)}))){
            QSqlQuery query;
            QString queryString = "Select UserId from Users where UserName = %1 and Time = \'%2\';";
            if(query.exec(queryString.arg(userName).arg(time))){
                QSqlRecord rec = query.record();
                query.last();
                this->currentUserId = query.value(rec.indexOf("UserId")).toInt();
            }
        }
    }
}

void Task1::slotStartRemoving(const QString& directory, const QString& fileType){
    this->removeFilesFromDirectory(directory,fileType);
}

void Task1::slotRemoveAccepted(){
    this->toRemove=true;
    emit removeAccepted();
}

void Task1::slotRemoveRejected(){
    this->toRemove=false;
    emit removeRejected();
}

bool Task1::logRemoving(const QString& file, bool isRemoved){
    if(!connectedToDb && currentUserId == -1){
        return false;
    }
    return this->insertToDb("RemovedFiles","UserId,File,Removed",QStringList({cover(QString::number(this->currentUserId)),cover(file),cover(QString::number(isRemoved))}));
}

