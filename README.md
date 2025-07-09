# 🧠 Philosophers - 42 School Project

The **Philosophers** project is a core part of the 42 School curriculum, designed to introduce key concepts of **concurrent programming** and **thread synchronization**. The goal is to simulate the dining philosophers problem — a classic concurrency challenge — while avoiding issues like **deadlocks**, **race conditions**, and **starvation**.

--

Throughout this project, I deepened my understanding of:

- 🧵 **Multithreading**: Creating and managing threads with `pthread_create` and `pthread_join`.
- 🧱 **Mutexes (Mutual Exclusion)**: Protecting shared resources (forks) using `pthread_mutex_t`.
- ⏱ **Time management**: Accurate sleep and timing using `gettimeofday` and custom sleep functions.
- ⚠️ **Race conditions & deadlocks**: Understanding and preventing common synchronization issues.
- 🚦 **Thread synchronization**: Managing execution order and shared state with mutexes and conditions.
- 👀 **Monitoring & supervision**: Implementing a separate thread or loop to detect philosopher death and completion conditions.

## 🛠 Technical Concepts Used

- **POSIX Threads (pthreads)**:
  - `pthread_t` for thread objects
  - `pthread_mutex_t` for mutual exclusion
  - `pthread_mutex_lock` / `unlock` for synchronization

- **Time handling**:
  - `gettimeofday` for precise timestamping
  - Custom sleep function to ensure millisecond-level accuracy

- **Circular resource management**:
  - Forks shared between neighbors using modular arithmetic
  - Deadlock prevention by choosing fork order or staggering start times

- **Custom logging**:
  - Timestamped output for each philosopher's state: thinking, eating, sleeping, died
  - Avoiding data races on `printf` via a global write mutex

## ⚙️ Implementation Highlights

- Each philosopher is a **separate thread**, running a loop of:
  1. Taking forks (mutex lock)
  2. Eating (with timing)
  3. Releasing forks (mutex unlock)
  4. Sleeping and thinking

- A **monitor thread** checks:
  - If any philosopher exceeded `time_to_die` without eating
  - If all philosophers have eaten the required number of times

- **Edge case handling**:
  - Single philosopher (cannot eat, should die after `time_to_die`)
  - Input validation and overflow protection

## 🚫 Challenges Addressed

- ✅ Preventing **deadlocks** by controlling fork pickup order
- ✅ Avoiding **starvation** by tracking each philosopher’s eating times
- ✅ Ensuring **precise timing**, even under CPU load
- ✅ Keeping output **synchronized** to prevent mixed logs

## 🧠 Key Takeaways

This project gave me hands-on experience with **low-level concurrency**, strengthened my understanding of how **OS-level threads and synchronization mechanisms** work, and showed me how subtle timing and state issues can break a seemingly simple simulation. It also emphasized the importance of **deterministic behavior** in multi-threaded applications.

---

Made with ⚙️ and 🧠 by [Your Name] — 42 [Your Campus]
