//C0F4DFE8B340D81183C208F70F9D2D797908754D
#include "TableEntry.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <getopt.h>
using namespace std;

struct Column {
    EntryType type;
    size_t index;
    //vector<TableEntry> entries;
    //string name;
};

//my three functors :D
struct LsFunct{
    public:
   
    //make constructors for functors.
    LsFunct(TableEntry comp) : comparison(comp){}

    LsFunct(TableEntry comparison, size_t colind) : comparison(comparison), colindex(colind){}
    
    //pass in a vector into the operator
    bool operator()(TableEntry &a){
        return a > comparison;
    }

    bool operator()(vector<TableEntry> &a){
        return a[colindex] > comparison;
    }


    private:

    TableEntry comparison;
    size_t colindex = 0;
};

struct GrFunct{
    public:

    GrFunct(TableEntry comp) : comparison(comp){}

    GrFunct(TableEntry comparison, size_t colind) : comparison(comparison), colindex(colind){}

    bool operator()(TableEntry a){
        return a < comparison; //formerly <
    }

    bool operator()(vector<TableEntry> &a){

        return a[colindex] < comparison;
    }

    private:
    TableEntry comparison;
    size_t colindex = 0;
};

struct EqFunct{
    public:
    
    EqFunct(TableEntry comp) : comparison(comp){}

    EqFunct(TableEntry comparison, size_t colind) : comparison(comparison), colindex(colind){}

    bool operator()(TableEntry a){
        return a == comparison;
    }

    bool operator()(vector<TableEntry> &a){
        
        return a[colindex] == comparison;
    }

    private:
    TableEntry comparison;
    size_t colindex = 0;
};

struct Table{

    
    //for GENERATE
    unordered_map<TableEntry, vector<size_t>> hash;
    map<TableEntry, vector<size_t>> bst;
    size_t indexind = 0;
    //add 2d vector w/ int, row
    unordered_map<string, Column> tablecols; // so that find is O(1)
    vector<EntryType> types;

    size_t numprinted = 0;

    vector<vector<TableEntry>> tableentries; //rows, TableEntries?
    //using column index, access this table. 
    //unordered_map<string, Column> tablecols; // so that find is O(1)
    //vector for the vals.
    bool InterpretSymbol(TableEntry a, TableEntry b, char symby){

        if(symby == '>'){
            LsFunct functor(b);

            return functor(a);

        }else if(symby == '<'){
            GrFunct functor(b);

            return functor(a);

        }else{

            EqFunct functor(b);

            return functor(a);
        }
    }

