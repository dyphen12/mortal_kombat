#include <iostream>
#include "match.h"
#include "dlclist.hpp"

using namespace std;

class Championship{
    private:
    DLCList<Karateka>* karatekaList;
    DLCList<Match>* section1;
    DLCList<Match>* section2;
    DLCList<Match>* section3;
    DLCList<Match>* section4;
    DLCList<Match>* semiFinals;
    DLCList<Match>* finals;
    DLCList<Match>* firstRound;
    

    int contestants;
    int weight;


    public:
    Championship() {
        cout<<"Championship Started!"<<endl;
        karatekaList = new DLCList<Karateka>();
        firstRound = new DLCList<Match>();
        section1 = new DLCList<Match>();
        section2 = new DLCList<Match>();
        section3 = new DLCList<Match>();
        section4 = new DLCList<Match>();
    }  // Initialize during object creation


    void signUpKarateka(Karateka* karateka) {
    // Add the karateka to the list
    karatekaList->push(karateka);  // Assuming karatekaList is a DLCList object
    }


    void printKaratekaList(){
        cout<<"print karateka list"<<endl;
        Karateka* dummy = new Karateka(1);
        this->karatekaList->printList(dummy);

    }

    void calculateMatches(){

        // Minimum 

        if (this->karatekaList->getLength() >= 8){
            

            if (this->karatekaList->getLength() >= 16){
                cout<<"Setting 4 Section Championship"<<endl;
                cout<<"Opening 1 Round 4 Section"<<endl;

                if (this->karatekaList->getLength() >= 32){
                    cout<<"Setting 4 Section Championship"<<endl;
                    cout<<"Opening 2 Round 4 Section"<<endl;

                    if (this->karatekaList->getLength() <= 64){
                        cout<<"Setting 4 Section Championship"<<endl;
                        cout<<"Opening 3 Round 4 Section"<<endl;

                        cout<<"Karatekas Left Out: "<<64 - this->karatekaList->getLength()<<endl;

                        int karatekasWaiting = 64 - this->karatekaList->getLength();

                        int karatekasForFirstRound = this->karatekaList->getLength() - karatekasWaiting;

                        int aux = 0;

                        for (int i = 1; i <= karatekasForFirstRound; i+=2){
                            //Karateka* KaratekaA = this->karatekaList->pop2();
                            //Karateka* KaratekaB = this->karatekaList->pop2();
                            //cout<<"Processing Match: "<<KaratekaA->getName()<<" VS "<<KaratekaB->getName()<<endl;

                            //Match* newMatch = new Match(KaratekaA,KaratekaB);

                            //this->firstRound->push(newMatch);

                            aux++;
                        }

                        cout<<aux<<" Matches Processed"<<endl;

                        cout<<"Dividing Sections..."<<endl;

                        cout<<"Section 1: "<<(aux/4) + aux%4<<endl;

                        int sec1div = (aux/4) + aux%4;

                        for (int i = 1; i <= sec1div; i++){

                            Karateka* KaratekaA = this->karatekaList->pop2();
                            Karateka* KaratekaB = this->karatekaList->pop2();
                            cout<<"Processing Match: "<<KaratekaA->getName()<<" VS "<<KaratekaB->getName()<<endl;

                            Match* newMatch = new Match(KaratekaA,KaratekaB);

                            this->section1->push(newMatch);

                        }

                        aux = aux - ((aux/4) + aux%4);

                        cout<<"Section 2: "<<(aux/3) + aux%3<<endl;

                        int sec2div = (aux/3) + aux%3;

                        for (int i = 1; i <= sec2div; i++){

                            Karateka* KaratekaA = this->karatekaList->pop2();
                            Karateka* KaratekaB = this->karatekaList->pop2();
                            cout<<"Processing Match: "<<KaratekaA->getName()<<" VS "<<KaratekaB->getName()<<endl;

                            Match* newMatch = new Match(KaratekaA,KaratekaB);

                            this->section2->push(newMatch);

                        }

                        aux = aux - ((aux/3) + aux%3);

                        cout<<"Section 3: "<<(aux/2) + aux%2<<endl;

                        int sec3div = (aux/2) + aux%2;

                        for (int i = 1; i <= sec3div; i++){

                            Karateka* KaratekaA = this->karatekaList->pop2();
                            Karateka* KaratekaB = this->karatekaList->pop2();
                            cout<<"Processing Match: "<<KaratekaA->getName()<<" VS "<<KaratekaB->getName()<<endl;

                            Match* newMatch = new Match(KaratekaA,KaratekaB);

                            this->section3->push(newMatch);

                        }

                        aux = aux - ((aux/2) + aux%2);

                        cout<<"Section 4: "<<(aux/1) + aux%1<<endl;

                        int sec4div = (aux/1) + aux%1;

                        for (int i = 1; i <= sec4div; i++){

                            Karateka* KaratekaA = this->karatekaList->pop2();
                            Karateka* KaratekaB = this->karatekaList->pop2();
                            cout<<"Processing Match: "<<KaratekaA->getName()<<" VS "<<KaratekaB->getName()<<endl;

                            Match* newMatch = new Match(KaratekaA,KaratekaB);

                            this->section4->push(newMatch);

                        }

                        
                        

                    } else {

                        cout<<"Error: 64 Karatekas max for a championship!"<<endl;
                        

                    }

                }



            }


        }
        

        

    }


    void topHalfRun(){
        
    }

    Match* bottomHalfRun(){

        Match* match = section1->pop2();

        return match;

    }

    void finalsRun(){

    }

    int countKaratekas(){
        return this->karatekaList->getLength();

    }

};


