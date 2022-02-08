#include <sys/time.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <cstdio>

struct TimeStat {
    const char  *name;
    int         duration;
};

class Chrono {
    struct timeval m_begin;
    struct timeval m_end;

public:
    Chrono() = default;

    void begin() {
        gettimeofday(&m_begin, NULL);
    }

    void end() {
        gettimeofday(&m_end, NULL);
    }

    int get_duration_s() const {
        return (
                (double)(m_end.tv_usec - m_begin.tv_usec) / 1000000 +
                (double)(m_end.tv_sec  - m_begin.tv_sec)) * 1000;
    }
};

int     time_it(const char *name){
    Chrono  chrono;
    int     pid;
    int     status;

    chrono.begin();
    pid = fork();
    if ( pid == -1 )
        return -1;
    if ( pid == 0 ){
        close(STDOUT_FILENO);
        if ( execl(name, name, NULL) == -1 ){
            exit(EXIT_FAILURE);
        }
    }
    waitpid(pid, &status, 0);
    if ( status == EXIT_FAILURE ){
        return -1;
    }
    chrono.end();
    return chrono.get_duration_s();
}

void    print_stats(const TimeStat &x, const TimeStat &y){
    int padding = -20;

    (void)x;
    (void)y;
    printf("%*s %*s %*s %*s\n", padding, "NAME", padding, "DURATION", padding, "DIFF", padding, "FACTOR");
    printf("%*s %*i %*i %*i\n",
           padding, x.name,
           padding, x.duration,
           padding, 0,
           padding, 0);
    printf("%*s %*i %*i %*i\n",
           padding, y.name,
           padding, y.duration,
           padding, 0,
           padding, 0);
    printf("%*s %*i %*i %*.2f\n",
           padding, "",
           padding, x.duration + y.duration,
           padding, y.duration - x.duration,
           padding, (float)y.duration / (float)x.duration);
}

int     main(int argc, char *argv[]){
    if ( argc == 3 ){
        TimeStat x = { argv[1], time_it(argv[1]) };
        TimeStat y = { argv[2], time_it(argv[2]) };

        print_stats(x, y);
    }
}