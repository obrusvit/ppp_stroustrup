template<typename T>
requires true   // True concept
struct Foo
{};

template<typename T>
requires false  // False concept
struct Bar
{};

int main()
{
    Foo<int>(); // Ok
    /* Bar<int>(); // Fail */
    return 0;
}
