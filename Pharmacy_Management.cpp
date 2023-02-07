#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int Add_medi();
int Show_medi();
int Find_medi();
int Display_Roder_medi();

int IDaily_soldMedi();
int Print_bill();

int R_main();
int Date();

int Itno , Qty_stock , ROrd_level ,Sold_Itno ,Qty,Re_no =1 ;
string MDSC1 , MDSC2, MDate , EDate;
float Unit_price ,Total , GTotal;

char OP1;

ofstream Stock_file,DailySal,DailySal_1,DailySal_2,DailyCsv,Csv_File;
ifstream inFile;


int main(){
    cout<<"\n=============================================================\n";
    cout<<"\t ____Pharmacy Management System____ \n";
    cout<<"\n\t\tA - Add new medicine items\n \t\tS - Show full Medicine list\n \t\tF - Find item from list\n \t\tD - Display medicine item to Re-order\n \t\tI - Input medicine items Sold Daily\n \t\tP - Print bill for Medicine items\n \t\tQ - Quit\n";
    cout<<"\n\tSelet Your option(A/S/F/D/I/P)__";
    cin>>OP1;
    OP1 = tolower(OP1);
    cout<<"\n";
    cout<<"\n=============================================================\n";

    switch(OP1){
        case 'a':Add_medi();
        case 's':Show_medi();
        case 'f':Find_medi();
        case 'd':Display_Roder_medi();
        case 'i':IDaily_soldMedi();
        case 'p':Print_bill();
        case 'q':cout<<"\t\t\t----Thanks----\n";exit(0);
        default: cout<<"\n----Select valid Option----\n\n";main();
    }
    
}

int Add_medi(){
    cout<<"\n=========== Add Medicine===========\n";

    char Cnt = 'Y';
    Stock_file.open("StockFile.txt",ios::app);

    while(Cnt == 'Y' || Cnt == 'y'){
        cout<<"\n \t  --Add Medicine--\n";
        cout<<"\nItem no: ";
        cin>>Itno;
        cout<<"Medicine description 1: ";
        cin>>MDSC1;
        cout<<"Medicine description 2: ";
        cin>>MDSC2;
        cout<<"Quntity in stock: ";
        cin>>Qty_stock;
        cout<<"Reorder Level: ";
        cin>>ROrd_level;
        cout<<"Manufacture Date: ";
        cin>>MDate;
        cout<<"Expire Date: ";
        cin>>EDate;
        cout<<"Unit Price: ";
        cin>>Unit_price;

        Stock_file<<Itno<<" "<<MDSC1<<" "<<MDSC2<<" "<<Qty_stock<<" "<<ROrd_level<<" "<<MDate<<" "<<EDate<<" "<<Unit_price<<"\n";

        cout<<"\n\tConntinue(Y/N)_";
        cin>>Cnt;
        cout<<"\n";
    }
    Stock_file.close(); 
    R_main();
    cout<<"\n===================================\n";

}    

int Show_medi(){
    inFile.open("StockFile.txt");
    cout<<"====================================================================================================================\n";
    cout<<"\n\t\t\t\t\t__ABC Pharmacy__\n";
    cout<<"\nItem no \t Description \t Qty Stock \t Reorder Level \t Manufactor Date \t Expire Date \t Unit Price \n\n";
    while(!inFile.eof()){
        inFile>>Itno;
        inFile>>MDSC1;
        inFile>>MDSC2;
        inFile>>Qty_stock;
        inFile>>ROrd_level;
        inFile>>MDate;
        inFile>>EDate;
        inFile>>Unit_price;

        if(Itno == 0){
            cout<<"\t --No records--\n";
            break;
        }
        else if(inFile.eof()){
            break;
        }
        else{
             cout<<Itno<<"\t\t  "<<MDSC1+" "+MDSC2<<"\t\t    "<<Qty_stock<<"\t\t\t"<<ROrd_level<<"\t  "<<MDate<<"\t\t  "<<EDate<<"\t   "<<Unit_price<<"\n";            
        }
    }
    cout<<"\n\t\t\t\t\t\t---End Report---\n";
    cout<<"====================================================================================================================\n";
    inFile.close();
    R_main();

}

