#pragma once

struct Timer
{
  double CurrentTimeInSeconds;
  double StartTimeInSeconds;
  double EndTimeInSeconds;

  Timer() { CurrentTimeInSeconds = StartTimeInSeconds = EndTimeInSeconds = 0.0f; }

  Timer(const Timer& _other)
  {
    CurrentTimeInSeconds = _other.CurrentTimeInSeconds;
    StartTimeInSeconds = _other.StartTimeInSeconds;
    EndTimeInSeconds = _other.EndTimeInSeconds;
  }

  Timer operator =(const Timer& _other)
  {
    CurrentTimeInSeconds = _other.CurrentTimeInSeconds;
    StartTimeInSeconds = _other.StartTimeInSeconds;
    EndTimeInSeconds = _other.EndTimeInSeconds;
    return *this;
  }
};