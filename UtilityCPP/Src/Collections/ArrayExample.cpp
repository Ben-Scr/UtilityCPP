#include <iostream>

using namespace std;

class Foo
{
private:
    int* array, size;

public:
    Foo(int s)
    {
        size = s;
        array = new int[size] {0};
    }

    // copy constructor
    // Foo f(g); where g is a Foo
    // Foo f = g;
    Foo(const Foo& rhs)
    {
        cout << "Copy constructor executes." << endl;
        size = rhs.size;
        array = new int[size];

        for (int i = 0; i < size; i++)
            array[i] = rhs.array[i];
    }

    // move constructor
    // for dealing r-values...
    Foo(Foo&& rhs) noexcept
    {
        cout << "move constructor executes." << endl;
        size = rhs.size;
        array = rhs.array;
        rhs.array = nullptr;
    }

    ~Foo()
    {
        if (array)
            delete[] array;
    }

    // f + g; cause an r-value to be created
    Foo operator+(const Foo& rhs)
    {
        Foo temp(size + rhs.size);

        auto i = 0;
        for (; i < size; i++)
            temp[i] = array[i];

        for (auto j = 0; j < rhs.size; i++, j++)
            temp[i] = rhs.array[j];

        return temp;
    }

    // f = g;
    Foo& operator=(const Foo& rhs)
    {
        cout << "Copy assignment operator executes." << endl;
        if (this == &rhs)
            return *this;

        if (array)
            delete[] array;

        size = rhs.size;
        array = new int[size];

        for (int i = 0; i < size; i++)
            array[i] = rhs.array[i];

        return *this;
    }

    // move assignment operator
    Foo& operator=(Foo&& rhs) noexcept
    {
        cout << "move assignment operator executes." << endl;

        if (this != &rhs) {
            size = rhs.size;
            array = rhs.array;
            rhs.array = nullptr;
            rhs.size = 0;
        }

        return *this;
    }

    int& operator[](int i)
    {
        return array[i];
    }

    int length() const
    {
        return size;
    }

    friend ostream& operator<<(ostream& o, const Foo& rhs)
    {
        for (int i = 0; i < rhs.size; i++)
            o << rhs.array[i] << " ";

        return o;
    }
};

int main_2()
{
    Foo f(5);

    for (int i = 0; i < f.length(); i++)
        f[i] = 3 * i;

    cout << f << endl;

    Foo g(f);
    cout << g << endl;

    Foo h(3);

    cout << h << endl;

    // f + g creates an r-value...that's an unnamed memory location that is TEMPORARY.
    // that temp r-value...
    h = f + g;

    cout << h << endl;

    cin.get();
    return 0;
}
