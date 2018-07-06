#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QWidget>
#include <QPushButton>

class NetworkManager : public QWidget 
{
    Q_OBJECT
private:
    QPushButton* backButton; //pulsante per tornare indietro

    //NetworkController* controller; TODO

    //costanti per le dimensioni della finestre
    const int hWindowSize = 1200;
    const int wWindowSize = 1200;
    const int hCreatorWindowSize = 1200;
    const int wCreatorWindowSize = 1200;

public:
    explicit NetworkManager(QWidget *parent = nullptr);
    ~NetworkManager();

signals:
    void networkManagerCloseSignal();

private slots:
    void handleBackButton();
};
#endif //NETWORKMANAGER_H
