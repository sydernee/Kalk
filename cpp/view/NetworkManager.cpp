#include "NetworkManager.h"

//TODO : rimuovo le ridondanze, e.g.     QListWidget* gul1InsRemViewUser = new QListWidget();    QListWidget* gul2InsRemViewUser = new QListWidget();

NetworkManager::NetworkManager(QWidget *parent)
    : QWidget(parent),
      backButton(new QPushButton("Torna indietro", this)),
    controller(new NetworkController(this))
{
    setWindowTitle("Network Manager: gestisci i tuoi social"); //imposta il titolo della finestra

    setMinimumSize(wWindowSize,hWindowSize);
    resize(wWindowSize,hWindowSize);
    
    QString groupBoxStyle = "QGroupBox{border:2px solid gray;border-radius:5px;margin-top: 1ex;} QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top center;padding:0 3px;}";
    /*createUserGroupBox->setStyleSheet("
        QGroupBox {
            border:2px solid gray;
            border-radius:5px;
            margin-top: 1ex;
        } 
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position:top center;
            padding:0 3px;}
    ");
*/

    QHBoxLayout *backButtonGroup = new QHBoxLayout;
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    backButtonGroup->addItem(spacer);
    backButtonGroup->addWidget(backButton);
    
    //1 - layout di creazione dell'utente
    createUserGroupBox = new QGroupBox(tr("Creazione degli utenti")); 
    createUserGroup = new QHBoxLayout;
    gulCreateUser = new QListWidget();
    connect(gulCreateUser, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showGlobalUserData(QListWidgetItem*)));

    userData = new QGridLayout;
    lblUsername = new QLabel(tr("Username"));
    edtUsername = new QLineEdit;
    lblName = new QLabel(tr("Name"));
    edtName = new QLineEdit;
    lblSurname = new QLabel(tr("Surname"));
    edtSurname = new QLineEdit;

    // form con i dati dell'utente (da inserire/modificare)
    userData->addWidget(lblUsername,0,0);
    userData->addWidget(edtUsername,1,0);
    userData->addWidget(lblName,2,0);
    userData->addWidget(edtName,3,0);
    userData->addWidget(lblSurname,4,0);
    userData->addWidget(edtSurname,5,0);
    
    // bottoni del layout createUser
    createUserBottonGroup = new QVBoxLayout;
    btnAddUser = new QPushButton(tr("Aggiungi un nuovo utente"));
    connect(btnAddUser, SIGNAL(clicked()), this, SLOT(createGlobalUserClicked()));
    btnModifyUser = new QPushButton(tr("Modifica l'utente selezionato"));
    connect(btnModifyUser, SIGNAL(clicked()), this, SLOT(modifyGlobalUserDataClicked()));    
    btnRemoveUser = new QPushButton(tr("Rimuovi l'utente selezionato"));
    connect(btnRemoveUser, SIGNAL(clicked()), this, SLOT(deleteGlobalUserClicked())); 
    btnResetUser = new QPushButton(tr("Resetta i campi dati"));
    connect(btnResetUser, SIGNAL(clicked()), this, SLOT(resetGlobalUserData()));    

    createUserBottonGroup->addWidget(btnAddUser);
    createUserBottonGroup->addWidget(btnModifyUser);
    createUserBottonGroup->addWidget(btnRemoveUser);
    createUserBottonGroup->addWidget(btnResetUser);

    createUserGroup->addWidget(gulCreateUser);
    createUserGroup->addLayout(userData);
    createUserGroup->addLayout(createUserBottonGroup);

    createUserGroupBox->setLayout(createUserGroup);

    createUserGroupBox->setStyleSheet(groupBoxStyle);

    //1.2 - layout di creazione della rete


    edtNetname = new QLineEdit;
    createNetGroupBox = new QGroupBox(tr("Creazione delle reti")); 
    createNetGroup = new QHBoxLayout;
    gulCreateNet = new QListWidget();
    connect(gulCreateNet, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showNetName(QListWidgetItem*)));
    netData = new QFormLayout;
    netData->addRow(tr("Netname"), edtNetname);

    // form con i dati della rete (da inserire/modificare)
   // netData->addWidget(lblNetname);
    netData->addWidget(edtNetname);

    // bottoni del layout createNet
    createNetBottonGroup = new QVBoxLayout;
    btnAddNet = new QPushButton(tr("Aggiungi una nuova rete"));

    connect(btnAddNet, SIGNAL(clicked()), this, SLOT(createNetClicked()));
    btnRenameNet = new QPushButton(tr("Rinomina la rete selezionata"));
    connect(btnRenameNet, SIGNAL(clicked()), this, SLOT(modifyNetNameClicked())); 
    btnRemoveNet = new QPushButton(tr("Elimina la rete selezionata"));
    connect(btnRemoveNet, SIGNAL(clicked()), this, SLOT(deleteNetClicked())); 
    btnResetNet = new QPushButton(tr("Resetta il campo dati"));
    connect(btnResetNet, SIGNAL(clicked()), this, SLOT(resetNetData()));

    createNetBottonGroup->addWidget(btnAddNet);
    createNetBottonGroup->addWidget(btnRenameNet);
    createNetBottonGroup->addWidget(btnRemoveNet);
    createNetBottonGroup->addWidget(btnResetNet);
    
    createNetGroup->addWidget(gulCreateNet);
    createNetGroup->addLayout(netData);
    createNetGroup->addLayout(createNetBottonGroup);

    createNetGroupBox->setLayout(createNetGroup);

    createNetGroupBox->setStyleSheet(groupBoxStyle);
    
    createUserNetGroup = new QHBoxLayout;
    createUserNetGroup->addWidget(createUserGroupBox);
    createUserNetGroup->addWidget(createNetGroupBox);
    
    btnRenameNet->setEnabled(false);
    btnRemoveNet->setEnabled(false);
    
    //2 - Inserimento, rimozione e visualizzazione di un utente in una rete
    QGroupBox* insRemViewUserGroupBox = new QGroupBox(tr("Inserimento, rimozione e visualizzazione di un utente in una rete"));
    QVBoxLayout* insRemViewUserList0Layout = new QVBoxLayout;
    QVBoxLayout* insRemViewUserList1Layout = new QVBoxLayout;
    QVBoxLayout* insRemViewUserList2Layout = new QVBoxLayout;
    QVBoxLayout* insRemViewUserButtonGroup = new QVBoxLayout;
    
    QLabel* gul0InsRemViewUserLabel = new QLabel(tr("Reti disponibili"));
    QListWidget* gul0InsRemViewUser = new QListWidget();
    QLabel* gul1InsRemViewUserLabel = new QLabel(tr("Utenti della rete selezionata"));
    QListWidget* gul1InsRemViewUser = new QListWidget();
    QLabel* gul2InsRemViewUserLabel = new QLabel(tr("Utenti globalmente esistenti"));
    QListWidget* gul2InsRemViewUser = new QListWidget();

    insRemViewUserList0Layout->addWidget(gul0InsRemViewUserLabel);
    insRemViewUserList0Layout->addWidget(gul0InsRemViewUser);
    insRemViewUserList1Layout->addWidget(gul1InsRemViewUserLabel);
    insRemViewUserList1Layout->addWidget(gul1InsRemViewUser);
    insRemViewUserList2Layout->addWidget(gul2InsRemViewUserLabel);
    insRemViewUserList2Layout->addWidget(gul2InsRemViewUser);
    
    QPushButton* btnIRVAddUser = new QPushButton(tr("Aggiungi l'utente selezionato"));
    QPushButton* btnIRVRemoveUser = new QPushButton(tr("Rimuovi l'utente selezionato"));
    QPushButton* btnIRVViewProfile = new QPushButton(tr("Visualizza l'utente selezionato"));

    insRemViewUserButtonGroup->addWidget(btnIRVAddUser);
    insRemViewUserButtonGroup->addWidget(btnIRVRemoveUser);
    insRemViewUserButtonGroup->addWidget(btnIRVViewProfile);

    QHBoxLayout* insRemViewUserGroup = new QHBoxLayout;
    insRemViewUserGroup->addLayout(insRemViewUserList0Layout);
    insRemViewUserGroup->addLayout(insRemViewUserList1Layout);
    insRemViewUserGroup->addLayout(insRemViewUserList2Layout);
    insRemViewUserGroup->addLayout(insRemViewUserButtonGroup);
    
    insRemViewUserGroupBox->setLayout(insRemViewUserGroup);
    insRemViewUserGroupBox->setStyleSheet(groupBoxStyle);

    //3 - Following e Follower
    QGroupBox* followerGroupBox = new QGroupBox(tr("Inserimento, rimozione e visualizzazione di un utente in una rete"));
    QVBoxLayout* gulFollowerNetLayout = new QVBoxLayout;
    QVBoxLayout* gulFollowerLayout = new QVBoxLayout;
    QVBoxLayout* gulFollowerOutputLayout = new QVBoxLayout;
    QVBoxLayout* gulFollowerButtonGroup = new QVBoxLayout;
    
    QLabel* gulFollowerNetLabel = new QLabel(tr("Reti disponibili"));
    QListWidget* gulFollowerNet = new QListWidget();
    QLabel* gulFollowerLabel = new QLabel(tr("Utenti della rete"));
    QListWidget* gulFollower = new QListWidget();    
    QLabel* gulFollowerOutputLabel = new QLabel(tr("Follower"));
    QListWidget* gulFollowerOutput = new QListWidget();


    gulFollowerNetLayout->addWidget(gulFollowerNetLabel);
    gulFollowerNetLayout->addWidget(gulFollowerNet);
    gulFollowerLayout->addWidget(gulFollowerLabel);
    gulFollowerLayout->addWidget(gulFollower);
    gulFollowerOutputLayout->addWidget(gulFollowerOutputLabel);
    gulFollowerOutputLayout->addWidget(gulFollowerOutput);
    
    QPushButton* btnGetFollower = new QPushButton(tr("Visualizza i follower"));
    QPushButton* btnGetFollowed = new QPushButton(tr("Visualizza i followed"));
    QPushButton* btnAddFollower = new QPushButton(tr("Aggiungi come follower "));
    QPushButton* btnRemoveFollower = new QPushButton(tr("Rimuovi il follower")); //attivo solo quando sto visualizzando i follower



    gulFollowerButtonGroup->addWidget(btnGetFollower);
    gulFollowerButtonGroup->addWidget(btnGetFollowed);
    gulFollowerButtonGroup->addWidget(btnAddFollower);
    gulFollowerButtonGroup->addWidget(btnRemoveFollower);

    QHBoxLayout* followerGroup = new QHBoxLayout;
    followerGroup->addLayout(gulFollowerNetLayout);
    followerGroup->addLayout(gulFollowerLayout);
    followerGroup->addLayout(gulFollowerOutputLayout);
    followerGroup->addLayout(gulFollowerButtonGroup);
    
    followerGroupBox->setLayout(followerGroup);
    followerGroupBox->setStyleSheet(groupBoxStyle);

    //4-

    QGroupBox* netOpGroupBox = new QGroupBox(tr("Operazioni tra matrici"));
    QVBoxLayout* netOpList0Layout = new QVBoxLayout;
    QVBoxLayout* netOpList1Layout = new QVBoxLayout;
    QVBoxLayout* netOpOutputLayout = new QVBoxLayout;
    QVBoxLayout* netOpButtonGroup = new QVBoxLayout;
    
    QLabel* gul0netOpLabel = new QLabel(tr("Seleziona rete A"));
    QListWidget* gul0netOp = new QListWidget();
    QLabel* gul1netOpLabel = new QLabel(tr("Seleziona rete A"));
    QListWidget* gul1netOp = new QListWidget();
    QLabel* gul2netOpLabel = new QLabel(tr("Output"));
    QListWidget* gul2netOp = new QListWidget();

    netOpList0Layout->addWidget(gul0netOpLabel);
    netOpList0Layout->addWidget(gul0netOp);
    netOpList1Layout->addWidget(gul1netOpLabel);
    netOpList1Layout->addWidget(gul1netOp);
    netOpOutputLayout->addWidget(gul2netOpLabel);
    netOpOutputLayout->addWidget(gul2netOp);
    
    QPushButton* btnGetUnion = new QPushButton(tr("A + B"));
    QPushButton* btnGetIntersection = new QPushButton(tr("Intersezione di A in B"));
    QPushButton* btnGetRelativeComplement = new QPushButton(tr("Complemento relativo di A in B"));
    QPushButton* btnGetSymmetricDifference = new QPushButton(tr("Differenza simmetrica di A in B"));

    netOpButtonGroup->addWidget(btnGetUnion);
    netOpButtonGroup->addWidget(btnGetIntersection);
    netOpButtonGroup->addWidget(btnGetRelativeComplement);
    netOpButtonGroup->addWidget(btnGetSymmetricDifference);

    QHBoxLayout* netOpGroup = new QHBoxLayout;
    netOpGroup->addLayout(netOpList0Layout);
    netOpGroup->addLayout(netOpList1Layout);
    netOpGroup->addLayout(netOpOutputLayout);
    netOpGroup->addLayout(netOpButtonGroup);
    
    netOpGroupBox->setLayout(netOpGroup);
    netOpGroupBox->setStyleSheet(groupBoxStyle);

    // set layout
    QVBoxLayout *layout = new QVBoxLayout;
    
    layout->addLayout(backButtonGroup);
    layout->addLayout(createUserNetGroup);
    layout->addWidget(insRemViewUserGroupBox);
    layout->addWidget(followerGroupBox);
    layout->addWidget(netOpGroupBox);

    setLayout(layout);


    connect(backButton, SIGNAL(clicked()), this, SLOT(handleBackButton()));
    
    //disabilito i bottoni che all'inizio non posso usare
    btnModifyUser->setEnabled(false);
    btnRemoveUser->setEnabled(false);
}


