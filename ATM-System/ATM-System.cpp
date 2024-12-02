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
enum enMainMenuOption { eQuickWithdraw = 1, eNormalWithdraw = 2,eDeposit = 3, eShowBalance = 4, eLogout = 5 };
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
sClient SaveClientDataFromFile(string FileName, sClient &Client)
{
    fstream bankfile;
    string DataLine;
    bankfile.open(FileName, ios::out || ios::app);
    if (bankfile.is_open())
    {
            if (Client.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(Client);
                bankfile << DataLine << endl;
            }
        bankfile.close();
    }
    return Client;
}
void Login();
void ShowBalance()
{
    cout << "\n--------------------------------------------\n";
    cout << "\Balance Screen";
    cout << "\n--------------------------------------------\n";
    cout << CurrentClient.Name << " Your Balance is : " << CurrentClient.AccountBalance << endl;
}
void GotoBackMainMenue()
{
    cout << "Press Any Key Go To Back Main Menu..." << endl;
    system("pause>0");
    MainMenu();
}
bool DepositAMount(double amount, sClient &Clinet)
{
    char answer = 'n';
    cout << "Do You Want Deposit " << amount << " Y/N : " << endl;
    cin >> answer;
    if (answer == 'y' || answer == 'Y')
    {
        CurrentClient.AccountBalance += amount;
        SaveClientDataFromFile(FileClient, Clinet);
        return true;
    }
    return false;
}
void ShowDeposit()
{
    double amount;
    cout << "\n--------------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n--------------------------------------------\n";
    cout << "Enter How Many Do You Want Deposit : " << endl;
    cin >> amount;
    DepositAMount(amount, CurrentClient);
    cout << CurrentClient.Name << " Your Balance is : " << CurrentClient.AccountBalance << endl;
}
void ShowNormalWithDram()
{
    double amount;
    cout << "\n--------------------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n--------------------------------------------\n";
    cout << "Enter How Many Do You Want Deposit : " << endl;
    cin >> amount;
    DepositAMount(amount * - 1, CurrentClient);
    cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
}
short readChoise()
{
    short choise;
    cout << "Choose What Do You Want : " << endl;
    cin >> choise;
    return choise;
}
void PerfomenceQuickWithdraw(enquickwithdraw quickwithdraw)
{
    double amount = 0;
    switch (quickwithdraw)
    {
    case Twenty:
        amount +=20;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * - 1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case Fiveteen:
        amount += 50;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * -1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case oneHundernd:
        amount += 100;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * -1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case FiveHundernd:
        amount += 500;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * -1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case FourHundernd:
        amount += 400;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * -1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case sixHundernd:
        amount += 600;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * -1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case eightHundernd:
        amount += 800;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * -1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case onethousen:
        amount += 1000;
        if (amount > CurrentClient.AccountBalance)
        {
            cout << "The Amount Exceeds Your Balance, Make Another Choice. " << endl;
        }
        DepositAMount(amount * -1, CurrentClient);
        cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
        break;
    case Backmainmenu:
        GotoBackMainMenue();
    default:
        cout << "Invalid input :(" << endl;
    }
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
    PerfomenceQuickWithdraw((enquickwithdraw)readChoise());
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