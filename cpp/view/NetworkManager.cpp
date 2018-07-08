#include "NetworkManager.h"

//TODO : rimuovo le ridondanze, e.g.     QListWidget* netUserInsRemUser = new QListWidget();    QListWidget* gulInsRemUser = new QListWidget();

//evito un disallineamento tra currentRow ed elemento selezionato TODO
//bool isValidNetsList {return validNetsList;}
//void setValidNetslist(bool b) {validNetsList = b;}
//bool isValiUserGList {return validUserGList;}
//void setValidNetGlist(bool b) {validUserGList = b;}


NetworkManager::NetworkManager(QWidget *parent)
    : QWidget(parent),
      backButton(new QPushButton("Torna indietro", this)),
    controller(new NetworkController(this))//,
    //validNetsList(false),
    //validUserGList(false)
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
    connect(gulCreateUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showGlobalUserData(QListWidgetItem*)));

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
    connect(gulCreateNet, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showNetName(QListWidgetItem*)));
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
    InsRemUserGroupBox = new QGroupBox(tr("Inserimento, rimozione e visualizzazione degli utenti in una rete"));
    InsRemUserList0Layout = new QVBoxLayout;
    InsRemUserList1Layout = new QVBoxLayout;
    InsRemUserList2Layout = new QVBoxLayout;
    InsRemUserButtonGroup = new QVBoxLayout;
    
    netInsRemUserLabel = new QLabel(tr("Reti disponibili"));
    netInsRemUser = new QListWidget();
    connect(netInsRemUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showNetworkUser()));
    connect(netInsRemUser,SIGNAL(itemSelectionChanged()), this, SLOT(setInsRemButtonStatus()));
    connect(netInsRemUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setInsRemButtonStatus()));
    netUserInsRemUserLabel = new QLabel(tr("Utenti della rete selezionata"));
    netUserInsRemUser = new QListWidget();
    connect(netUserInsRemUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectedUserNetwork()));
    gulInsRemUserLabel = new QLabel(tr("Utenti globalmente esistenti"));
    gulInsRemUser = new QListWidget();
    connect(gulInsRemUser,SIGNAL(itemSelectionChanged()), this, SLOT(setInsRemButtonStatus()));
    connect(gulInsRemUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setInsRemButtonStatus()));    
    

    InsRemUserList0Layout->addWidget(netInsRemUserLabel);
    InsRemUserList0Layout->addWidget(netInsRemUser);
    InsRemUserList1Layout->addWidget(netUserInsRemUserLabel);
    InsRemUserList1Layout->addWidget(netUserInsRemUser);
    InsRemUserList2Layout->addWidget(gulInsRemUserLabel);
    InsRemUserList2Layout->addWidget(gulInsRemUser);
    
    btnIRAddUser = new QPushButton(tr("Aggiungi l'utente selezionato"));
    connect(btnIRAddUser, SIGNAL(clicked()), this, SLOT(addUserToNetwork()));
    btnIRRemoveUser = new QPushButton(tr("Rimuovi l'utente selezionato"));
    connect(btnIRRemoveUser, SIGNAL(clicked()), this, SLOT(deleteUserFromNetworkClicked())); 
    
    btnIRAddUser->setEnabled(false);
    btnIRRemoveUser->setEnabled(false);

    InsRemUserButtonGroup->addWidget(btnIRAddUser);
    InsRemUserButtonGroup->addWidget(btnIRRemoveUser);

    InsRemUserGroup = new QHBoxLayout;
    InsRemUserGroup->addLayout(InsRemUserList0Layout);
    InsRemUserGroup->addLayout(InsRemUserList1Layout);
    InsRemUserGroup->addLayout(InsRemUserList2Layout);
    InsRemUserGroup->addLayout(InsRemUserButtonGroup);
    
    InsRemUserGroupBox->setLayout(InsRemUserGroup);
    InsRemUserGroupBox->setStyleSheet(groupBoxStyle);

    //3 - Following e Follower
    followerGroupBox = new QGroupBox(tr("Inserimento, rimozione e visualizzazione di un utente in una rete"));
    gulFollowerNetLayout = new QVBoxLayout;
    gulFollowerLayout = new QVBoxLayout;
    gulFollowerOutputLayout = new QVBoxLayout;
    gulFollowerButtonGroup = new QVBoxLayout;
    
    gulFollowerNetLabel = new QLabel(tr("Reti disponibili"));
    gulFollowerNet = new QListWidget();
    gulFollowerLabel = new QLabel(tr("Utenti della rete"));
    gulFollower = new QListWidget();    
    gulFollowerOutputLabel = new QLabel(tr("Follower"));
    gulFollowerOutput = new QListWidget();


    gulFollowerNetLayout->addWidget(gulFollowerNetLabel);
    gulFollowerNetLayout->addWidget(gulFollowerNet);
    gulFollowerLayout->addWidget(gulFollowerLabel);
    gulFollowerLayout->addWidget(gulFollower);
    gulFollowerOutputLayout->addWidget(gulFollowerOutputLabel);
    gulFollowerOutputLayout->addWidget(gulFollowerOutput);
    
    btnGetFollower = new QPushButton(tr("Visualizza i follower"));
    btnGetFollowed = new QPushButton(tr("Visualizza i followed"));
    btnAddFollower = new QPushButton(tr("Aggiungi come follower "));
    btnRemoveFollower = new QPushButton(tr("Rimuovi il follower")); //attivo solo quando sto visualizzando i follower

    gulFollowerButtonGroup->addWidget(btnGetFollower);
    gulFollowerButtonGroup->addWidget(btnGetFollowed);
    gulFollowerButtonGroup->addWidget(btnAddFollower);
    gulFollowerButtonGroup->addWidget(btnRemoveFollower);

    followerGroup = new QHBoxLayout;
    followerGroup->addLayout(gulFollowerNetLayout);
    followerGroup->addLayout(gulFollowerLayout);
    followerGroup->addLayout(gulFollowerOutputLayout);
    followerGroup->addLayout(gulFollowerButtonGroup);
    
    followerGroupBox->setLayout(followerGroup);
    followerGroupBox->setStyleSheet(groupBoxStyle);

    //4-Operazioni tra matrici

    netOpGroupBox = new QGroupBox(tr("Operazioni tra matrici"));
    netOpList0Layout = new QVBoxLayout;
    netOpList1Layout = new QVBoxLayout;
    netOpOutputLayout = new QVBoxLayout;
    netOpButtonGroup = new QVBoxLayout;
    
    gul0netOpLabel = new QLabel(tr("Seleziona rete A"));
    gul0netOp = new QListWidget();
    connect(gul0netOp,SIGNAL(itemSelectionChanged()), this, SLOT(setOperationNetButtonStatus()));
    connect(gul0netOp, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setOperationNetButtonStatus()));
    gul1netOpLabel = new QLabel(tr("Seleziona rete B"));
    gul1netOp = new QListWidget();
    connect(gul1netOp,SIGNAL(itemSelectionChanged()), this, SLOT(setOperationNetButtonStatus()));
    connect(gul1netOp, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setOperationNetButtonStatus()));
    gul2netOpLabel = new QLabel(tr("Output"));
    gul2netOp = new QListWidget();

    netOpList0Layout->addWidget(gul0netOpLabel);
    netOpList0Layout->addWidget(gul0netOp);
    netOpList1Layout->addWidget(gul1netOpLabel);
    netOpList1Layout->addWidget(gul1netOp);
    netOpOutputLayout->addWidget(gul2netOpLabel);
    netOpOutputLayout->addWidget(gul2netOp);
    
    btnGetUnion = new QPushButton(tr("A + B"));
    connect(btnGetUnion, SIGNAL(clicked()), this, SLOT(calculateUnion()));
    btnGetIntersection = new QPushButton(tr("Intersezione di A in B"));
    connect(btnGetIntersection, SIGNAL(clicked()), this, SLOT(calculateIntersection()));    
    btnGetRelativeComplement = new QPushButton(tr("Complemento relativo di A in B"));
    connect(btnGetRelativeComplement, SIGNAL(clicked()), this, SLOT(calculateRelativeComplement()));    
    btnGetSymmetricDifference = new QPushButton(tr("Differenza simmetrica di A in B"));
    connect(btnGetSymmetricDifference, SIGNAL(clicked()), this, SLOT(calculateSymmetricDifference()));

    netOpButtonGroup->addWidget(btnGetUnion);
    netOpButtonGroup->addWidget(btnGetIntersection);
    netOpButtonGroup->addWidget(btnGetRelativeComplement);
    netOpButtonGroup->addWidget(btnGetSymmetricDifference);

    netOpGroup = new QHBoxLayout;
    netOpGroup->addLayout(netOpList0Layout);
    netOpGroup->addLayout(netOpList1Layout);
    netOpGroup->addLayout(netOpOutputLayout);
    netOpGroup->addLayout(netOpButtonGroup);
    
    netOpGroupBox->setLayout(netOpGroup);
    netOpGroupBox->setStyleSheet(groupBoxStyle);

    // set layout
    layout = new QVBoxLayout;
    
    layout->addLayout(backButtonGroup);
    layout->addLayout(createUserNetGroup);
    layout->addWidget(InsRemUserGroupBox);
    layout->addWidget(followerGroupBox);
    layout->addWidget(netOpGroupBox);

    setLayout(layout);


    connect(backButton, SIGNAL(clicked()), this, SLOT(handleBackButton()));
    
    //disabilito i bottoni che all'inizio non posso usare
    disableButtons();
}

 //data una QListWidget*, ritorna la posizione del suo primo elemento