void NetworkManager::handleBackButton() {
    emit networkManagerCloseSignal();
    close();
}

NetworkManager::~NetworkManager() {   
if (controller != nullptr)
    delete controller;
}

//slots createUser

void NetworkManager::createGlobalUserClicked() {
    qDebug() << "createGlobalUserClicked";
    QString username = edtUsername->text();
    QString name     = edtName->text();
    QString surname  = edtSurname->text();

    // aggiungo un User sono se non esiste già un altro con lo stesso username    
    bool resCreate = controller->createGlobalUser(username,name,surname);
    if (resCreate) {
        gulCreateUser->addItem(username);
        resetGlobalUserData();
        // TODO : emetto un segnale che ho inserito un utente, la userGlobalList è variata
    } else {
        QErrorMessage* err = new QErrorMessage;
        err->setAttribute(Qt::WA_DeleteOnClose);
        err->showMessage("Username già esistente, scegli un altro username");
    }
    
}

void NetworkManager::showGlobalUserData(QListWidgetItem*) {
    qDebug() << "Hai effettuato il doppio click sulla riga" << gulCreateUser->currentRow() << "di gulCreateUser";
    QVector<QString> vData = controller->getUserData(gulCreateUser->currentRow());
    
    edtUsername->setText(vData[0]);
    edtName->setText(vData[1]);
    edtSurname->setText(vData[2]);
    
    edtUsername->setReadOnly(true);
    btnModifyUser->setEnabled(true);
    btnRemoveUser->setEnabled(true);
    btnAddUser->setEnabled(false);
}

