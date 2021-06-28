#include <iostream>
using namespace std;

#include <Bizarre.h>
#include <BWindow.h>

void start( BStartConfig* config ){
    cout << "Exec: Start Function" << endl;
}

int main(int argc, char* argv[])
{
    return BizarreMain(argc, argv);
}