    void PrintTraversal(vector<string> cols, TableEntry tben, Column mycolumn, char symby, bool quiet){
      
        numprinted = 0;
        bool printed = false;

        //HASH CASE FOR '='
        if(hash.empty() == false && mycolumn.index == indexind && symby == '='){
            
            if(hash.find(tben) != hash.end()){
                for(size_t i = 0; i < hash[tben].size(); ++i){
                    for(size_t j = 0; j < cols.size(); ++j){
                       if(quiet != true){
                        cout<<tableentries[hash[tben][i]][tablecols[cols[j]].index]<<" ";
                       }
                        
                    }
                    ++numprinted;
                if(quiet != true){
                    cout<<"\n";
                    }
                }
                
            }
        //BST CASE FOR ALL SYMBOLS
        }else if(bst.empty() == false && mycolumn.index == indexind){
            //three way split.
           
            if(symby == '<'){
                
                for(auto it = bst.begin(); it != bst.lower_bound(tben); ++it){
                    for(size_t i = 0; i < (it->second).size(); ++i){
                        for(size_t j = 0; j < cols.size(); ++j){
                            if(quiet != true){ //here?
                                cout<<tableentries[(it->second)[i]][tablecols[cols[j]].index]<<" ";
                            }
                        }
                    ++numprinted;
                    if(quiet != true){
                        cout<<"\n";
                        }
                    }
                }

            } else if(symby == '>'){
               
                for(auto it = bst.upper_bound(tben); it != bst.end(); ++it){
                    for(size_t i = 0; i < (it->second).size(); ++i){//this line. 
                        for(size_t j = 0; j < cols.size(); ++j){
                            if(quiet != true){
                                cout<<tableentries[(it->second)[i]][tablecols[cols[j]].index]<<" ";
                            }
                        }
                    ++numprinted;
                    if(quiet != true){
                        cout<<"\n";
                        }
                    }
                }

            }else{
            
                if(bst.find(tben) != bst.end()){
                 
                    for(size_t i = 0; i < bst[tben].size(); ++i){
                        for(size_t j = 0; j < cols.size(); ++j){
                            if(quiet != true){
                             
                                cout<<tableentries[bst[tben][i]][tablecols[cols[j]].index]<<" ";
                            }
                        }
                        ++numprinted;

                        if(quiet != true){
                            cout<<"\n";
                        }
                    }
                }
            }

        }else{
       
        for(size_t i = 0;  i < tableentries.size(); ++i){
            //for(size_t j = 0; j < cols.size(); ++j){
                
            if(InterpretSymbol(tableentries[i][mycolumn.index], tben, symby) == true){
                printed = true;

                for(size_t j = 0; j < cols.size(); ++j){
                    if(quiet != true){
                        cout<<tableentries[i][tablecols[cols[j]].index]<<" ";
                    }
            
                }

                if(printed == true){
                    ++numprinted;
                    printed = false;
                }

                if(quiet != true){
                    cout<<"\n";
                }
                //printed = true;
            }
        }

            /*if(printed == true){
                ++numprinted;
                printed = false;
            }*/
        
            /*if(quiet != true){
                cout<<"\n";
            }*/
        }

            /*if(quiet != true){
                cout<<"\n";
            }*/
        
    
    cout<<"Printed "<<numprinted<<" matching rows from ";
    //}
    }

    void Print_all(vector<size_t> printindxs, vector<string> printcolns){
   
    for(size_t j = 0; j < printindxs.size(); ++j){
    
        cout<<printcolns[j]<<" ";
        
    }
    
    cout<<"\n";
    
    for(size_t i = 0; i < tableentries.size(); ++i){
        for(size_t j = 0; j < printcolns.size(); ++j){
          
            cout<<tableentries[i][printindxs[j]]<<" ";
            
        }
        cout<<"\n";
    }
}

    //do this after reading in the symbol.
    void TypeHelper(vector<string> cols, string colname, char symboly, char cmd, bool quiet){
        Column mycolumn = tablecols[colname];   
        
        if(mycolumn.type == EntryType::Int){
            int var;
            cin>>var;
            TableEntry newentry(var);

            if(cmd == 'p'){
                PrintTraversal(cols, newentry, mycolumn, symboly, quiet);
            }else{ 
                DeleteTraversal(newentry, mycolumn, symboly);
            }

        }else if(mycolumn.type == EntryType::Double){
            double var;
            cin>>var;
            TableEntry newentry(var);
           
            if(cmd == 'p'){
                PrintTraversal(cols, newentry, mycolumn, symboly, quiet);
            }else{
                DeleteTraversal(newentry, mycolumn, symboly);
            }

        }else if(mycolumn.type == EntryType::String){
            string var;
            cin>>var;
            TableEntry newentry(var);

            if(cmd == 'p'){
                PrintTraversal(cols, newentry, mycolumn, symboly, quiet);
            }else{
                DeleteTraversal(newentry, mycolumn, symboly);
            }

        }else{
            bool var;
            cin>>var;
            TableEntry newentry(var);

            if(cmd == 'p'){
                PrintTraversal(cols, newentry, mycolumn, symboly, quiet);
            }else{
                DeleteTraversal(newentry, mycolumn, symboly);
            }
        }
    }

