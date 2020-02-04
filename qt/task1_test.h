#ifndef TASK1_TEST_H
#define TASK1_TEST_H

#include <QObject>
#include <QtTest/QtTest>
#include <QTest>
#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QIODevice>
#include "task1.h"

class Task1_test : public QObject
{
    Q_OBJECT
    Task1* toTest;
    QDir testDir;
public:
    explicit Task1_test(QObject *parent = nullptr);
    virtual ~Task1_test();
private slots:
    void initTestCase();
    void testConnectionToDb();
    void testUserId();
    void testFilesRemoved();
    void testLogs();
    void cleanupTestCase();
};

#endif // TASK1_TEST_H
