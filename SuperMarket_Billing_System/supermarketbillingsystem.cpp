/*THE CODE IS SELF EXPLANATORY HOWEVER COMMENTS
ARE USED WHERE EVER THEY ARE REQUIRED
DEFAULT PASS: 12345
*/
#include <bits/stdc++.h>

using namespace std;

class product
{
private:
    int productNo;
    char productName[50];
    float rate, discount, tax;

public:
    product()
    {
        productNo = 0;
        productName[50] = 0;
        rate = 0;
        discount = 0;
        tax = 0;
    }

    void creatProduct()
    {
        cout << "Enter Product No\n";
        cin >> productNo;
        cout << "Enter Product Name\n";
        cin.ignore();
        cin.getline(productName, 50);
        cout << "Enter Product Cost\n";
        cin >> rate;
        cout << "Enter Discount Offered\n";
        cin >> discount;
        cout << "Enter Tax\n";
        cin >> tax;
    }

    void showProduct()
    {
        cout << "\t\t\t" << productNo
             << "\t\t" << productName
             << "\t\t" << discount
             << "\t\t" << tax
             << "\t\t" << rate + (rate * getTax() / 100) << "\n";
    }

    int getProductNo()
    {
        return productNo;
    }

    float getRate()
    {
        return rate;
    }

    char *getProductName()
    {
        return productName;
    }

    float getDiscount()
    {
        return discount;
    }

    float getTax()
    {
        return tax;
    }
};

fstream file;
product p;

void doTaskAgain(string question, void (*f)(void))  //FUNCTION TO REPEAT A CERTAIN TASK AGAIN
{
    cout << question;
    char choice;
    cin >> choice;
    cout << "\n";
    if (choice == 'Y' || choice == 'y')
        f();
}

void addProduct()
{
    system("cls");
    char option;
    file.open("ShopInventory.dat", ios::out | ios::app);
    p.creatProduct();
    file.write((char *)&p, sizeof(product));
    file.close();
    cout << "\n\n\t\t\t\t\t\tPRODUCT ADDED SUCCESSFULLY\n";
    doTaskAgain("\t\t\t\t\t\tDO YOU WANT TO ADD ANOTHER PRODUCT?(Y/N): ", addProduct);
}

void deleteProduct()
{
    system("cls");
    int num;
    cout << "Enter Product No: ";
    cin >> num;
    file.open("ShopInventory.dat", ios::in | ios::out);
    fstream file2;
    file2.open("temp.dat", ios::out);
    file.seekg(0, ios::beg);
    while (file.read((char *)&p, sizeof(product)))
    {
        if (p.getProductNo() == num)
        {
            cout << "\n\t\t\tPr No.\t\tPr Name\t\tDiscount\tTax\t\tRate\n";
            cout << "\t-----------------------------------------------------------------------------------------------------\n";
            p.showProduct();
            cout << "\t-----------------------------------------------------------------------------------------------------\n";
        }
        if (p.getProductNo() != num)
        {
            file2.write((char *)&p, sizeof(product));
        }
    }
    file2.close();
    file.close();
    remove("ShopInventory.dat");
    rename("temp.dat", "ShopInventory.dat");
    cout << "\n\t\t\t\t\t\tRECORD DELETED!!";
    doTaskAgain("\n\t\t\t\t\t\tDO YOU WANT TO DELETE ANOTHER PRODUCT?(Y/N): ", deleteProduct);
}

void updateProduct()
{
    system("cls");
    bool found = false;
    int num;
    cout << "Enter the Product No \n";
    cin >> num;

    file.open("ShopInventory.dat", ios::in | ios::out);

    while (file.read((char *)&p, sizeof(product)) && found == false)
    {
        if (p.getProductNo() == num)
        {
            cout << "\n\t\t\tPr No.\t\tPr Name\t\tDiscount\tTax\t\tRate\n";
            cout << "\t-----------------------------------------------------------------------------------------------------\n";
            p.showProduct();
            cout << "\t-----------------------------------------------------------------------------------------------------\n";
            cout << "\n\n\n\t\t\t\t\t\tENTER NEW DETAILS\n\n\n";
            p.creatProduct();
            int pos = -1 * sizeof(product);
            file.seekp(pos, ios::cur);
            file.write((char *)&p, sizeof(product));
            cout << "\t\t\t\t\t\tRECORD UPDATED SUCCESSFULLY\n\n";
            found = true;
        }
    }
    file.close();

    if (found == false)
    {
        cout << "\t\t\t\t\t\tPRODUCT NOT FOUND!!\n";
    }
    doTaskAgain("\t\t\t\t\t\tDO YOU WANT TO UPDATE ANOTHER PRODUCT?(Y/N):", updateProduct);
}

