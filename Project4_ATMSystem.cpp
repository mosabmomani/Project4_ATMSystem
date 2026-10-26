
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
string filename = "clientdata.txt";
short ReadNumberBetween(short from, short to) {
    short number;
    do {

        cout << "please enter number from " << from << " to " << to << "?";
        cin >> number;
    } while (number < from || number>to);
    return number;
}
int ReadMultiple5Number() {
    int number;
    do {
        cout << "please enter an amount multiple of 5's?";
        cin >> number;
    } while (number % 5 != 0);
    return number;
}
enum enATMmenue { eQuickWithdrow = 1, eNormalWithdrow = 2, eDeposit = 3, eCheckBalance = 4, eLogout };
enum enQuickWethdrow { e20 = 1, e50 = 2, e100 = 3, e200 = 4, e400 = 5, e600 = 6, e800 = 7, e1000 = 8, eExit = 9 };
struct sClientData {
    string accountenumber;
    string pincode;
    string name;
    string phone;
    double accountbalance;
    bool markclient = false;
};
sClientData theclient;
vector<string>SpritLineToRecord(string line, string spreter = "#//#") {
    short pos = 0;
    string word = "";
    vector<string>clientinfo;
    while ((pos = line.find(spreter)) != std::string::npos) {
        word = line.substr(0, pos);
        if (word != "") {
            clientinfo.push_back(word);
        }
        line.erase(0, pos + spreter.length());
    }
    if (line != "") {
        clientinfo.push_back(line);

    }
    return clientinfo;
}
sClientData ConvertLineToRicord(string line, string spreter = "#//#") {
    vector<string>clientrecord = SpritLineToRecord(line);
    sClientData client;
    client.accountenumber = clientrecord[0];
    client.pincode = clientrecord[1];
    client.name = clientrecord[2];
    client.phone = clientrecord[3];
    client.accountbalance = stod(clientrecord[4]);
    return client;
}
vector<sClientData>LoadAllClientDataFromFileToVector() {
    vector<sClientData>allclients;
    sClientData client;
    vector<string>record;
    fstream myfile;
    myfile.open(filename, ios::in);
    if (myfile.is_open()) {
        string line;
        while (getline(myfile, line)) {
            client = ConvertLineToRicord(line);
            allclients.push_back(client);

        }
        myfile.close();
    }
    return allclients;
}
string ConvertCleintRecordToLine(sClientData client, string spreter = "#//#") {
    string line = "";
    line += client.accountenumber + spreter;
    line += client.pincode + spreter;
    line += client.name + spreter;
    line += client.phone + spreter;
    line += to_string(client.accountbalance);
    return line;
}
void LoadClientDataFromVectorToFile(vector<sClientData>allclient) {
    string line;
    fstream myfile;
    myfile.open(filename, ios::out);
    if (myfile.is_open()) {
        for (sClientData& client : allclient) {
            line = ConvertCleintRecordToLine(client);
            myfile << line << endl;
        }
        myfile.close();
    }
}

bool FindClientByAccountNumberAndPincode(vector<sClientData>& clients, string accountnumber, string pincode) {

    for (sClientData& clint : clients) {
        if (clint.accountenumber == accountnumber && clint.pincode==pincode) {
            clint.markclient = true;
            return true;
        }
    }
    return false;
}

