#include<iostream>
#include "functor.h"
class Test {
public:
    void printMultipliedByTen(int m) {
        std::cout << "<" << 10*m << "> This finally works!\n";
    }
};
int main() {
    ArgsPack<int, int> packIntInt(4, 5);
    packIntInt.Call([](int, int){std::cout<<"Does it work?\n";});

    Test test;
    ArgsPack<int, Test, int> packIntTestInt(4, std::move(test), 5);
    packIntTestInt.Call([](int, Test&, int){std::cout<<"Yes, it does!\n";});



    Test test1, test2;
    ArgsPack<Test*, Test> packTestTest(&test1, std::move(test2));
    packTestTest.Call([](Test*, Test*){std::cout<<"And even this one!\n";});
    packTestTest.Call([](Test*, Test&){std::cout<<"And even this one!\n";});
    packTestTest.Call([](Test&, Test*){std::cout<<"And even this one!\n";});
    packTestTest.Call([](Test&, Test&){std::cout<<"And even this one!\n";});
    std::cout<<"\n\nLet's test Functors:\n";

    auto sumUpAndWrite = [](float a, float b, std::string s) {
        float c = a + b;
        std::cout << "("<< c << ", " << s << ")\n";
    };
    auto functor1 = make_functor(sumUpAndWrite, 2.5, 17.5, "OMG it also works");
    functor1.Call();

    auto multipleUpAndWriteFirst10Chars = [](float a, float b, std::string s) {
        float c = a * b;
        std::cout << "("<< c << ", " << s[0] << s[1] << s[2] << s[3] << s[4] << s[5] << s[6] << s[7] << s[8] << s[9] << ")\n";
    };
    auto functor2 = make_functor(multipleUpAndWriteFirst10Chars, 2.5, 30.0, "OMG it also works");
    functor2.Call();

    auto functor3 = make_functor(Test::printMultipliedByTen, 25);
    functor3.Call(test1);
    return 0;
}
