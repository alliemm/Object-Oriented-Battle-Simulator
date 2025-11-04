//
// Created by almam on 11/24/2024.
//
#include "Noble.h"
#include "Protector.h"
#include <iostream>
using namespace std;
namespace WarriorCraft {

// Noble's hiring function for warriors goes through all checks first
    bool Lord::hires(Protector& prot) {
        //check = Protector doesnt exist yet or if already hired and if nobles alive
        if (!check(prot) && !prot.isHired() && isAlive()) {
            Protector* p = &prot;
            army.push_back(p);
            //adds a pointer to a Protector to army and sets hired
            prot.setNoble(this);
            return true;
        } else {
            cout << getName() << " failed to hire " << prot.getName() << endl;
            return false;
        }
    }
//Noble's firing function for warriors (does all checks first)
    bool Lord::fires(Protector& prot) {
        //!check means Protector is found in army
        //checks if noble is alive and Protector hired
        if (remove(prot)) {
            cout << prot.getName() << ", you don't work for me any more! -- "
                 << getName() << "." << endl;
            return true;
        }
        cout << getName() << " failed to fires " << prot.getName() << endl;
        return false;
    }
//updates each individual Protector strength
    void Lord::weaken(double ratio) {
        for (Protector* prot : army) {
            if (ratio == 1) {
                prot->setStrength(0);
            } else {
                double newStrength = (prot->getStrength()) * (1-ratio);
                prot->setStrength(prot->getStrength() - newStrength);
            }
        }
    }


//checks to see if a Protector exists in that nobles army
    bool Lord::check(const Protector& protector) const {
        //check if Protector in noble's army
        for (const Protector* p : this->army) {
            if (p == &protector) {
                return true;
            }
        } return false;
    }

//calculates army strength
    double Lord::calcStrength() const {
        double sum = 0;
        for (const Protector* p : army) {
            sum += p->getStrength();
        }
        return sum;
    }
//output operator for Noble
    ostream& operator <<(ostream& os, const Lord& lord) {
        os << lord.getName() << " has an army of size: " << lord.army.size() << endl;
        for (const Protector* p : lord.army) {
            os << "\t" << *p << "\n";
        }
        return os;
    }
//calls indiviual protector defend methods
    void Lord::defend() const {
        for (const Protector* p : army) {
            p->defend();
        }
    }
    bool Noble::setDead() { return alive = false; }
// returns Noble name
    const string& Noble::getName() const { return name; }
    bool Noble::isAlive() const { return alive; }
// battle function
    void Noble::battle(Noble& other) {
        //makes strength variables for easy access
        double strength1, strength2;
        strength1 = this->calcStrength();
        strength2 = other.calcStrength();
//battle starts, checks all the conditions of differing/equal strengths
//then, proceeds to edit the warriors strength in the loop accordingly
// and kills nobles
        cout << getName() << " battles " << other.getName() << endl;
        if (!alive && !other.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else if (!alive) {
            other.defend();
            cout << "He's dead, " << other.getName() << endl;
        } else if (!other.alive) {
            defend();
            cout << "He's dead, " << getName() << endl;
        } else if (strength1 > strength2) {
            defend();
            other.defend();
            other.setDead();
            cout << getName() << " defeats " << other.getName() << endl;
            if (strength1 == 0 || strength2 == 0) {
                return;
            }
            double ratio = 1-(strength2 / strength1);
            weaken(ratio);
            other.weaken(1);
        } else if (strength1 < strength2) {
            defend();
            other.defend();
            cout << other.getName() << " defeats " << getName() << endl;
            setDead();
            if (strength2 == 0 || strength1 == 0) {
                return;
            }
            double ratio = 1-(strength1 / strength2);

            weaken(1);
            other.weaken(ratio);
        } else {
            defend();
            other.defend();
            cout << "Mutual Annihilation: " << getName() << " and " <<
                 other.getName() <<" die at each other's hands" << endl;
            other.setDead();
            setDead();
            weaken(1);
            other.weaken(1);
        }
    }

//removes a Protector from army and checks if allowed to begin p
    bool Lord::remove(Protector& prot) {
        if (isAlive() && prot.isHired() && check(prot)) {
            for (size_t i = 0; i < army.size(); i++) {
                if (army[i] == &prot) {
                    for (size_t j = i; j < army.size()-1; ++j) {
                        army[j] = army[j+1];
                    }
                    army.pop_back();
                    prot.setNoble(nullptr);
                    return true;
                }
            }
        }
        return false;
    }
    void PersonWithStrengthToFight::defend() const {
        cout << "UGH!!!" << endl;
    }
    double PersonWithStrengthToFight::calcStrength() const { return strength; }
    ostream& operator<<(ostream& os, const PersonWithStrengthToFight& pwstf) {
        os << pwstf.getName() << " has strength: " << pwstf.strength << endl;
        return os;
    }
    void PersonWithStrengthToFight::weaken(double ratio) {
        if (ratio == 1) {
            strength = 0;
        } else {
            strength = (strength * (ratio));
        }
    }
}