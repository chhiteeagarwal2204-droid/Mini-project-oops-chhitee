#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <utility>
using namespace std;

// EXPERIMENT 1
// Data Types, Variables, Constants, Operators and I/O

void experiment1()
{
    cout << "\nEXPERIMENT 1\n";

    int age = 20;
    float marks = 85.5;
    char grade = 'A';
    string name = "Rahul";
    const int year = 2026;

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Marks: " << marks << endl;
    cout << "Grade: " << grade << endl;
    cout << "Year: " << year << endl;

    cout << "Addition: " << age + 5 << endl;
    cout << "Multiplication: " << age * 2 << endl;

    cout << "Enter a number: ";
    int num;
    cin >> num;

    cout << "You entered: " << num << endl;

    cout << "\nGitHub Activity:";
    cout << "\nRepository created and code committed.";
    cout << "\nSuggested commit: Add Experiment 1";
}


// EXPERIMENT 2
// Class, Objects, Access Specifiers and Member Functions

class BankAccount
{
private:
    int accountNumber;
    double balance;

public:
    BankAccount(int a, double b)
    {
        accountNumber = a;
        balance = b;
    }

    void deposit(double amount)
    {
        balance += amount;
        cout << "Amount deposited.\n";
    }

    void display()
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

void experiment2()
{
    cout << "\nEXPERIMENT 2\n";

    BankAccount account(101, 5000);

    account.display();
    account.deposit(2000);
    account.display();
}


// EXPERIMENT 3
// Constructors, Destructors and Rule of Five

class Sample
{
private:
    int *data;

public:

    // Default Constructor
    Sample()
    {
        data = new int(0);
        cout << "Default Constructor\n";
    }

    // Parameterized Constructor
    Sample(int x)
    {
        data = new int(x);
        cout << "Parameterized Constructor\n";
    }

    // Copy Constructor
    Sample(const Sample &s)
    {
        data = new int(*s.data);
        cout << "Copy Constructor\n";
    }

    // Move Constructor
    Sample(Sample &&s) noexcept
    {
        data = s.data;
        s.data = nullptr;
        cout << "Move Constructor\n";
    }

    // Copy Assignment
    Sample& operator=(const Sample &s)
    {
        if (this != &s)
        {
            int *temp = new int(*s.data);
            delete data;
            data = temp;
        }
        cout << "Copy Assignment\n";
        return *this;
    }

    // Move Assignment
    Sample& operator=(Sample &&s) noexcept
    {
        if (this != &s)
        {
            delete data;
            data = s.data;
            s.data = nullptr;
        }
        cout << "Move Assignment\n";
        return *this;
    }

    void display()
    {
        if (data != nullptr)
            cout << "Value: " << *data << endl;
    }

    // Destructor
    ~Sample()
    {
        delete data;
        cout << "Destructor\n";
    }
};

void experiment3()
{
    cout << "\nEXPERIMENT 3\n";

    Sample s1;
    Sample s2(100);
    Sample s3(s2);
    Sample s4(move(s2));

    s1 = s3;
    s1.display();

    s1 = move(s4);
    s1.display();
}


// EXPERIMENT 4
// Single and Multilevel Inheritance

class Person
{
public:
    string name;

    void getPerson()
    {
        cout << "Enter name: ";
        cin >> name;
    }
};

class Student : public Person
{
public:
    int roll;

    void getStudent()
    {
        cout << "Enter roll number: ";
        cin >> roll;
    }
};

class GraduateStudent : public Student
{
public:
    string course;

    void getGraduate()
    {
        cout << "Enter course: ";
        cin >> course;
    }

    void display()
    {
        cout << "\nName: " << name;
        cout << "\nRoll Number: " << roll;
        cout << "\nCourse: " << course << endl;
    }
};

void experiment4()
{
    cout << "\nEXPERIMENT 4\n";

    GraduateStudent s;

    s.getPerson();
    s.getStudent();
    s.getGraduate();
    s.display();
}


// EXPERIMENT 5
// Runtime Polymorphism and Virtual Functions

class Shape
{
public:
    virtual void area() = 0;
};

class Circle : public Shape
{
public:
    void area()
    {
        float r = 5;
        cout << "Circle Area: " << 3.14 * r * r << endl;
    }
};

class Rectangle : public Shape
{
public:
    void area()
    {
        int l = 5, b = 4;
        cout << "Rectangle Area: " << l * b << endl;
    }
};

class Triangle : public Shape
{
public:
    void area()
    {
        int b = 6, h = 4;
        cout << "Triangle Area: " << 0.5 * b * h << endl;
    }
};

void experiment5()
{
    cout << "\nEXPERIMENT 5\n";

    Circle c;
    Rectangle r;
    Triangle t;

    Shape *s;

    s = &c;
    s->area();

    s = &r;
    s->area();

    s = &t;
    s->area();
}


// EXPERIMENT 6
// Function Overloading and Operator Overloading

int add(int a, int b)
{
    return a + b;
}

float add(float a, float b)
{
    return a + b;
}

class Matrix
{
public:
    int a[2][2];

    void input()
    {
        cout << "Enter 4 matrix elements:\n";

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                cin >> a[i][j];
        }
    }

    Matrix operator+(Matrix m)
    {
        Matrix result;

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                result.a[i][j] = a[i][j] + m.a[i][j];
        }

        return result;
    }

    void display()
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
                cout << a[i][j] << " ";

            cout << endl;
        }
    }
};

