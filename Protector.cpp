//
// Created by almam on 11/24/2024.
//
#include "Protector.h"
#include "Noble.h"
#include <iostream>
using namespace std;
namespace WarriorCraft {

// all comments are above prototypes in classes
    const string& Protector::getLordName() const { return lord->getName(); }
    void Protector::setNoble(Lord* lord) { this->lord = lord; }
    const string& Protector::getName() const { return name; }
    bool Protector::isHired() const{ return (lord != nullptr); }
// returns Protector strength
    double Protector::getStrength() const { return strength; }
//update indivdual strengths
    void Protector::setStrength(double val) { strength = val; }
    bool Protector::isAlive() const { return alive; }
//output operators for Protector
    ostream& operator<<(ostream& os, const Protector& prot) {
        os << prot.name << " has strength " << prot.strength;
        return os;
    }
//warriors runaway function, calls noble
    void Protector::runaway() {
        if (isHired() && isAlive()) {
            cout << getName() << " flees in terror, abandoning his lord, "
                 << lord->getName() << endl;
            lord->remove(*this);
            lord = nullptr;
        }else  {
            cout << name << " failed to run away from " <<
                 lord->getName() << endl;
        }
        cout << endl;
    }
    void Warrior::defend() const  {
        cout << getName() << " says: Take that in the name of my lord, " << getLordName() << endl;
    }
    void Wizard::defend() const {
        cout << "POOF" << endl;
    }
    void Archer::defend() const {
        cout << "TWANG! ";
        Warrior::defend();
    }
    void Swordsman::defend() const {
        cout << "CLANG! ";
        Warrior::defend();

    }

}