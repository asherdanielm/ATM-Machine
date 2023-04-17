#include <iostream>
using namespace std;

//Strucutre of customer information
struct CustomerInfo {
    string customerName;
    string loginID;
    string passWord;
    int numOfAccounts;
    int accountNumber [3];
    float accountBalance [3];
};
//Array of structure
CustomerInfo ATM [20];

//Enrolling Variables
char enrollOption;
bool inService = true;
int numOfEnrolled = 0;

//Login Variables
string loginValid;
string passValid;
string loginName;
bool loginService = true;
void loginDisplay ();

//Main Menu Variable & Prototype
int optionMain;
void mainMenu ();
bool bankinService = true;
//Opening Bank
int activeAccount = 0;
int numOfBanks = 0;
//Checking Balance Variable
int accountIndex = 0;
int inputtedAccountNum = 0;
//Depositing
float depositAmount = 0.00;
//Withdrawing
int withdrawAmount;
//Transferring
int transferAmmount;
int sourceAccountIndex;
int destinationAccountIndex;
int inputtedSAccountNum;
int inputtedDAccountNum;
bool sourceLoop = true;
bool destinationLoop = true;

bool searchForName(CustomerInfo atm[], int size, string name, int j);
bool searchForID (CustomerInfo atm[], int size, string id, int j);
int searchForAccountIndex(CustomerInfo customer);

