#include "weatherservice.h"

WeatherService::WeatherService(QObject *parent) :
    QObject(parent)
{
    //http://wsf.cdyne.com/WeatherWS/Weather.asmx/GetCityWeatherByZIP?ZIP=string

    networkAccessMgr=new QNetworkAccessManager();


    settimerInterval(10000);
    timer.setSingleShot(false); //has to repeat when elapses
    connect(networkAccessMgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(processDataFromRemoteServer(QNetworkReply*)));
    connect(&timer,SIGNAL(timeout()),this,SLOT(getWeatherUpdate()));


    timer.start();
    getWeatherUpdate();
}

int WeatherService::timerInterval()
{
    return timer.interval();
}

void WeatherService::settimerInterval(int interval)
{
    timer.setInterval(interval);
}

WeatherInfo *WeatherService::currentWeather()
{
    return &currentWeatherInfo;
}

void WeatherService::processDataFromRemoteServer(QNetworkReply *reply)
{
    if(reply->error()!=QNetworkReply::NoError) return;


    if(netTask==GetCityWeatherByZIP)
    {
        timer.stop();
        QDomDocument domDocument;
        domDocument.setContent(reply->readAll());
        QDomNodeList nodeList= domDocument.elementsByTagName("WeatherReturn");
        nodeList =nodeList.at(nodeList.size()-1).childNodes();
        QString map_key,map_val;
        QDomElement element;

        for (int i = 0; i < nodeList.size(); ++i) {
            element= nodeList.at(i).toElement();
            map_key=element.tagName();
            map_val=element.text();
            xmlWeatherData.insert(map_key,map_val);
        }

        currentWeatherInfo.setCity(xmlWeatherData["City"]);
        currentWeatherInfo.setDescription(xmlWeatherData["Description"]);
        currentWeatherInfo.setPressure(xmlWeatherData["Pressure"]);
        currentWeatherInfo.setRelativeHumidity(xmlWeatherData["RelativeHumidity"].toDouble());
        currentWeatherInfo.setResponseText(xmlWeatherData["ResponseText"]);
        currentWeatherInfo.setState(xmlWeatherData["State"]);
        currentWeatherInfo.setSuccess(xmlWeatherData["Success"]=="true"?true:false);
        currentWeatherInfo.setTemperature(xmlWeatherData["Temperature"].toDouble());
        currentWeatherInfo.setWind(xmlWeatherData["Wind"]);
        currentWeatherInfo.setWeatherID(xmlWeatherData["WeatherID"]);

        if(xmlWeatherData["Success"]=="true")
        {
            setlastUpdateTime( QDateTime::currentDateTime()); //setting last updatetime
            //Sending request for weather photo
            netTask=GetWeatherInformation;
            QUrl url;
            url.setUrl("http://wsf.cdyne.com/WeatherWS/Weather.asmx/GetWeatherInformation?");
            networkGetRequest.setUrl(url);
            networkAccessMgr->get(networkGetRequest);
        }
        xmlWeatherData.clear();


        emit oncurrentWeatherChanged();
        timer.start();
    }
    else if (netTask==GetWeatherInformation)
    {
        QDomDocument domDocument;
        domDocument.setContent(reply->readAll());
//        QUrl url;
//        netTask=GetWeatherPhoto;
        QDomNodeList nodeList=domDocument.elementsByTagName("WeatherDescription");
        if(nodeList.isEmpty())
            return;
        nodeList=(nodeList.at(currentWeatherInfo.WeatherID().toInt()-1)).childNodes();
        QDomElement element;
        for (int i = 0; i < nodeList.size(); ++i) {
            element=nodeList.at(i).toElement();
            if (element.tagName()=="PictureURL") break;
        }
        if(currentWeatherInfo.Photo()!=element.text())
            currentWeatherInfo.setPhoto(element.text());


//        networkGetRequest.setUrl(url);
//        networkAccessMgr->get(networkGetRequest);
    }
//    else if(netTask==GetWeatherPhoto)
//    {
//        QImageReader imageReader(reply);
//        imageReader.setAutoDetectImageFormat(true);
//        currentWeatherInfo.setPhoto(new QImage(imageReader.read()));
//    }

}

void WeatherService::getWeatherUpdate()
{
    netTask=GetCityWeatherByZIP;
    QUrl url;
    url.setUrl("http://wsf.cdyne.com/WeatherWS/Weather.asmx/GetCityWeatherByZIP");
    QUrlQuery urlquery;
    urlquery.addQueryItem("ZIP","45701");
    url.setQuery(urlquery);
    networkGetRequest.setUrl(url);
    networkAccessMgr->get(networkGetRequest);
}





//    xmlReader.addData(reply->readAll());

//    while(xmlReader.readNext()!=QXmlStreamReader::StartElement &&
//          xmlReader.name()!="WeatherReturn");

//    QString map_key,map_val;

//    while(xmlReader.readNext()!=QXmlStreamReader::EndElement &&
//          xmlReader.name()!="WeatherReturn" )
//    {
//        if(xmlReader.tokenType()==QXmlStreamReader::StartElement)
//        {
//            map_key=xmlReader.name().toString();
//            if(xmlReader.readNext()==QXmlStreamReader::Characters)
//            {
//                map_val=xmlReader.text().toString();
//                xmlWeatherData.insert(map_key,map_val);
//                xmlReader.readNext();
//            }
//        }

//    }
