//todo header

#include "philosophers.h"

int	should_stop_routine(t_monitor *monitor)
{
	pthread_mutex_lock(&monitor->flags_lock);
	if (monitor->all_meals_flag || monitor->dead_philo_flag)
	{
		pthread_mutex_unlock(&monitor->flags_lock);
		return (B_TRUE);
	}
	pthread_mutex_unlock(&monitor->flags_lock);
	return (B_FALSE);
}

void	*lone_philo_case(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	ft_philo_print(philo, MSG_TAKE_FORK);
	ft_usleep(philo->monitor->mtime_to_die);
	philo_print(philo, MSG_DYING);
	pthread_mutex_lock(&philo->state_lock);
	philo->state_enum = PHILO_DEAD;
	pthread_mutex_unlock(&philo->state_lock);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_lock(&philo->monitor->flags_lock);
	philo->monitor->flags_lock = B_TRUE;
	pthread_mutex_unlock(&philo->monitor->flags_lock);
	return (NULL);
}

/*
The even-numbered philosophers will start their routine with a delay
to avoid conflicts.
*/
void	*philo_routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *) void_philo;
	if (philo->monitor->meal_target_nb == 0)
		return (NULL);
	if (philo->monitor->philo_nb <= 1)
		return (lone_philo_case(philo));
	wait_for_start_time(philo->monitor->start_utime);
	if (philo->id_nb % 2)
		ft_usleep(10);
	//todo
	return (NULL);
}