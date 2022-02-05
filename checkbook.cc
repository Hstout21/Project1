/**
 * Name: Hunter Stout
 * File Name: checkbook.cc
 * Date: 2/4/2022
 * Brief: Checkbook class function file.
 */

#include "checkbook.h"
#include "check.h"
#include <iostream>
#include <iomanip>

using namespace std;

//############################### C O N S T R U C T O R ###############################

Checkbook::Checkbook(){
    used = 0;
    new_check_number = 1;
    balance = 0;
}

//############################ M E M B E R S (load & save) ############################

void Checkbook::load_from_file(istream& ins){ 

    Check placeholder_check;
    //Grabs balance & check number from file.
    ins >> balance;
    ins >> new_check_number;

    //Skips spaces in file.
    while(ins.peek() == '\n' || ins.peek() == '\r')
	    ins.ignore();

    //Fills array until all data is collected from file.
    while(ins >> placeholder_check){
        data[used] = placeholder_check;
        used++;
    }
}

void Checkbook::save(ostream& outs) {

    outs << balance << "\n";
    outs << new_check_number << "\n";

    for (size_t i = 0; i < used; i++) {
        outs << data[i].get_num() << "\n";
        outs << data[i].get_date() << "\n";
        outs << data[i].get_payto() << "\n";
        outs << data[i].get_amount() << "\n";
    }
}

//############################### M E M B E R S (1-10) ###############################

void Checkbook::write_check(istream& ins){ //2

    if (used < CB_MAX) {
        //Grabs new check.
        Check placeholder_check;
        ins >> placeholder_check;

        //Makes sure there is enough balance in account for new check.
        double new_balance = balance - placeholder_check.get_amount();
        if (new_balance >= 0) {
            //Updates balance.
            balance = new_balance;
            //Updates check number.
            placeholder_check.set_check_num(new_check_number);
            new_check_number++;
            //Updates checkbook.
            data[used] = placeholder_check;
            used++;
        }
        else{
            cout << "Error: Must have sufficient funds to create this check!\n";
        }
    }
    else{
        cout << "Error: Checkbook is full!\n";
    }
}

void Checkbook::show_all(ostream& outs)const{ //4

    for (size_t i = 0; i < used; i++){
        outs << data[i] << "\n";
    }
}

void Checkbook::remove(int const remove_checknumber){ //5

    if (used >= 1) {
        Check placeholder_check;
        for (size_t i = 0; i < used; i++) {
            if (remove_checknumber == data[i].get_num()) {
                //Reduces check array & number.
                new_check_number--;
                used--;
                //Updates total.
                balance += data[i].get_amount();
                //Updates array (note: used was subtracted by one).
                placeholder_check = data[used];
                data[used] = data[i];
                data[i] = placeholder_check;
            }
        }
    }
    else {
        cout << "Error: Checkbook is empty!\n";
    }
}

void Checkbook::number_sort(){ //6

    //Check number bubble sort.
    Check placeholder_check;
    bool done = false;
    while (!done) {
        done = true;
        for (size_t i = 0; i < used - 1; i++) {
            if (data[i].get_num() > data[i + 1].get_num()) {
                placeholder_check = data[i];
                data[i] = data[i + 1];
                data[i + 1] = placeholder_check;
                done = false;
            }
        }
    }
}

void Checkbook::payto_sort(){ //7

    //Payto bubble sort.
    Check placeholder_check;
    bool done = false;
    while (!done) {
        done = true;
        for (size_t i = 0; i < used - 1; i++) {
            if (data[i].get_payto() > data[i + 1].get_payto()) {
                placeholder_check = data[i];
                data[i] = data[i + 1];
                data[i + 1] = placeholder_check;
                done = false;
            }
        }
    }
}

void Checkbook::date_sort(){ //8

    //Date bubble sort.
    Check placeholder_check;
    bool done = false;
    while (!done) {
        done = true;
        for (size_t i = 0; i < used - 1; i++) {
            if (data[i].get_date() > data[i + 1].get_date()) {
                placeholder_check = data[i];
                data[i] = data[i + 1];
                data[i + 1] = placeholder_check;
                done = false;
            }
        }
    }
}

void Checkbook::show(string check_search)const{ //9

    double total_paid = 0.0; //total amount paid to specified user.
    int total_checks = 0; //amount of checks paid to specified user.

    for (size_t i = 0; i < used; i++){
        if (check_search == data[i].get_payto()){
            cout << data[i] << "\n";
            total_paid = total_paid + data[i].get_amount();
            total_checks++;
        }
    }

    //Different outputs based on amount of checks paid.
    if (total_checks <= 1) {
        cout << "You paid $" << fixed << setprecision(2) << total_paid << " to " << check_search << "\n";
    }
    else {
        cout << "You paid " << total_checks << " checks to " << check_search;
        cout << ", in total $" << fixed << setprecision(2) << total_paid << "\n";
    }
}

double Checkbook::average()const{ //10

    double total = 0.0;
    int array_size = 0; //Safety precaution so we don't use "used (size_t unsigned)" to find "average (signed)".
    for (size_t i = 0; i < used; i++){
        total += data[i].get_amount();
        array_size++;
    }  
    return (total / array_size);
}
