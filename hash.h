#ifndef HASH_H
#define HASH_H
#include <string>
using namespace std;
class hash
{
    public:
        hash();
        int Hash(string key);
        void  AddItem(string email);
        void printTable();
        void findEmail();
        void removeItem(string email);
        void update();

    private:
        static const int table_size = 4; // the size will begin with
        struct item{ // information about our user
            string email; // make info with only email
            item* next;
        };
        item* HashTable[table_size]; // define a table with size (table_size)
        int NumberOfItemsInIndex(int index); // print the  num of items in index
        void printItemsInIndex(int index);   // print items in an index
};
#endif // HASH_H