    //how do I connect the TableEntry to remove_if?
    void DeleteTraversal(TableEntry tben, Column mycolumn, char symby){ 

    // if tableentries[mycolumn.index][j] > comparison, delete tableentries[mycolumn.index][j]
        //pass the tben into the functor from here.
        if(symby == '>'){
            LsFunct pred(tben, mycolumn.index);
            
                tableentries.erase(remove_if(tableentries.begin(), tableentries.end(), pred), tableentries.end()); //not sure how to declare this.
                
        }else if(symby == '<'){
            GrFunct pred(tben, mycolumn.index);
            
                tableentries.erase(remove_if(tableentries.begin(), tableentries.end(), pred), tableentries.end()); //not sure how to declare this.

        }else{
            EqFunct pred(tben, mycolumn.index);
            
                tableentries.erase(remove_if(tableentries.begin(), tableentries.end(), pred), tableentries.end()); //not sure how to declare this.
            //here, returning an error when nothing is erased.
        }
    
    }

    void GenHelper(string indtype, string colname){
  
        if(hash.empty() == false){//HASH INDEX SHOULD NOT BE EMPTY

            hash.clear();

        } 
        
        if(bst.empty() == false){
       
            bst.clear();
        }
   
        auto tablesize = tableentries.size();

        indexind = tablecols[colname].index;

        if(indtype == "hash"){
    
            for(size_t i = 0; i < tablesize; ++i){
        
                TableEntry loopentry = tableentries[i][tablecols[colname].index];

                auto it = hash.find(loopentry);

            if(it == hash.end()){

                hash[loopentry] = {i};

            }else{

                it->second.push_back(i);

            }

        }

    } else {

        for(size_t i = 0; i < tablesize; ++i){
        
            TableEntry loopentry = tableentries[i][tablecols[colname].index];

            auto it = bst.find(loopentry);

                if(it == bst.end()){

                    bst[loopentry] = {i};

                }else{

                    it->second.push_back(i);

                } 
            }
        }
    }

void DeleteGenHelper(string indtype){
    
    if(hash.empty() == false){

            hash.clear();

        } 
        
    if(bst.empty() == false){
            
            bst.clear();
    }
   
    auto tablesize = tableentries.size();


        if(indtype == "hash"){
    
            for(size_t i = 0; i < tablesize; ++i){
        
                TableEntry loopentry = tableentries[i][indexind];

                auto it = hash.find(loopentry);

            if(it == hash.end()){

                hash[loopentry] = {i};

            }else{

                it->second.push_back(i);

            }

        }

    } else {

        for(size_t i = 0; i < tablesize; ++i){
        
            TableEntry loopentry = tableentries[i][indexind];

            auto it = bst.find(loopentry);

                if(it == bst.end()){

                    bst[loopentry] = {i};

                }else{

                    it->second.push_back(i);

                } 
            }
        }
}

void InsertHashHelper(TableEntry &tbentry, size_t row, size_t col){
    /*cout<<"in the hash helper"<<endl;
    //all going on in here.
    cout<<"index ind : "<<indexind<<endl;
    cout<<"table entry is "<<tbentry<<endl;*/
    if(indexind == col){
        if(hash.find(tbentry) == hash.end()){
        //cout<<"no tbentry?"<<endl;
            hash[tbentry] = {row};

        }else{
      
            hash[tbentry].push_back(row);

        }
    }
}

void InsertBstHelper(TableEntry &tbentry, size_t row, size_t col){
 
    //cout<<"tableentry = "<<tbentry<<endl;
    //THERES AN ERROR HERE.
    if(indexind == col){
        if(bst.find(tbentry) == bst.end()){

            bst[tbentry] = {row};

        }else{

            bst[tbentry].push_back(row);

        }
    }
}


};