int NetworkManager::getSelectedRow(QListWidget* qwl) {
    if (qwl->currentRow() < 0) {return -1;} 

    QListWidgetItem *selected = qwl->selectedItems().first();
    return qwl->row(selected);
    
}

void NetworkManager::handleBackButton() {
    emit networkManagerCloseSignal();
    close();
}

NetworkManager::~NetworkManager() {   
    if (controller != nullptr)
        delete controller;
}

void NetworkManager::setInsRemButtonStatus() {
    qDebug() << "gulInsRemUser->currentRow(): " << gulInsRemUser->currentRow(); 
    qDebug() << "getSelectedRow(netInsRemUser): " << getSelectedRow(netInsRemUser);
    qDebug() << "netInsRemUser->currentRow(): " << netInsRemUser->currentRow();
    qDebug() << "getSelectedRow(gulInsRemUser): " << getSelectedRow(gulInsRemUser);
    qDebug() << "============";
        
    if (gulInsRemUser->currentRow() > -1 && 
        netInsRemUser->currentRow() > -1 &&
        getSelectedRow(gulInsRemUser) == gulInsRemUser->currentRow() &&
        getSelectedRow(netInsRemUser) == netInsRemUser->currentRow()
    ) {
        btnIRAddUser->setEnabled(true);
    } else {
        btnIRAddUser->setEnabled(false);
        btnIRRemoveUser->setEnabled(false);
    }
}


