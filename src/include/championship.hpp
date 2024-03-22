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

    DLCList<Match>* section1SecondRound;
    DLCList<Match>* section2SecondRound;
    DLCList<Match>* section3SecondRound;
    DLCList<Match>* section4SecondRound;

    DLCList<Match>* section1ThirdRound;
    DLCList<Match>* section2ThirdRound;
    DLCList<Match>* section3ThirdRound;
    DLCList<Match>* section4ThirdRound;

    DLCList<Match>* section1QuarterFinals;
    DLCList<Match>* section2QuarterFinals;
    DLCList<Match>* section3QuarterFinals;
    DLCList<Match>* section4QuarterFinals;

    DLCList<Match>* sectionSemiFinals;

    DLCList<Match>* sectionFinals;

    DLCList<Match>* simulatedMatches;

    bool firstRound = false;
    bool secondRound = false;
    bool thirdRound = false;
    bool quarterFinals = false;
    bool semiFinals = false;
    bool finals = false;


    int contestants;
    int weight;


    public:
    Championship() {
        cout<<"Championship Started!"<<endl;
        karatekaList = new DLCList<Karateka>();
        section1 = new DLCList<Match>();
        section2 = new DLCList<Match>();
        section3 = new DLCList<Match>();
        section4 = new DLCList<Match>();

        section1SecondRound = new DLCList<Match>();
        section2SecondRound = new DLCList<Match>();
        section3SecondRound = new DLCList<Match>();
        section4SecondRound = new DLCList<Match>();

        section1ThirdRound = new DLCList<Match>();
        section2ThirdRound = new DLCList<Match>();
        section3ThirdRound = new DLCList<Match>();
        section4ThirdRound = new DLCList<Match>();

        section1QuarterFinals = new DLCList<Match>();
        section2QuarterFinals = new DLCList<Match>();
        section3QuarterFinals = new DLCList<Match>();
        section4QuarterFinals = new DLCList<Match>();

        sectionSemiFinals = new DLCList<Match>();

        sectionFinals = new DLCList<Match>();





        simulatedMatches = new DLCList<Match>();

        firstRound = true;
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

        Match* match = this->section1->pop2();

        return match;

    }

    int getMatchesLeft(){
        return this->section1->getLength();
    }

    void finalsRun(){

    }

    void retrieveMatches(Match* simulatedMatch){

        this->simulatedMatches->push(simulatedMatch);

    }

    Match* simulateChampionship(){

        if(this->section1->getMatchWithNoWinner() != NULL){

            return this->section1->getMatchWithNoWinner();

        } else if(this->section2->getMatchWithNoWinner() != NULL){

            return this->section2->getMatchWithNoWinner();

        } else if (this->section3->getMatchWithNoWinner() != NULL){

            return this->section3->getMatchWithNoWinner();

        } else if(this->section4->getMatchWithNoWinner() != NULL){

            return this->section4->getMatchWithNoWinner();

        } else {
            //cout<<"First Round Ended!"<<endl;
            

            if (!secondRound){
                secondRoundSetup();
                secondRound = true;
                cout<<"Second Round Started!"<<endl;
            }

            if(this->section1SecondRound->getMatchWithNoWinner() != NULL){

                return this->section1SecondRound->getMatchWithNoWinner();

            } else if(this->section2SecondRound->getMatchWithNoWinner() != NULL){

                return this->section2SecondRound->getMatchWithNoWinner();

            } else if(this->section3SecondRound->getMatchWithNoWinner() != NULL){

                return this->section3SecondRound->getMatchWithNoWinner();

            } else if(this->section4SecondRound->getMatchWithNoWinner() != NULL){

                return this->section4SecondRound->getMatchWithNoWinner();

            } else {

                if (!thirdRound){
                    thirdRoundSetup();
                    thirdRound = true;
                    cout<<"Third Round Started!"<<endl;
                }

                if(this->section1ThirdRound->getMatchWithNoWinner() != NULL){

                    return this->section1ThirdRound->getMatchWithNoWinner();

                } else if(this->section2ThirdRound->getMatchWithNoWinner() != NULL){

                    return this->section2ThirdRound->getMatchWithNoWinner();

                } else if(this->section3ThirdRound->getMatchWithNoWinner() != NULL){

                    return this->section3ThirdRound->getMatchWithNoWinner();

                } else if(this->section4ThirdRound->getMatchWithNoWinner() != NULL){

                    return this->section4ThirdRound->getMatchWithNoWinner();

                } else {

                    if (!quarterFinals){
                        quarterFinalsSetup();
                        quarterFinals = true;
                        cout<<"Quarter Finals Started!"<<endl;
                    }

                    if(this->section1QuarterFinals->getMatchWithNoWinner() != NULL){

                        return this->section1QuarterFinals->getMatchWithNoWinner();

                    } else if(this->section2QuarterFinals->getMatchWithNoWinner() != NULL){

                        return this->section2QuarterFinals->getMatchWithNoWinner();

                    } else if(this->section3QuarterFinals->getMatchWithNoWinner() != NULL){

                        return this->section3QuarterFinals->getMatchWithNoWinner();

                    } else if(this->section4QuarterFinals->getMatchWithNoWinner() != NULL){

                        return this->section4QuarterFinals->getMatchWithNoWinner();

                    } else {

                        if (!semiFinals){
                            semiFinalsSetup();
                            semiFinals = true;
                            cout<<"Semi Finals Started!"<<endl;
                        }

                        if(this->sectionSemiFinals->getMatchWithNoWinner() != NULL){

                            return this->sectionSemiFinals->getMatchWithNoWinner();

                        } else {
                            if (!finals){
                                finalsSetup();
                                finals = true;
                                cout<<"Finals Started!"<<endl;
                            }

                            if(this->sectionFinals->getMatchWithNoWinner() != NULL){

                                return this->sectionFinals->getMatchWithNoWinner();

                            } else {
                                cout<<"*********************************"<<endl;
                                cout<<"The winner of the championship is"<<endl;
                                cout<<sectionFinals->pop2()->getWinner()->getName()<<endl;
                                cout<<"*********************************"<<endl;
                                return NULL;
                            }    
                        }
                    }
                }

                
            }
        }


    }

    void secondRoundSetup(){

        bool setupDone = false;

        cout<<"Section 1: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section1->pop2();
            Match* simulatedMatchB = this->section1->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section1SecondRound->push(newMatch);
            if(this->section1SecondRound->getLength() == 4){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 2: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section2->pop2();
            Match* simulatedMatchB = this->section2->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section2SecondRound->push(newMatch);
            if(this->section2SecondRound->getLength() == 4){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 3: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section3->pop2();
            Match* simulatedMatchB = this->section3->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section3SecondRound->push(newMatch);
            if(this->section3SecondRound->getLength() == 4){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 4: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section4->pop2();
            Match* simulatedMatchB = this->section4->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section4SecondRound->push(newMatch);
            if(this->section4SecondRound->getLength() == 4){
                setupDone = true;
            }
        }
        
        
    }

    
    void thirdRoundSetup(){

        bool setupDone = false;

        cout<<"Section 1: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section1SecondRound->pop2();
            Match* simulatedMatchB = this->section1SecondRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section1ThirdRound->push(newMatch);
            if(this->section1ThirdRound->getLength() == 2){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 2: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section2SecondRound->pop2();
            Match* simulatedMatchB = this->section2SecondRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section2ThirdRound->push(newMatch);
            if(this->section2ThirdRound->getLength() == 2){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 3: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section3SecondRound->pop2();
            Match* simulatedMatchB = this->section3SecondRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section3ThirdRound->push(newMatch);
            if(this->section3ThirdRound->getLength() == 2){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 4: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section4SecondRound->pop2();
            Match* simulatedMatchB = this->section4SecondRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section4ThirdRound->push(newMatch);
            if(this->section4ThirdRound->getLength() == 2){
                setupDone = true;
            }
        }
        
        
    }

    void quarterFinalsSetup(){

        bool setupDone = false;

        cout<<"Section 1: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section1ThirdRound->pop2();
            Match* simulatedMatchB = this->section1ThirdRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section1QuarterFinals->push(newMatch);
            if(this->section1QuarterFinals->getLength() == 1){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 2: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section2ThirdRound->pop2();
            Match* simulatedMatchB = this->section2ThirdRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section2QuarterFinals->push(newMatch);
            if(this->section2QuarterFinals->getLength() == 1){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 3: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section3ThirdRound->pop2();
            Match* simulatedMatchB = this->section3ThirdRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section3QuarterFinals->push(newMatch);
            if(this->section3QuarterFinals->getLength() == 1){
                setupDone = true;
            }
        }

        setupDone = false;

        cout<<"Section 4: "<<endl;

        while (!setupDone){
            Match* simulatedMatchA = this->section4ThirdRound->pop2();
            Match* simulatedMatchB = this->section4ThirdRound->pop2();
            Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
            cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
            this->section4QuarterFinals->push(newMatch);
            if(this->section4QuarterFinals->getLength() == 1){
                setupDone = true;
            }
        }
        
        
    }


    void semiFinalsSetup(){

        cout<<"Semifinal 1: "<<endl;

        Match* simulatedMatchA = this->section1QuarterFinals->pop2();
        Match* simulatedMatchB = this->section2QuarterFinals->pop2();
        Match* newMatchA = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
        cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
        this->sectionSemiFinals->push(newMatchA);

        cout<<"Semifinal 2: "<<endl;

        Match* simulatedMatchC = this->section3QuarterFinals->pop2();
        Match* simulatedMatchD = this->section4QuarterFinals->pop2();
        Match* newMatchB = new Match(simulatedMatchC->getWinner(), simulatedMatchD->getWinner());
            
        cout<<"Processing Match: "<<simulatedMatchC->getWinner()->getName()<<" VS "<<simulatedMatchD->getWinner()->getName()<<endl;
        this->sectionSemiFinals->push(newMatchB);
        
    }

    void finalsSetup(){

        cout<<"Finals: "<<endl;

        Match* simulatedMatchA = this->sectionSemiFinals->pop2();
        Match* simulatedMatchB = this->sectionSemiFinals->pop2();
        Match* newMatch = new Match(simulatedMatchA->getWinner(), simulatedMatchB->getWinner());
            
        cout<<"Processing Match: "<<simulatedMatchA->getWinner()->getName()<<" VS "<<simulatedMatchB->getWinner()->getName()<<endl;
        this->sectionFinals->push(newMatch);
        
    }

    int countKaratekas(){
        return this->karatekaList->getLength();

    }

};


