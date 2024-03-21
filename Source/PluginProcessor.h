#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "/Applications/pitchshifter-master/stft.h"
#include "/Applications/pitchshifter-master/istft.h"
#include "/Applications/pitchshifter-master/shifter.h"
#include <complex>
#include <vector>

typedef std::complex<float> Cfloat;
constexpr auto MINBLOCKSPERWINDOW = 16;

//==============================================================================
/**
*/
class PitchShifterAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PitchShifterAudioProcessor();
    ~PitchShifterAudioProcessor();

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
  
    float rawVolume = 0.5f;


private:
    //==============================================================================
    std::vector<std::unique_ptr<SHIFTER>> shifterBank;

    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* semitonesParam = nullptr;
    juce::dsp::Chorus <float> chorusEffect;
    
    float lastSample = 0;
    //ch
    std::atomic<float>* gainParam;

    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShifterAudioProcessor)
};
