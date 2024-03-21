#include "VocoderTools.h"
#include <cmath>
#include <stdexcept>

void PVresample(float* x, int Nx, float* y, int Ny)
{
    if (Nx <= 0 || Ny <= 0) {
        throw std::invalid_argument("Input or output length cannot be zero or negative.");
    }

    float ratio = float(Nx - 1) / float(Ny - 1);

    // Assign boundary cases directly
    y[0] = x[0];
    y[Ny - 1] = x[Nx - 1];

    // Initialize index and perform linear interpolation for inner points
    int n = 1;
    while (n < Ny - 1)
    {
        float xn = ratio * float(n);
        int n1 = int(std::floor(xn));
        y[n] = x[n1] + (xn - std::floor(xn)) * (x[n1 + 1] - x[n1]);
        n++;
    }
}
