## allowed functions 
###	signal() 
	void(*signal(int sig, void (*func)(int)))(int);
		- calls func when the signal sig occurs.
###	sigemptyset()
	int	sigemptyset(sigset_t *set);
		- initializes the signal set given by set to empty, with all signals excluded from the set.

###	sigaddset()
	int	siggaddset(sigset_t *set, int signum);
		- adds signal signum to set.

### sigaction()
	int	sigaction(int sig, const struct sa *act, struct sa *oldact);
		- allows the calling process to examine and/or specify the action to be associated with a specific signal.
		- struct sa, used to describe an action to be taken, includes (at least) the following members: 
			{
				void			(*sa_handler)(int);
					=> Pointer to a signal-catching function or SIG_IGN - SIG_DFL macros.

				sigset_t		sa_mask;
					=> Additional set of signals to be blocked during execution of a signal-catching function.

				int				sa_flags;
					=> Special flags to affect behavior of signal.

				void			(*sa_sigaction)(int, siginfo_t *, void *);
					=> Pointer to a signal-catching function.
			}
			

### kill()
### getpid()
### malloc()
### free()
### pause()
### sleep()
### usleep()
### exit()
