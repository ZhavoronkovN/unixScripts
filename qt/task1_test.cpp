#include "task1_test.h"

Task1_test::Task1_test(QObject *parent) : QObject(parent)
{
    testDir=QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    toTest=new Task1(this);
}
Task1_test::~Task1_test(){
    delete toTest;
}

void Task1_test::initTestCase(){
    testDir.mkdir("test1");
    testDir.cd("test1");
    QStringList tmpFiles = {"1.test","2.test","1.notest","2.notest","3.test","4.notest"};
    for (QString file : tmpFiles){
        QFile temp(testDir.absolutePath()+QDir::separator()+file);
        temp.open(QIODevice::WriteOnly);
        temp.close();
    }
}

void Task1_test::testConnectionToDb(){
    QVERIFY(toTest->connectedToDb==true);
}

void Task1_test::testUserId(){
    QVERIFY(toTest->currentUserId!=-1);
}

void Task1_test::testFilesRemoved(){
    toTest->removeFilesFromDirectory(testDir.absolutePath(),"test");
    QCOMPARE(testDir.count()-2,3);
}

void Task1_test::testLogs(){
    QString id=QString::number(toTest->currentUserId);
    QVERIFY(toTest->execQuery("Select * from RemovedFiles where userid = "+id+";")==true);
}

void Task1_test::cleanupTestCase(){
    for(QString file : testDir.entryList()){
        testDir.remove(file);
    }
    testDir.cdUp();
    testDir.rmdir("test1");
    QString id=QString::number(toTest->currentUserId);
    toTest->execQuery("Delete from RemovedFiles where userid = "+id+";");
    toTest->execQuery("Delete from Users where userid = "+id+";");
}
