#ifndef PARSER_H
#define PARSER_H

#include "qcustomplot.h"

#include<string>
#include<vector>
#include<map>
#include<iostream>

using namespace std;

class parser
{
public:
    struct quoteValues
    {   string date;
        double open;
        double higest;
        double lowest;
        double close;
        long int volume;
        string name;
    }exampleStruct;

    parser();
    void assignValues(string, string&, double &, double& , double& , double& , long int& );
    void loadFromFile();
    void show();
    void setName(string &n);
    static QMap<string, vector<parser::quoteValues>> getMapQuoteValues();
    static QVector <parser::quoteValues> getVctQuoteValues();

    static int getSizeOfPlot();
    static void getStartDate(int &d, int &m, int &y);
    static void getOpenForPlot(QVector <double> vct);
    static void getCloseForPlot(QVector <double> vct);


};

#endif // PARSER_H