class Database{

public:

unordered_map<string, Table> bigmap;

bool quiet = false;

//getting modes
void getMode(int argc, char** argv){

    // use getopt to find command line options
      int index = 0;
      int option;

    // use getopt to find command line options
    struct option longOpts[] = {{ "help", optional_argument, nullptr, 'h' },
                                { "quiet", optional_argument, nullptr, 'q' },
                                { nullptr, 0, nullptr, '\0' }};
    
    while ((option = getopt_long(argc, argv, "hq", longOpts, &index)) != -1) {
        switch (option) {
            
            case 'h':
            cout<<"helpful message\n";
            break;

            case 'q':
            quiet = true;
            break;
            
    }
    }   
}

void Create(){

    Table newTable;

    string tblename;

    cin>>tblename;
    if(bigmap.find(tblename) != bigmap.end()){
        cout<<"Error during CREATE: Cannot create already existing table "<<tblename<<"\n";
        getline(cin, tblename);
        return;//should I do something else here?
    }

    size_t numcols;
    cin>>numcols;
    
    //newTable.columns.resize(numcols); //is a map now.
 
    string usedname;

    char usedchar;

   
    vector<string> names(numcols);

    newTable.types.resize(numcols);
    //string usedname = "string";
    for(size_t i = 0; i < numcols; ++i){
    
        cin>>usedchar;

        switch(usedchar){
            
        case 's':
            
            newTable.types[i] = EntryType::String;
            //just to get rid of rest of word.
            cin>>usedname;
            break;

        case 'b':
            
            newTable.types[i] = EntryType::Bool;
            
            cin>>usedname;
            break;
    
        case 'i':
            
            newTable.types[i] = EntryType::Int;
           
            cin>>usedname;
            break;

        case 'd':
            
            newTable.types[i] = EntryType::Double;
            
            cin>>usedname;
            break;
        }
    }


    for(uint8_t j = 0; j < numcols; ++j){
    
        cin>>usedname;
        names[j] = usedname;
    }

    for(uint8_t l = 0; l < numcols; ++l){
        Column newcol;
        newcol.index = l;
        newcol.type = newTable.types[l];
        newTable.tablecols.insert({names[l], newcol});
    }
    
    bigmap.insert({tblename, newTable});
    cout<<"New table "<<tblename<<" with column(s) ";

    for(size_t k = 0; k < names.size(); ++k){
        cout<< names[k] <<" ";
    }

    cout<<"created\n";

}


void Insert(){
    string junkstring;
    
    string tblnm;
    size_t newrows;
    
    cin>>junkstring>>tblnm>>newrows>>junkstring;
    
    if(bigmap.find(tblnm) == bigmap.end()){

        cout<<"Error during INSERT: "<<tblnm<<" does not name a table in the database\n";
        getline(cin, junkstring);
        return;
    }
    
    size_t fmrentrysz = bigmap[tblnm].tableentries.size();
   
    //remember to resize tableentries vector!
    bigmap[tblnm].tableentries.resize(bigmap[tblnm].tableentries.size() + newrows);
    
    for(size_t i = fmrentrysz; i < bigmap[tblnm].tableentries.size(); ++i){//start from where we left off.
        
        for(size_t j = 0; j < bigmap[tblnm].tablecols.size(); ++j){
            //read in the string entries.
        
            if(bigmap[tblnm].types[j] == EntryType::String){
                
                cin>>junkstring;
           
                TableEntry entry(junkstring);
               
                bigmap[tblnm].tableentries[i].emplace_back(entry);
                //cout<<entry<<endl;
               if(bigmap[tblnm].hash.empty() == false){
                bigmap[tblnm].InsertHashHelper(entry, i, j);

               }else if(bigmap[tblnm].bst.empty() == false){
                bigmap[tblnm].InsertBstHelper(entry, i, j);
               }
                //bigmap[tablename].hash.insert({loopentry, locs});

            }else if(bigmap[tblnm].types[j] == EntryType::Int){
                
                int integ;
                cin>>integ;
              
                TableEntry entry(integ);
                bigmap[tblnm].tableentries[i].emplace_back(entry);

                if(bigmap[tblnm].hash.empty() == false){
                bigmap[tblnm].InsertHashHelper(entry, i, j);
                
               }else if(bigmap[tblnm].bst.empty() == false){
                bigmap[tblnm].InsertBstHelper(entry, i, j);
               }

            }else if(bigmap[tblnm].types[j] == EntryType::Bool){
                
                bool boolin;
                cin>>boolin; //having trouble reading in bool.
            
                TableEntry entry(boolin);
                bigmap[tblnm].tableentries[i].emplace_back(entry); //this line...
                
                if(bigmap[tblnm].hash.empty() == false){
                bigmap[tblnm].InsertHashHelper(entry, i, j);
                
               }else if(bigmap[tblnm].bst.empty() == false){
                bigmap[tblnm].InsertBstHelper(entry, i, j);
               }
        
            }else{
            
                double duble;
                cin>>duble;
              
                TableEntry entry(duble);
                bigmap[tblnm].tableentries[i].emplace_back(entry);

                if(bigmap[tblnm].hash.empty() == false){
                bigmap[tblnm].InsertHashHelper(entry, i, j);
                
               }else if(bigmap[tblnm].bst.empty() == false){
                bigmap[tblnm].InsertBstHelper(entry, i, j);
               }
            }
            
        }
    }
    cout<<"Added "<<newrows<<" rows to "<<tblnm<<" from position "<<fmrentrysz
    <<" to "<< (bigmap[tblnm].tableentries.size() - 1) <<"\n";
    //exit(0);
}

void Remove(){

    string tablename;
    cin>>tablename;

    if(bigmap.find(tablename) == bigmap.end()){

        cout<<"Error during REMOVE: "<<tablename<<" does not name a table in the database\n";
        getline(cin, tablename);
        return;
    }
    //likely more complex.
    bigmap.erase(bigmap.find(tablename));

    cout<<"Table "<<tablename<<" deleted\n";
}

void Print_where(Table printtable, vector<string> printcols, string colname, char symbo){
    if(quiet != true){
    for(size_t j = 0; j < printcols.size(); ++j){
    
        cout<<printcols[j]<<" ";
        
    }
    cout<<"\n";
    }

    printtable.TypeHelper(printcols, colname, symbo, 'p', quiet);

}       


void Print(){
  
    string tablename;   
    cin>>tablename; //FROM
   
    cin>>tablename;
   
    if(bigmap.find(tablename) == bigmap.end()){
        cout<<"Error during PRINT: "<<tablename<<" does not name a table in the database\n";
        getline(cin, tablename);
        return;
    }

    size_t colnum;
    
    cin>>colnum;

    vector<size_t> printinds(colnum);
    vector<string> printcols(colnum);


    Table &printtable = bigmap[tablename];
    
    string colname;
   
   for(size_t i = 0; i < colnum; ++i){

        cin>>colname;

        if(printtable.tablecols.find(colname) == printtable.tablecols.end()){
            cout<<"Error during PRINT: "<<colname<<" does not name a column in "<<tablename<<"\n";
            getline(cin, colname);
            return;
        }
        
        printinds[i] = (printtable.tablecols[colname].index);
        
        printcols[i] = colname;
        
   }
    
    cin>>colname;
    

    if(colname == "ALL"){
       if(quiet != true){
            printtable.Print_all(printinds, printcols);
       }
        cout<<"Printed "<<printtable.tableentries.size()<<" matching rows from "<<tablename<<"\n";

    }else{

        char symbol;
        //1. read in the column.
        cin>>colname;
        
        if(printtable.tablecols.find(colname) == printtable.tablecols.end()){
            cout<<"Error during PRINT: "<<colname<<" does not name a column in "<<tablename<<"\n";
            return;
        }

        //2. read in the symbol, either <, >, or =. Use the functors.
        cin>>symbol;
        
            Print_where(bigmap[tablename], printcols, colname, symbol);
       
       
        cout<<tablename<<"\n";
    }
}

void Delete(){
    //1. follow steps of print_where.
    //2. in a for loop, perform vec.erase(remove_if(vec.begin(), vec.end(), pred)) ask about syntax too.
    string tablename;
    string colname;
    string junky;
    char symbol;
    cin>>junky; //FROM
    cin>>tablename;

    if(bigmap.find(tablename) == bigmap.end()){

        cout<<"Error during DELETE: "<<tablename<<" does not name a table in the database\n";
        getline(cin, junky);
        return;
    }

    Table &dTable = bigmap[tablename]; 
    size_t formersize = dTable.tableentries.size();

    cin>>junky; //WHERE
    cin>>colname;

     if(bigmap[tablename].tablecols.find(colname) == bigmap[tablename].tablecols.end()){
            cout<<"Error during DELETE: "<<colname<<" does not name a column in "<<tablename<<"\n";
            getline(cin, junky);
            return;
        }

    cin>>symbol;
    vector<string> cols(dTable.tablecols.size());
    size_t i = 0;

    for(auto name : dTable.tablecols){
        cols[i] = name.first;
        ++i;
    }
    
    bigmap[tablename].TypeHelper(cols, colname, symbol, 'd', quiet);
    //USE GEN HELPER HERE(or in DeleteTraversal)
        if(bigmap[tablename].bst.empty() == false){
            
            bigmap[tablename].DeleteGenHelper("bst");

        }else if(bigmap[tablename].hash.empty() == false){
          
            bigmap[tablename].DeleteGenHelper("hash");
        }
    
    //going to increment number of rows in the function.
    formersize -= bigmap[tablename].tableentries.size();
    cout<<"Deleted "<<formersize<<" rows from " << tablename<<"\n";

    }

void Generate(){
    //HANDLE THE CASE THAT ONLY ONE INDEX MAY EXIST PER TABLE.
    //Only one user-generated Index may exist per table, at any one time.
    //If a valid index is requested on a table that already has one, 
    //discard the old index before building the new one.
    string junky;
    string tablename;
    string colname;
    string indtype;
    //FOR <tablename> <indtype> INDEX ON <colname>
    cin>>junky>>tablename;
    
    
    if(bigmap.find(tablename) == bigmap.end()){

        cout<<"Error during GENERATE: "<<tablename<<" does not name a table in the database\n";
        getline(cin, junky);
        return;
    }
    

    cin>>indtype>>junky;
   
    cin>>junky;
 
    cin>>colname;

    if(bigmap[tablename].tablecols.find(colname) == bigmap[tablename].tablecols.end()){
            cout<<"Error during GENERATE: "<<colname<<" does not name a column in "<<tablename<<"\n";
            getline(cin, junky);
            return;
        }

    bigmap[tablename].GenHelper(indtype, colname);

    //If there's an existing hash or bst in the table, delete before starting anew.
     //cout<<"should be here."<<endl;
    

    cout<<"Created "<<indtype<<" index for table "<<tablename<<" on column "<<colname<<"\n";
    //GENERATE FOR 281class hash INDEX ON emotion
}


void Join(){
  
    string table1name;
    string table2name;
    string col1;
    string col2;
    string junky;
    size_t numcols;
    string printcol;
    size_t coltab;
    size_t rowcount = 0;
    unordered_map<TableEntry, vector<size_t>> temphash;
    //GENERATE A TEMPORARY HASH TABLE ON THE SECOND TABLE.
    
    //JOIN <tbl1> AND <tbl2> WHERE <col1> = <col2> AND PRINT <numcols>
  
    cin>>table1name;
    cin>>junky;
    cin>>table2name;
    cin>>junky;
   
    cin>>col1;
    cin>>junky;
    cin>>col2;
    cin>>junky;
    cin>>junky;
    
    cin>>numcols;
    //col 1 = Name, col 2 = person

    vector<Column> printcols(numcols);
    vector<size_t> colnums(numcols);
    vector<string> colnames(numcols);

    Table &table1 = bigmap[table1name];
    Table &table2 = bigmap[table2name];

    if(table1.tablecols.find(col1) == table1.tablecols.end()){
            cout<<"Error during JOIN: "<<col1<<" does not name a column in "<<table1name<<"\n";
            getline(cin, junky);
            return;
        }

    if(table2.tablecols.find(col2) == table2.tablecols.end()){
            cout<<"Error during JOIN: "<<col2<<" does not name a column in "<<table2name<<"\n";
            getline(cin, junky);
            return;
        }

    Column &coln1 = bigmap[table1name].tablecols[col1];

//CREATING A TEMP HASH MAP FOR TABLE2 (if no hash/bst in table2)

if(table2.indexind == table2.tablecols[col2].index && table2.hash.empty() == false){
    
        temphash = bigmap[table2name].hash;

}else{

for(size_t i = 0; i < bigmap[table2name].tableentries.size(); ++i){
        
        TableEntry loopentry = table2.tableentries[i][table2.tablecols[col2].index];

        if(temphash.find(loopentry) == temphash.end()){

            temphash[loopentry] = {i};

        }else{

            temphash[loopentry].push_back(i);

        }
    }

}

    //make a vector of columns
    for(size_t i = 0; i < numcols; ++i){
        cin>>printcol;
        
        cin>>coltab;
        Column pcol;
        
        if(coltab == 1){

            if(table1.tablecols.find(printcol) == table1.tablecols.end()){
                cout<<"Error during JOIN: "<<printcol<<" does not name a column in "<<table1name<<"\n";
                getline(cin, junky);
                return;
            }

            pcol = table1.tablecols[printcol];
            colnums[i] = 1;

        }else{

            if(table2.tablecols.find(printcol) == table2.tablecols.end()){
                cout<<"Error during JOIN: "<<printcol<<" does not name a column in "<<table2name<<"\n";
                getline(cin, junky);
                return;
            }

            pcol = table2.tablecols[printcol];
            colnums[i] = 2;
        }
        colnames[i] = printcol;

        printcols[i] = pcol;//{Name, emotion, likes_dogs?}

    }

    if(quiet != true){
        for(size_t i = 0; i < colnames.size(); ++i){
        
            cout<<colnames[i]<<" ";
        
        }

        cout<<"\n";
    }

    
    for(size_t j = 0; j < table1.tableentries.size(); ++j){
       
        if(temphash.find(table1.tableentries[j][coln1.index]) != temphash.end()){
         
        for(size_t t = 0; t < temphash[table1.tableentries[j][coln1.index]].size(); ++t){
            for(size_t v = 0; v < printcols.size(); ++v){ 
                
                if(quiet != true){
                    //cout<<"colnums[v] = "<<colnums[v]<<endl;
                    if(colnums[v] == 1){
                        //cout<<" v = 1\n";
                        cout<<table1.tableentries[j][printcols[v].index]<<" ";

                    }else{
                        //cout<<" v = 2\n";
                        
                            cout<<table2.tableentries[temphash[table1.tableentries[j][coln1.index]][t]][printcols[v].index]<<" ";
                        }
                    }
                }

                if(quiet != true){
                    cout<<"\n";
                }
            ++rowcount;
            }
            //++rowcount;
        }
    }
    
    //Printed 3 rows from joining pets to 281class
    cout<<"Printed "<<rowcount<<" rows from joining "<<table1name<<" to "<<table2name<<"\n";
}

};

