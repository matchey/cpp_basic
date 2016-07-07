#include <vector>
#include <utility>
#include <string>
#include <algorithm>

struct Container
{
    Container(int c) : _c(c) { }
    int _c;
};

struct comp
{
    comp(std::string const& s) : _s(s) { }

    bool operator () (std::pair<std::string, Container> const& p)
    {
        return (p.first == _s);
    }

    std::string _s;
};

#include <iostream>

int main()
{
    typedef std::vector<std::pair<std::string, Container> > my_vector;
    my_vector v;
    v.push_back(std::make_pair("Hello", Container(42)));
    v.push_back(std::make_pair("World", Container(1729)));
    my_vector::iterator i = std::find_if(v.begin(), v.end(), comp("World"));
    if (i != v.end())
    {
        Container& c = i->second;
        std::cout << c._c; // <== Prints 1729
    }
}
