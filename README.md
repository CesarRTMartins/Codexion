*This project has been created as part of the 42 curriculum by crodrigo.*

## Table of Contents

- Description
- Instructions
- Command-line arguments
- Logging format
- Resources
- Blocking cases handled
- Thread synchronization mechanisms

---

## `🔍` | Description

**Codexion** is a C concurrency project inspired by the classic **Dining Philosophers problem**. In place of philosophers and forks, several "coder" threads compete for a limited pool of USB dongles. Before a coder can compile, it must first hold the two dongles assigned to it.

The simulation explores how multiple threads can coordinate access to scarce resources while enforcing each coder’s deadline.

---

## `🚀` | Instructions

Build the project with the included Makefile. Compilation uses `-Wall -Wextra -Werror`, and the resulting executable is linked with the POSIX threads library.

bash

```bash
# from project root
make

# run the program (example)
./codexion 4 1500 200 200 200 3 100 fifo
```

---

## `⚙️` | Command-line arguments

All arguments are mandatory. The first six accept positive integers, cooldown accepts zero or a positive integer, and the scheduler accepts `fifo` or `edf`.

1. number\_of\_coders -\> number of coders
2. time\_to\_burnout (ms) -\> deadline: if a coder does not start compiling before this window since their last compile or simulation start, they burn out
3. time\_to\_compile (ms)
4. time\_to\_debug (ms)
5. time\_to\_refactor (ms)
6. number\_of\_compiles\_required -\> simulation ends when every coder reached this compile count
7. dongle\_cooldown (ms) -\> after a dongle is released it is unavailable for this cooldown
8. scheduler -\> `fifo` (First In, First Out) or `edf` (Earliest Deadline First)

Example:

bash

```bash
./codexion 4 1500 200 200 200 5 100 edf
```

---

## `📝` | Logging format

Each change of state is written on a separate line with an elapsed timestamp in milliseconds and the coder ID. A compile starts with two contiguous dongle acquisition lines followed by the compile line. The burnout line ends the log.

Example:

```
0 1 has taken a dongle
0 1 has taken a dongle
0 1 is compiling
200 1 is debugging
400 1 is refactoring
1204 3 burned out
```

---

## `📁` | Resources

- [Dining philosophers problem](<https://en.wikipedia.org/wiki/Dining_philosophers_problem>)
- [POSIX threads documentation](<https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html>)

### AI usage

- Identifying edge-case failures.
- Drafting and polishing this README.

---

## `🛡️` | Blocking cases handled

### Deadlock prevention

A worker acquires its two dongles together under the simulation mutex. A worker that is waiting holds neither dongle. Waiters block on a condition variable, which releases the mutex while they sleep.

### Scheduler, cooldown and deadlines

FIFO orders requests by arrival, while EDF orders by burnout deadline with FIFO as the tie break. A coder can reserve its pair when both dongles are available and it precedes every waiting request that shares either one. Requests for disjoint pairs can proceed independently.

All coders enter the queue at startup. The simulation queues even indices before odd indices to let compatible pairs start together. On odd rings with tight deadlines, it can stagger the first eligible starts so the dongles become available in successive turns.

Cooldown begins when a compile releases its dongles. Each coder’s burnout deadline is measured from the start of its last compile or the start of the simulation. Coders that reach the compile quota leave burnout monitoring.

---

## `🔧` | Thread synchronization mechanisms

One mutex protects cooldown and ownership, scheduler requests, deadlines and output. The monitor and the workers use a condition variable to wait for a cooldown, phase or deadline, and recheck the shared state when they wake. The simulation broadcasts on shutdown so all threads can exit before cleanup.
