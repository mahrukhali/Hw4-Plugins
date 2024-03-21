#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

//==============================================================================
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

PitchShifterAudioProcessorEditor::PitchShifterAudioProcessorEditor(PitchShifterAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), valueTreeState(vts)
{
    // Create labels
    addAndMakeVisible(semitonesLabel);
    semitonesLabel.setText("Semitone Shift", juce::dontSendNotification);
    semitonesLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    // Create sliders
    addAndMakeVisible(semitonesSlider);
    semitonesSlider.setColour(juce::Slider::trackColourId, juce::Colours::blue);
    semitonesSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 60, 20);
    semitonesSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    semitonesSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    semitonesAttachment.reset(new SliderAttachment(valueTreeState, "SemiTones", semitonesSlider));
    // Set slider range from -6 to +6 semitones
//    semitonesSlider.setRange(-6.0, 6.0, 0.1); // or adjust the step size as needed

    // Initialize gain slider
//    gainSlider.setSliderStyle(juce::Slider::LinearVertical);
    // Create gain label
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    // Create gain slider
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setColour(juce::Slider::trackColourId, juce::Colours::blue);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 60, 20);
    gainSlider.setRange(0.0, 1.0, 0.01);
    gainSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    gainSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    gainAttachment.reset(new SliderAttachment(valueTreeState, "Gain", gainSlider));
    
    setSize(TitleWidth + 2 * Margin, TitleHeight + SliderWidth + 3 * Margin);
}

PitchShifterAudioProcessorEditor::~PitchShifterAudioProcessorEditor()
{
}

void PitchShifterAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::pink);
    g.setColour(juce::Colours::black);
    g.setFont(24.0f);
    g.drawFittedText("Audio Pitch Shifter", Margin, 0, TitleWidth, TitleHeight, juce::Justification::centred, 1);
}

void PitchShifterAudioProcessorEditor::resized()
{
    int x = Margin;
        int y = TitleHeight + Margin;

        // Set position and size of the semitones label and slider
        semitonesLabel.setBounds(x, y, LabelWidth, LabelHeight);
        x += LabelWidth;
        semitonesSlider.setBounds(x, y, SliderLength, SliderWidth);

     //ch
    y = SliderWidth + Margin+30;

    // Set position and size of the gain label and slider
    gainLabel.setBounds(Margin, y, LabelWidth, LabelHeight);
    gainSlider.setBounds(Margin + LabelWidth, y, SliderLength, SliderWidth);
}

void PitchShifterAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // Handle slider value changes
    //ch
    if (slider == &gainSlider) {
            processor.rawVolume = gainSlider.getValue();
        }
    
}
