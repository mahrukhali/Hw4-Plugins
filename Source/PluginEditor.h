#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
/**
*/
class PitchShifterAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                           public juce::Slider::Listener
{
public:
    enum
    {
        TitleWidth = 400,
        TitleHeight = 50,
        LabelWidth = 100,
        LabelHeight = 50,
        SliderWidth = 50,
        SliderLength = 300,
        Margin = 50
    };

    PitchShifterAudioProcessorEditor(PitchShifterAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~PitchShifterAudioProcessorEditor();

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;

private:
    PitchShifterAudioProcessor& processor;
   
    juce::AudioProcessorValueTreeState& valueTreeState;
  
    juce::Label semitonesLabel;
    juce::Slider semitonesSlider;
    std::unique_ptr<SliderAttachment> semitonesAttachment;
    //ch
    juce::Label gainLabel;
    juce::Slider gainSlider;
    std::unique_ptr<SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShifterAudioProcessorEditor)
};
