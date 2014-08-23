import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0
import WeatherService 1.0

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height
    title: qsTr("Weather Station")



    WeatherService{
        id:weatherService
        onCurrentWeatherChanged: {
            statusText.text=currentWeather.Success?
                        qsTr("Successfully pulled data from server"):
                        qsTr("Failed to pull data from remote server");

        }
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }



    statusBar: StatusBar{
        id: statusBar
        width: parent.width

        Flickable
        {
            height: statusText.height
            contentHeight: statusText.height
            width: statusText.width+lastUpdateTime.width
            contentWidth: Screen.width
            anchors.leftMargin: parent
            flickableDirection: Flickable.HorizontalFlick
            RowLayout{
                anchors.leftMargin: parent

                Label{
                    id: statusText
                }
                Label{
                    id: lastUpdateTime
                    text:"Last Update Time : "+weatherService.lastUpdateTime

                }
            }
        }
    }
    GridLayout
    {
        id:mainLayout

        rowSpacing: 8
        columnSpacing: 2
        columns: 2
        rows: 10
        anchors.centerIn: parent

        Text{
            id: description
            Layout.row: 2
            Layout.column: 0
            text:weatherService.currentWeather.Description;
        }
        Image {
            id: weatherPhoto
            Layout.row:2
            Layout.column: 1

            source: weatherService.currentWeather.Photo
        }

        Text{
            id: temperature
            Layout.row: 3
            Layout.column: 0
            text:"Temperature:"
        }
        Text{
            id: temperatureReading
            text:weatherService.currentWeather.Temperature;
        }

        Text{
            id: relativeHumidity
            Layout.row: 4
            Layout.column: 0
            text:"Relative humidity:"
        }
        Text{
            id: relativeHumidityReading
            text:weatherService.currentWeather.RelativeHumidity;
        }
        Text{
            id: pressure
            Layout.row: 5
            Layout.column: 0
            text:"Atmospheric pressure: "
        }
        Text{
            id: pressureReading
            text:weatherService.currentWeather.Pressure.toString();
        }
    }
}
