/*
  ==============================================================================

    RingBuffer.h
    Created: 25 Apr 2020 4:29:32pm
    Author:  nachi

  ==============================================================================
*/

#pragma once

template <int S>
class RingBuffer {
 public:
  RingBuffer() { data = new float[S]; }
  ~RingBuffer() { delete[] data; }

  void push(float in) {
    data[head++] = in;
    head %= S;
  }
  
  float get(int delay) const {  // delay < buf.getSize()
    int index = head - delay + S;
    index %= S;
    return data[index];
  }

  int size() const {
    return S;
  }

 private:
  float* data;
  int head = 0;
};
