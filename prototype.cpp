#include <iostream>
#include <unordered_map> // https://codeforces.com/blog/entry/4710
using namespace std;

// Абстрактный класс Животное - Прототип
class Animal {
public:
    virtual ~Animal() {}
    virtual Animal* Clone() const = 0;
    virtual void MakeSound() const = 0;
};

// Конкретный класс Прототипа - овечка
class Sheep : public Animal {
public:
    Sheep(string name, string color) : name_(name), color_(color) {}

    Animal* Clone() const override {
        return new Sheep(*this);
    }

    void MakeSound() const override {
        cout << "Бее-ее!\n";
    }

    void SetName(string name) {
        name_ = name;
    }

    void SetColor(string color) {
        color_ = color;
    }

    void ShowInfo() const {
        cout << "Кличка: " << name_ << ", цвет: " << color_ << endl;
    }

private:
    string name_;
    string color_;
};

// Прототип фабрики
class AnimalFactory {
public:
    AnimalFactory() {
        prototypes["sheep"] = new Sheep("Долли", "белый");
    }

    ~AnimalFactory() {
        for (auto it : prototypes) {
            delete it.second; // https://stackoverflow.com/questions/15451287/what-does-iterator-second-mean
        }
    }

    Animal* CreateAnimal(const string& name) {
        return prototypes[name]->Clone();
    }

private:
    unordered_map<string, Animal*> prototypes;
};

int main() {
    setlocale(0, "");

    AnimalFactory factory;
    Animal* original = factory.CreateAnimal("sheep");
    Animal* clone = original->Clone();

    cout << "Оригинальное животное:\n";
    original->MakeSound(); // выводит: Бееее!

    if (Sheep* sheep = dynamic_cast<Sheep*>(original)) {
        sheep->ShowInfo(); // выводит: кличка: Долли, цвет: белый
        sheep->SetName("Молли"); // меняем состояние оригинала
        sheep->SetColor("чёрный");
    }

    cout << "\nКлонированное животное:" << endl;
    clone->MakeSound(); // выводит: Бееее!
    if (Sheep* sheep = dynamic_cast<Sheep*>(clone)) {
        sheep->ShowInfo(); // выводит: Name: Долли, Color: белый
    }

    cout << "\nПроверка данных оригинала (который уже успел изменить состояние):\n";
    if (Sheep* sheep = dynamic_cast<Sheep*>(original)) {
        sheep->ShowInfo();
    }

    delete original;
    delete clone;
}

/*
Код реализует паттерн "Прототип" для создания объектов,
используя уже существующие объекты в качестве прототипов.
В коде определены следующие классы:
1) Абстрактный класс Animal - Прототип, имеющий два чисто
виртуальных метода Clone() и MakeSound().
Clone() возвращает копию объекта, а MakeSound()
выводит звук, издаваемый животным.

2) Конкретный класс Sheep, наследуемый от Animal.
Класс Sheep представляет овечку, имеющую кличку и цвет,
а также методы SetName(), SetColor() и ShowInfo(),
которые позволяют установить/изменить имя и цвет
овечки, а также вывести информацию о ней.

3) Класс AnimalFactory, представляющий фабрику животных.
В конструкторе фабрики создается объект-прототип
для овечки, а в методе CreateAnimal() на основе этого
прототипа создается новый объект.

В функции main() создается фабрика AnimalFactory,
затем создаются оригинальный и клонированный объекты
овечки, и для каждого из них вызывается метод
MakeSound(). Далее происходит проверка на то,
является ли оригинал объектом класса Sheep, и если да,
то его имя и цвет меняются. Затем выводится информация
об оригинале и клоне, а также проверяется, были ли
изменены данные оригинала.
*/

// https://refactoring.guru/ru/design-patterns/prototype

/*
Прототип — это порождающий паттерн проектирования,
который позволяет копировать объекты, не вдаваясь
в подробности их реализации.
*/