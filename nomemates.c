#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handleSignal(int signal) {
    printf("Signal received, %d\n",signal);
}

int main() {
    signal(2, handleSignal); //Ctrl+C
    signal(20, handleSignal); //nombre de la función es como un apuntador a ella
    //Ctrl+Z
    while (1) {
        printf("Trabajando\n");
        sleep(1);
    }
    return 0;
}