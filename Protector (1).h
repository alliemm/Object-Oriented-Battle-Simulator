//
// Created by almam on 11/24/2024.
//

#ifndef HW8_PROTECTOR_H
#define HW8_PROTECTOR_H
#include <string>
#include <ostream>

namespace WarriorCraft {
    //contains Protector name and strength, along with a isHired bool

    class Lord;
    class Protector {
    private:
        std::string name;
        double strength;
        bool alive = true;
        Lord *lord = nullptr;

        //output operator
        friend std::ostream &operator<<(std::ostream &os, const Protector &prot);

    public:
        Protector(const std::string &name, double strength) : name(name),
                                                         strength(strength) {}

        //getters for the Noble class to access the warriors name, strength
        const std::string &getName() const;

        //  whether they are hired or not
        bool isHired() const;

        // returns Protector strength
        double getStrength() const;

        //update indivdual strengths
        void setStrength(double val);

        // checks if alive
        bool isAlive() const;

        // returns lord name
        const std::string &getLordName() const;

        //runaway method
        void runaway();

        // pure virtual defend method
        virtual void defend() const = 0;

        // assign noble
        void setNoble(Lord *lord);
    };

//Wizard class
    class Wizard : public Protector {
    public:
        Wizard(const std::string& name, double strength) :
                Protector(name, strength) {}
        //defend declaration
        void defend() const override;
    };
//Warrior class
    class Warrior : public Protector {
    public:
        Warrior(const std::string& name, double strength) :
                Protector(name, strength) {}
        // new defend pure virtual method
        virtual void defend() const = 0;
    };
//Archer class
    class Archer : public Warrior {
    public:
        Archer(const std::string& name, double strength) :
                Warrior(name, strength) {}
        //defend method
        void defend() const override;
    };
//Swordsman class
    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string& name, double strength) :
                Warrior(name, strength) {}
        //defend method
        void defend() const override;
    };
}
#endif //HW8_PROTECTOR_H
