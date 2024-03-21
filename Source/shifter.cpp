#include "shifter.h"
#include "VocoderTools.h"

SHIFTER::SHIFTER()
{
    windowlength = 1;
    firsttime = true;
}

void SHIFTER::init(int order)
{
    stft.init(order);
    istft.init(order);
    windowlength = pow(2.0f, order);
    fftdata.assign(windowlength, 0.0f);
    fftmag.assign(windowlength, 0.0f);
    fftphase.assign(windowlength, 0.0f);
    oldphase.assign(windowlength, 0.0f);
    modphase.assign(windowlength, 0.0f);
    deltaphase.assign(windowlength, 0.0f);
    firsttime = true;
}

void SHIFTER::step(float* samples, int numsamples, float semitonesShift)
{
    const float SEMITONES_PER_OCTAVE = 12.0f;
    // Calculate the pitch shift ratio based on semitones shift
    float pitchShiftRatio = pow(2.0f, semitonesShift / SEMITONES_PER_OCTAVE);

    // Calculate STFT
    stft.step(samples, numsamples, fftdata.data());

    // Phase vocoder processing
    int n = 0;
    while (n < windowlength) {
        fftdata[n] *= std::polar(1.0f, -2.0f * juce::MathConstants<float>::pi * n * pitchShiftRatio / windowlength);
        n++;
    }

    // Calculate ISTFT using modified block size
    int modifiedBlockSize = int(round(float(numsamples) / pitchShiftRatio));
    std::vector<float> modifiedBlockSamples;
    modifiedBlockSamples.assign(modifiedBlockSize, 0.0f);
    istft.step(fftdata.data(), modifiedBlockSamples.data(), modifiedBlockSize);

    // Resample to original block size
    PVresample(modifiedBlockSamples.data(), modifiedBlockSize, samples, numsamples);
}
