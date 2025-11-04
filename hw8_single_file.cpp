/*
 Alma Marcu - hw08 - single file solution
 John Sterling
 Inheritance
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//contains Protector name and strength, along with a isHired bool
class Lord;
class Protector {
private:
    string name;
    double strength;
    bool alive = true;
    Lord* lord = nullptr;
    //output operator
    friend ostream& operator <<(ostream& os, const Protector& prot);
public:
    Protector(const string& name, double strength) : name(name),
                                                   strength(strength) {}
    //getters for the Noble class to access the warriors name, strength
    const string& getName() const;
    //  whether they are hired or not
    bool isHired() const;
    // returns Protector strength
    double getStrength() const;
    //update indivdual strengths
    void setStrength(double val);
    // checks if alive
    bool isAlive() const;
    // returns lord name
    const string& getLordName() const;
    //runaway method
    void runaway();
    // pure virtual defend method
    virtual void defend() const = 0;
    // assign noble
    void setNoble(Lord* lord);
};
//Wizard class
class Wizard : public Protector {
public:
    Wizard(const string& name, double strength) : 
        Protector(name, strength) {}
        //defend declaration
    void defend() const override;
};
//Warrior class
class Warrior : public Protector {
public:    
    Warrior(const string& name, double strength) :
            Protector(name, strength) {}
            // new defend pure virtual method
    virtual void defend() const = 0;
};
//Archer class
class Archer : public Warrior {
public:
    Archer(const string& name, double strength) :
            Warrior(name, strength) {}
            //defend method
    void defend() const override;
};
//Swordsman class
class Swordsman : public Warrior {
public:
    Swordsman(const string& name, double strength) :
            Warrior(name, strength) {}
            //defend method
    void defend() const override;
};
//Noble class
class Noble {
public:
    Noble(const string& name) : name(name) {}
    //functions to hires, fires, check if a Protector exists/isHired, etc
    //kills noble function
    bool setDead();
    // returns Noble name
    const string& getName() const;
    //battle function and calculating army strength for battles
    void battle(Noble& other);
    virtual void defend() const = 0; // speaking function
    // calculates total army strength
    virtual double calcStrength() const = 0;
    //checks if alive
    bool isAlive() const;
    // weaken pure virtual method
    virtual void weaken(double ratio) = 0;

private:
    string name;
    bool alive = true;
};
//Lord class
class Lord : public Noble {
    //Lord output operator
    friend ostream& operator <<(ostream& os, const Lord& lord);

public:
    Lord(const string& name) : Noble(name){}
    //removes Protector from army
    bool remove(Protector& prot);
    //hires function
    bool hires(Protector& prot);
    //fires function
    bool fires(Protector& prot);
    //check to see if exists in army method
    bool check(const Protector& prot) const;
    //calculate army strength
    double calcStrength() const;
    //weakens protectors
    void weaken(double ratio);
    //defend method
    void defend() const;

private:
    vector<Protector*> army;
    Protector* protector = nullptr;
};
class PersonWithStrengthToFight : public Noble {
    friend ostream& operator<<(ostream& os,
            const PersonWithStrengthToFight& pwstf);
public:
    PersonWithStrengthToFight(const string& name, double strength) :
        Noble(name), strength(strength) {}
        //defend method
    void defend() const;
    //returns strength
    double calcStrength() const;
    //weakens PersonWithStrengthToFight
    void weaken(double ratio);

private:
    double strength;
};
int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins ->120
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hires
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "==========\n";
}


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