void NetworkManager::setOperationNetButtonStatus() { //TODONOW
    qDebug() << "gul0netOp->currentRow(): " << gul0netOp->currentRow(); 
    qDebug() << "getSelectedRow(gul0netOp): " << getSelectedRow(gul0netOp);
    qDebug() << "gul1netOp->currentRow(): " << gul1netOp->currentRow();
    qDebug() << "getSelectedRow(gul1netOp): " << getSelectedRow(gul1netOp);
    qDebug() << "============";
        
    if (gul0netOp->currentRow() > -1 && 
        gul1netOp->currentRow() > -1 &&
        getSelectedRow(gul0netOp) == gul0netOp->currentRow() &&
        getSelectedRow(gul1netOp) == gul1netOp->currentRow()
    ) {
        btnGetUnion->setEnabled(true);
        btnGetIntersection->setEnabled(true);
        btnGetRelativeComplement->setEnabled(true);
        btnGetSymmetricDifference->setEnabled(true);
    } else {
        btnGetUnion->setEnabled(false);
        btnGetIntersection->setEnabled(false);
        btnGetRelativeComplement->setEnabled(false);
        btnGetSymmetricDifference->setEnabled(false);
    }
}

void NetworkManager::disableButtons() {
    qDebug() << "Disabilito i bottoni dei box 2-4";
    //2
    btnIRAddUser->setEnabled(false);
    btnIRRemoveUser->setEnabled(false);

    //3 - Following e Follower
    btnGetFollower->setEnabled(false);
    btnGetFollowed->setEnabled(false);
    btnAddFollower->setEnabled(false);
    btnRemoveFollower->setEnabled(false);

    //4-Operazioni tra matrici
    btnGetUnion->setEnabled(false);
    btnGetIntersection->setEnabled(false);
    btnGetRelativeComplement->setEnabled(false);
    btnGetSymmetricDifference->setEnabled(false);
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
        gulInsRemUser->addItem(username);
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
    gulInsRemUser->takeItem(gulCreateUser->currentRow());
    
    resetGlobalUserData();
    disableButtons();
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
        //2
        netInsRemUser->addItem(netname);
        //3
        gulFollowerNet->addItem(netname);
        //4
        gul0netOp->addItem(netname);
        gul1netOp->addItem(netname);
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
        int posNetModify = gulCreateNet->currentRow();
        (gulCreateNet->item(posNetModify))->setText(netname);
        //2
        (netInsRemUser->item(posNetModify))->setText(netname);
        //3
        (gulFollowerNet->item(posNetModify))->setText(netname);
        //4
        (gul0netOp->item(posNetModify))->setText(netname);
        (gul1netOp->item(posNetModify))->setText(netname);
        
        resetNetData();
        // TODO : emetto un segnale che ho inserito una rete, la netGlobalList è variata
    } else {
        QErrorMessage* err = new QErrorMessage;
        err->setAttribute(Qt::WA_DeleteOnClose);
        err->showMessage("Netname già esistente, scegli un altro netname");
    }    
}        

