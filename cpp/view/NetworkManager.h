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
    QGroupBox* InsRemUserGroupBox;
    QVBoxLayout* InsRemUserList0Layout;
    QVBoxLayout* InsRemUserList1Layout;
    QVBoxLayout* InsRemUserList2Layout;
    QVBoxLayout* InsRemUserButtonGroup;
    
    QLabel* netInsRemUserLabel;
    QListWidget* netInsRemUser;
    QLabel* netUserInsRemUserLabel;
    QListWidget* netUserInsRemUser;
    QLabel* gulInsRemUserLabel;
    QListWidget* gulInsRemUser;
    
    QPushButton* btnIRAddUser;
    QPushButton* btnIRRemoveUser;

    QHBoxLayout* InsRemUserGroup;
    
    //3 - Following e Follower
    QGroupBox* followerGroupBox;
    QVBoxLayout* gulFollowerNetLayout;
    QVBoxLayout* gulFollowerNetUserLayout;
    QVBoxLayout* gulFollowerLayout;
    QVBoxLayout* gulFollowedLayout;
    QVBoxLayout* gulFollowerSelUserLayout;
    QVBoxLayout* gulFollowerButtonGroup;
    
 
    QLabel* gulFollowerNetLabel;
    QListWidget* gulFollowerNet;
    QLabel* gulFollowerNetUserLabel;
    QListWidget* gulFollowerNetUser;
    QLabel* gulFollowerLabel;
    QListWidget* gulFollower;
    QLabel* gulFollowedLabel;
    QListWidget* gulFollowed;
    QLabel* gulFollowerSelUserLabel;
    QListWidget* gulFollowerSelUser;

    QPushButton* btnAddFollower;
    QPushButton* btnRemoveFollowed;

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

protected:
    int getSelectedRow(QListWidget*); //data una QListWidget*, ritorna la posizione del suo primo elemento

public:
    explicit NetworkManager(QWidget *parent = nullptr);
    ~NetworkManager();

signals:
    void networkManagerCloseSignal();

private slots:
    void handleBackButton();
    
protected slots:
    virtual void setInsRemButtonStatus();
    virtual void setOperationNetButtonStatus();
    virtual void disableButtons(); // disabilito i bottoni dei box >= 2 
    
public slots:
    virtual void createGlobalUserClicked();
    virtual void showGlobalUserData(QListWidgetItem*);
    virtual void modifyGlobalUserDataClicked();
    virtual void deleteGlobalUserClicked();
    virtual void resetGlobalUserData(); 
    
    virtual void createNetClicked();
    virtual void modifyNetNameClicked(); 
    virtual void showNetName(QListWidgetItem*);
    virtual void deleteNetClicked();          
    virtual void resetNetData();        
    
    virtual void addUserToNetwork();
    virtual void showNetworkUser();
    
    virtual void selectedUserNetwork();
    virtual void deleteUserFromNetworkClicked();
    
    virtual void calculateUnion();
    virtual void calculateIntersection();    
    virtual void calculateRelativeComplement();    
    virtual void calculateSymmetricDifference();    
    
    virtual void showFollowerNetworks();
    
    virtual void setNewFollowerButtonStatus();
    
    virtual void addFollowerClicked();
    
    virtual void showFollower();
    virtual void showFollowed();
    
    virtual void userFollowedClicked();
    
    virtual void removeFollowerClicked();
    
};
#endif //NETWORKMANAGER_H
