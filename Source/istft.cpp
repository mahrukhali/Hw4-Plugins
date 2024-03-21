#include "istft.h"

void ISTFT::init(int order)
{
    windowlen = int(pow(2.0f, order));
    hannwindow.assign(windowlen, 0.0f);
    sampleframe.assign(windowlen, 0.0f);
    fftoutput.assign(windowlen, 0.0f);
    float pi = 3.14159f;
    hannsum = 0.0f;
    
    // Calculate Hann window and sum of window values
    int n = 0;
    while (n < windowlen)
    {
        hannwindow[n] = sqrt(0.5f * (1.0f - cosf(2.0f * pi * float(n) / float(windowlen))));
        hannsum += hannwindow[n];
        n++;
    }
    
    fft = std::make_unique<juce::dsp::FFT>(order);
}

void ISTFT::step(Cfloat* fftinput, float* samples, int numsamples)
{
    // Enforce conjugate symmetry
    int m = windowlen - 1;
    int N = windowlen / 2;
    int n = 1;
    while (n < N)
    {
        fftinput[m--] = std::conj(fftinput[n]);
        n++;
    }
    fftinput[N] = std::real(fftinput[N]);
    
    // Compute inverse FFT
    fft->perform(fftinput, fftoutput.data(), true);
    
    // Add windowed output to sample frame
    n = 0;
    while (n < windowlen)
    {
        sampleframe[n] += fftoutput[n].real() * hannwindow[n];
        n++;
    }
    
    // Get output samples
    n = 0;
    while (n < numsamples)
    {
        samples[n] = sampleframe[n] * float(numsamples) / hannsum;
        n++;
    }
    
    // Shift sample frame
    n = numsamples;
    while (n < windowlen)
    {
        sampleframe[n - numsamples] = sampleframe[n];
        n++;
    }
    n = windowlen - numsamples;
    while (n < windowlen)
    {
        sampleframe[n] = 0.0f;
        n++;
    }
}