void NetworkManager::deleteNetClicked() {
    int posNetDelete = gulCreateNet->currentRow();
    
    controller->deleteNet(posNetDelete);
    gulCreateNet->takeItem(posNetDelete);
    //2
    netInsRemUser->takeItem(posNetDelete);
    //3
    gulFollowerNet->takeItem(posNetDelete);
    //4
    gul0netOp->takeItem(posNetDelete);
    gul1netOp->takeItem(posNetDelete);
    
    resetNetData();
    disableButtons();
}
    
void NetworkManager::resetNetData() {
    edtNetname->clear();
    
    btnRenameNet->setEnabled(false);
    btnRemoveNet->setEnabled(false);
    btnAddNet->setEnabled(true);    
    
    qDebug() << "Resettati i campi dati - creazione rete";
}


void NetworkManager::addUserToNetwork() {
    qDebug() << "add user to network";
    int userPos = gulInsRemUser->currentRow();
    int netPos = netInsRemUser->currentRow();
    qDebug() << "gulInsRemUser->currentRow():" << userPos;
    qDebug() << "netInsRemUser->currentRow():" << netPos;
    
    int row = getSelectedRow(netInsRemUser);
    qDebug() << "netInsRemUser selected row:" << row;
    
    
    if (controller->addUserToNetwork(netPos, userPos)) {
        showNetworkUser();
    }
}

void NetworkManager::showNetworkUser() {
    QStringList users = controller->getNetworkUsers(netInsRemUser->currentRow());
    
    netUserInsRemUser->clear();

    foreach (const QString &strUser, users) {
        netUserInsRemUser->addItem(strUser);
    }
}

void NetworkManager::selectedUserNetwork() {
    btnIRRemoveUser->setEnabled(true);
}

void NetworkManager::deleteUserFromNetworkClicked() {
    qDebug() << "delete user from network";
    
    int posNet = netInsRemUser->currentRow();
    qDebug()  << "Posizione rete da eliminare: " << posNet;
    
    QString username = netUserInsRemUser->selectedItems().first()->text(); 
        
    qDebug() << "Username da eliminare dalla rete: " << username;
    
    netUserInsRemUser->takeItem(netUserInsRemUser->currentRow());
    controller->removeUserFromNetwork(posNet, username);
    
    btnIRRemoveUser->setEnabled(false);
    //TODO aggiorno la visualizzazione 
}

void NetworkManager::calculateUnion() {
    int posNetA = gul0netOp->currentRow();
    int posNetB = gul1netOp->currentRow();
    
    QStringList res = controller->calculateUnion(posNetA,posNetB);
    
    gul2netOp->clear();
    
    foreach (const QString &str, res) {
        gul2netOp->addItem(str);
    }
}

void NetworkManager::calculateIntersection() {
    int posNetA = gul0netOp->currentRow();
    int posNetB = gul1netOp->currentRow();
    
    QStringList res = controller->calculateIntersection(posNetA,posNetB);
    
    gul2netOp->clear();
    
    foreach (const QString &str, res) {
        gul2netOp->addItem(str);
    }
}

void NetworkManager::calculateRelativeComplement() {
    int posNetA = gul0netOp->currentRow();
    int posNetB = gul1netOp->currentRow();
    
    QStringList res = controller->calculateRelativeComplement(posNetA,posNetB);
    
    gul2netOp->clear();
    
    foreach (const QString &str, res) {
        gul2netOp->addItem(str);
    }
}

void NetworkManager::calculateSymmetricDifference() {
    int posNetA = gul0netOp->currentRow();
    int posNetB = gul1netOp->currentRow();
    
    QStringList res = controller->calculateSymmetricDifference(posNetA,posNetB);
    
    gul2netOp->clear();
    
    foreach (const QString &str, res) {
        gul2netOp->addItem(str);
    }
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
