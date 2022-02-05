/**
 * Name: Hunter Stout
 * File Name: checkbook.h
 * Date: 2/4/2022
 * Brief: Checkbook header file.
 */

#ifndef CHECKBOOK_H
#define CHECKBOOK_H

#include "check.h"
#include <iostream>

class Checkbook{
    public:

    //##### Constructor #####.
    Checkbook();

    //##### Getters #####.
    /**
    * get_balance - Grabs "balance".
    * return - balance.
    */
    double get_balance()const {return balance;} //3

    //##### Members #####.
    /**
    * load_from_file - Loads checkbook file.
    * @ins - Preferred input stream.
    */
    void load_from_file(std::istream& ins); //Checkbook load

    /**
    * save - Saves checkbook file.
    * @outs - Preferred output stream.
    */
    void save(std::ostream& outs); //Checkbook save

    /**
    * deposit - Deposits money into bank account.
    * @deposit_amount - Amount of money deposited.
    */
    void deposit(double const deposit_amount) {balance += deposit_amount;} //1

    /**
    * write_check - Writes a check from scratch.
    * @ins - Preferred input stream.
    */
    void write_check(std::istream& ins); //2

    /**
    * show_all - Outputs check(s) written.
    * @outs - Preferred output stream.
    */
    void show_all(std::ostream& outs)const; //4

    /**
    * remove - Removes a check from checkbook.
    * @remove_checknumber - Check number that desires removal.
    */
    void remove(int const remove_checknumber); //5

    /**
    * number_sort - Sorts checkbook by checknumber.
    */
    void number_sort(); //6

    /**
    * payto_sort - Sorts checkbook by payto.
    */
    void payto_sort(); //7

    /**
    * date_sort - Sorts checkbook by date.
    */
    void date_sort(); //8

    /**
    * show - Shows a check based on inputed check number.
    * @check_search - Desired check number.
    */
    void show(std::string check_search)const; //9

    /**
    * average - Finds average based on the balance & amount of checks.
    */
    double average()const; //10

    private:

    static const size_t CB_MAX = 200;
    Check data[CB_MAX];
    size_t used;
    size_t new_check_number;
    double balance;
};


#endif