void Quit(){
    cout<<"Thanks for being silly!\n";
}

int main(int argc, char** argv){
    ios_base::sync_with_stdio(false); // you should already have this
    cin >> boolalpha;  // add these two lines
    cout << boolalpha; // add these two lines

    char cond;
    string junky;
    Database bigdata;
    bigdata.getMode(argc, argv);
    //string cmd;
    //bare-bones do-while loop
    do{

        cout<<"% ";
        cin>>cond;
        
        if(cond != '#' && cond != 'C' && cond != 'I' && cond != 'R' && 
        cond != 'P' && cond != 'D' && cond != 'J' && cond != 'G' && cond != 'Q'){
            cout<<"Error: unrecognized command\n";
            getline(cin, junky);
        }
        
        if(cond == '#'){ //still prints the %
            getline(cin, junky);
        }

        if(cond == 'C'){
            cin>>junky;
            bigdata.Create();
        }

        else if(cond == 'I'){
            cin>>junky;
            bigdata.Insert();
        }
        
        else if(cond == 'R'){
            cin>>junky;
            bigdata.Remove();
        }

        else if(cond == 'P'){
            cin>>junky;
            bigdata.Print();
        
        }  else if(cond == 'D'){
            cin>>junky;
            bigdata.Delete();
        //bigdata.Delete();
        } else if(cond == 'G'){
            cin>>junky;
            bigdata.Generate();

        } else if(cond == 'J'){
            cin>>junky;
            bigdata.Join();
        }
    //need to put error message here

    }while(cond != 'Q');
    
    //case Quit:
    Quit();
    return 0;
}