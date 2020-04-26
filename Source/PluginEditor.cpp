/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

#include "PluginProcessor.h"

//==============================================================================
MidiCombFilterAudioProcessorEditor::MidiCombFilterAudioProcessorEditor(
    MidiCombFilterAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p) {
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(400, 300);
  addAndMakeVisible(feedbackSlider);
  feedbackSlider.setRange(0.0, 1.2);
  feedbackSlider.setTextValueSuffix("%");
  feedbackSlider.addListener(this);

  addAndMakeVisible(waveshaperSlider);
  waveshaperSlider.setRange(0.1, 5.0);
  waveshaperSlider.setTextValueSuffix("");
  waveshaperSlider.addListener(this);

  addAndMakeVisible(combTypeToggle);
  combTypeToggle.setButtonText("Toggle Comb Type");
  combTypeToggle.onClick = [this] { processor.combType *= -1; };

  setRepaintsOnMouseActivity(true);
}

MidiCombFilterAudioProcessorEditor::~MidiCombFilterAudioProcessorEditor() {}

//==============================================================================
void MidiCombFilterAudioProcessorEditor::paint(Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a solid
  // colour)
  g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

  g.setColour(Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Hello World!", getLocalBounds(), Justification::centred, 1);
  g.drawFittedText(String(processor.delaySec), getLocalBounds().removeFromTop(100),
                   Justification::centred, 1);
  g.drawFittedText(processor.debugText, getLocalBounds().removeFromTop(200),
                   Justification::centred, 1);
  combTypeToggle.setButtonText(processor.combType == 1 ? "Switch to Negative Comb"
                                                       : "Switch to Positive Comb");
}

void MidiCombFilterAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
  auto sliderLeft = 10;
  feedbackSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 20);
  waveshaperSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
  combTypeToggle.setBounds(100, 150, 200, 30);
}

void MidiCombFilterAudioProcessorEditor::sliderValueChanged(Slider* slider) {
  // std::cout << "slider changed\n";
  if (slider == &waveshaperSlider)
    processor.waveshaperDelta = waveshaperSlider.getValue();
  if (slider == &feedbackSlider) processor.feedback = feedbackSlider.getValue();
  repaint();
}
