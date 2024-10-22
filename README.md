<div align="center">
  <h1>⚙️ philosophers (a <a href="https://42perpignan.fr/">42</a> project) ⚙️</h1>
  <img src="ressources/preview.gif" alt="Preview">
  <p><b>Subject:</b> <a href="ressources/en.subject.pdf">fr.subject.pdf</a></p>
</div>
<div align="center">
  <h2>✅ Grade</h2>
  <img src="ressources/grade.png" alt="Grade">
</div><br>

## <div align="center">📄 Introduction</div>
**philosophers** is a project about managing multiple threads in the same program. In this project, we learn how to use threads, how to make them waiting or using shared variables.

Here, each thread is a philosopher, who has to eat to survive. When a philosopher can't eat soon enough, he dies, and the simulation stops.
<br><br>

## <div align="center">📒 Rules</div>
- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively **eat**, **think**, or **sleep**. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are **as many forks as philosophers**.
- Because serving and eating spaghetti with only one fork is very inconvenient, **a philosopher takes their right and their left forks to eat**, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. **The simulation stops when
a philosopher dies** of starvation.
- Every philosopher needs to eat and should never starve.
- **Philosophers don’t speak with each other**.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

`Each philosopher is a thread, and each fork is a mutex. In the bonus part, rules are the same, but instead of threads and mutex, we must use processes and semaphores.`
<br><br>

## <div align="center">💻 Usage</div>
### Clone the repository
```bash
git clone https://github.com/Arawyn42/42_philosophers
```
### Go into the program folder
**Base version:**
```bash
cd 42_philosophers/philo
```
**Bonus version:**
```bash
cd 42_philosophers/philo_bonus
```

### Compile the program
```bash
make && make clean
```

### Launch the program
**Base version:**
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
**Bonus version:**
```bash
./philo_bonus number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Replace *number_of_philosophers*, *time_to_die*, *time_to_eat* and *time_to_sleep* with the values you want to test (time in milliseconds). You can also add a 5th argument (optional) to indicate the number of times each philosopher must eat before the simulation stops.