void displaySpecificRecord()
{
    system("cls");
    bool found = false;
    int value;
    cout << "Enter Product No\n";
    cin >> value;
    file.open("ShopInventory.dat", ios::in);
    cout << "Displaying Record Of Product #: " << value << "\n\n";
    cout << "\n\t\t\tPr No.\t\tPr Name\t\tDiscount\tTax\t\tRate\n";
    cout << "\t\t---------------------------------------------------------------------------------------\n";
    while (file.read((char *)&p, sizeof(product)))
    {
        if (p.getProductNo() == value)
        {
            found = true;
            p.showProduct();
            cout << "\t\t---------------------------------------------------------------------------------------";
            cout << "\n";
        }
    }
    file.close();
    if (found == false)
    {
        cout << "\t\t\t\t\t\tPRODUCT NOT FOUND!!\n";
    }
    doTaskAgain("\t\t\t\t\t\tDO YOU WANT TO SEARCH AGAIN?(Y/N): ", displaySpecificRecord);
}

void displayData()
{
    system("cls");
    file.open("ShopInventory.dat", ios::in);
    cout << "\t\t\t\t\t\t**************************\n";
    cout << "\t\t\t\t\t\t\tINVENTORY\n";
    cout << "\t\t\t\t\t\t**************************\n";
    cout << "\n\t\t\tPr No.\t\tPr Name\t\tDiscount\tTax\t\tRate\n";
    cout << "\t\t---------------------------------------------------------------------------------------\n";
    while (file.read((char *)&p, sizeof(product)))
    {
        p.showProduct();
        cout << "\t\t---------------------------------------------------------------------------------------";
        cout << "\n";
    }
    cout << "\n\n";
    file.close();
}

void productList()  //DISPLAY A LIST OF AVAILABLE PRODUCTS TO THE CUSTOMER
{
    cout << "\t\t\t\t\t\t\t    Available Products\n\n";
    cout << "\t\t\t\t*************************************************************************\n";
    cout << "\t\t\t\t\tPr. #\t\tP.Name\t\tRate\t\tDiscount\n";
    cout << "\t\t\t\t-------------------------------------------------------------------------\n";
    file.open("ShopInventory.dat", ios::in);

    while (file.read((char *)&p, sizeof(product)))
    {
        cout << "\t\t\t\t\t" << p.getProductNo() << "\t\t" << p.getProductName() << "\t\t" << p.getRate()
             << "\t\t" << p.getDiscount() << "\n";
        cout << "\t\t\t\t-------------------------------------------------------------------------\n";
    }
    file.close();
}

void currentTime()  //GETS CURRENT TIME OF SYSTEM
{
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    cout << local_time->tm_hour << ":"
         << local_time->tm_min << ":"
         << local_time->tm_sec << "\n";
}

void orderPlacement()
{
    system("cls");
    vector<int> order;
    vector<int> quant;
    int ordVal, quaVal, c = 0, inc = 0;
    float amount, disamt, total = 0;
    long long billNo = 134463;
    char ch;
    productList();
    cout << "\n\t\t\t\t\t\t\t\tPLACE AN ORDER\n";
    do
    {
        cout << "Enter Product No. \n";
        cin >> ordVal;
        order.push_back(ordVal);
        cout << "Enter quantity\n";
        cin >> quaVal;
        quant.push_back(quaVal);
        c++;
        cout << "\t\t\t\t\t\tDO YOU WANT TO ORDER MORE: ";
        cin >> ch;
        inc++;
    } while (ch == 'y' || ch == 'Y');
    cout << "\n\n";
    cout << "\t\t\t\t\t****************************************\n";
    cout << "\t\t\t\t\t\t\tINVOICE\n";
    cout << "\t\t\t\t\t****************************************\n\n";
    cout << "\tBill No. : " << billNo + inc << "\t\t\t\t\t\t\t\tTime: ";
    currentTime();
    cout << "\n";
    cout << "\t-----------------------------------------------------------------------------------------------------\n";
    cout << "\t\tPr No.\t\tPr Name\t\tRate\tQuantity\tDiscount\t\tAMOUNT\n";
    cout << "\t-----------------------------------------------------------------------------------------------------";
    for (int x = 0; x <= c; x++)
    {
        file.open("ShopInventory.dat", ios::in);
        file.read((char *)&p, sizeof(product));
        while (!file.eof())
        {
            if (p.getProductNo() == order[x])
            {
                amount = p.getRate() * quant[x];
                disamt = amount - (amount * p.getDiscount() / 100);
                cout << "\n\t\t"
                     << order[x] << "\t\t" << p.getProductName() << "\t\t" << p.getRate()
                     << "\t" << quant[x] << "\t\t"
                     << p.getDiscount() << "\t\t\t" << disamt;
                cout << "\n\t-----------------------------------------------------------------------------------------------------";
                total += disamt;
            }
            file.read((char *)&p, sizeof(product));
        }
        file.close();
    }
    cout << "\n\n\t\t\t\t\t\t\t\t\t\t\tTOTAL = " << total << "\n\n";
}