void PrintATMMainMenueScreen() {
    cout << "============================================================\n";
    cout << "\t\t\tATM Main Menu Screen\n";
    cout << "============================================================\n";
    cout << "\t\t[1] Quick Withdraw\n";
    cout << "\t\t[2] Normal Withdraw\n";
    cout << "\t\t[3] Deposit\n";
    cout << "\t\t[4] Check Balance\n";
    cout << "\t\t[5] logout" << endl;
    cout << "============================================================\n";
}
void PrintQuickWethdtowscreen() {
    cout << "============================================================\n";
    cout << "\t\t\tQuick Withdraw\n";
    cout << "============================================================\n";
    cout << "\t\t[1]20\t\t[2]50\n";
    cout << "\t\t[3]100\t\t[4]200\n";
    cout << "\t\t[5]400\t\t[6]600\n";
    cout << "\t\t[7]800\t\t[8]1000\n";
    cout << "\t\t[9]Exit\n";
    cout << "============================================================" << endl;

}
int AccountBalance(string accountnumber) {
    vector<sClientData>vclint = LoadAllClientDataFromFileToVector();
    for (sClientData& client : vclint) {
        if (client.accountenumber == accountnumber) {
            return client.accountbalance;

        }

    }
    return 0;
}
void NewBalance(string accountnumber, double transction) {
    vector<sClientData>vclint = LoadAllClientDataFromFileToVector();
    char m;
    cout << "Are you sure you want to do that transition ?";
    cin >> m;
    if (m == 'y' || m == 'Y') {
        for (sClientData& client : vclint) {
            if (client.accountenumber == accountnumber) {
                client.accountbalance += transction;
                cout << "the new balance is   " << client.accountbalance;
                LoadClientDataFromVectorToFile(vclint);
                break;
            }

        }
    }
}
void PrintDepositScreen() {
    cout << "============================================================\n";
    cout << "\t\t\Deposit Screen\n";
    cout << "============================================================\n";
}
void Deposit() {
    system("cls");
    PrintDepositScreen();
    double Diposet;
    cout << "Enter a positive deposit amount?";
    Diposet = ReadNumberBetween(0, 10000);
    NewBalance(theclient.accountenumber, Diposet);
}
void PrintNormalWethdrowScreen() {
    cout << "============================================================\n";
    cout << "\t\t\tNormal Withdraw Screen\n";
    cout << "============================================================\n";
}
void NormalWithdraw() {
    system("cls");
    PrintNormalWethdrowScreen();
    int balance = AccountBalance(theclient.accountenumber);
    double wethdrow = ReadMultiple5Number();
    while (wethdrow > balance) {
        cout << "the amount exceeds your balance,make anther  choice\npress any key to continue\n";
        system("pause>0");
        wethdrow = ReadMultiple5Number();
    }
    NewBalance(theclient.accountenumber, wethdrow * -1);

}
short QuickWithdrawChoices(short choice) {
    switch (choice) {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;
    default:
        return 0;
    }
}
void QuickWethdtow() {
    system("cls");
    PrintQuickWethdtowscreen();
    int balance = AccountBalance(theclient.accountenumber);
    cout << "your balance is " << balance << endl;
    short choice = ReadNumberBetween(1, 9);
    int Withdraw = QuickWithdrawChoices(choice);
    if(choice==9)
		return;
    while (Withdraw > balance) {
        cout << "the amount exceeds your balance,make anther choice\npress any key to continue\n";
        system("pause>0");
        choice = ReadNumberBetween(1, 9);
        Withdraw = QuickWithdrawChoices(choice);
    }
    NewBalance(theclient.accountenumber, Withdraw * -1);

}
void PrintCheckBalanceScreen() {
    cout << "============================================================\n";
    cout << "\t\t\tCheck Balance Screen\n";
    cout << "============================================================\n";
}
void CheckBalance() {
    system("cls");
    PrintCheckBalanceScreen();
    cout << "your balance is " << AccountBalance(theclient.accountenumber);
}
void ATMMainMenuScreen(sClientData client) {
    short choice;

    do {
        system("cls");
        PrintATMMainMenueScreen();
        choice = ReadNumberBetween(1, 5);
        switch (enATMmenue(choice)) {
        case enATMmenue::eQuickWithdrow: {
            QuickWethdtow();
            break;
        }
        case enATMmenue::eNormalWithdrow: {
            NormalWithdraw();
            break;
        }
        case enATMmenue::eDeposit: {
            Deposit();
            break;
        }
        case enATMmenue::eCheckBalance: {
            CheckBalance();
            break;
        }
        case enATMmenue::eLogout: {
            theclient = sClientData();
            break;

        }

        }
        if (choice != 5) {
            cout << "\npress any key to back to main menu\n";
            system("pause>0");
        }
    } while (choice != 5);

}
sClientData ReadLoginInfo() {
    sClientData clint;
    cout << "please enter accountnumber? ";
    getline(cin >> ws, clint.accountenumber);
    cout << "please enter pincode ? ";
    getline(cin, clint.pincode);
    return clint;
}

void PrintLoginScreen() {
    cout << "============================================================\n";
    cout << "\t\t\tLogin Screen\n";
    cout << "============================================================\n";
}
sClientData LoginScreen() {

    vector<sClientData>allclientdata = LoadAllClientDataFromFileToVector();
    system("cls");
    PrintLoginScreen();
    while (true) {

        theclient = ReadLoginInfo();
        if (!FindClientByAccountNumberAndPincode(allclientdata, theclient.accountenumber, theclient.pincode)) {
            cout << "\ninvalid login info \n";
        }
        else {
            return theclient;
        }
    }

}
void Start() {
    do {
        theclient = LoginScreen();
        ATMMainMenuScreen(theclient);

    } while (true);
}
int main()
{
    Start();
} 
