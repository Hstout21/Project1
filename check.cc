/*************************************************************************
    This is the implementation file for the Check class. For more 
		information about the class see check.h.
    Students are expected to implement some of the functions shown 
		below.
	John Dolan			Ohio University EECS	September 2019
	Patricia Lindner	Ohio University EECS	August 2021
*************************************************************************/
#include "check.h"
#include "date.h"
#include <cctype>
#include <iostream>
#include <iomanip>
using namespace std;

Check::Check(Date d, string p, int num, double amt){
	checknum = num;
	date = d;
	payto = p;
	amount = amt;
}

//############################### Functions edited by Hunter Stout ###############################

void Check::write_check(std::istream& ins){
	string placeholder;
	if (&ins == &cin){
		cout << "Enter the check date (MM/DD/YYYY):\n";
		ins >> date;
		cout << "Enter the check pay to:\n";

        while(ins.peek() == '\n' || ins.peek() == '\r') {
        	ins.ignore();
		}

		getline(ins, placeholder);
		payto = placeholder;
		cout << "Enter the check amount:\n";
		ins >> amount;
	}
	else{
        ins >> checknum;
        ins >> date;

        while(ins.peek() == '\n' || ins.peek() == '\r') {
			ins.ignore();
		}

	    getline(ins, placeholder);
		//Checks to see if its a string.		
		int string_test = 1, length = placeholder.length();
    	for (int i = 0; i < length; i++) {
        	if (! isdigit(placeholder[i])) {
            	string_test = 0;
        		}
		}
		if (string_test == 0) {
			payto = placeholder;
		}

        ins >> amount;
    }
}

void Check::output(std::ostream& outs)const{
	if (&outs == &cout){
		cout << "Check Number: " << checknum << "\n";
		cout << "Date: " << date << "\n";
		cout << "Pay to: " << payto << "\n";
		cout << "Amount: " << setprecision(2) << fixed << amount << "\n";
	}
	else{
		outs << checknum << "\n";
		outs << date << "\n";
		outs << payto << "\n";
		outs << amount << "\n";		
	}
}

//################################################################################################

ostream& operator << (ostream& outs, const Check& c){
	c.output(outs);
	return outs;
}

istream& operator >> (istream& ins, Check& c){
	c.write_check(ins);
	return ins;
}