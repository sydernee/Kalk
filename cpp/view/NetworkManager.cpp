#include "NetworkManager.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSpacerItem>
#include <QErrorMessage>
//#include "../controller/NetworkController.h" TODO

//TODO : rimuovo le ridondanze, e.g.     QListWidget* gul1InsRemViewUser = new QListWidget();    QListWidget* gul2InsRemViewUser = new QListWidget();

NetworkManager::NetworkManager(QWidget *parent)
    : QWidget(parent),
      backButton(new QPushButton("Torna indietro", this))
//    controller(nullptr) TODO
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
    QGroupBox* createUserGroupBox = new QGroupBox(tr("Creazione degli utenti")); 
    QHBoxLayout* createUserGroup = new QHBoxLayout();
    QListWidget* gulCreateUser = new QListWidget();

    QGridLayout *userData = new QGridLayout;
    QLabel* lblUsername = new QLabel(tr("Username"));
    QLineEdit* edtUsername = new QLineEdit;
    QLabel* lblName = new QLabel(tr("Name"));
    QLineEdit* edtName = new QLineEdit;
    QLabel* lblSurname = new QLabel(tr("Surname"));
    QLineEdit* edtSurname = new QLineEdit;

    // form con i dati dell'utente (da inserire/modificare)
    userData->addWidget(lblUsername,0,0);
    userData->addWidget(edtUsername,1,0);
    userData->addWidget(lblName,2,0);
    userData->addWidget(edtName,3,0);
    userData->addWidget(lblSurname,4,0);
    userData->addWidget(edtSurname,5,0);
    
    // bottoni del layout createUser
    QVBoxLayout* createUserBottonGroup = new QVBoxLayout();
    QPushButton* btnAddUser = new QPushButton(tr("Aggiungi un nuovo utente"));
    QPushButton* btnModifyUser = new QPushButton(tr("Modifica l'utente selezionato"));
    QPushButton* btnRemoveUser = new QPushButton(tr("Rimuovi l'utente selezionato"));

    createUserBottonGroup->addWidget(btnAddUser);
    createUserBottonGroup->addWidget(btnModifyUser);
    createUserBottonGroup->addWidget(btnRemoveUser);

    createUserGroup->addWidget(gulCreateUser);
    createUserGroup->addLayout(userData);
    createUserGroup->addLayout(createUserBottonGroup);

    createUserGroupBox->setLayout(createUserGroup);

     createUserGroupBox->setStyleSheet(groupBoxStyle);
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

    //2 - Inserimento, rimozione e visualizzazione di un utente in una rete
    QGroupBox* insRemViewUserGroupBox = new QGroupBox(tr("Inserimento, rimozione e visualizzazione di un utente in una rete"));
    QVBoxLayout* insRemViewUserList0Layout = new QVBoxLayout();
    QVBoxLayout* insRemViewUserList1Layout = new QVBoxLayout();
    QVBoxLayout* insRemViewUserList2Layout = new QVBoxLayout();
    QVBoxLayout* insRemViewUserButtonGroup = new QVBoxLayout();
    
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

    QHBoxLayout* insRemViewUserGroup = new QHBoxLayout();
    insRemViewUserGroup->addLayout(insRemViewUserList0Layout);
    insRemViewUserGroup->addLayout(insRemViewUserList1Layout);
    insRemViewUserGroup->addLayout(insRemViewUserList2Layout);
    insRemViewUserGroup->addLayout(insRemViewUserButtonGroup);
    
    insRemViewUserGroupBox->setLayout(insRemViewUserGroup);
    insRemViewUserGroupBox->setStyleSheet(groupBoxStyle);

    //3 - Following e Follower
    QGroupBox* followerGroupBox = new QGroupBox(tr("Inserimento, rimozione e visualizzazione di un utente in una rete"));
    QVBoxLayout* gulFollowerNetLayout = new QVBoxLayout();
    QVBoxLayout* gulFollowerLayout = new QVBoxLayout();
    QVBoxLayout* gulFollowerOutputLayout = new QVBoxLayout();
    QVBoxLayout* gulFollowerButtonGroup = new QVBoxLayout();
    
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

    QHBoxLayout* followerGroup = new QHBoxLayout();
    followerGroup->addLayout(gulFollowerNetLayout);
    followerGroup->addLayout(gulFollowerLayout);
    followerGroup->addLayout(gulFollowerOutputLayout);
    followerGroup->addLayout(gulFollowerButtonGroup);
    
    followerGroupBox->setLayout(followerGroup);
    followerGroupBox->setStyleSheet(groupBoxStyle);

    //4-

    QGroupBox* netOpGroupBox = new QGroupBox(tr("Operazioni tra matrici"));
    QVBoxLayout* netOpList0Layout = new QVBoxLayout();
    QVBoxLayout* netOpList1Layout = new QVBoxLayout();
    QVBoxLayout* netOpOutputLayout = new QVBoxLayout();
    QVBoxLayout* netOpButtonGroup = new QVBoxLayout();
    
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

    QHBoxLayout* netOpGroup = new QHBoxLayout();
    netOpGroup->addLayout(netOpList0Layout);
    netOpGroup->addLayout(netOpList1Layout);
    netOpGroup->addLayout(netOpOutputLayout);
    netOpGroup->addLayout(netOpButtonGroup);
    
    netOpGroupBox->setLayout(netOpGroup);
    netOpGroupBox->setStyleSheet(groupBoxStyle);

    // set layout
    QVBoxLayout *layout = new QVBoxLayout();
    
    layout->addLayout(backButtonGroup);
    layout->addWidget(createUserGroupBox);
    layout->addWidget(insRemViewUserGroupBox);
    layout->addWidget(followerGroupBox);
    layout->addWidget(netOpGroupBox);

    setLayout(layout);


    connect(backButton, SIGNAL(clicked()), this, SLOT(handleBackButton()));
}


void NetworkManager::handleBackButton() {
    emit networkManagerCloseSignal();
    close();
}

NetworkManager::~NetworkManager() {   
// if (controller != nullptr)
  //      delete controller; TODO

}