int Find_medi(){
    cout<<"\n======== Find medicine List========\n";

    int S_ItemNo;
    inFile.open("StockFile.txt");
    cout<<"Enter Item No: ";
    cin>>S_ItemNo;
    cout<<"\n";
    while(!inFile.eof()){
        inFile>>Itno;
        inFile>>MDSC1;
        inFile>>MDSC2;
        inFile>>Qty_stock;
        inFile>>ROrd_level;
        inFile>>MDate;
        inFile>>EDate;
        inFile>>Unit_price;

        if(S_ItemNo == Itno){
            cout<<"Item no: "<<Itno<<"\n";
            cout<<"Description: "<<MDSC1+" "+MDSC2<<"\n";
            cout<<"Quntity in Stock: "<<Qty_stock<<"\n";
            cout<<"Reorder Level: "<<ROrd_level<<"\n";
            cout<<"Manufacture Date: "<<MDate<<"\n";
            cout<<"Expire Date: "<<EDate<<"\n";
            cout<<"Unit Price: "<<Unit_price<<"\n";            

        }
        
    }
    inFile.close();
    R_main();
    cout<<"\n===================================\n";
}


int Display_Roder_medi(){
    inFile.open("StockFile.txt");
    cout<<"\n\t===============Reorder medicine List===============\n";
    cout<<"Item no \t description \t Qty stock \t reorder level \t Manuf Date \t Expire Date\t Unit price\n";
    cout<<"\n";

    while(!inFile.eof()){
        inFile>>Itno;
        inFile>>MDSC1;
        inFile>>MDSC2;
        inFile>>Qty_stock;
        inFile>>ROrd_level;
        inFile>>MDate;
        inFile>>EDate;
        inFile>>Unit_price;

        if(inFile.eof()){
            inFile.close();
            break;
        }
        else if(Qty_stock<ROrd_level){
            cout<<Itno<<"\t\t   "<<MDSC1<<" "<<MDSC2<<"\t\t"<<Qty_stock<<"\t\t"<<ROrd_level<<"\t "<<MDate<<"\t "<<EDate<<"\t   "<<Unit_price<<"\n";
        }
        
    }
    inFile.close();
    R_main();
    cout<<"\n===================================\n";

}

int IDaily_soldMedi(){
    
    DailySal.open("DailySal.txt");
    DailySal_1.open("DailySales1.txt");
    DailySal_2.open("DailySales2.txt",ios::app);
    DailyCsv.open("DailySales3.csv",ios::app);
    
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *ltm = localtime(&now);
    
    DailySal_1<<"\nresipt no: "<<Re_no<<"\t\t\t\t\t\t\t\t\t\t "<<"Date:"<< ltm->tm_mday <<"/"<< 1 + ltm->tm_mon <<"/"<< 1900 + ltm->tm_year<<"\n";
    DailySal_1<<"Itno \tDesc\t manuf date\t EXP date \t Qsold\t unitprice\t total\n";
        
    DailySal_2<<"\nresipt no: "<<Re_no<<"\t\t\t\t\t\t\t\t\t\t "<<"Date:"<< ltm->tm_mday <<"/"<< 1 + ltm->tm_mon <<"/"<< 1900 + ltm->tm_year<<"\n";
    DailySal_2<<"Itno \tDesc\t manuf date\t EXP date\t Qsold\t unitprice\t total\n";
    
    DailyCsv<<"\nresipt no: "<<Re_no<<"\t\t\t\t\t "<<"Date:"<< ltm->tm_mday <<"/"<< 1 + ltm->tm_mon <<"/"<< 1900 + ltm->tm_year<<"\n";
    DailyCsv<<"itno,desc,qsold,exDate,Mdate,uprice,total \n";
    
    Re_no += 1;
    char Cnt = 'Y';   
    while(Cnt == 'Y'|| Cnt =='y'){
        cout<<"=======Daily Sales=======\n";

        inFile.open("StockFile.txt");
        
        cout<<"Item no: ";
        cin>>Sold_Itno;
        cout<<"Quntity: ";
        cin>>Qty;
        while(!inFile.eof()){
           inFile>>Itno;
           inFile>>MDSC1;
           inFile>>MDSC2;
           inFile>>Qty_stock;
           inFile>>ROrd_level;
           inFile>>MDate;
           inFile>>EDate;
           inFile>>Unit_price;
            if(inFile.eof()){
                inFile.close();
                break;
            }
            else if(Sold_Itno == Itno){
                Total = Unit_price*Qty;
                DailySal<<Itno<<"\t"<<MDSC1<<"\t"<<MDSC2<<"\t"<<MDate<<"\t"<<EDate<<"\t"<<Qty<<"\t\t"<<Unit_price<<"\t "<<Total<<"\n";
                DailySal_1<<Itno<<"\t"<<MDSC1<<"\t"<<MDSC2<<"\t"<<MDate<<"\t"<<EDate<<"\t\t"<<Qty<<"\t\t"<<Unit_price<<"\t "<<Total<<"\n";
                DailySal_2<<Itno<<"\t"<<MDSC1<<"\t"<<MDSC2<<"\t"<<MDate<<"\t"<<EDate<<"\t\t"<<Qty<<"\t\t"<<Unit_price<<"\t "<<Total<<"\n";
                DailyCsv<<Itno<<","<<MDSC1<<","<<MDSC2<<","<<MDate<<","<<EDate<<","<<Qty<<","<<Unit_price<<","<<Total<<"\n";

            }

        }
        
        cout<<"Continue(Y/N)_";
        cin>>Cnt;
        cout<<"\n";
        
    }
    inFile.close();
        DailySal.close();
        DailySal_1.close();         
        DailySal_2.close();
        DailyCsv.close();
    
    R_main();

}

