#include "parser.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <sstream>


using namespace std;

static int sizeOfPlot=0;

parser::parser()
{

}

QMap <string, vector<parser::quoteValues>> mapQuoteValues;
QVector <parser::quoteValues> vctOfMapQuoteValues;

QMap<string, vector<parser::quoteValues>> parser::getMapQuoteValues()
{
    return mapQuoteValues;
}

QVector <parser::quoteValues> parser::getVctQuoteValues()
{
    return vctOfMapQuoteValues;
}

int parser::getSizeOfPlot()
{
    int i = sizeOfPlot;
    return i;
}

void parser::getStartDate(int &d, int &m, int &y)
{
   for (auto it=vctOfMapQuoteValues.begin();it!=vctOfMapQuoteValues.begin()+1;it++)
   {
       cout<<it->date<<" f" <<endl;

       string str=it->date.substr(0,4);
       string str2=it->date.substr(5,2);
       string str3=it->date.substr(8,2);

       y=atoi(str.c_str());
       m=atoi(str2.c_str());
       d=atoi(str3.c_str());
        cout<<str<<" t"<<endl;
        cout<<str2<<" t"<<endl;
        cout<<str3<<" t"<<endl;
        cout<<d<<" i"<<endl;
        cout<<m<<" i"<<endl;
        cout<<y<<" i"<<endl;

   }
}

void parser::getOpenForPlot(QVector <double> vct)
{
    for (auto it=vctOfMapQuoteValues.begin();it!=vctOfMapQuoteValues.end();it++)
    {
       vct.push_back(it->open);
    }
}

void parser::getCloseForPlot(QVector <double> vct)
{
    for (auto it=vctOfMapQuoteValues.begin();it!=vctOfMapQuoteValues.end();it++)
    {
       vct.push_back(it->close);
    }
}

void parser::show() //pomocnicza metoda, do usuniecia w finalnym etapie
{
    for(auto it=vctOfMapQuoteValues.begin();it!=vctOfMapQuoteValues.end();it++)
    {
        cout.precision(8);

        cout<<it->date<<endl;
        cout<<it->open<<endl;
        cout<<it->higest<<endl;
        cout<<it->lowest<<endl;
        cout<<it->close<<endl;
        cout<<it->volume<<endl;
        cout<<exampleStruct.name<<" nazwa tutaj"<<endl;
    }
cout<<mapQuoteValues.size()<<endl;
cout<<vctOfMapQuoteValues.size()<<endl;
}

void parser::assignValues(string wichLine, string &d, double &o, double &h, double &l, double &c, long int &v)
{
   static int numberOfValue=1;

     switch (numberOfValue)
     {
            case 1:
            {
                   d=wichLine;
            }
            break;
            case 2:
            {
                   o=atof(wichLine.c_str());
            }
            break;
            case 3:
            {
                   h=atof(wichLine.c_str());
            }
            break;
            case 4:
            {
                   l=atof(wichLine.c_str());
            }
            break;
            case 5:
            {
                   c=atof(wichLine.c_str());
            }
            break;
            case 6:
            {
                   v=atol(wichLine.c_str());
            }
            break;
            default:
            {
                   cout<<"Blad"<<endl;
            }
            break;
     }

    numberOfValue++;
    if (numberOfValue==7)
    {
        vctOfMapQuoteValues.push_back({d,o,h,l,c,v});
        //mapQuoteValues[exampleStruct.name]=vctOfMapQuoteValues;
        numberOfValue=1;
        sizeOfPlot++;
    }
}

void parser::setName(string &n)
{
    exampleStruct.name=n;
}

void parser::loadFromFile()
{
    fstream quoteData;
    quoteData.open("C:/Users/Hid/Desktop/App/stockapp/Date/WIG.aqs", ios::in); //Podana pelna sciezka na moim komputerze. Dopracowac mobilnosc na innych portach

    if (quoteData.good()==false)
    {
        std::cout<<"Plik nie istnieje"<<std::endl;
        exit(0);
    }

    string line,name;
    long int numberOfLines=0;
    int numberOfComma=0;

    getline(quoteData,line);
    string::size_type foundName=line.find("$NAME");
    name=line.substr(foundName+6,line.size());
    setName(name);

        while (!quoteData.eof())
        {
            getline(quoteData,line, ',');
            numberOfLines++;

        if (numberOfLines>5)// aby zaczelo wczytywac od wartosci notowan
        {
            assignValues(line,exampleStruct.date,exampleStruct.open,exampleStruct.higest,exampleStruct.lowest,exampleStruct.close,exampleStruct.volume);

        }

        numberOfComma++;
        if (numberOfComma==5) //aby poprawnie nie przypisywalo napisu "wolumen"
        {
            getline(quoteData,line);
            numberOfComma=6;
        }

        if (numberOfComma==11) //aby poprawnie wychwytywalo znak konca linii, gdyż nie ma tam ","
        {
            getline(quoteData,line);
            assignValues(line,exampleStruct.date,exampleStruct.open,exampleStruct.higest,exampleStruct.lowest,exampleStruct.close,exampleStruct.volume);
            numberOfComma=6;

        }
    }
    quoteData.close();
}
