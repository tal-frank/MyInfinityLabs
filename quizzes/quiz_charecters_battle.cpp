#include <string>
#include <iostream>

//////////////////////////////////////////////////// classes

class Character
{
public:
    Character(const std::string& name, int health);
    virtual ~Character() = default;
    
    const std::string& GetName() const;
    int GetHealth() const;
    void TakeDamage(int damage);
    
    virtual int attack() const = 0;

private:
    std::string m_name;
    int m_health;
};

class Warrior : public Character
{
public:
    Warrior(const std::string& name, int health, int strength);
    int attack() const override;
private:
    int m_strength;
};

class Mage : public Character
{
public:
    Mage(const std::string& name, int health, int magic_power);
    int attack() const override;
private:
    int m_magic_power;
};

//////////////////////////////////////////////////// implementations

Character::
Character(const std::string& name, int health) : m_name(name),
                                                 m_health(health) {}

const std::string& Character::GetName() const
{
    return m_name;
}

int Character::GetHealth() const
{
    return m_health;
}

void Character::TakeDamage(int damage)
{
    m_health = m_health < damage ? 0 : m_health - damage;
}

Warrior::
Warrior(const std::string& name, int health, int strength) : Character(name, health),
                                                             m_strength(strength) {}

int Warrior::attack() const
{
    return 2 * m_strength;
}

Mage::
Mage(const std::string& name, int health, int magic_power) : Character(name, health),
                                                             m_magic_power(magic_power) {}

int Mage::attack() const
{
    return 3 * m_magic_power;
}

void battle(Character& attacker, Character& defender)
{
    int damage = attacker.attack();
    std::cout << attacker.GetName() << " attacks " << defender.GetName() << " for " << damage << " damage\n";
    
    defender.TakeDamage(damage);
    std::cout << "Final Health:\n" << defender.GetName() << ": " << defender.GetHealth() << "\n";
}

//////////////////////////////////////////////////// main

int main()
{
    Warrior thor("Thor", 100, 15);
    Mage merlin("Merlin", 80, 20);

    battle(thor, merlin);
    battle(merlin, thor);
    return 0;
}