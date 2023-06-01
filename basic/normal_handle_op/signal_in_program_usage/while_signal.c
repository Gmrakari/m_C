#include <stdio.h>
#include <signal.h>
#include <stdbool.h>

static volatile bool exit_flag = false;

static void on_signal(int signo)
{
  if (SIGINT == signo || SIGTSTP == signo || SIGTERM == signo || SIGQUIT == signo || SIGPIPE == signo || SIGKILL == signo)
  {
    exit_flag = 1;
  }
}

int main(int argc, char const *argv[])
{
    /** redefine signal */
    signal(SIGINT, on_signal);
    signal(SIGTERM, on_signal);

    while (1) {
        ;
    }
    return 0;
}