void changePass() //CHANGE ADMIN MENU ACCESS PASSWORD
{
    system("cls");
    string oldPass, newPass, defaultPass;
    cout << "\t\t\t\t\tENTER OLD PASSWORD\n";
    cin >> oldPass;
    ifstream inf;
    inf.open("PASSWORD.txt");
    getline(inf, defaultPass);
    if (oldPass == defaultPass)
    {
        cout << "\n\n\t\t\t\t\tPASSWORD SHOULD NOT INCLUDE SPACES";
        cout << "\n\n\t\t\t\t\tENTER NEW PASSWORD\n\n";
        cin >> newPass;
        if (newPass == oldPass)
        {
            cout << "\t\t\t\t\tNEW PASSWORD CANNOT BE SAME AS OLD PASSWORD\n\n";
            cout << "\t\t\t\t\tRETURNING BACK TO ADMIN MENU\n\n";
            return;
        }
        ofstream temp("temp.txt");
        temp << newPass;
        temp.close();
        inf.close();
        remove("PASSWORD.txt");
        rename("temp.txt", "PASSWORD.txt");
        cout << "\t\t\t\t\tPASSWORD CHANGED SUCCESSFULLY\n\n";
        return;
    }
    else
    {
        cout << "\t\t\t\t\tWRONG PASSWORD\n\n";
        doTaskAgain("\t\t\t\t\tTRY AGAIN?(Y/N):", changePass);
    }
}

void intro() //BASIC DETAILS ABOUT THE CODER (CALLED AT THE END OF PROGRAM)
{
    system("cls");
    cout << "\t\t\t\t---------------------------------------------------------\n";
    cout << "\t\t\t\t| CREATED BY : AVI SHARMA\t\t\t        |\n";
    cout << "\t\t\t\t| COURSE : BACHELOR OF TECHNOLOGY\t\t\t|\n";
    cout << "\t\t\t\t| BRANCH : COMPUTER SCIENCE AND ENGINEERING\t\t|\n";
    cout << "\t\t\t\t| UNIVERSITY : GRAPHIC ERA (DEEMED TO BE) UNIVERSITY\t|\n";
    cout << "\t\t\t\t|\t       DHERADUN\t\t\t\t\t|\n";
    cout << "\t\t\t\t---------------------------------------------------------\n\n\n";
}

void adminMenu()
{
    system("cls");
    int option;
    do
    {
        cout << "\t\t\t\t\t**************************\n";
        cout << "\t\t\t\t\t\tADMIN MENU\n";
        cout << "\t\t\t\t\t**************************\n";
        cout << "\t\t\t\t\t1. Add Product\n"
             << "\t\t\t\t\t2. Update Product\n\t\t\t\t\t3. Search by Product No\n"
             << "\t\t\t\t\t4. Display Inventory\n\t\t\t\t\t5. Delete Product\n"
             << "\t\t\t\t\t6. Change Password\n\t\t\t\t\t7. Back TO Main Menu\n\t\t\t\t\t8. Exit\n\n\n";

        cin >> option;

        switch (option)
        {
        case 1:
            addProduct();
            break;
        case 2:
            updateProduct();
            break;
        case 3:
            displaySpecificRecord();
            break;
        case 4:
            displayData();
            break;
        case 5:
            deleteProduct();
            break;
        case 6:
            system("cls");
            changePass();
            break;
        case 7:
            system("cls");
            break;
        case 8:
            system("cls");
            intro();
            exit(0);
            break;
        default:
            system("cls");
            adminMenu();
        }
    } while (option != 7);
}

void adminLogin() //ASK FOR PASSWORD BEFORE DISPLAYING ADMIN MENU
{
    system("cls");
    string defaultPass = "12345", inputPass;
    ifstream inf("PASSWORD.txt");
    inf >> defaultPass;
    inf.close();
    cout << "\t\t\t\t\tENTER PASSWORD TO ACCESS ADMIN MENU\n\n";
    cin >> inputPass;
    if (inputPass == defaultPass)
    {
        system("cls");
        adminMenu();
    }
    else
    {
        cout << "\t\t\t\t\tWRONG PASSWORD\n";
        cout << "\t\t\t\t\tRETURNING TO MAIN MENU\n\n";
        return;
    }
}

void mainMenu()
{
    system("cls");
    cout << "\t\t\t\t----------------------------------------------\n";
    cout << "\t\t\t\t|  Super Market Billing Calculation Project  |\n";
    cout << "\t\t\t\t----------------------------------------------\n\n\n";
    int choice, val;

    do
    {

        cout << "\t\t\t\t\t**************************\n";
        cout << "\t\t\t\t\t\tMAIN MENU\n";
        cout << "\t\t\t\t\t**************************\n";
        cout << "\t\t\t\t\t1. Customer\n\t\t\t\t\t2. Admin\n\t\t\t\t\tPress 0 to Exit\n\n";
        cin >> choice;
        switch (choice)
        {
        case 0:
            intro();
            break;

        case 1:
            orderPlacement();
            break;

        case 2:
            adminLogin();
            break;

        default:
            cout << "INVALID INPUT\n\n";
            break;
        }
    } while (choice != 0);
}

int main() //DRIVER CODE
{
    system("cls");
    system("color 01");
    mainMenu();
}