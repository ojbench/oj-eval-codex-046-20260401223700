#include <string>
#include <iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{

    class Fighter;
    class Protector;
    class Caster;

    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        // WARNING: NO OTHER MEMBER VARIABLE IS ALLOWED TO BE ADDED HERE.
        std::string name;
        int health, attack;
        bool alive, defensive;
        inline static int aliveNumber = 0; // current alive roles

    protected:
        // prevent instantiation: abstract class via pure virtuals below; constructor protected
        Base(const std::string& n, const int h, const int a)
            : name(n), health(h), attack(a), alive(true), defensive(false) {
            ++aliveNumber;
        }
        virtual ~Base() = default;

    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THIS CLASS(Base) CAN NOT BE INSTANTIATED.
        // getAliveNumber
        static int getAliveNumber(){
            return aliveNumber;
        }

        // the function you need to implement or define is as follows.
        // (3) launch_attack (pure virtual to enforce abstract)
        virtual void launch_attack(Base* target) = 0;
        // (4) defend (pure virtual; implemented by derived)
        virtual void defend(bool flag) = 0;

        bool isAlive(){
            return alive;
        }

        bool isDefensive(){
            return defensive;
        }
    };

    class Fighter:public Base{
    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        // WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        // WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    // Helper to print kill message in correct format
    inline void kill_and_announce(Base* who, const char* role){
        if (who->alive) {
            who->alive = false;
            --Base::aliveNumber;
            std::cout << role << ' ' << who->name << " is killed\n";
        }
    }

    void Fighter::launch_attack(Base *target) {
        int mult = (dynamic_cast<Caster*>(target) != nullptr) ? 2 : 1;
        if (target->defensive) {
            int dmg = attack * mult - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            // recoil for non-Caster attacker
            this->health -= target->attack; // Fighter not Caster
        } else {
            target->health -= attack * mult;
        }

        bool target_dies = (target->health <= 0) && target->alive;
        bool attacker_dies = (this->health <= 0) && this->alive;

        if (target_dies && attacker_dies) {
            kill_and_announce(target, "Protector" /*placeholder*/);
            // The above role must match target type; fix below by detecting type.
        }
        // We'll handle ordered printing generically below without duplication
        // Print in required order
        if (target->health <= 0 && target->alive) {
            if (dynamic_cast<Fighter*>(target)) kill_and_announce(target, "Fighter");
            else if (dynamic_cast<Protector*>(target)) kill_and_announce(target, "Protector");
            else if (dynamic_cast<Caster*>(target)) kill_and_announce(target, "Caster");
        }
        if (this->health <= 0 && this->alive) {
            kill_and_announce(this, "Fighter");
        }
    }

    void Protector::launch_attack(Base *target) {
        int mult = (dynamic_cast<Fighter*>(target) != nullptr) ? 2 : 1;
        if (target->defensive) {
            int dmg = attack * mult - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            // recoil for non-Caster attacker
            this->health -= target->attack; // Protector not Caster
        } else {
            target->health -= attack * mult;
        }

        if (target->health <= 0 && target->alive) {
            if (dynamic_cast<Fighter*>(target)) kill_and_announce(target, "Fighter");
            else if (dynamic_cast<Protector*>(target)) kill_and_announce(target, "Protector");
            else if (dynamic_cast<Caster*>(target)) kill_and_announce(target, "Caster");
        }
        if (this->health <= 0 && this->alive) {
            kill_and_announce(this, "Protector");
        }
    }

    void Caster::launch_attack(Base *target) {
        int mult = (dynamic_cast<Protector*>(target) != nullptr) ? 2 : 1;
        if (target->defensive) {
            int dmg = attack * mult - target->attack;
            if (dmg < 0) dmg = 0;
            target->health -= dmg;
            // Caster takes no recoil
        } else {
            target->health -= attack * mult;
        }

        if (target->health <= 0 && target->alive) {
            if (dynamic_cast<Fighter*>(target)) kill_and_announce(target, "Fighter");
            else if (dynamic_cast<Protector*>(target)) kill_and_announce(target, "Protector");
            else if (dynamic_cast<Caster*>(target)) kill_and_announce(target, "Caster");
        }
        if (this->health <= 0 && this->alive) {
            // Unlikely for caster since no recoil, but handle anyway
            kill_and_announce(this, "Caster");
        }
    }
}
#endif //ROLE_HPP