void NetworkManager::modifyGlobalUserDataClicked() {
    QString name    = edtName->text();
    QString surname = edtSurname->text();
    
    controller->setUserData(gulCreateUser->currentRow(), name, surname);
    
    resetGlobalUserData();
}

void NetworkManager::deleteGlobalUserClicked() {
    controller->deleteUser(gulCreateUser->currentRow());
    gulCreateUser->takeItem(gulCreateUser->currentRow());
    
    resetGlobalUserData();
}

void NetworkManager::resetGlobalUserData() {    
    edtUsername->clear();
    edtName->clear();
    edtSurname->clear();
        
    edtUsername->setReadOnly(false);
    btnModifyUser->setEnabled(false);
    btnRemoveUser->setEnabled(false);
    btnAddUser->setEnabled(true);
    
    qDebug() << "Resettati i campi dati - creazione utente";
}

//slots createNet

void NetworkManager::createNetClicked() {
    QString netname = edtNetname->text();

    bool resCreate = controller->createNet(netname);
    if (resCreate) {
        gulCreateNet->addItem(netname);
        resetNetData();
        // TODO : emetto un segnale che ho inserito una rete, la netGlobalList è variata
    } else {
        QErrorMessage* err = new QErrorMessage;
        err->setAttribute(Qt::WA_DeleteOnClose);
        err->showMessage("Netname già esistente, scegli un altro netname");
    }
    
}

