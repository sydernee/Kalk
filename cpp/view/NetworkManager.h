#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "../controller/NetworkController.h"

#include <QFormLayout>

#include <QWidget>
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
#include <QPushButton>

#include <QVector>
#include <QStringList>


class NetworkController;

class NetworkManager : public QWidget 
{
    Q_OBJECT
private:
    QPushButton* backButton; //pulsante per tornare indietro

    NetworkController* controller;

    //costanti per le dimensioni della finestre
    const int hWindowSize = 1200;
    const int wWindowSize = 1600;
    const int hCreatorWindowSize = 1200;
    const int wCreatorWindowSize = 1600;
    
    //1.1-groupbox creazione utente
    QGroupBox* createUserGroupBox; 
    QHBoxLayout* createUserGroup;
    QListWidget* gulCreateUser;

    QGridLayout *userData;
    QLabel* lblUsername;
    QLineEdit* edtUsername;
    QLabel* lblName;
    QLineEdit* edtName;
    QLabel* lblSurname;
    QLineEdit* edtSurname;
    
    // bottoni del layout createUser
    QVBoxLayout* createUserBottonGroup;
    QPushButton* btnAddUser;
    QPushButton* btnModifyUser;
    QPushButton* btnRemoveUser;
    QPushButton* btnResetUser;

//1.2-groupbox creazione rete
    QGroupBox* createNetGroupBox; 
    QHBoxLayout* createNetGroup;
    QListWidget* gulCreateNet;

    QFormLayout *netData;
    //QLabel* lblNetname;
    QLineEdit* edtNetname;
    
    // bottoni del layout createNet
    QVBoxLayout* createNetBottonGroup;
    QPushButton* btnAddNet;
    QPushButton* btnRenameNet;
    QPushButton* btnRemoveNet;
    QPushButton* btnResetNet;

    //layout per la creazione di reti e user
    QHBoxLayout* createUserNetGroup;

    //2 - Inserimento, rimozione e visualizzazione di un utente in una rete
    QGroupBox* insRemViewUserGroupBox;
    QVBoxLayout* insRemViewUserList0Layout;
    QVBoxLayout* insRemViewUserList1Layout;
    QVBoxLayout* insRemViewUserList2Layout;
    QVBoxLayout* insRemViewUserButtonGroup;
    
    QLabel* netInsRemViewUserLabel;
    QListWidget* netInsRemViewUser;
    QLabel* netUserInsRemViewUserLabel;
    QListWidget* netUserInsRemViewUser;
    QLabel* gulInsRemViewUserLabel;
    QListWidget* gulInsRemViewUser;
    
    QPushButton* btnIRVAddUser;
    QPushButton* btnIRVRemoveUser;
    QPushButton* btnIRVViewProfile;

    QHBoxLayout* insRemViewUserGroup;
    
    //3 - Following e Follower
    QGroupBox* followerGroupBox;
    QVBoxLayout* gulFollowerNetLayout;
    QVBoxLayout* gulFollowerLayout;
    QVBoxLayout* gulFollowerOutputLayout;
    QVBoxLayout* gulFollowerButtonGroup;
    
    QLabel* gulFollowerNetLabel;
    QListWidget* gulFollowerNet;
    QLabel* gulFollowerLabel;
    QListWidget* gulFollower;    
    QLabel* gulFollowerOutputLabel;
    QListWidget* gulFollowerOutput;

    QPushButton* btnGetFollower;
    QPushButton* btnGetFollowed;
    QPushButton* btnAddFollower;
    QPushButton* btnRemoveFollower;

    QHBoxLayout* followerGroup;

    //4-Operazioni tra matrici

    QGroupBox* netOpGroupBox;
    QVBoxLayout* netOpList0Layout;
    QVBoxLayout* netOpList1Layout;
    QVBoxLayout* netOpOutputLayout;
    QVBoxLayout* netOpButtonGroup;
    
    QLabel* gul0netOpLabel;
    QListWidget* gul0netOp;
    QLabel* gul1netOpLabel;
    QListWidget* gul1netOp;
    QLabel* gul2netOpLabel;
    QListWidget* gul2netOp;
 
    QPushButton* btnGetUnion;
    QPushButton* btnGetIntersection;
    QPushButton* btnGetRelativeComplement;
    QPushButton* btnGetSymmetricDifference;

    QHBoxLayout* netOpGroup;

    // set layout
    QVBoxLayout *layout;

public:
    explicit NetworkManager(QWidget *parent = nullptr);
    ~NetworkManager();

signals:
    void networkManagerCloseSignal();

private slots:
    void handleBackButton();
    
public slots:
    void createGlobalUserClicked();
    void showGlobalUserData(QListWidgetItem*);
    void modifyGlobalUserDataClicked();
    void deleteGlobalUserClicked();
    void resetGlobalUserData(); 
    
    void createNetClicked();
    void modifyNetNameClicked(); 
    void showNetName(QListWidgetItem*);
    void deleteNetClicked();          
    void resetNetData();        
    
    void addUserToNetwork();
    void showNetworkUser();
};
#endif //NETWORKMANAGER_H
