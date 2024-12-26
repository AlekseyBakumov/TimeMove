#include <iostream>

class Time
{
    int hours, minutes, seconds;
    static unsigned int counter;

public:
    Time() noexcept
    {
        hours = 0;
        minutes = 0;
        seconds = 0;
        counter++;
        std::cout << "Time object created using default constructor. Current counter: " << counter << std::endl;
    }
    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s)
    {
        if (h < 0 || h > 24 ||
            m < 0 || m > 60 ||
            s < 0 || s > 60)
            throw std::invalid_argument("Invalid argument for constructor");
        Normalize();
        counter++;
        std::cout << "Time object created using initializing constructor. Current counter: " << counter << std::endl;
    }
    Time(const Time& t) noexcept : hours(t.GetHours()), minutes(t.GetMinutes()), seconds(t.GetSeconds())
    {
        Normalize();
        counter++;
        std::cout << "Time object created using copy constructor. Current counter: " << counter << std::endl;
    }
    Time(Time&& moved) noexcept {
        if (&moved != this) {
            hours = moved.hours;
            minutes = moved.minutes;
            seconds = moved.seconds;
        }
        Normalize();
        counter++;
        std::cout << "Time object created using move constructor. Current counter: " << counter << std::endl;
    }
    ~Time() noexcept
    {
        counter--;
        std::cout << "Time object destroyed. Current counter: " << counter << std::endl;
    }

    int GetHours() const { return hours; }
    int GetMinutes() const { return minutes; }
    int GetSeconds() const { return seconds; }

    void SetHours(int h)
    {
        if (h < 0 || h > 24)
            throw std::invalid_argument("Invalid argument for set function");
        hours = h;

    }
    void SetMinutes(int m)
    {
        if (m < 0 || m > 60)
            throw std::invalid_argument("Invalid argument for set function");
        minutes = m;

    }
    void SetSeconds(int s)
    {
        if (s < 0 || s > 60)
            throw std::invalid_argument("Invalid argument for set function");
        seconds = s;

    }

    void PrintTime() noexcept {
        std::cout
            << "H:" << this->GetHours()
            << " M:" << this->GetMinutes()
            << " S:" << this->GetSeconds()
            << std::endl;
    }

    static int GetCount() { return counter; }

    void Normalize() noexcept {
        minutes += seconds / 60;
        seconds %= 60;
        hours += minutes / 60;
        minutes %= 60;
        hours %= 24;

        if (seconds < 0)
        {
            seconds += 60;
            minutes--;
        }

        if (minutes < 0)
        {
            minutes += 60;
            hours--;
        }

        if (hours < 0)
        {
            hours += 24;
        }
    }

    int ToSeconds() { return ((GetHours() * 60) + GetMinutes()) * 60 + GetSeconds(); }

    Time operator+ (int s) noexcept
    {
        return Time(GetHours(), GetMinutes(), GetSeconds() + s);
    }
    Time operator+= (int s) noexcept
    {
        seconds += s;
        Normalize();
        return *this;
    }
    Time operator- (int s) noexcept
    {
        return Time(GetHours(), GetMinutes(), GetSeconds() - s);
    }
    Time operator-= (int s) noexcept
    {
        seconds -= s;
        Normalize();
        return *this;
    }

    Time& operator= (const Time& other) noexcept {
        hours = other.hours;
        minutes = other.minutes;
        seconds = other.seconds;
        return *this;
    }
    Time& operator=(Time&& moved) noexcept {
        std::cout << "Move operator" << std::endl;
        if (&moved != this) {
            hours = moved.hours;
            minutes = moved.minutes;
            seconds = moved.seconds;
        }
        return *this;
    }

    bool operator== (const Time& t) noexcept
    {
        return (GetSeconds() == t.GetSeconds()
            && GetMinutes() == t.GetMinutes()
            && GetSeconds() == t.GetSeconds());
    }
    bool operator!= (const Time& t) noexcept
    {
        return !(*this == t);
    }
    bool operator< (const Time& t) noexcept
    {
        if (GetHours() < t.GetHours()) return true;
        if (GetHours() > t.GetHours()) return false;
        if (GetMinutes() < t.GetMinutes()) return true;
        if (GetMinutes() > t.GetMinutes()) return false;
        if (GetSeconds() < t.GetSeconds()) return true;
        return false;
    }
    bool operator> (const Time& t) noexcept
    {
        return (!(*this < t)) && (*this != t);
    }
    bool operator<= (const Time& t) noexcept
    {
        return !(*this > t);
    }
    bool operator>= (const Time& t) noexcept
    {
        return !(*this < t);
    }
};

unsigned int Time::counter = 0;


int main()
{
    Time t3;
    std::cout << std::endl;
    {
        Time t1(5, 10, 0);
        std::cout << "Rvalue constructor" << std::endl;
        Time t2(t1);

        std::cout << "Rvalue operator=" << std::endl;
        t3 = t1;
        std::cout << "End1" << std::endl;
    }

    {
        std::cout << "Lvalue constructor" << std::endl;
        Time t2(std::move(Time(5,10,2)));

        std::cout << "Lvalue operator=" << std::endl;
        t3 = std::move(Time(5, 10, 0));
        std::cout << "End2" << std::endl;
    }

    return 0;
}