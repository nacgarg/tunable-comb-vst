/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiCombFilterAudioProcessor::MidiCombFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
      )
#endif
{
}

MidiCombFilterAudioProcessor::~MidiCombFilterAudioProcessor() {}

//==============================================================================
const String MidiCombFilterAudioProcessor::getName() const { return JucePlugin_Name; }

bool MidiCombFilterAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool MidiCombFilterAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool MidiCombFilterAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double MidiCombFilterAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int MidiCombFilterAudioProcessor::getNumPrograms() {
  return 1;  // NB: some hosts don't cope very well if you tell them there are 0 programs,
             // so this should be at least 1, even if you're not really implementing
             // programs.
}

int MidiCombFilterAudioProcessor::getCurrentProgram() { return 0; }

void MidiCombFilterAudioProcessor::setCurrentProgram(int index) {}

const String MidiCombFilterAudioProcessor::getProgramName(int index) { return {}; }

void MidiCombFilterAudioProcessor::changeProgramName(int index, const String& newName) {}

//==============================================================================
void MidiCombFilterAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  int samplesDelay = sampleRate * delaySec;
  sampleRate = sampleRate;
  delays.resize(getNumInputChannels());
  lfos.resize(getNumInputChannels());
}

void MidiCombFilterAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiCombFilterAudioProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
  ignoreUnused(layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
      layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

    // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet()) return false;
#endif

  return true;
#endif
}
#endif

void MidiCombFilterAudioProcessor::processBlock(AudioBuffer<float>& buffer,
                                                MidiBuffer& midiMessages) {
  ScopedNoDenormals noDenormals;
  auto totalNumInputChannels = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  MidiBuffer::Iterator midiIter(midiMessages);
  MidiMessage midi(0xf0);
  int sampleTime;

  while (midiIter.getNextEvent(midi, sampleTime)) {
    if (midi.isNoteOn()) {
      auto note = midi.getNoteNumber();
      auto freq = midi.getMidiNoteInHertz(note);
      delaySec = 1.f / freq;
    }
  }

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear(i, 0, buffer.getNumSamples());

  // This is the place where you'd normally do the guts of your plugin's
  // audio processing...
  // Make sure to reset the state if your inner loop is processing
  // the samples and the outer loop is handling the channels.
  // Alternatively, you can process the samples with the channels
  // interleaved by keeping the same state.

  debugText = String(sampleRate) + "hz, " + String(delaySec * sampleRate) + " samples, " + String(feedback*100) + "% feedback";
  for (int channel = 0; channel < totalNumOutputChannels; ++channel) {
    int numSamples = buffer.getNumSamples();
    auto* channelData = buffer.getWritePointer(channel);

	delays[channel].setDelaySamples(delaySec * sampleRate);
    for (int i = 0; i < numSamples; i++) {
        //delays[channel].setDelaySamples((unsigned int)(std::sin(0.00002f * lfos[channel]++)*700)+1200);
      float delayedSample = delays[channel].getSample();
      float outputSample = (2.0f / (std::exp(-1.0f * waveshaperDelta * ((float)channelData[i] - feedback * delayedSample)) + 1.0f)) - 1.0f;
      delays[channel].pushSample(outputSample);
      channelData[i] = outputSample;
    }
  }
}

//==============================================================================
bool MidiCombFilterAudioProcessor::hasEditor() const {
  return true;  // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiCombFilterAudioProcessor::createEditor() {
  return new MidiCombFilterAudioProcessorEditor(*this);
}

//==============================================================================
void MidiCombFilterAudioProcessor::getStateInformation(MemoryBlock& destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.
}

void MidiCombFilterAudioProcessor::setStateInformation(const void* data,
                                                       int sizeInBytes) {
  // You should use this method to restore your parameters from this memory block,
  // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new MidiCombFilterAudioProcessor();
}
