#ifndef LAB20_H
#define LAB20_H

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Unit {
    string name;
    string type;
    int hp;
    int hpmax;
    int atk;
    int def;
    bool guard_on;
    bool dodge_on;  // เพิ่มตัวแปรสถานะหลบหลีก

public:
    Unit(); // Default Constructor
    Unit(string, string); // Constructor ที่รับชื่อและประเภท

    void showStatus();
    void newTurn();
    int attack(Unit &);
    int ultimateAttack(Unit &); // ท่าไม้ตาย
    int beAttacked(int);
    int heal(); // เพิ่มฟังก์ชัน heal() คืนค่าพลังที่ฟื้นฟู
    void guard();
    void dodge(); // เพิ่มฟังก์ชัน dodge()
    bool isDead();
};

// Implement heal()
int Unit::heal() {
    int heal_amount = rand() % 21 + 10;  // ฟื้นฟู 10-30 หน่วย
    if (hp + heal_amount > hpmax) {
        heal_amount = hpmax - hp; // จำกัดไม่ให้เกิน max hp
    }
    hp += heal_amount;
    return heal_amount;
}

Unit::Unit(string t, string n) {
    type = t;
    name = n;
    if (t == "Hero") {
        hpmax = rand() % 20 + 90;
        atk = rand() % 5 + 14;
        def = rand() % 3 + 9;
    } else if (t == "Monster") {
        hpmax = rand() % 20 + 200;
        atk = rand() % 5 + 25;
        def = rand() % 3 + 5;
    }
    hp = hpmax;
    guard_on = false;
    dodge_on = false;
}

void Unit::showStatus() {
    cout << "---------------------------------------\n";
    cout << name << "\n";
    cout << "HP: " << hp << "/" << hpmax << "\tATK: " << atk << "\tDEF: " << def;
    cout << "\n---------------------------------------\n";
}

void Unit::newTurn() {
    guard_on = false;
    dodge_on = false;
}

bool Unit::isDead() {
    return hp <= 0;
}

void Unit::guard() {
    guard_on = true;
}

void Unit::dodge() {
    dodge_on = true;
}

int Unit::beAttacked(int oppatk) {
    int dmg;
    if (dodge_on && rand() % 2 == 0) {
        dmg = 0; // หลบได้สำเร็จ
    } else {
        dmg = (oppatk - def);
        if (dodge_on) dmg *= 2; // หลบไม่สำเร็จ โดนดาเมจ x2
        if (guard_on) dmg /= 3; // ถ้าการ์ดอยู่ ลดดาเมจลง
        if (dmg < 0) dmg = 0;
        hp -= dmg;
    }
    return dmg;
}

int Unit::attack(Unit &target) {
    return target.beAttacked(atk);
}

int Unit::ultimateAttack(Unit &target) {
    return target.beAttacked(atk * 2);
}

#endif
