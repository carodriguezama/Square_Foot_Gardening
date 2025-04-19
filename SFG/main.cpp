#include <iostream>
#include <cstring>

using namespace std;

const int MAXBOXES=16;

class Box {
    int boxNumber, howMany;
    string plant;
public:
    void print() {
        cout<<"Enter the plant an howmany:";
    }
    friend istream & operator >>(istream & in, Box &b) {
    cout<<"Enter the plant: ";
    in>>b.plant;
    b.howMany=b.setPlant(b.plant);
    return in;
    }
    friend ostream & operator <<(ostream &out, const Box &b) {
    out<<b.howMany<<' '<<b.plant;
    return out;
    }
    int setPlant(string &b) {
    if(b=="Apple"||b=="apple"||b=="apples"||b=="Apples"
     ||b=="Peaches"||b=="peaches")//these are large plants that require a 3x3
        return 1;
    else if(b=="Onions"||b=="Onion"||b=="onions"
          ||b=="Cilantro"||b=="cilantro"
          ||b=="Spinach"||b=="spinach")//these are medium plants that require a 2x2
         return 9;
    else if(b=="Raddishes"||b=="raddishes"||b=="Raddish"||b=="raddish"
          ||b=="Carrots"||b=="carrots")
        return 16;
    else if(b=="lettuce"||b=="Lettuce")
        return 4;
    else if (b=="Kale"||b=="kale"
           ||b=="Potatoes"||b=="Potato"||b=="potatoes")
    return 2;
    else if(b=="tomatoes"||b=="Tomatoes")//small plants that need 1x1
         return 1;
    }
    int checkPlant() {
        return howMany;
    }
    void incremented() {
    howMany=0;
    plant="";
    }
};
class Garden {
    Box boxes[MAXBOXES];
    int box[4][4]={NULL};
    int boxchoice;
    int increment;
public:
	 void printPlantsOffered(){
	 cout<<"Choose from the following plants offered:\n\
	 apples,onions, tomatoes, carrots, peaches\n\
	 lettuce, raddish, kale, spinach, cilantro, and potatoes"<<endl;
	 increment=0;
	 }
     void printBoxMenu() {
        cout<<"Which box would you like to access(enter 17 to view the whole garden)"<<endl;
        cout<<"|-----------|\n| 1  2  3  4|\n| 5  6  7  8|\n| 9 10 11 12|\n|13 14 15 16|\n|-----------|"<<endl;
        cin>>boxchoice;//get the users choice of box
        while(boxchoice!=17)
        processBoxmenu(boxchoice);
    }
    void processBoxmenu(int boxNumber) {
          if(boxArray(boxNumber)==0) {
            cin>>boxes[boxNumber-1];
         if(boxes[boxNumber-1].checkPlant()==1)
            setLargePlant(boxNumber);
         else if(boxes[boxNumber-1].checkPlant()>1&&boxes[boxNumber-1].checkPlant()<9)
            setMediumPlant(boxNumber);
            }
            else
            cout<<boxes[boxNumber-1]<<endl;
            printBoxMenu();
    }
    void setLargePlant(int boxNumber) {//fucntion to set all 3x3 plants and boxes aswell as set all 2x2 plants as 1x1 plants are the defualt
       if(increment==0) {
        cout<<"This is a large plant that will require 9(3x3) total boxes\n any boxes that had plants in them will be replaced "<<endl;
        cout<<"Would you like to continue(y/n): ";
        char c;
        cin>>c;
        if(c=='y') {
        boxes[boxNumber]=boxes[boxNumber-1];
        boxes[boxNumber+1]=boxes[boxNumber-1];
        boxes[boxNumber+3]=boxes[boxNumber-1];
        boxes[boxNumber+4]=boxes[boxNumber-1];
        boxes[boxNumber+5]=boxes[boxNumber-1];
        boxes[boxNumber+7]=boxes[boxNumber-1];
        boxes[boxNumber+8]=boxes[boxNumber-1];
        boxes[boxNumber+9]=boxes[boxNumber-1];
        countDown(boxNumber);
        countDown((boxNumber+1));
        countDown((boxNumber+2));
        countDown((boxNumber+4));
        countDown((boxNumber+5));
        countDown((boxNumber+6));
        countDown((boxNumber+8));
        countDown((boxNumber+9));
        countDown((boxNumber+10));
        increment+=1;
        }
       }
        else {
        cout<<"You do not have enough space"<<endl;
        boxes[boxNumber-1].incremented();
        return;
        }

    }
    void setMediumPlant(int boxNumber) {
        if(increment==0) {
        cout<<"This is a large plant that will require 4(2x2) total boxes\n any boxes that had plants in them will be replaced "<<endl;
        cout<<"Would you like to continue(y/n): ";
        char c;
        cin>>c;
        if(c=='y') {
        boxes[boxNumber]=boxes[boxNumber-1];
        boxes[boxNumber+3]=boxes[boxNumber-1];
        boxes[boxNumber+4]=boxes[boxNumber-1];
        countDown(boxNumber);
        countDown((boxNumber+1));
        countDown((boxNumber+4));
        countDown((boxNumber+5));
        increment+=1;
        }
        }
        else {
        cout<<"You do not have enough space"<<endl;
        boxes[boxNumber-1].incremented();
        return;
        }
    }
    int boxArray(int boxNumber) {
        if(1<=boxNumber&&boxNumber<=4)
            return box[0][boxNumber-1];
       else if(5<=boxNumber&&boxNumber<=8)
            return box[1][boxNumber-5];
        else if(9<=boxNumber&&boxNumber<=12)
            return box[2][boxNumber-9];
        else if(13<=boxNumber&&boxNumber<=16)
            return box[3][boxNumber-13];
    }
    void countDown(int boxNumber) {
        if(1<=boxNumber&&boxNumber<=4)
            box[0][boxNumber-1]+=1;
        if(5<=boxNumber&&boxNumber<=8)
            box[1][boxNumber-5]+=1;
        if(9<=boxNumber&&boxNumber<=12)
            box[2][boxNumber-9]+=1;
        if(13<=boxNumber&&boxNumber<=16)
            box[3][boxNumber-13]+=1;
    }
    friend ostream & operator <<(ostream &out, const Garden &g) {
        for(int i=0;i<MAXBOXES;i++)
            out<<"you have "<<g.boxes[i]<<" in box "<<i+1<<endl;
        return out;
    }
};
int main() {
    Garden g;
    g.printPlantsOffered();
    int i;
    cout<<"Press 0 after viewing the full garden to leave program\n\
    enter 1 to continue to program: ";
    cin>>i;
    while(!i==0) {
    g.printBoxMenu();
    cout<<g;
    cout<<"Press 0 to quit or 1 to continue: ";
    cin>>i;
    }

    return 0;
}
