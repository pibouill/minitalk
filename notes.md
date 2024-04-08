## allowed functions 

###	signal() 
```void(*signal(int sig, void (*func)(int)))(int);```
- calls func when the signal sig occurs.
- recommended to use sigaction() instead - portability issues
###	sigemptyset()
```int	sigemptyset(sigset_t *set);```
- initializes the signal set given by set to empty, with all signals excluded from the set.

###	sigaddset()
```int	siggaddset(sigset_t *set, int signum);```
- adds signal signum to set.

### sigaction()
```int	sigaction(int sig, const struct sa *act, struct sa *oldact);```
- allows the calling process to examine and/or specify the action to be associated with a specific signal.
- struct sa, used to describe an action to be taken, includes (at least) the following members: 

```
			{
				void			(*sa_handler)(int);
					=> Pointer to a signal-catching function or SIG_IGN - SIG_DFL macros.

				sigset_t		sa_mask;
					=> Additional set of signals to be blocked 
					during execution of a signal-catching function.

				int				sa_flags;
					=> Special flags to affect behavior of signal.

				void			(*sa_sigaction)(int, siginfo_t *, void *);
					=> Pointer to a signal-catching function.
			}
```
			

### kill()
```int kill(pid_t pid, int sig);```
- sends a signal to a process. 
- if pid > 0 --> sig is sent to the process with the ID specified by pid.
- if pid == 0 --> sig is sent to every process in the process group of the calling process
- if pid == -1 --> sig is sent to every process for which the calling process has permissions to send signals (Except system process).
- if pid < -1 --> same as -1 but the signal is sent to the processes with the same group ID as pid.

- if sig == 0 (null signal) --> used to check the validity of pid.

- returns 0 on completion, -1 on error.
### getpid()
```pid_t getpid(void);```
- returns the process ID (PID) of the calling process.
### pause()
```int pause(void);```
- causes the calling process (or thread) to sleep until a signal is delivered that either terminates the process or causes the invocation of a signal-catching function.
- returns only -1 when a signal was caught and the signal-catching function returned.
### sleep()
### usleep()
