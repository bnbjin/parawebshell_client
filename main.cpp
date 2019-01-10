#include <iostream>

#include <unistd.h>
#include <signal.h>

using namespace std;




void sigfunc_dispatcher(int signo)
{
    if (SIGUSR1 == signo)
    {
        cout << "catch signal usr 1" << endl;
    }
    else if (SIGUSR2 == signo)
    {
        cout << "catch signal usr 2" << endl;
    }
    else 
    {
        cout << "catch unkown signal" << endl;
    }
}


// extern char *sys_siglist[];


int main(int argc, char *argv[])
{
    //sighandler_t sigfn_usr1 = signal(SIGUSR1, sigfunc_dispatcher);
    //sighandler_t sigfn_usr2 = signal(SIGUSR2, sigfunc_dispatcher);

    //cout << "old sigfn_usr1: " << sigfn_usr1 << endl;
    //cout << "old sigfn_usr2: " << sigfn_usr2 << endl;

    psignal(SIGUSR1, "hello");

    size_t i = 1;
    while (sys_siglist[i])
    {
        cout << i << " : " << sys_siglist[i] << endl;

        ++i;
    }

    sleep(300);

    return 0;
}
