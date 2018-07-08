#include "NetworkManager.h"



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
    followerGroupBox = new QGroupBox(tr("Gestione follower degli utenti"));
    gulFollowerNetLayout = new QVBoxLayout;
    gulFollowerNetUserLayout = new QVBoxLayout;
    gulFollowerLayout = new QVBoxLayout;
    gulFollowedLayout = new QVBoxLayout;
    gulFollowerSelUserLayout = new QVBoxLayout;
    gulFollowerButtonGroup = new QVBoxLayout;
    
    gulFollowerNetLabel = new QLabel(tr("Reti disponibili"));
    gulFollowerNet = new QListWidget();
    connect(gulFollowerNet, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showFollowerNetworks()));
    gulFollowerNetUserLabel = new QLabel(tr("Utenti della rete"));
    gulFollowerNetUser = new QListWidget();    
    connect(gulFollowerNetUser,SIGNAL(itemSelectionChanged()), this, SLOT(setNewFollowerButtonStatus()));
    connect(gulFollowerNetUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setNewFollowerButtonStatus())); 
    connect(gulFollowerNetUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showFollower()));
    connect(gulFollowerNetUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showFollowed()));
    gulFollowerLabel = new QLabel(tr("Utenti che ti seguono"));
    gulFollower = new QListWidget();
    gulFollowedLabel = new QLabel(tr("Utenti che segui"));
    gulFollowed = new QListWidget();
    connect(gulFollowed, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(userFollowedClicked())); 
    gulFollowerSelUserLabel = new QLabel(tr("Utenti selezionabili"));
    gulFollowerSelUser = new QListWidget();
    connect(gulFollowerSelUser,SIGNAL(itemSelectionChanged()), this, SLOT(setNewFollowerButtonStatus()));
    connect(gulFollowerSelUser, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setNewFollowerButtonStatus()));

    gulFollowerNetLayout->addWidget(gulFollowerNetLabel);
    gulFollowerNetLayout->addWidget(gulFollowerNet);
    gulFollowerNetUserLayout->addWidget(gulFollowerNetUserLabel);
    gulFollowerNetUserLayout->addWidget(gulFollowerNetUser);
    gulFollowerLayout->addWidget(gulFollowerLabel);
    gulFollowerLayout->addWidget(gulFollower);
    gulFollowedLayout->addWidget(gulFollowedLabel);
    gulFollowedLayout->addWidget(gulFollowed);
    gulFollowerSelUserLayout->addWidget(gulFollowerSelUserLabel);
    gulFollowerSelUserLayout->addWidget(gulFollowerSelUser);
    
    btnAddFollower = new QPushButton(tr("Segui l'utente "));
    connect(btnAddFollower, SIGNAL(clicked()), this, SLOT(addFollowerClicked()));
    btnRemoveFollowed = new QPushButton(tr("Smetti di seguire")); //attivo solo quando sto visualizzando i follower
    connect(btnRemoveFollowed, SIGNAL(clicked()), this, SLOT(removeFollowerClicked()));

    gulFollowerButtonGroup->addWidget(btnAddFollower);
    gulFollowerButtonGroup->addWidget(btnRemoveFollowed);

    followerGroup = new QHBoxLayout;
    followerGroup->addLayout(gulFollowerNetLayout);
    followerGroup->addLayout(gulFollowerNetUserLayout);
    followerGroup->addLayout(gulFollowerLayout);
    followerGroup->addLayout(gulFollowedLayout);
    followerGroup->addLayout(gulFollowerSelUserLayout);        
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
        btnIRRemoveUser->setEnabled(true);
    } else {
        btnIRAddUser->setEnabled(false);
        btnIRRemoveUser->setEnabled(false);
    }
}


void NetworkManager::setOperationNetButtonStatus() { 
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
    btnAddFollower->setEnabled(false);
    btnRemoveFollowed->setEnabled(false);

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
    
    netUserInsRemUser->clear();
    gulFollowerNetUser->clear();
    gulFollower->clear();
    gulFollowed->clear();
    gulFollowerSelUser->clear();
    
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
    btnIRAddUser->setEnabled(false);
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


void NetworkManager::showFollowerNetworks() { 
    qDebug() << gulFollowerNet->currentRow();
    QStringList users = controller->getNetworkUsers(gulFollowerNet->currentRow());
    
       
    gulFollowerNetUser->clear();
    gulFollower->clear();
    gulFollowed->clear();
    gulFollowerSelUser->clear();
  
    if (users.size() > 0) {
        foreach (auto strUser, users) {
            gulFollowerNetUser->addItem(strUser);
            gulFollowerSelUser->addItem(strUser);   
        }
    }
}

void NetworkManager::setNewFollowerButtonStatus() {
    qDebug() << "setNewFollowerButtonStatus()";
        
    if (gulFollowerNetUser->currentRow() > -1 && 
        gulFollowerSelUser->currentRow() > -1 &&
        getSelectedRow(gulFollowerNetUser) == gulFollowerNetUser->currentRow() &&
        getSelectedRow(gulFollowerSelUser) == gulFollowerSelUser->currentRow()
    ) {
        btnAddFollower->setEnabled(true);
    } else {
        btnAddFollower->setEnabled(false);
        btnRemoveFollowed->setEnabled(false);
    }
}

void NetworkManager::addFollowerClicked() {
    QString followerName = gulFollowerNetUser->selectedItems().first()->text();
    QString followedName      = gulFollowerSelUser->selectedItems().first()->text();
    int netPos           = gulFollowerNet->currentRow();
    
    controller->addFollower(followerName, followedName, netPos);
    
    showFollower();
    showFollowed();
    
    btnAddFollower->setEnabled(false);
    btnRemoveFollowed->setEnabled(false);
}

void NetworkManager::showFollower() {
    int netPos           = gulFollowerNet->currentRow(); 
    QStringList follower = controller->getFollower(netPos,gulFollowerNetUser->selectedItems().first()->text());
    
    gulFollower->clear();

    foreach (auto strUser, follower) {
        gulFollower->addItem(strUser);
    }
}

void NetworkManager::showFollowed() {
    int netPos           = gulFollowerNet->currentRow(); 
    QStringList followed = controller->getFollowed(netPos,gulFollowerNetUser->selectedItems().first()->text());
    
    gulFollowed->clear();

    foreach (auto strUser, followed) {
        gulFollowed->addItem(strUser);
    }
}

void NetworkManager::userFollowedClicked() {
    btnAddFollower->setEnabled(false);
    btnRemoveFollowed->setEnabled(true);
}

void NetworkManager::removeFollowerClicked() {
    QString followerName = gulFollowerNetUser->selectedItems().first()->text();
    QString followedName      = gulFollowed->selectedItems().first()->text();
    int netPos           = gulFollowerNet->currentRow();

    controller->removeFollowed(followerName, followedName, netPos);

    showFollower();
    showFollowed();
    
    btnAddFollower->setEnabled(false);
    btnRemoveFollowed->setEnabled(false);
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
