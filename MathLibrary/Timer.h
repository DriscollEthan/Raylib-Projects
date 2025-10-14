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


  //Conversions for NanoSecodns
  double NanoSecondsToMicroSeconds(double _nanoSeconds)
  {
    return _nanoSeconds / 1000.0f;
  }

  double NanoSecondsToMilliSeconds(double _nanoSeconds)
  {
    return _nanoSeconds / 1000000.0f;
  }

  double NanoSecondsToSeconds(double _nanoSeconds)
  {
    return _nanoSeconds / 1000000000.0f;
  }

  double NanoSecondsToMinutes(double _nanoSeconds)
  {
    return _nanoSeconds / 60000000000.0f;
  }

  double NanoSecondsToHours(double _nanoSeconds)
  {
    return _nanoSeconds / 3600000000000.0f;
  }


  //Converisions for MicroSeconds
  double MicroSecondsToNanoSeconds(double _microSeconds)
  {
    return _microSeconds * 1000.0f;
  }

  double MicroSecondsToMilliSeconds(double _microSeconds)
  {
    return _microSeconds / 1000.0f;
  }

  double MicroSecondsToSeconds(double _microSeconds)
  {
    return _microSeconds / 1000000.0f;
  }

  double MicroSecondsToMinutes(double _microSeconds)
  {
    return _microSeconds / 60000000.0f;
  }

  double MicroSecondsToHours(double _microSeconds)
  {
    return _microSeconds / 3600000000.0f;
  }


  //Converisions for MilliSeconds
  double MilliSecondsToNanoSeconds(double _milliSeconds)
  {
    return _milliSeconds * 1000000.0f;
  }

  double MilliSecondsToMicroSeconds(double _milliSeconds)
  {
    return _milliSeconds * 1000.0f;
  }

  double MilliSecondsToSeconds(double _milliSeconds)
  {
    return _milliSeconds / 1000.0f;
  }

  double MilliSecondsToMinutes(double _milliSeconds)
  {
    return _milliSeconds / 60000.0f;
  }

  double MilliSecondsToHours(double _milliSeconds)
  {
    return _milliSeconds / 3600000.0f;
  }



  //Converisions for Seconds
  double SecondsToNanoSeconds(double _seconds)
  {
    return _seconds * 1000000000.0f;
  }

  double SecondsToMicroSeconds(double _seconds)
  {
    return _seconds * 1000.0f;
  }

  double SecondsToMilliSeconds(double _seconds)
  {
    return _seconds * 1000.0f;
  }

  double SecondsToMinutes(double _seconds)
  {
    return _seconds / 60.0f;
  }

  double SecondsToHours(double _seconds)
  {
    return _seconds / 3600.0f;
  }


  //Converisions for Minutes
  double MinutesToNanoSeconds(double _minutes)
  {
    return _minutes * 60000000000.0f;
  }

  double MinutesToMicroSeconds(double _minutes)
  {
    return _minutes * 60000000.0f;
  }

  double MinutesToMilliSeconds(double _minutes)
  {
    return _minutes * 60000.0f;
  }

  double MinutesToSeconds(double _minutes)
  {
    return _minutes * 60.0f;
  }

  double MinutesToHours(double _minutes)
  {
    return _minutes / 60.0f;
  }


  //Converisions for Hours
  double HoursToNanoSeconds(double _hours)
  {
    return _hours * 3600000000000.0f;
  }

  double HoursToMicroSeconds(double _hours)
  {
    return _hours * 3600000000.0f;
  }

  double HoursToMilliSeconds(double _hours)
  {
    return _hours * 3600000.0f;
  }

  double HoursToSeconds(double _hours)
  {
    return _hours * 3600.0f;
  }

  double HoursToMinutes(double _hours)
  {
    return _hours * 60.0f;
  }


  //Get Current Time + Converisions
  double GetCurrentTimeInNanoSeconds()
  {
    return SecondsToNanoSeconds(CurrentTimeInSeconds);
  }

  double GetCurrentTimeInMicroSeconds()
  {
    return SecondsToMicroSeconds(CurrentTimeInSeconds);
  }

  double GetCurrentTimeInMilliSeconds()
  {
    return SecondsToMilliSeconds(CurrentTimeInSeconds);
  }

  double GetCurrentTimeInSeconds()
  {
    return CurrentTimeInSeconds;
  }

  double GetCurrentTimeInMinutes()
  {
    return SecondsToMinutes(CurrentTimeInSeconds);
  }

  double GetCurrentTimeInHours()
  {
    return SecondsToHours(CurrentTimeInSeconds);
  }


  //Get End Time + Converisions
  double GetEndTimeInNanoSeconds()
  {
    return SecondsToNanoSeconds(EndTimeInSeconds);
  }

  double GetEndTimeInMicroSeconds()
  {
    return SecondsToMicroSeconds(EndTimeInSeconds);
  }

  double GetEndTimeInMilliSeconds()
  {
    return SecondsToMilliSeconds(EndTimeInSeconds);
  }

  double GetEndTimeInSeconds()
  {
    return EndTimeInSeconds;
  }

  double GetEndTimeInMinutes()
  {
    return SecondsToMinutes(EndTimeInSeconds);
  }

  double GetEndTimeInHours()
  {
    return SecondsToHours(EndTimeInSeconds);
  }


  //Get Start Time + Converisions
  double GetStartTimeInNanoSeconds()
  {
    return SecondsToNanoSeconds(StartTimeInSeconds);
  }

  double GetStartTimeInMicroSeconds()
  {
    return SecondsToMicroSeconds(StartTimeInSeconds);
  }

  double GetStartTimeInMilliSeconds()
  {
    return SecondsToMilliSeconds(StartTimeInSeconds);
  }

  double GetStartTimeInSeconds()
  {
    return StartTimeInSeconds;
  }

  double GetStartTimeInMinutes()
  {
    return SecondsToMinutes(StartTimeInSeconds);
  }

  double GetStartTimeInHours()
  {
    return SecondsToHours(StartTimeInSeconds);
  }


  //Timer Work
  void SetTimerInNanoSeconds(double _startTime, double _endTime)
  {
    StartTimeInSeconds = NanoSecondsToSeconds(_startTime);
    EndTimeInSeconds = NanoSecondsToSeconds(_endTime);
    CurrentTimeInSeconds = StartTimeInSeconds;
  }

  void SetTimerInMicroSeconds(double _startTime, double _endTime)
  {
    StartTimeInSeconds = MicroSecondsToSeconds(_startTime);
    EndTimeInSeconds = MicroSecondsToSeconds(_endTime);
    CurrentTimeInSeconds = StartTimeInSeconds;
  }

  void SetTimerInMilliSeconds(double _startTime, double _endTime)
  {
    StartTimeInSeconds = MilliSecondsToSeconds(_startTime);
    EndTimeInSeconds = MilliSecondsToSeconds(_endTime);
    CurrentTimeInSeconds = StartTimeInSeconds;
  }

  void SetTimerInSeconds(double _startTime, double _endTime)
  {
    StartTimeInSeconds = _startTime;
    EndTimeInSeconds = _endTime;
    CurrentTimeInSeconds = StartTimeInSeconds;
  }

  void SetTimerInMinutes(double _startTime, double _endTime)
  {
    StartTimeInSeconds = MinutesToSeconds(_startTime);
    EndTimeInSeconds = MinutesToSeconds(_endTime);
    CurrentTimeInSeconds = StartTimeInSeconds;
  }

  void SetTimerInHours(double _startTime, double _endTime)
  {
    StartTimeInSeconds = HoursToSeconds(_startTime);
    EndTimeInSeconds = HoursToSeconds(_endTime);
    CurrentTimeInSeconds = StartTimeInSeconds;
  }

  void ResetTimer()
  {
    CurrentTimeInSeconds = StartTimeInSeconds;
  }

  
  //Run Timer

  /* Run Timer, takes in deltaTime in Seconds. Returns true if done. */
  bool RunTimer(double _deltaTime)
  {
    CurrentTimeInSeconds += _deltaTime;
    return CurrentTimeInSeconds >= EndTimeInSeconds;
  }
};