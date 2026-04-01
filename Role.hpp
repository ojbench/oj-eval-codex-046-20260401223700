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

        // Make destructor public virtual to allow deletion via Base*
        virtual ~Base() = default;

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

        // Determine death order: target first, then attacker
        auto role_name = [](Base* ptr)->const char*{
            if (dynamic_cast<Fighter*>(ptr)) return "Fighter";
            if (dynamic_cast<Protector*>(ptr)) return "Protector";
            return "Caster";
        };

        if (target->health <= 0 && target->alive) {
            target->alive = false;
            --Base::aliveNumber;
            std::cout << role_name(target) << ' ' << target->name << " is killed\n";
        }
        if (this->health <= 0 && this->alive) {
            this->alive = false;
            --Base::aliveNumber;
            std::cout << role_name(this) << ' ' << this->name << " is killed\n";
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

        auto role_name = [](Base* ptr)->const char*{
            if (dynamic_cast<Fighter*>(ptr)) return "Fighter";
            if (dynamic_cast<Protector*>(ptr)) return "Protector";
            return "Caster";
        };
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            --Base::aliveNumber;
            std::cout << role_name(target) << ' ' << target->name << " is killed\n";
        }
        if (this->health <= 0 && this->alive) {
            this->alive = false;
            --Base::aliveNumber;
            std::cout << role_name(this) << ' ' << this->name << " is killed\n";
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

        auto role_name = [](Base* ptr)->const char*{
            if (dynamic_cast<Fighter*>(ptr)) return "Fighter";
            if (dynamic_cast<Protector*>(ptr)) return "Protector";
            return "Caster";
        };
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            --Base::aliveNumber;
            std::cout << role_name(target) << ' ' << target->name << " is killed\n";
        }
        if (this->health <= 0 && this->alive) {
            this->alive = false;
            --Base::aliveNumber;
            std::cout << role_name(this) << ' ' << this->name << " is killed\n";
        }
    }
}
#endif //ROLE_HPP
