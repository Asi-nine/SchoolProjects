#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "database/CSVReader.h"

// Loads the CSV file at file_name.

void CSVReader::loadCSV(std::string file_name) {
    std::ifstream myfile(file_name.c_str());
    if (myfile.fail()) {
        std::cout << "Couldn't open file \"" << file_name << "\"." << std::endl;
        return;
    }

    if (myfile.is_open()) {
        std::stringstream sstr;
        sstr << myfile.rdbuf();
        std::string f = sstr.str();
        myfile.close();

        size_t len = f.length();

        bool setHeaders = false;

        size_t pos = 0;
        while( pos < len ) { // While the file's not empty
            std::vector<std::string> line;
            while( f.at( pos ) != '\n' && pos < len ) { // For each character in the line
                std::string element = "";
                while( f.at( pos ) != ',' && pos < len && f.at( pos ) != '\n' && f.at( pos ) != '\r' ) { // For each element
                    if( f.at( pos ) == '"' ) { // If we have a quote, continue till the next quote
                        pos++;
                        while( f[pos] != '"' && pos < len ) {
                            element += f.at( pos );
                            pos++;
                        }
                        pos++; // Last quote
                    } else {
                        element += f.at( pos );
                        pos++;
                    }
                }
                line.push_back( element );

                if ( f.at( pos ) == '\n') {
                    break;
                }
                pos++;
            }
            if( !setHeaders ) {
                setHeaders = true;
                headers = line;
            } else {
                all_data.push_back( line );
            }
            pos++;
        }
    }
}

// Returns the year in a date string.
/*
int CSVReader::parseDateString(std::string dateString) {
    int year;
    sscanf(dateString.c_str(), "%4d", &year); // The only 4-digit number in a date field is a year, period
    return year;
}
*/

int CSVReader::parseDateString(std::string dateString) {
    int year;

    if (dateString.length() == 4){
        sscanf(dateString.substr(0,4).c_str(), "%4d", &year); // The only 4-digit number in a date field is a year, period
        return year;
    }
    if (dateString.length() == 5){
        if(isdigit(dateString[0])&&isdigit(dateString[1])){
            sscanf(dateString.substr(0,2).c_str(), "%2d", &year); // The only 4-digit number in a date field is a year, period
            std::string shortform;
            if (year<10)
                shortform="0" + std::to_string(year);
            else
                shortform=std::to_string(year);
            if (year>16)
                return std::stoi("19"+shortform);
            else
               return std::stoi("20"+shortform);
        }
        if(isdigit(dateString[3])&&isdigit(dateString[4])){
            sscanf(dateString.substr(3,2).c_str(), "%2d", &year); // The only 4-digit number in a date field is a year, period
            std::string shortform;
            if (year<10)
                shortform="0" + std::to_string(year);
            else
                shortform=std::to_string(year);
            if (year>16)
                return std::stoi("19"+shortform);
            else
               return std::stoi("20"+shortform);
        }
    }
    if (dateString.length() == 2){
        if(isdigit(dateString[0])&&isdigit(dateString[1])){
            sscanf(dateString.substr(0,2).c_str(), "%2d", &year); // The only 4-digit number in a date field is a year, period
            std::string shortform;
            if (year<10)
                shortform="0" + std::to_string(year);
            else
                shortform=std::to_string(year);
            if (year>16)
                return std::stoi("19"+shortform);
            else
               return std::stoi("20"+shortform);
        }
    else{ return 0000;}
   /*
    for (int i=0; i<(dateString.length()-3); i++){
        if (isdigit(dateString[i])&&isdigit(dateString[i+1])&&isdigit(dateString[i+2])&&isdigit(dateString[i+3])){
            sscanf(dateString.substr(i,4).c_str(), "%4d", &year); // The only 4-digit number in a date field is a year, period
            return year;
        }
    }
    //std::cout << "NOT 4" << std::endl;
    for (int i=0; i<(dateString.length()-1); i++){
        if (isdigit(dateString[i])&&isdigit(dateString[i+1])){
            //std::cout <<  dateString[i] << dateString[i+1] << std::endl;
            sscanf(dateString.substr(i,2).c_str(), "%2d", &year); // The only 4-digit number in a date field is a year, period
            std::string shortform;
            if (year<10)
                shortform="0" + std::to_string(year);
            else
                shortform=std::to_string(year);
            if (year>16)
                return std::stoi("19"+shortform);
            else
               return std::stoi("20"+shortform);
        }*/
    }
}

// Returns the header vector for a CSV

std::vector<std::string> CSVReader::getHeaders() {
    return headers;
}

// Returns all data from a CSV

std::vector<std::vector<std::string>> CSVReader::getData() {
    return all_data;
}

CSVReader::CSVReader() {

}

CSVReader::CSVReader(std::string file) {
    loadCSV(file);
}