void experiment6()
{
    cout << "\nEXPERIMENT 6\n";

    cout << "Integer Addition: " << add(10, 20) << endl;
    cout << "Float Addition: " << add(2.5f, 3.5f) << endl;

    Matrix m1, m2, m3;

    cout << "Enter first matrix:\n";
    m1.input();

    cout << "Enter second matrix:\n";
    m2.input();

    m3 = m1 + m2;

    cout << "Sum of Matrices:\n";
    m3.display();
}


// EXPERIMENT 7
// Generic Stack Using Templates

template <class T>
class Stack
{
private:
    vector<T> items;

public:
    void push(T x)
    {
        items.push_back(x);
    }

    void pop()
    {
        if (!items.empty())
        {
            cout << "Popped: " << items.back() << endl;
            items.pop_back();
        }
        else
        {
            cout << "Stack is empty\n";
        }
    }

    void display()
    {
        for (int i = items.size() - 1; i >= 0; i--)
            cout << items[i] << endl;
    }
};

void experiment7()
{
    cout << "\nEXPERIMENT 7\n";

    Stack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    cout << "Integer Stack:\n";
    s1.display();
    s1.pop();

    Stack<float> s2;
    s2.push(2.5);
    s2.push(5.5);

    cout << "\nFloat Stack:\n";
    s2.display();

    Stack<string> s3;
    s3.push("Hello");
    s3.push("C++");

    cout << "\nString Stack:\n";
    s3.display();
}


// EXPERIMENT 8
// STL Containers and Algorithms

void experiment8()
{
    cout << "\nEXPERIMENT 8\n";

    vector<int> marks = {75, 90, 60, 85, 95};

    sort(marks.begin(), marks.end());

    cout << "Sorted Marks:\n";

    for (int x : marks)
        cout << x << " ";

    auto it = find_if(marks.begin(), marks.end(),
                      [](int x) { return x >= 90; });

    if (it != marks.end())
        cout << "\nFirst mark above or equal to 90: " << *it;

    transform(marks.begin(), marks.end(), marks.begin(),
              [](int x) { return x + 5; });

    cout << "\nUpdated Marks:\n";

    for (int x : marks)
        cout << x << " ";

    map<string, int> studentMarks;
    studentMarks["Rahul"] = 85;
    studentMarks["Aman"] = 90;

    cout << "\n\nMap:\n";

    for (auto x : studentMarks)
        cout << x.first << " " << x.second << endl;

    unordered_map<string, int> students;
    students["Riya"] = 95;
    students["Neha"] = 88;

    cout << "\nUnordered Map:\n";

    for (auto x : students)
        cout << x.first << " " << x.second << endl;
}


// EXPERIMENT 9
// Custom Exception Hierarchy

class BankingException : public runtime_error
{
public:
    BankingException(string message)
        : runtime_error(message) {}
};

class InsufficientFunds : public BankingException
{
public:
    InsufficientFunds()
        : BankingException("Insufficient Balance") {}
};

class InvalidAmount : public BankingException
{
public:
    InvalidAmount()
        : BankingException("Invalid Amount") {}
};

class Bank
{
private:
    double balance = 5000;

public:
    void withdraw(double amount)
    {
        if (amount <= 0)
            throw InvalidAmount();

        if (amount > balance)
            throw InsufficientFunds();

        balance -= amount;

        cout << "Withdrawal Successful\n";
        cout << "Remaining Balance: " << balance << endl;
    }
};

void experiment9()
{
    cout << "\nEXPERIMENT 9\n";

    Bank b;

    try
    {
        double amount;

        cout << "Enter withdrawal amount: ";
        cin >> amount;

        b.withdraw(amount);
    }
    catch (InvalidAmount &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (InsufficientFunds &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }
}


// EXPERIMENT 10
// CSV File Handling and File Pointers

void experiment10()
{
    cout << "\nEXPERIMENT 10\n";

    fstream file("students.csv",
                 ios::in | ios::out | ios::trunc);

    if (!file)
    {
        cout << "File opening failed\n";
        return;
    }

    // Writing records
    file << "Name,Marks\n";
    file << "Rahul,85\n";
    file << "Aman,90\n";
    file << "Riya,95\n";

    cout << "Write Position: " << file.tellp() << endl;

    // Using seekp
    file.seekp(0, ios::end);

    file << "Neha,88\n";

    cout << "New Write Position: " << file.tellp() << endl;

    // Using seekg
    file.seekg(0, ios::beg);

    cout << "\nStudent Records:\n";

    string line;

    while (getline(file, line))
    {
        cout << line << endl;
        cout << "Read Position: " << file.tellg() << endl;
    }

    file.close();

    cout << "\nFile operation completed.\n";
}


// MAIN MENU

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== OOP EXPERIMENTS =====\n";

        cout << "1. Basic C++ Concepts\n";
        cout << "2. Classes and Objects\n";
        cout << "3. Constructors and Rule of Five\n";
        cout << "4. Inheritance\n";
        cout << "5. Runtime Polymorphism\n";
        cout << "6. Function and Operator Overloading\n";
        cout << "7. Templates\n";
        cout << "8. STL Containers and Algorithms\n";
        cout << "9. Exception Handling\n";
        cout << "10. File Handling\n";
        cout << "0. Exit\n";

        cout << "\nEnter experiment number: ";
        cin >> choice;

        switch (choice)
        {
            case 1: experiment1(); break;
            case 2: experiment2(); break;
            case 3: experiment3(); break;
            case 4: experiment4(); break;
            case 5: experiment5(); break;
            case 6: experiment6(); break;
            case 7: experiment7(); break;
            case 8: experiment8(); break;
            case 9: experiment9(); break;
            case 10: experiment10(); break;
            case 0: cout << "Program ended.\n"; break;
            default: cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}
