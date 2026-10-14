/*
A farmer with a fox, a goose, and a sack of corn needs to cross a river
The farmer has a rowboat, but there is room for only the farmer and one of his three items.
Unfortunately, both the fox and the goose are hungry.
The fox cannot be left alone with goose, or the fox will eat the goose.
Likewise, the goose cannot be left alone with sack of corn, or the goose will eat the corn.
How does the farmer get everything across the river?

Constraints:

1) There is room for only the farmer and one of his three items
2) The fox cannot be left alone with goose
3) The goose cannot be left alone with sack of corn

Operations:

1) Row the boat from one shore to the other
2) If boat is empty, load an item from the shore.
3) If the boat is not empty, unload the item to the shore.

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

const vector<string> all_items = {"corn","fox","goose"};
vector<string> shore_one_items = {};
vector<string> shore_two_items = {};
vector<string> boat_items = {};
int attempts = 0;
const int BOAT_MAX_CAPACITY = 1;

void row_the_boat();
bool are_all_items_across();
void load_an_item(const string&);
string unload_an_item();
bool boat_is_empty();
string get_position();
bool are_items_allowed(const vector<string>&);

int main() {
    cout << "How to cross the river." << endl;
    cout << "=======================" << endl;
    shore_one_items = all_items;
    while(true){
        string item_unloaded = unload_an_item();
        if (are_all_items_across()){
            cout << "All done !!!, took " << attempts << " attempts." << endl;
            break;
        }
        load_an_item(item_unloaded);
        row_the_boat();
    }
    return 0;
}

// row the boat from one shore to the other
void row_the_boat(){
    cout << "Rowing the boat from " << get_position() << " carrying ";
    for (const auto& item : boat_items){
        cout << item << " ";
    }
    cout << "..." << endl
    << endl;
    attempts++;
}

bool are_all_items_across(){
    if (all_items.size() != shore_two_items.size()) return false;

    sort(shore_two_items.begin(),shore_two_items.end());

    return (all_items == shore_two_items);
}

// if boat is empty, load an item from the shore.
void load_an_item(const string& item_unloaded){
    if (boat_is_empty()){
        string position = get_position();
        vector<string> items_available = {};
        vector<string> items_available_after_unloading = {};
        if ( position == "shore_one" ){
            items_available = shore_one_items;
        } else {
            items_available = shore_two_items;
        }
        if (position == "shore_two") {
            if (are_all_items_across()){
                return;
            }
            if (are_items_allowed(items_available)) {
                return;
            }
        }
        // get every item except the one we just unloaded
        if (!item_unloaded.empty()){
            for (const auto& item : items_available){
                if ( item != item_unloaded ){
                    items_available_after_unloading.push_back(item);
                }
            }
        } else {
            items_available_after_unloading = items_available;
        }
        if(items_available_after_unloading.size()){
            items_available = items_available_after_unloading;
            string item_selected = {};
            while ( items_available.size() > 0 ){
                // get random number from hardware
                random_device rd;
                // seed the generator with that number
                mt19937 gen(rd());
                uniform_int_distribution<> distr(0, items_available_after_unloading.size() - 1);
                item_selected = items_available_after_unloading[distr(gen)];
                vector<string> items_left = {};
                for ( const auto& item : items_available_after_unloading){
                    if (item != item_selected) {
                        items_left.push_back(item);
                    }
                }
                items_available = items_left;
                if(are_items_allowed(items_left)){
                    cout << "Loading item " << item_selected << " to the boat" << endl;
                    boat_items.push_back(item_selected);
                    break;
                }
            }

            if ( position == "shore_one"){
                erase(shore_one_items, item_selected);
                cout << "Now " << position << " has ";
                for (const auto& item : shore_one_items){
                    cout << item << " ";
                }
                cout << "..." << endl;
            } else {
                erase(shore_two_items, item_selected);
                cout << "Now " << position << " has ";
                for (const auto& item : shore_two_items){
                    cout << item << " ";
                }
                cout << "..." << endl;
            }
        }
    } else {
        return;
    }

}

// if the boat is not empty, unload the item to the shore.
string unload_an_item(){
    string item_unloaded;
    if (boat_is_empty()) {
        return "";
    } else {
        string position = get_position();
        item_unloaded = boat_items.back();
        boat_items.pop_back();
        cout << "Unloading item " << item_unloaded << " from the boat" << endl;
        if ( position == "shore_one" ){
            shore_one_items.push_back(item_unloaded);
            cout << "Now " << position << " has ";
            for (const auto& item : shore_one_items){
                cout << item << " ";
            }
            cout << "..." << endl;
        } else {
            shore_two_items.push_back(item_unloaded);
            cout << "Now " << position << " has ";
            for (const auto& item : shore_two_items){
                cout << item << " ";
            }
            cout << "..." << endl;
        }
    }
    return item_unloaded;
}

bool boat_is_empty(){
    return (boat_items.size() == 0);
}

// there is room for only the farmer and one of his three items
bool boat_is_full(){
    return (boat_items.size() == BOAT_MAX_CAPACITY);
}

// the fox cannot be left alone with goose
// the goose cannot be left alone with sack of corn
bool are_items_allowed(const vector<string>& items){

    auto contains = [&](string item) {
        return find(items.begin(), items.end(),item) != items.end();
    };
    bool has_corn = contains("corn");
    bool has_fox = contains("fox");
    bool has_goose = contains("goose");

    return !(( has_corn && has_goose ) || ( has_fox && has_goose ));

}

string get_position(){
    return ((attempts % 2) == 0)?"shore_one":"shore_two";
}
