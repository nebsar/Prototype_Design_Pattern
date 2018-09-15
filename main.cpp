#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
using namespace std;

/** Bullet is the base Prototype */
class Bullet {
protected:
    string _bulletName;
    float _speed;
    float _firePower;
    float _damagePower;
    float _direction;

public:

    Bullet() {
    }

    Bullet(string bulletName, float speed, float firePower, float damagePower)
    : _bulletName(bulletName), _speed(speed), _firePower(firePower), _damagePower(damagePower) {
    }

    virtual ~Bullet() {
    }
    virtual unique_ptr<Bullet> clone() = 0;

    void fire(float direction) {
        _direction = direction;

        cout << "Name        : " << _bulletName << endl
                << "Speed       : " << _speed << endl
                << "FirePower   : " << _firePower << endl
                << "DamagePower : " << _damagePower << endl
                << "Direction   : " << _direction << endl << endl;
    }

    void printFeatures() {
        cout << "Name        : " << _bulletName << endl
                << "Speed       : " << _speed << endl
                << "FirePower   : " << _firePower << endl
                << "DamagePower : " << _damagePower << endl
                << "Direction   : " << _direction << endl << endl;
    }
};

/** SimpleBullet is a Concrete Prototype */
class SimpleBullet : public Bullet {
public:

    SimpleBullet(string bulletName, float speed, float firePower, float damagePower) :
    Bullet(bulletName, speed, firePower, damagePower) {
    }

    unique_ptr<Bullet> clone() override {
        return make_unique<SimpleBullet>(*this);
    }
};

/** GoodBullet is the Concrete Prototype */
class GoodBullet : public Bullet {
public:

    GoodBullet(string bulletName, float speed, float firePower, float damagePower)
    : Bullet(bulletName, speed, firePower, damagePower) {
    }

    unique_ptr<Bullet> clone() override {
        return std::make_unique<GoodBullet>(*this);
    }
};

/** Opaque Bullet type, avoids exposing concrete implementations */
enum BulletType {
    SIMPLE,
    GOOD
};

/** BulletFactory is the client */
class BulletFactory {
private:
    unordered_map<BulletType, unique_ptr<Bullet>, hash<int> > m_Bullets;

public:

    BulletFactory() {
        m_Bullets[SIMPLE] = make_unique<SimpleBullet>("Simple Bullet", 50, 75, 75);
        m_Bullets[GOOD] = make_unique<GoodBullet>("Good Bullet", 75, 100, 100);
    }

    unique_ptr<Bullet> createBullet(BulletType BulletType) {
        return m_Bullets[BulletType]->clone();
    }
};

int main() {
    BulletFactory bulletFactory;

    auto bullet = bulletFactory.createBullet(SIMPLE);
    bullet->fire(90);

    auto bullet2 = bulletFactory.createBullet(GOOD);
    bullet2->fire(100);

    auto bullet3 = bulletFactory.createBullet(SIMPLE);
    bullet3->fire(180);

    auto bullet4 = bulletFactory.createBullet(GOOD);
    bullet4->fire(65);

    bullet->printFeatures();
    bullet2->printFeatures();
    bullet3->printFeatures();
    bullet4->printFeatures();
}