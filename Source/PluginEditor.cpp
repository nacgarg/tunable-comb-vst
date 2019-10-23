/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiCombFilterAudioProcessorEditor::MidiCombFilterAudioProcessorEditor (MidiCombFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

MidiCombFilterAudioProcessorEditor::~MidiCombFilterAudioProcessorEditor()
{
}

//==============================================================================
void MidiCombFilterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
	g.drawFittedText(String(processor.delaySec), getLocalBounds().removeFromTop(100), Justification::centred, 1);
	g.drawFittedText(processor.debugText, getLocalBounds().removeFromTop(200), Justification::centred, 1);


}

void MidiCombFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
