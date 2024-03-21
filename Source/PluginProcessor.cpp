#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "/Applications/pitchshifter-master/VocoderTools.h"
#include "/Applications/JUCE/modules/juce_audio_processors/juce_audio_processors.h"

PitchShifterAudioProcessor::PitchShifterAudioProcessor()
    : parameters(*this, nullptr, juce::Identifier("CompTreeState"),
        {
            std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("SemiTones", 1), 
                                                         "Semitones Shift",              // parameter name
                                                         juce::NormalisableRange<float>(-6.0f, 5.0f, 1.0f),
                                                         0.0f),
        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Gain", 2),
                                                                 "Gain",
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f, 0.01f),
                                                                 0.5f)
        }),
      semitonesParam(parameters.getRawParameterValue("SemiTones")),
        gainParam(parameters.getRawParameterValue("Gain"))

{
}

PitchShifterAudioProcessor::~PitchShifterAudioProcessor()
{
}

const juce::String PitchShifterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PitchShifterAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PitchShifterAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PitchShifterAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PitchShifterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PitchShifterAudioProcessor::getNumPrograms()
{
    return 1;
}

int PitchShifterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PitchShifterAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String PitchShifterAudioProcessor::getProgramName(int index)
{
    return {};
}

void PitchShifterAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

void PitchShifterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();

    chorusEffect.prepare(spec);

    chorusEffect.setCentreDelay(27.0f);
    chorusEffect.setMix(0.8f);
    chorusEffect.setFeedback(0.8f);
    chorusEffect.setDepth(0.8f);
    int minWindowLength = MINBLOCKSPERWINDOW * samplesPerBlock;
    int order = 0;
    int windowLength = 1;
    while (windowLength < minWindowLength)
    {
        order++;
        windowLength *= 2;
    }

    // Initialize shifters
    shifterBank.resize(getTotalNumInputChannels());

    for (auto ch = 0; ch < getTotalNumInputChannels(); ch++)
    {
        shifterBank[ch] = std::make_unique<SHIFTER>();
        shifterBank[ch]->init(order);
    }
}

void PitchShifterAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PitchShifterAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void PitchShifterAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
        juce::ScopedNoDenormals noDenormals;
    //ch
    // Retrieve gain parameter's value
    float gain = *gainParam;

    // Apply gain to audio processing
    buffer.applyGain(gain);
//
        auto totalNumInputChannels = getTotalNumInputChannels();

        // Map slider value (0 to 1) to pitch shift range (-6 to 5 semitones)
        float semitonesShift = *semitonesParam * 12.0f - 6.0f;
        // Check if semitones shift is zero
        if (semitonesShift == 0.0f)
        {
            // If semitones shift is zero, no pitch shifting is applied
            return;
        }

       
        float hopratio = pow(2.0f, semitonesShift / 12.0f);

        // Apply pitch shifting to each input channel
    for (auto ch = 0; ch < totalNumInputChannels; ch++)
        {
            
          

            // Apply pitch shifting
            shifterBank[ch]->step(buffer.getWritePointer(ch), buffer.getNumSamples(), hopratio);
        }
}


bool PitchShifterAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* PitchShifterAudioProcessor::createEditor()
{
    return new PitchShifterAudioProcessorEditor(*this, parameters);
}

void PitchShifterAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void PitchShifterAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr && xmlState->hasTagName(parameters.state.getType()))
        parameters.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PitchShifterAudioProcessor();
}