int main() {
    cout << "Welcome to the Eagles ATM!" << endl;
    //Enrolling first account to Virtual Bank
    cout << "Please enter your first name to enroll to the ATM..."<< endl;
    cin >> ATM[0].customerName;
    cout << "You've successfully enrolled. "<< endl;
    cout << "Please select a login ID..."<< endl;
    cin >> ATM[0].loginID;
    cout << "Please select a password..."<< endl;
    cin >> ATM[0].passWord;
    
    //Enrolling multiple accounts to Virtual Bank
    while (inService == true) {
        if (numOfEnrolled >= 20) {
            cout << "*** Error: the maxium number of enrollments has been reached.***" << endl;
            break;
        }
        cout <<"Would you like to enroll another account? (Y/y or N/n)..." << endl;
        cin >> enrollOption;

        //Input Validation
        while (enrollOption != 'N' && enrollOption != 'n' && enrollOption != 'Y' && enrollOption != 'y') {
            cout << "Invalid input please try again..." << endl;
            cin >> enrollOption;
        }
        //Enrolling additioanl people and cheking to make sure names and logins aren't repeated
        if (enrollOption == 'N' || enrollOption == 'n') {
            inService = false;
        } else if (enrollOption == 'Y' || enrollOption == 'y') {
            numOfEnrolled++;
            string custName;
            //First name validation
            do {
                cout << "Please enter your first name to enroll to the ATM..."<< endl;
                
                cin >> custName;
            } while (searchForName(ATM, 20, custName, numOfEnrolled));
                
            ATM[numOfEnrolled].customerName = custName;
            
            string custid;
            //Login input validation
            do {
                cout << "Please select a login ID..."<< endl;
                cin >> custid;
            } while (searchForID(ATM, 20, custid, numOfEnrolled));
                
            ATM[numOfEnrolled].loginID = custid;
            
            cout << "Please select a password..."<< endl;
            cin >> ATM[numOfEnrolled].passWord;
        }
    }
    cout << "----------------------------------------" << endl;
    
    //Login to Virtual Bank
    loginDisplay ();
    
    //Welcome Screen
    cout <<"Welcome " << loginName << ", to your account!" << endl;

    //Virtual Banking Activities & Operations Loop
    while (bankinService == true) {
        //Displaying Main Menu
        mainMenu();
        cin >> optionMain;
    
        //Input Validation
        while (optionMain <= 1 && optionMain >= 8) {
            cout << "Invalid input please try again..." << endl;
            cin >> optionMain;
        }
        //Main Menu Operation
        switch (optionMain) {
            case 1:
                if (numOfBanks <= 2) {
                    ATM[activeAccount].accountNumber[numOfBanks] = 100 + numOfBanks;
                    cout << "A bank account with account number " << ATM[activeAccount].accountNumber[numOfBanks] << " has been successfully opened." << endl;
                    numOfBanks++;
                } else {
                    cout << "*** Error: you cannot open more than 3 accounts. ***" << endl;
                }
                cout << "----------------------------------------" << endl;
                break;
            case 2:
                //Searching for account
                cout << "Please enter the account number..." << endl;
                cin >> inputtedAccountNum;
                for (int i = 0; i <= 2; i++)
                {
                    if (inputtedAccountNum == ATM[activeAccount].accountNumber[i])
                    {
                        accountIndex = i;
                    }
                }
                //Input validation and dislaying account
                if (inputtedAccountNum == ATM[activeAccount].accountNumber[accountIndex]) {
                    cout << "The balance in the account is $" << ATM[activeAccount].accountBalance[accountIndex] << endl;
                } else if (ATM[activeAccount].accountNumber[accountIndex] == -1){
                    cout << "*** Error: the account has been closed. *** " << endl;
                } else {
                    cout << "*** Error: there is no such an account. *** " << endl;
                }
                cout << "----------------------------------------" << endl;
                break;
            case 3:
                //Searching Array for account
                cout << "Please enter the account number..." << endl;
                cin >> inputtedAccountNum;
                for (int i = 0; i <= 2; i++) {
                    if (inputtedAccountNum == ATM[activeAccount].accountNumber[i])
                    {
                        accountIndex = i;
                    }
                }
                //Input validation for deposit amount to make sure it;s non-negative and account and sufficent funds
                if (inputtedAccountNum == ATM[activeAccount].accountNumber[accountIndex]) {
                    cout << "Please enter the amount of money you like to deposit into the account..." << endl;
                    cin >> depositAmount;
                    while (depositAmount <= 1) {
                        cout << "*** Error: the amount of money should be non-negative. *** " << endl;
                        cout << "Please enter the amount of money you like to deposit into the account..." << endl;
                        cin >> depositAmount;
                    }
                    //Adding deposit amount into account
                    ATM[activeAccount].accountBalance[accountIndex] = depositAmount + 0;
                    cout << "$" << depositAmount << " has been successfully deposited into the account." << endl;
                } else {
                    cout << "*** Error: there is no such an account. *** " << endl;
                }
                cout << "----------------------------------------" << endl;
                break;
        case 4:
                //Search Array for account
                cout << "Please enter the account number..." << endl;
                cin >> inputtedAccountNum;
                for (int i = 0; i <= 2; i++) {
                    if (inputtedAccountNum == ATM[activeAccount].accountNumber[i])
                    {
                        accountIndex = i;
                    }
                }
                //Input Validating that the withdraw amaount isn't a negative number also making sure the account has sufficent funds
                if (inputtedAccountNum == ATM[activeAccount].accountNumber[accountIndex]) {
                    cout << "Please enter the amount of money you like to withdraw..." << endl;
                    cin >> withdrawAmount;
                    while (withdrawAmount > ATM[activeAccount].accountBalance[accountIndex] || withdrawAmount < 0) {
                        //Input Validation for sufficent funds
                        if (withdrawAmount > ATM[activeAccount].accountBalance[accountIndex]){
                            cout << "*** Error: money requested is over drafted *** " << endl;
                            cout << "Please enter the amount of money you like to withdraw..." << endl;
                            cin >> withdrawAmount;
                        //Input Validation for negative number
                        } else if (withdrawAmount < 0) {
                            cout << "*** Error: the amount of money should be nonnegative. *** " << endl;
                            cout << "Please enter the amount of money you like to withdraw..." << endl;
                            cin >> withdrawAmount;
                        }
                    }
                    //Decreasing withdrawl amount from the account & displaying
                    ATM[activeAccount].accountBalance[accountIndex] = ATM[activeAccount].accountBalance[accountIndex] - withdrawAmount;
                    cout << "$" << withdrawAmount << " has been successfully withdrawn from the account." << endl;
                } else {
                    cout << "*** Error: there is no such an account. *** " << endl;
                }
                cout << "----------------------------------------" << endl;
            break;
        case 5:
            //Collecting and validating the source acount entered
            if (numOfBanks > 1){
            while (sourceLoop == true) {
                cout << "Please enter the source account number..." << endl;
                cin >> inputtedSAccountNum;
                    for (int i = 0; i <= 2; i++) {
                        if (inputtedSAccountNum == ATM[activeAccount].accountNumber[i]) {
                            sourceAccountIndex = i;
                            sourceLoop = false;
                        }
                    }
                if (inputtedSAccountNum != ATM[activeAccount].accountNumber[sourceAccountIndex]) {
                    cout <<"*** Error: there is no such an account. ***" << endl;
                }
            }
            //Collecting and validating the source acount entered
            while (destinationLoop == true) {
                cout << "Please enter the destination account number..." << endl;
                cin >> inputtedDAccountNum;
                    for (int i = 0; i <= 2; i++) {
                        if (inputtedDAccountNum == ATM[activeAccount].accountNumber[i]) {
                            destinationAccountIndex = i;
                            destinationLoop = false;
                        }
                    }
                if (inputtedDAccountNum != ATM[activeAccount].accountNumber[destinationAccountIndex]) {
                    cout <<"*** Error: there is no such an account. ***" << endl;
                }
            }
            //Validating trans
            if (inputtedDAccountNum == ATM[activeAccount].accountNumber[destinationAccountIndex] && inputtedSAccountNum == ATM[activeAccount].accountNumber[sourceAccountIndex]) {
                cout << "Please enter the amount of money to be transferred..." << endl;
                cin >> transferAmmount;
                    while (transferAmmount > ATM[activeAccount].accountBalance[sourceAccountIndex] || transferAmmount <=0) {
                        if (transferAmmount > ATM[activeAccount].accountBalance[sourceAccountIndex] ) {
                            cout << "*** Error: money requested is over drafted *** " << endl;
                            cout << "Please enter the amount of money to be transferred..." << endl;
                            cin >> transferAmmount;
                        } else if (transferAmmount <=0) {
                        cout << "*** Error: transfer amount can't be an non-negative.*** " << endl;
                        cout << "Please enter the amount of money to be transferred..." << endl;
                        cin >> transferAmmount;
                        }
                    }
                ATM[activeAccount].accountBalance[sourceAccountIndex] = ATM[activeAccount].accountBalance[sourceAccountIndex] - transferAmmount;
                ATM[activeAccount].accountBalance[destinationAccountIndex] = transferAmmount + ATM[activeAccount].accountBalance[destinationAccountIndex];
                cout << "The $" << transferAmmount << " has been transferred successfully." << endl;
            }
            //Making sure the input validation loop for the soruce and desitnation account works on the next attempt.
                sourceLoop = true;
                destinationLoop = true;
            } else {
                cout << "***Error: only one bank account has been opened.***" << endl;
            }
            cout << "----------------------------------------" << endl;
            break;
        case 6:
            cout << "Please enter the account number..." << endl;
            cin >> inputtedAccountNum;
                for (int i = 0; i <= 2; i++)
                {
                    if (inputtedAccountNum == ATM[activeAccount].accountNumber[i])
                    {
                        accountIndex = i;
                    }
                }
                if (inputtedAccountNum == ATM[activeAccount].accountNumber[accountIndex]) {
                    ATM[activeAccount].accountNumber[accountIndex] = -1;
                    ATM[activeAccount].accountBalance[accountIndex] = 0;
                    cout << "The account has been closed successfully." << endl;
                }
                numOfBanks = numOfBanks - 1;
            cout << "----------------------------------------" << endl;
            break;
        case 7:
                cout << "Thank you " << loginName << " using the ATM machine. You've logged off successfully. Bye!" << endl;
                cout << "----------------------------------------" << endl;
                loginService = true;
                numOfBanks = 0;
                loginDisplay ();
                cout <<"Welcome " << loginName << ", to your account!" << endl;
            break;
        case 8:
                bankinService = false;
            break;
            
        default:
            break;
    }
}
    return 0;
}

