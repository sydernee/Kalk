NetworkList::NetworkList(QWidget *parent = nullptr)
    : QWidget(parent),
      stackedWidget(new QStackedWidget(this)),
      networkListWidget(new QListWidget(stackedWidget)),
      btnAddNetwork(new QPushButton("Aggiungi una rete", stackedWidget)),
      btnBackButton(new QPushButton("Torna indietro", this)),
      controller(nullptr)
{
    setWindowTitle("Network disponibili"); //imposta il titolo della finestra

    pages.append(new QWidget(this));       //pages[0]
    // TODO pages.append(nullptr) ad libitum

    stackedWidget->addWidget(pages[0]);


    stackedWidget->setCurrentWidget(pages[0]);
// TODO continuo da qua
    QVBoxLayout *hvlayout0 = new QVBoxLayout(pages[0]);
    hvlayout0->addWidget(networkListWidget);
    hvlayout0->addWidget(btnAddNetwork);

    QHBoxLayout *backButtonGroup = new QHBoxLayout;
    //memory leak?
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    backButtonGroup->addItem(spacer);
    backButtonGroup->addWidget(btnBackButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(backButtonGroup);
    layout->addWidget(stackedWidget);

    setLayout(layout);

    connect(btnBackButton, SIGNAL(clicked()), this, SLOT(handleBtnBackButton()));
    //connect(matrixSelection, SIGNAL(clicked()), this, SLOT(handleMatrixSelection()));

}

NetworkList::~NetworkList() {
    if (controller != nullptr)
        delete controller;
}

//SLOTS

void NetworkList::handleBtnBackButton() {
    if (stackedWidget->currentWidget() == pages[0]) {
        emit networkListCloseSignal();
        close();
    }
/*    else if (stackedWidget->currentWidget() == pages[1]) { //pages[1]
        //resetta il QWidget pages[1]
        delete pages[1];
        pages[1] = nullptr;
        stackedWidget->setCurrentWidget(pages[0]); //imposta pages[0] come attivo

        //ridimensionamento finestra
        setMinimumSize(wWindowSize,hWindowSize);
        resize(wWindowSize,hWindowSize);
    }
    else { //pages[2]
        delete pages[1];
        delete pages[2];
        pages[1] = nullptr;
        pages[2] = nullptr;
        stackedWidget->setCurrentWidget(pages[0]);

        //ridimensionamento finestra
        setMinimumSize(wWindowSize,hWindowSize);
        resize(wWindowSize,hWindowSize);
    }

*/
}
