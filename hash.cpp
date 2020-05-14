#include "hash.h"
#include <string>
#include <iostream>
using namespace std;
hash::hash()
{
    for(int i = 0; i < table_size ; i++){ // initialize the table
        HashTable[i] = new item;          // make an item
        HashTable[i] ->email = "empty";   // the default value is empty
        HashTable[i] ->next = NULL;       // next item is not exist (null)
    }
}

void hash::AddItem(string email){
        int index = Hash(email); // get the index of the email
        if(HashTable[index] -> email == "empty"){ // if the email is the first item in this index
            HashTable[index] -> email = email;
        }
        // if there is other items in this index
        else{
            item* first_item= HashTable[index]; //get the first item in the index
            item* new_item = new item; // make new item
            new_item -> email = email; // put the value of email
            new_item -> next = NULL;

            while(first_item -> next != NULL){  // get the end of the list
                first_item = first_item -> next;
            }
            first_item -> next = new_item; // add the new item to the end of the list
        }
}

int hash::NumberOfItemsInIndex(int index){ // get the Number of items in specified index
    int count = 0;
    if(HashTable[index]->email == "empty"){ // index has no item
        return count;
    }
    else{
        count++;
        item* first_item = HashTable[index];
        while(first_item ->next != NULL){ // go to the end of this index and count
            count++;
            first_item = first_item ->next ;
        }
    }
    return count;
}

void hash::printTable(){ // print all table
    int number = 0;
    for(int i =0; i < table_size ; i++ ){ //loop for the items
        number = NumberOfItemsInIndex(i); // get the number of item in the index
        hash::printItemsInIndex(i);             // print the items in this index
        cout<< "num of items = " << number << endl;
        cout<<"----------------------------------\n";
    }
}

void hash::printItemsInIndex(int index){ // print items in specified index
    item* first_item = HashTable[index]; // get the first item in this index
    if(first_item -> email == "empty"){ // if the index is empty
        cout<< "index = "<< index << " is empty"<<endl;
    }
    else{
        cout<< "index " << index << " contains the following people"<<endl;
        while(first_item != NULL){ // if the index have item or more print it
            cout<<"------------------\n";
            cout<<first_item-> email <<endl;
            cout<<"------------------\n";
            first_item = first_item->next; // go to the next item
        }
    }
}

void hash::findEmail(){ // find an email
    string email;
    cout << "enter the Email you want to look for"<<endl;
    cin >> email;
    int index = Hash(email); // get the hash of the email
    bool foundEmail = false;
    item* first_item = HashTable[index]; // point the first item in this index
    while(first_item != NULL){ // loop to the end of this index
        if(first_item -> email == email){ // if you get the email make this true
            foundEmail = true;
        }
        first_item = first_item -> next;
    }
    if(foundEmail){ // get the email
        cout << "the Email  " << email <<" is Found"<< endl;
    }
    else{ // email not found
        cout<< "the Email " << email << " was not found";
    }
}

void hash::removeItem(string email){ // remove an item
    int index = Hash(email);
    item* delPtr;
    item* p1;
    item* p2;
    if(HashTable[index]-> email == "empty"){ // this index have no items
        cout<< email << " is not found" <<endl;
    }
    // the index have only one item
    else if(HashTable[index]->email == email && HashTable[index]-> next == NULL){
        HashTable[index] -> email = "empty";
        cout << "email "<< email << " was removed"<<endl;
    }
    // find email in the first_item in the index but they have more than one item
    else if(HashTable[index]->email == email){
        delPtr = HashTable[index]; // get the email wanna to remove
        HashTable[index] = HashTable[index] -> next; // make the first item hold the next
        delete delPtr;                       // remove the item
        cout << "email "<< email << " was removed"<<endl;
    }
    else{ // have the item we wanna to remove but it was in the middle
        // look to second item
        p1 = HashTable[index] ->next; // the second item in the index
        p2 = HashTable[index];        // the first item in the index
        while(p1 != NULL && p1 ->email != email){ // loop until p1 go to the end or email found
                p2 = p1;
                p1 = p1->next;
        }
        // no item have this email
        if(p1 == NULL){
            cout<< "Email "<< email << " is not found" <<endl;
        }
        // find the email
        else{
            delPtr = p1; // get the item wanna to delete
            p1 = p1->next; // make it own the next
            p2 -> next = p1; // make the previous own the new
            delete delPtr;   // delete the item
            cout << "the Email: "<<email << " was removed"<<endl;
        }
    }
}

void hash::update(){ // update Email
    string email;
    string new_email;
    cout << "Enter the email you wanna to update"<<endl;
    cin >> email;
    int index = Hash(email);
    bool foundEmail = true;
    item* first_item = HashTable[index]; // get the first item in this index
    item* my_email;                      // take the email i will found
    while( foundEmail && first_item != NULL){ // loop to the end of this index or found email
        if(first_item -> email == email){ // if you get the email make this true
            foundEmail = false;           // make false to end the loop
            my_email = first_item;         // get the item need to update
        }
        first_item = first_item -> next;
    }
    if(!foundEmail){   // if the email is exist we have two cases
        cout << "Enter the new email"<<endl;
        cin >> new_email;
        if(index == Hash(new_email)){  // case 1 the old email and the new one have the same index
            my_email -> email = new_email;
            cout << "email updated" <<endl;
        }
        else{                 // case 2 they have different index
            removeItem(my_email->email); // delete the old
            AddItem(new_email);           // insert the new one
        }
    }
    else{
        cout<<"Email dose not exist to update"<<endl;
    }
}

int hash::Hash(string key){ // hash the email
    int hash = 0;
    int index = 0;
    for(int i=0;i <key.length();i++ ){
        hash = (hash+ (int)key[i]) * 7; // my own hash function 7 is lucky num
    }
    index = hash % table_size;
    return index;
}
