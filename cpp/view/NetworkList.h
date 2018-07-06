class NetworkList : public QWidget {
    Q_OBJECT

    QStackedWidget* stackedWidget;      //contiene uno Stack di QWidget switchabili
    QVector<QWidget*> pages;            //QWidgets "paralleli"
    QList<Network*> networksList;       
    QListWidget* networkListWidget;     //list con tutte le reti disponibili
    QPushButton* btnAddNetwork;        //pulsante per aggiungere una rete
    QPushButton* btnBackButton;        //pulsante per tornare indietro

    NetworkListController* controller;

    //costanti per le dimensioni della finestra
    const int hWindowSize = 200;
    const int wWindowSize = 300;
    const int hCreatorWindowSize = 300;
    const int wCreatorWindowSize = 500;

    //TODO : ricarico gli elementi della networkList

public:
    explicit NetworkList(QWidget *parent = nullptr);
    ~NetworkList();

signals:
    void networkListCloseSignal();

private slots:
    void handleBtnBackButton();
};
