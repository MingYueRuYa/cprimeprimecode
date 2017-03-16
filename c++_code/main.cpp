#include <QtGui/QImage>
#include <QtCore/QCoreApplication>
#include <QtCore/QFileInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QTime>

#define PICTURE_DIR "channel0"
#define SUFFIX_FILE ".prot"

#define PEER_INDEX_COUNT (8+4+4) //peer index byte count
#define INDEX_TABLE_BYTE_COUNT 1608 //8(redundance) + (8+4+4)*100


bool WritToDisk()
{
    QDir currentdir = QDir(QCoreApplication::applicationDirPath());
    QFileInfoList fileinfolist = ((QDir)(currentdir.filePath(PICTURE_DIR))).entryInfoList(QDir::Files);

    //use memeset function
    QByteArray contentarray;
    for (int i=0; i<INDEX_TABLE_BYTE_COUNT; ++i) {  //fill 0x00 -> 1608
        contentarray.append((char)0x00);
    }

    int packfileindex = 0;
    quint64 filebytescount = INDEX_TABLE_BYTE_COUNT;
    QFile *filepoint = NULL;
    for (int i=0; i<fileinfolist.count(); ++i) {
        if (! fileinfolist[i].suffix().isEmpty()) {
            continue;
        }

        QString filename = fileinfolist[i].baseName();
        quint64 time = QTime(0, 0, 0).msecsTo(QTime::fromString((filename)));
        int temppackfileindex = time/(2000*100); //2000ms*100; calc packfile index;
        if (packfileindex != temppackfileindex) { //packfile index changed.
            packfileindex = temppackfileindex;
            contentarray.clear();
            filebytescount = INDEX_TABLE_BYTE_COUNT;
            //close last file point
            filepoint->close();
            delete filepoint;
            filepoint = NULL;
            for (int j=0; j<INDEX_TABLE_BYTE_COUNT; ++j) {  //fill 0x00 -> 1408
                contentarray.append((char)0x00);
            }
        }

        int table_index = (time-(2000*100*temppackfileindex))/2000; // calc table index, from 0 start
        if (filepoint == NULL) {
            filepoint = new QFile (QString::number(temppackfileindex)+SUFFIX_FILE);
        }

        if (! filepoint->isOpen()) {
            if (! filepoint->open(QIODevice::WriteOnly)) {
                qDebug() << "file open.";
                continue;
            }
        }

        QFile imagefile(fileinfolist[i].absoluteFilePath());
        if (! imagefile.open(QIODevice::ReadOnly)) {
            qDebug() << "imagefile open.";
            continue;
        }
        QByteArray imagebyte = imagefile.readAll();
        imagefile.close();
        int imagecount = imagebyte.count();

        QByteArray indexinfoarray;
        indexinfoarray.append(filename);

        indexinfoarray.append(filebytescount & 0xFF);
        indexinfoarray.append((filebytescount >> 8) & 0xFF);
        indexinfoarray.append((filebytescount >> 16) & 0xFF);
        indexinfoarray.append((filebytescount >> 24) & 0xFF);
        indexinfoarray.append(imagecount & 0xFF);
        indexinfoarray.append((imagecount >> 8) & 0xFF);
        indexinfoarray.append((imagecount >> 16) & 0xFF);
        indexinfoarray.append((imagecount >> 24) & 0xFF);

        if (0 == filebytescount - INDEX_TABLE_BYTE_COUNT) { //for the first time need write table index bytes.
            //write table index
            if (filepoint->write(contentarray) != contentarray.size()) {
                continue;
            }
        }

        if (! filepoint->seek(table_index*PEER_INDEX_COUNT+8)) {
            continue;
        }

        if (filepoint->write(indexinfoarray) != indexinfoarray.count()) {
            continue;
        }

        if (! filepoint->seek(filebytescount)) {
            continue;
        }

        if (filepoint->write(imagebyte) != imagebyte.count()) {
            continue;
        }
        filebytescount += imagecount;

        if (i == fileinfolist.count()-1) { // last file, need to close file, delete file point
            filepoint->close();
            delete filepoint;
            filepoint = NULL;
        }

    } //for i
    return true;
}

bool ReadFromDisk(const QString &pImageName)
{
    if (pImageName.isEmpty()) {
        return false;
    }

    quint64 time = QTime(0, 0, 0).msecsTo(QTime::fromString((pImageName)));
    int temppackfileindex = time/(2000*100); //2000ms*100; calc packfile index;
    int table_index = (time-(2000*100*temppackfileindex))/2000; // calc table index, from 0 start

    QDir currentdir = QDir(QCoreApplication::applicationDirPath());
    QFile file(currentdir.filePath(QString::number(temppackfileindex)+SUFFIX_FILE));
    if (! file.open(QIODevice::ReadOnly)) {
        return false;
    }

    if (! file.seek(8+table_index*PEER_INDEX_COUNT)) {
        file.close();
        return false;
    }

    QByteArray array = file.read(PEER_INDEX_COUNT);
    if (array.isEmpty()) {
        file.close();
        return false;
    }

    quint64 position = (array[8] & 0xFF) | ((array[9] << 8) & 0xFFFF) | ((array[10] << 16) & 0xFFFFFF) | ((array[11] << 24) & 0xFFFFFFFF);
    quint64 length = (array[12] & 0xFF) | ((array[13] << 8) & 0xFFFF) | ((array[14] << 16) & 0xFFFFFF) | ((array[15] << 24) & 0xFFFFFFFF);

    if (length == 0) {
        qDebug() << "Not find file name " << pImageName;
        return false;
    }

    if (! file.seek(position)) {
        file.close();
        return false;
    }

    QByteArray imagebyte = file.read(length);
    if (imagebyte.isEmpty()) {
        file.close();
        return false;
    }

    QImage image = QImage::fromData(imagebyte);
    if (! image.save("/home/liushixiong/Desktop/thumbnailpack/2.png")) {
        qDebug() << "save image error.";
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

//    if (! WritToDisk()) {
//        qDebug() << "Write to disk error.";
//    }
//    if (! ReadFromDisk("00:03:42")) {
//        qDebug() << "Not find.";
//    }
    return app.exec();
}
