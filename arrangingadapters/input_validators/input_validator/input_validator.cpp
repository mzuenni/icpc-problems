#include "validation.h"

int main(int argc, char *argv[]) {
    InputValidator v(argc, argv);
    int n = v.read_integer("n", 1, 200'000);
    v.space();
    v.read_integer("s", 1, 1'000'000'000);
    v.newline();
    for(int i = 0; i < n-1; i++)
    {
        v.read_integer("w", 3, 1'000'000'000);
        v.space();
    }
    v.read_integer("w", 3, 1'000'000'000);
    v.newline();
}
