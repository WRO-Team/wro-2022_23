#include <iostream>
#include <opencv2/highgui.hpp> //OpenCV Bibilotheken laden
#include <opencv2/opencv.hpp> //OpenCV Bibilotheken laden

using namespace cv; //Um cv::<...> zu vermeiden

int main(int, char**) { //main-Funktion
    
    Mat image; //TODO: #2 Was macht der Befehl genau bzw. was ist "Mat"?
    image = imread("C:/Users/pepes/Pictures/Saved Pictures/88223a.jpg"); //!Pfad zu Bild aus eigenem Verzeichnis eintragen

    if ( !image.data ){ //Prüfen, ob Bild vorhanden
        printf("No image data \n");
        return -1;
    }

    namedWindow("Display Image", WINDOW_AUTOSIZE); //Erstellt neues Fenster namens "Display Image"
    imshow("Display Image", image); //Stellt Bild in Fenster dar
    waitKey(0); //Abbruch, wenn Taste gedrückt
    return 0;
}
