#Overview
This is the HAL layer extract from [YetAnotherPilot2](https://github.com/my12doom/pilot2 "YetAnotherPilot2").
I wrote too many unrelated projects in that repository, it's time to clear up.

#Coding Guidelines
use C+class, minimun template and basic operator override is acceptable.

platform specified assembly acceleration is allowed, but a C/C++ fallback is required.

use tabs, not spaces.

use stack and global/member variables. heap allocation is forbidden.

non-blocking functions in time-critical thread only. put unpredictable works to "AsyncWorker".
