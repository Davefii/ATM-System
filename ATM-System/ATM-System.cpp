#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
const string FileClient = "Clients.txt";
const sClient CurrentClient;
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};
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
bool CheckExistClient(string AccountNumber, sClient Client)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(FileClient);
    for (sClient c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            c.AccountNumber = AccountNumber;
            return true;
        }
    }
    return false;
}
void MainMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menu\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
}
void Login()
{
    sClient Client;
    string accountNumber, PinCode;
    do
    {

    } while (CheckExistClient(accountNumber, Client));
}
int main()
{

    return 0;
}