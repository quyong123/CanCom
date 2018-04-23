#ifndef MYHELPER_H
#define MYHELPER_H

#include <QTime>
#include <QProcess>
#include <QDebug>
#include <QByteArray>
#include <QString>
class myHelper:public QObject
{
public:
    static void Sleep(int sec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(sec);
        while( QTime::currentTime() < dieTime )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    static QString ByteArraryToHexString(QByteArray data)
    {
        QString temp = "";
        QString hex = data.toHex();
        for(int i=0;i<hex.length();i+=2)
        {
            temp+=hex.mid(i,2)+" ";
        }
        return temp;
    }

    //16进制字符串转字节数组
        static QByteArray HexStrToByteArray(QString str)
        {
            QByteArray senddata;
            int hexdata,lowhexdata;
            int hexdatalen = 0;
            int len = str.length();
            senddata.resize(len/2);
            char lstr,hstr;
            for(int i=0; i<len; )
            {
                hstr=str[i].toLatin1();
                if(hstr == ' ')
                {
                    i++;
                    continue;
                }
                i++;
                if(i >= len)
                    break;
                lstr = str[i].toLatin1();
                hexdata = ConvertHexChar(hstr);
                lowhexdata = ConvertHexChar(lstr);
                if((hexdata == 16) || (lowhexdata == 16))
                    break;
                else
                    hexdata = hexdata*16+lowhexdata;
                i++;
                senddata[hexdatalen] = (char)hexdata;
                hexdatalen++;
            }
            senddata.resize(hexdatalen);
            return senddata;
        }
        static char ConvertHexChar(char ch)
        {
            if((ch >= '0') && (ch <= '9'))
                return ch-0x30;
            else if((ch >= 'A') && (ch <= 'F'))
                return ch-'A'+10;
            else if((ch >= 'a') && (ch <= 'f'))
                return ch-'a'+10;
            else return (-1);
        }
};
#endif // MYHELPER_H
