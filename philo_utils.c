#include "philo.h"

int    check(char **av, int ac)
{
    int    i;

    i = 1;
    if (ac < 5 || ac > 6)
    {
        printf("Error\n");
        return (1);
    }
    while (i < ac)
    {
        if (av[i][0] == '-' || check_num(av[i])
            || ft_atoi(av[i]) == 0)
        {
            printf("Error\n");
            return (1);
        }
        i++;
    }
    return (0);
}

t_philo    **philo_init(t_args *table)
{
    t_philo    **philo;
    int        i;

    philo = (t_philo **)malloc(sizeof(t_philo *) * table->n_philo);
    if (!philo)
        return (NULL);
    i = 0;
    while (i < (int)table->n_philo)
    {
        philo[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
        if (!philo[i])
            return (NULL);
        if (pthread_mutex_init(&philo[i]->mutex_eating, NULL))
            return (NULL);
        philo[i]->philo_n = i;
        philo[i]->table = table;
        philo[i]->is_eating = 0;
        philo[i]->count = 0;
        philo[i]->left_fork = i;
        philo[i]->right_fork = (i + 1) % table->n_philo;
        i++;
    }
    return (philo);
}

pthread_mutex_t    *fork_init(t_args    *table)
{
    pthread_mutex_t    *forks;
    int                i;

    i = 0;
    if (table->n_philo == -1 || table->t_die == -1
        || table->t_eat == -1 || table->t_sleep == -1
        || table->t_must_eat == -1)
    {
        printf("Error\n");
        return (NULL);
    }
    forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
    if (!forks)
        return (NULL);
    while (i < table->n_philo)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
    return (forks);
}

t_args    *init(int ac, char **av)
{
    t_args    *table;

    table = malloc(sizeof(t_args) * 1);
    if (!table)
        return (NULL);
    table->n_philo = (uint64_t)ft_atoi(av[1]);
    table->t_die = (uint64_t)ft_atoi(av[2]);
    table->t_eat = (uint64_t)ft_atoi(av[3]);
    table->t_sleep = (uint64_t)ft_atoi(av[4]);
    table->t_must_eat = 0;
    if (ac == 6)
        table->t_must_eat = ft_atoi(av[5]);
    pthread_mutex_init(&table->mutex_write, NULL);
    table->start = get_time();
    table->forks = fork_init(table);
    table->philo = philo_init(table);
    if (!table->philo || !table->forks)
        return (NULL);
    return (table);
}

void    take_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
    message(philo->table, philo->philo_n, "has taken the left fork");
    pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
    message(philo->table, philo->philo_n, "has taken the right fork");
    pthread_mutex_lock(&philo->mutex_eating);
    philo->last_eat = get_time();
    philo->is_eating = 1;
    message(philo->table, philo->philo_n, "is eating");
    ft_usleep(philo->table->t_eat);
    philo->is_eating = 0;
    philo->count++;
    pthread_mutex_unlock(&philo->mutex_eating);
}