int Print_bill(){
    
    Csv_File.open("DailySalesx.csv");
    Csv_File<<"Itno ,Desc,Qsold,unitprice,total\n";
    inFile.open("DailySal.txt");
    cout<<"\n============================================\n";
    cout<<"|                Welcome                   |\n";
    cout<<"============================================\n";
    cout<<"\n\t   -ABC Pharmacy Bill-\n";
    cout<<"\n";
    Date();
    cout<<"Recipt no: "<<Re_no;
    cout<<"\n";
    cout<<"Item no   Name    Qty   Unit Price      Total\n\n";

    while(!inFile.eof()){
        inFile>>Itno;
        inFile>>MDSC1;
        inFile>>MDSC2;
        inFile>>MDate;
        inFile>>EDate;
        inFile>>Qty;
        inFile>>Unit_price;
        inFile>>Total;

        if(inFile.eof()){
            inFile.close();
            Csv_File.close();
            break;
        }
        else{
            cout<<Itno<<"\t  "<<MDSC1+" "+MDSC2<<"\t  "<<Qty<<"\t   "<<Unit_price<<"\t\t"<<Total<<"\n";
            Csv_File<<Itno<<","<<MDSC1+" "+MDSC2<<","<<Qty<<","<<Unit_price<<","<<Total<<"\n";
            GTotal = GTotal + Total;

        }

    }
    cout<<"\n\t\t\t  Grand Total: "<<GTotal<<"\n";
    cout<<"\n\t        -Thank You-\n";
    cout<<"============================================\n";
    cout<<"============================================\n";
    Csv_File.close();
    inFile.close();
    R_main();

}


int Date(){
    // current date/time based on current system
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *ltm = localtime(&now);
    // print various components of tm structure.

    cout<< "Date:"<< ltm->tm_mday <<"/"<< 1 + ltm->tm_mon <<"/"<< 1900 + ltm->tm_year<<"\n";
    
    // DailySal_2<<"Date:" << ltm->tm_mday <<"/"<< 1 + ltm->tm_mon <<"/"<< 1900 + ltm->tm_year<<"\n";
    // DailyCsv<<"Date:" << ltm->tm_mday <<"/"<< 1 + ltm->tm_mon <<"/"<< 1900 + ltm->tm_year<<"\n";

}
  


int R_main(){
    int Cnt;
    cout<<"\n";
    cout<<"\t[1] Main Menu\n\t[0] Quit\n \t\t____";
    cin>>Cnt;

    switch(Cnt){
        case 0: exit(0);break;
        case 1: main();
        default: cout<<"---enter(1/0)---\n";R_main();
    }
}