//hidden A force test() to be hidden too

class __attribute__((visibility("hidden"))) A
{
    public :
        int x;
};

template <typename T>
class __attribute__((visibility("default"))) B
{
    public:
    T a;
};

using tempType = B<A>;
tempType test();