void NetworkManager::showNetName(QListWidgetItem*) {
    qDebug() << "Hai effettuato il doppio click sulla riga" << gulCreateNet->currentRow() << "di gulCreateNet";
    QString name = controller->getNetName(gulCreateNet->currentRow());
    edtNetname->setText(name);
    
    btnRenameNet->setEnabled(true);
    btnRemoveNet->setEnabled(true);
    btnAddNet->setEnabled(false);
}

void NetworkManager::modifyNetNameClicked() {
    QString netname = edtNetname->text();

    bool resRename = controller->renameNet(gulCreateNet->currentRow(),netname);
    if (resRename) {
        QList<QListWidgetItem *> sItems = gulCreateNet->selectedItems();
        sItems.first()->setText(netname);
        resetNetData();
        // TODO : emetto un segnale che ho inserito una rete, la netGlobalList è variata
    } else {
        QErrorMessage* err = new QErrorMessage;
        err->setAttribute(Qt::WA_DeleteOnClose);
        err->showMessage("Netname già esistente, scegli un altro netname");
    }    
}        

void NetworkManager::deleteNetClicked() {
    controller->deleteNet(gulCreateNet->currentRow());
    gulCreateNet->takeItem(gulCreateNet->currentRow());
    
    resetNetData();
}
    
void NetworkManager::resetNetData() {
    edtNetname->clear();
    
    btnRenameNet->setEnabled(false);
    btnRemoveNet->setEnabled(false);
    btnAddNet->setEnabled(true);    
    
    qDebug() << "Resettati i campi dati - creazione rete";
}



/*

()
    QStringList list;
    list << "Bill Murray" << "John Doe" << "Bill Clinton" << "Re Pomponio Mela" << "Beyond" << "Wu Ming 0";
    list << "Wu Ming 1" << "Wu Ming 2" << "Wu Ming 3" << "Wu Ming 4" <<"Wu Ming 5";
    foreach (const QString &str, list) {
        gulCreateUser->addItem(str);
    }
    
*/
