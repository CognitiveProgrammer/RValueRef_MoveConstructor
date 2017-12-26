/*
* MIT Licence
* Copyright 2017 @9lean
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files(the "Software"), to deal in the 
* Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of the Software, 
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions :
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR 
* ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
* THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* 
* visit https://github.com/9lean/RValueRef_MoveConstructor for description of the code
*/

#include <iostream>
#include <vector>
using namespace std;
struct A {
    A() {
        cout<<"Cons..."<<endl;
    }
    A(const A & a1) {
        cout<<"Copy Cons.."<<endl;
    }
    A(A && a1) noexcept {
        cout<<"Mov Cons.."<<endl;
    }
    ~A() {
        cout<<"Dest..."<<endl;
    }
};

int main() {
    {
        vector<A> v1;
        v1.push_back(A()); // calls Move
    }
    {
        vector<A> v1;
        A a2;
        v1.push_back(a2); // calls Copy
    }
    
    {
        vector<A> v1;
        A a3;
        v1.push_back(move(a3)); // calls Move
    }
 
    return 0;
}
