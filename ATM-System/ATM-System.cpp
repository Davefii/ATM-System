#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
const string FileClient = "Clients.txt";
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    bool MarkForDelete = false;
    double AccountBalance;
};
sClient CurrentClient;
void MainMenu();
enum enMainMenuOption { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eShowBalance = 4, eLogout = 5 };
enum enquickwithdraw { Twenty = 1, Fiveteen = 2, oneHundernd = 3, FiveHundernd = 4, FourHundernd = 5, sixHundernd = 6, eightHundernd = 7, onethousen = 8, Backmainmenu = 9 };
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    size_t pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length()); /* erase() until
        positon and move to next word. */
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);
    return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
vector <sClient> SaveClientDataFromFile(string FileName, vector <sClient> vClients)
{
    fstream bankfile;
    string DataLine;
    bankfile.open(FileName, ios::out);
    if (bankfile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                bankfile << DataLine << endl;
            }
        }
        bankfile.close();
    }
    return vClients;
}
void PerformenceNormalWithdram();
void ShowQuickWithdraw();
void Login();
void ShowBalance()
{
    cout << "\n--------------------------------------------\n";
    cout << "\tBalance Screen";
    cout << "\n--------------------------------------------\n";
    cout << CurrentClient.Name << " Your Balance is : " << CurrentClient.AccountBalance << endl;
}
void GotoBackMainMenue()
{
    cout << "Press Any Key Go To Back Main Menu..." << endl;
    system("pause>0");
    MainMenu();
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double amount, vector <sClient>& vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += amount;
                SaveClientDataFromFile(FileClient, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
}
double ReadDepositAmount()
{
    double amount;
    cout << "\nEnter a Positive Deposit Amount ?";
    cin >> amount;
    while (amount <= 0)
    {
        cout << "\nEnter a Positive Deposit Amount ?";
        cin >> amount;
    }
    return amount;
}
void PerfromDepositOption()
{
    double DepositAmount = ReadDepositAmount();
    vector <sClient> vClients = LoadCleintsDataFromFile(FileClient);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);
    CurrentClient.AccountBalance += DepositAmount;
}
void ShowDeposit()
{
    cout << "\n--------------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n--------------------------------------------\n";
    PerfromDepositOption();
}
int ReadWithDraw()
{
    int amount;
    cout << "\nEnter an Amount multiple of 5's :\n";
    cin >> amount;
    while (amount % 5 != 0)
    {
        cout << "\nEnter an Amount multiple of 5's :\n";
        cin >> amount;
    }
    return amount;
}
void ShowNormalWithDram()
{
    system("cls");
    cout << "\n--------------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n--------------------------------------------\n";
    PerformenceNormalWithdram();
    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
}
void PerformenceNormalWithdram()
{
    double amount = ReadWithDraw();
    if (amount > CurrentClient.AccountBalance)
    {
        system("cls");
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Any key to continue...";
        system("pause>0");
        ShowNormalWithDram();
        return;
    }
    vector <sClient> vClients;
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, amount * -1, vClients);
    CurrentClient.AccountBalance += amount;
}
short readChoise()
{
    short choise;
    cout << "Choose What Do You Want : " << endl;
    cin >> choise;
    return choise;
}
short getQuickWithDrawAmount(short QuickWithDrawOption)
{
    switch (QuickWithDrawOption)
    {
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
void PerfromQuickWithdrawOption(short QuickWithdrawOption)
{
    if (QuickWithdrawOption == 9)
        return;
    short WithDrawBalance = getQuickWithDrawAmount(QuickWithdrawOption);
    if (WithDrawBalance > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Any key to continue...";
        system("pause>0");
        ShowQuickWithdraw();
        return;
    }
    vector <sClient> vClients = LoadCleintsDataFromFile(FileClient);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= WithDrawBalance;
}
void ShowQuickWithdraw()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(FileClient);
    cout << "===========================================\n";
    cout << "\tQuick Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1] 20." << setw(10) << "\t[2] 50." << endl;
    cout << "\t[3] 100." << setw(10) << "\t[4] 500." << endl;
    cout << "\t[5] 400.\n" << setw(10) << "\t[6] 600." << endl;
    cout << "\t[7] 800.\n" << setw(10) << "\t[8] 1000." << endl;
    cout << "\t[9] Back To Main Menu\n";
    cout << "===========================================\n";
    cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
    PerfromQuickWithdrawOption((enquickwithdraw)readChoise());
}
short ReadOptionMenu()
{
    short select = 0;
    cout << "Choose What Do You Want 1 to 5 :" << endl;
    cin >> select;
    return select;
}
void PerformenceMainMenu(enMainMenuOption MainMenuOption)
{
    switch (MainMenuOption)
    {
    case eQuickWithdraw:
        system("cls");
        ShowQuickWithdraw();
        GotoBackMainMenue();
    case eNormalWithdraw:
        system("cls");
        ShowNormalWithDram();
        GotoBackMainMenue();
        break;
    case eDeposit:
        system("cls");
        ShowDeposit();
        GotoBackMainMenue();
        break;
    case eShowBalance:
        system("cls");
        ShowBalance();
        GotoBackMainMenue();
        break;
    case eLogout:
        Login();
        break;
    default:
        break;
    }
}
bool CheckExistClient(const string& AccountNumber, const string& pincode, sClient& Client)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(FileClient);
    for (sClient c : vClients)
    {
        if (c.AccountNumber == AccountNumber && c.PinCode == pincode)
        {
            Client = c;
            return true;
        }
    }
    return false;
}
void MainMenu()
{
    system("cls");
    cout << "Welcome : " << CurrentClient.Name << " Nice To Meet You :)" << endl;
    cout << "===========================================\n";
    cout << "\t\tATM Main Menu\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerformenceMainMenu((enMainMenuOption)ReadOptionMenu());
}
void Login()
{
    sClient Client;
    string accountNumber, PinCode;
    bool LoginFailed = false;
    do
    {
        system("cls");
        cout << "\n----------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n----------------------------\n";
        cout << "\nPlease Enter Account Number :\n";
        cin >> accountNumber;
        cout << "\nPlease Enter PinCode :\n";
        cin >> PinCode;
        LoginFailed = !CheckExistClient(accountNumber, PinCode, CurrentClient);
        if (LoginFailed)
        {
            cout << "\nInvalid Account Number or PinCode. Please try again.\n";
            system("pause");
        }
    } while (LoginFailed);
    MainMenu();
}
int main()
{
    Login();
    return 0;
}