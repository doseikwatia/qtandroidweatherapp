#ifndef WEBSERVICE_H
#define WEBSERVICE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QTimer>
#include <QDateTime>
#include <QDomDocument>
#include <QProcessEnvironment>
#include <QFile>
#include <QDir>
#include <QImage>
#include <QImageReader>
#include <QtQuick/QQuickImageProvider>

//class ImageProvider: public QQuickImageProvider
//{
//public:
//explicit ImageProvider();
//virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize);

//};


class WeatherInfo:public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool Success READ Success WRITE setSuccess NOTIFY successChanged)
    Q_PROPERTY(QString State READ State WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString ResponseText READ ResponseText WRITE setResponseText NOTIFY responseTextChanged)
    Q_PROPERTY(QString City READ City WRITE setCity NOTIFY cityChanged)
    Q_PROPERTY(QString WeatherStationCity READ WeatherStationCity WRITE setWeatherStationCity NOTIFY weatherStationCityChanged)
    Q_PROPERTY(QString WeatherID READ WeatherID WRITE setWeatherID NOTIFY weatheridChanged)
    Q_PROPERTY(QString Description READ Description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(double Temperature READ Temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(double RelativeHumidity READ RelativeHumidity WRITE setRelativeHumidity NOTIFY relativeHumidityChanged)
    Q_PROPERTY(QString Wind READ Wind WRITE setWind NOTIFY windChanged )
    Q_PROPERTY(QString Pressure READ Pressure WRITE setPressure NOTIFY pressureChanged)
    Q_PROPERTY(QString Photo READ Photo WRITE setPhoto NOTIFY photoChanged)

public:
    explicit WeatherInfo( QObject* parent =0)
        :QObject(parent)
    {
        setSuccess(false);
        setState("");
        setResponseText("");
        setCity("");
        setWeatherID("");
        setWeatherStationCity("");
        setDescription("");
        setTemperature(0.0);
        setRelativeHumidity(0.0);
        setWind("");
        setPressure("");
    }



    bool Success() const
    {
        return m_Success;
    }

    QString State() const
    {
        return m_State;
    }

    QString ResponseText() const
    {
        return m_ResponseText;
    }

    QString City() const
    {
        return m_City;
    }

    QString WeatherStationCity() const
    {
        return m_WeatherStationCity;
    }

    QString WeatherID() const
    {
        return m_WeatherID;
    }

    QString Description() const
    {
        return m_Description;
    }

    double Temperature() const
    {
        return m_Temperature;
    }

    double RelativeHumidity() const
    {
        return m_RelativeHumidity;
    }

    QString Wind() const
    {
        return m_Wind;
    }

    QString Pressure() const
    {
        return m_Pressure;
    }

    QString Photo() const
    {
        return m_Photo;
    }

public slots:
    void setSuccess(bool arg)
    {
        if (m_Success != arg) {
            m_Success = arg;
            emit successChanged(arg);
        }
    }

    void setState(QString arg)
    {
        if (m_State != arg) {
            m_State = arg;
            emit stateChanged(arg);
        }
    }

    void setResponseText(QString arg)
    {
        if (m_ResponseText != arg) {
            m_ResponseText = arg;
            emit responseTextChanged(arg);
        }
    }

    void setCity(QString arg)
    {
        if (m_City != arg) {
            m_City = arg;
            emit cityChanged(arg);
        }
    }

    void setWeatherStationCity(QString arg)
    {
        if (m_WeatherStationCity != arg) {
            m_WeatherStationCity = arg;
            emit weatherStationCityChanged(arg);
        }
    }

    void setWeatherID(QString arg)
    {
        if (m_WeatherID != arg) {
            m_WeatherID = arg;
            emit weatheridChanged(arg);
        }
    }

    void setDescription(QString arg)
    {
        if (m_Description != arg) {
            m_Description = arg;
            emit descriptionChanged(arg);
        }
    }

    void setTemperature(double arg)
    {
        if (m_Temperature != arg) {
            m_Temperature = arg;
            emit temperatureChanged(arg);
        }
    }

    void setRelativeHumidity(double arg)
    {
        if (m_RelativeHumidity != arg) {
            m_RelativeHumidity = arg;
            emit relativeHumidityChanged(arg);
        }
    }

    void setWind(QString arg)
    {
        if (m_Wind != arg) {
            m_Wind = arg;
            emit windChanged(arg);
        }
    }

    void setPressure(QString arg)
    {
        if (m_Pressure != arg) {
            m_Pressure = arg;
            emit pressureChanged(arg);
        }
    }

    void setPhoto(QString arg)
    {
        if (m_Photo != arg) {
            m_Photo = arg;
            emit photoChanged(arg);
        }
    }

signals:


    void successChanged(bool arg);

    void stateChanged(QString arg);

    void responseTextChanged(QString arg);

    void cityChanged(QString arg);

    void weatherStationCityChanged(QString arg);

    void weatheridChanged(QString arg);

    void descriptionChanged(QString arg);

    void temperatureChanged(double arg);

    void relativeHumidityChanged(double arg);

    void windChanged(QString arg);

    void pressureChanged(QString arg);

    void photoChanged(QString arg);

private:

    bool m_Success;
    QString m_State;
    QString m_ResponseText;
    QString m_City;
    QString m_WeatherStationCity;
    QString m_WeatherID;
    QString m_Description;
    double m_Temperature;
    double m_RelativeHumidity;
    QString m_Wind;
    QString m_Pressure;
    QString m_Photo;
};
























class WeatherService :public QObject
{
    Q_OBJECT
    Q_PROPERTY(int timerInterval READ timerInterval WRITE settimerInterval)
    Q_PROPERTY(WeatherInfo* currentWeather READ currentWeather NOTIFY oncurrentWeatherChanged)
    Q_PROPERTY(QString lastUpdateTime READ lastUpdateTime  NOTIFY lastUpdateTimeChanged)

public:
    explicit WeatherService(QObject *parent = 0);
    int timerInterval();
    void settimerInterval(int interval);
    WeatherInfo* currentWeather();


    QString lastUpdateTime() const
    {
        return m_lastUpdateTime.toString("MM/dd/yyyy HH:mm");
    }

signals:
    void oncurrentWeatherChanged();
    void lastUpdateTimeChanged(QDateTime arg);

public slots:
    void processDataFromRemoteServer(QNetworkReply *reply);
    void getWeatherUpdate();


private:
    enum NetTask{GetCityWeatherByZIP ,GetWeatherInformation,GetWeatherPhoto} netTask;
    QNetworkAccessManager* networkAccessMgr;
    QNetworkRequest networkGetRequest;
    QTimer timer;

    WeatherInfo currentWeatherInfo;
    QMap<QString,QString> xmlWeatherData;
    QDateTime m_lastUpdateTime;

    void setlastUpdateTime(QDateTime arg)
    {
        if (m_lastUpdateTime != arg) {
            m_lastUpdateTime = arg;
            emit lastUpdateTimeChanged(arg);
        }
    }
};

#endif // WEBSERVICE_H
