// marker.cpp,v 1.2 2000/08/19 00:25:00 kirthika Exp
#include "marker.h"

void
Marker::accumulate_into (ACE_Throughput_Stats &throughput,
                         int which_method) const
{
  switch (which_method)
    {
    case 1: // method ready
      throughput.accumulate (this->throughput_method_ready_);
      break;
    case 2: // method authenticate
      throughput.accumulate (this->throughput_method_authenticate_);
      break;
    case 3: // method update_records
      throughput.accumulate (this->throughput_method_update_records_);
      break;
    default:
      break; 
    }
  
}

void
Marker::dump_stats (const char* msg, 
                    ACE_UINT32 gsf,
                    int which_method)
{
  switch (which_method)
    {
    case 1: // method ready
      this->throughput_method_ready_.dump_results (msg, gsf);
      break;
    case 2: // method authentciate
      this->throughput_method_authenticate_.dump_results (msg, gsf);
      break;
    case 3: // method update_records
      this->throughput_method_update_records_.dump_results (msg, gsf);
      break;
    default:
      break;
    }
}

void
Marker::sample (ACE_hrtime_t throughput_diff,
                ACE_hrtime_t latency_diff,
                int which_method)
{
  switch (which_method)
    {
    case 1: // method ready
      this->throughput_method_ready_.sample (throughput_diff, 
                                             latency_diff);
      break;
    case 2: // method authentciate
      this->throughput_method_authenticate_.sample (throughput_diff, 
                                                    latency_diff);
      break;
    case 3: // method update_records
      this->throughput_method_update_records_.sample (throughput_diff, 
                                                      latency_diff);
      break;
    default:
      break;
    }

} 
