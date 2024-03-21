#include "stft.h"
#include <cmath>

void STFT::init(int order)
{
    windowlen = int(pow(2.0f, order));
    hannwindow.assign(windowlen, 0.0f);
    sampleframe.assign(windowlen, 0.0f);
    fftinput.assign(windowlen, 0.0f);
    const float pi = M_PI; // Use M_PI for better readability
    int n = 0;
    while (n < windowlen)
    {
        hannwindow[n] = sqrt(0.5f * (1.0f - cosf(2.0f * pi * float(n) / float(windowlen))));
        n++;
    }
    fft = std::make_unique<juce::dsp::FFT>(order);
}

void STFT::step(float* samples, int numSamples, Cfloat* fftoutput)
{
    // Shift samples into frame
    int n = numSamples;
    while (n < windowlen)
    {
        sampleframe[n - numSamples] = sampleframe[n];
        n++;
    }
    n = 0;
    while (n < numSamples)
    {
        sampleframe[windowlen - numSamples + n] = samples[n];
        n++;
    }
    // Apply window
    n = 0;
    while (n < windowlen)
    {
        fftinput[n] = sampleframe[n] * hannwindow[n];
        n++;
    }
    // Compute FFT
    fft->perform(fftinput.data(), fftoutput, false);
}
