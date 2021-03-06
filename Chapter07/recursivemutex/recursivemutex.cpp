/* recursivemutex.cpp */
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

struct Math
{
    recursive_mutex mtx;
    int m_content;

    Math() : m_content(1)
    {
    }

    // This method will lock the mutex
    void Multiplexer(int i)
    {
        lock_guard<recursive_mutex> lock(mtx);
        m_content *= i;
        cout << "Multiplexer() is called. m_content = ";
        cout << m_content << endl;
    }

    // This method will lock the mutex also
    void Divisor(int i)
    {
        lock_guard<recursive_mutex> lock(mtx);
        m_content /= i;
        cout << "Divisor() is called. m_content = ";
        cout << m_content << endl;
    }

    // This method will invoke 
    // the two preceding methods
    // which each method locks the mutex
    void RunAll(int a)
    {
        lock_guard<recursive_mutex> lock(mtx);
        Multiplexer(a);
        Divisor(a);
    }
};

auto main() -> int
{
    cout << "[recursivemutex.cpp]" << endl;

    // Instantiating Math struct
    // and invoking the RunAll() method 
    Math math;
    math.RunAll(10);

    return 0;
}