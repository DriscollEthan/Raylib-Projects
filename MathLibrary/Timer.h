#pragma once

struct Timer
{
protected:
  double CurrentTimeInSeconds;
  double StartTimeInSeconds;
  double EndTimeInSeconds;

public:
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

  //Conversions
  double GetCurrentTimeInHour()
  {
    return CurrentTimeInSeconds / 3600.0f;
  }

  double GetCurrentTimeInMinutes()
  {
    return CurrentTimeInSeconds / 60.0f;
  }

  double GetCurrentTimeInSeconds()
  {
    return CurrentTimeInSeconds;
  }
};