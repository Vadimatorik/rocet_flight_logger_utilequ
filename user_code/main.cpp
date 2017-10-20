#include "main.h"

extern "C" {

int main (void){
    vTaskStartScheduler();
    while ( true ) {};
}

}
