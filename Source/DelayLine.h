/*
  ==============================================================================

    DelayLine.h
    Created: 23 Oct 2019 12:13:06pm
    Author:  nachi

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#pragma once

class DelayLine {
 public:
  DelayLine() : DelayLine(600){};
  DelayLine(unsigned int delayInSamplesIn) : delayInSamples{delayInSamplesIn} {
    data.resize(2 * delayInSamples);
  }

  ~DelayLine() {}

  void setDelayTime(float delaySec, double sampleRate) {
    int delayInSamples = delaySec * sampleRate;
    if (delayInSamples >= data.size()) {
      data.resize(2 * delayInSamples);
      lastIndex = 0;
    }
    jassert(delayInSamples >= 0 && delayInSamples < data.size());
  }

  void setDelaySamples(unsigned int delaySamples) {
    delayInSamples = delaySamples;
    if (delayInSamples >= data.size()) {
      data.resize(2 * delayInSamples);
      lastIndex = 0;
    }
  }

  void getOutputSamples(float* out, int numSamples) {
    auto end = out + numSamples;
    while (out != end) {
      *out++ = getSample();
    }
  }

  void pushInputSamples(const float* in, int numSamples) {
    auto end = in + numSamples;
    while (in != end) {
      pushSample(*in++);
    }
  }

  void pushSample(float val) {
    data[lastIndex] = val;
    lastIndex = lastIndex == 0 ? data.size() - 1 : lastIndex - 1;
  }

  float getSample() {
    jassert(delayInSamples >= 0 && delayInSamples < data.size());
    int index = (lastIndex + 1 + delayInSamples) % data.size();
    return data[index];
  }

 private:
  std::vector<float> data;
  unsigned int delayInSamples;
  int lastIndex = 0;
};