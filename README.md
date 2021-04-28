# Average_Buffer template class

A AverageBuffer template class (sliding window) that calculates:
  'Average', 'Average-forever', 'Upper Quarter Average' and 'Lower Quarter Average'.
- Every time a new sample enters the buffer the oldest sample will be extracted
  from the buffer (if the buffer is full).
- 'Average' is the average of the 100 samples that are currently in the buffer (if buffer size is currently 100).
- 'Average-forever' is the average of all samples from the beginning of the run.
 - 'Upper Quarter Average' is the average of the newest 25 samples (if buffer size is currently 100).
 - 'Lower Quarter Average' is the average of the oldest 25 samples (if buffer size is currently 100).


   For example, if the buffer size is 8 and the last samples are [10,40,30,44,20,50,35,55]:
     'Upper Quarter Average' is the average of [35,55] (the newest two samples).
     'Lower Quarter Average' is the average of [10,40] (the oldest two samples).
