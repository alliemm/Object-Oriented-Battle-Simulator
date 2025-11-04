//
// Created by almam on 11/24/2024.
//

#ifndef HW8_NOBLE_H
#define HW8_NOBLE_H
#include <string>
#include <vector>
#include <ostream>
//Noble class
namespace WarriorCraft {
    class Protector;

    class Noble {
    public:
        Noble(const std::string &name) : name(name) {}

        //functions to hires, fires, check if a Protector exists/isHired, etc
        //kills noble function
        bool setDead();

        // returns Noble name
        const std::string &getName() const;

        //battle function and calculating army strength for battles
        void battle(Noble &other);

        virtual void defend() const = 0; // speaking function
        // calculates total army strength
        virtual double calcStrength() const = 0;

        //checks if alive
        bool isAlive() const;

        // weaken pure virtual method
        virtual void weaken(double ratio) = 0;

    private:
        std::string name;
        bool alive = true;
    };

//Lord class
    class Lord : public Noble {
        //Lord output operator
        friend std::ostream &operator<<(std::ostream &os, const Lord &lord);

    public:
        Lord(const std::string &name) : Noble(name) {}

        //removes Protector from army
        bool remove(Protector &prot);

        //hires function
        bool hires(Protector &prot);

        //fires function
        bool fires(Protector &prot);

        //check to see if exists in army method
        bool check(const Protector &prot) const;

        //calculate army strength
        double calcStrength() const;

        //weakens protectors
        void weaken(double ratio);

        //defend method
        void defend() const;

    private:
        std::vector<Protector *> army;
        Protector *protector = nullptr;
    };

    class PersonWithStrengthToFight : public Noble {
        friend std::ostream &operator<<(std::ostream &os,
                                        const PersonWithStrengthToFight &pwstf);

    public:
        PersonWithStrengthToFight(const std::string &name, double strength) :
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
}
#endif //HW8_NOBLE_H