//Function for Main Menu
void mainMenu (){
cout << "Select an option from the main menu..." << endl;
cout << "1. Opening a bank account" << endl;
cout << "2. Checking account balance" << endl;
cout << "3. Depoiting into account" << endl;
cout << "4. Withdrawing from account" << endl;
cout << "5. Transferring to an account" << endl;
cout << "6. Closing Account" << endl;
cout << "7. Logging off from ATM" << endl;
cout << "8. Exiting ATM Machine" << endl;
}

//Function for Login Display
void loginDisplay (){
    while (loginService == true) {
        cout << "Please enter your login ID..." << endl;
        cin >> loginValid;
        cout << "Please enter your Password..." << endl;
        cin >> passValid;
        //Checking/Validating login information
        for (int l=0; l <= numOfEnrolled; l++) {
            if (loginValid == ATM[l].loginID && passValid == ATM[l].passWord) {
                loginService = false;
                loginName = ATM[l].customerName;
                activeAccount = l;
            }
        }
        if (loginService == true) {
            cout << "*** Error:login ID or password or both is/are incorrect ***" << endl;
        }
    }
    cout << "----------------------------------------" << endl;
}
bool searchForName (CustomerInfo atm[], int size, string name, int j) {
    for (int i = 0; i < size; i++)
    {
        if (atm[i].customerName == name && i != j)
        {
            cout << "***Error: Unfortunately the name is already taken.***" << endl;
            return true;
        }
    }
    
    return false;
}
bool searchForID (CustomerInfo atm[], int size, string id, int j) {
    for (int i = 0; i < size; i++)
    {
        if (atm[i].loginID == id && i != j)
        {
            cout << "***Error: Unfortunately the login ID is already taken.***" << endl;
            return true;
        }
    }
    
    return false;
}
