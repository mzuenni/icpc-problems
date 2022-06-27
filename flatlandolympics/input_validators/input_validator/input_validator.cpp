#include "validation.h"
#define max_x 1'000'000'000

int main(int argc, char** argv) {
	InputValidator v(argc, argv);
    v.read_integer("x_s",-max_x,max_x);
    v.space();
    v.read_integer("y_s",-max_x,max_x);
    v.space();
    v.read_integer("x_e",-max_x,max_x);
    v.space();
    v.read_integer("y_e",-max_x,max_x);
    v.newline();
    int n = v.read_integer("n",2,100'000);
    v.newline();
    for (int i=0;i<n;i++){
        v.read_integer("x",-max_x,max_x);
        v.space();
        v.read_integer("y",-max_x,max_x);
        v.newline();
    }
    return 0;
}
