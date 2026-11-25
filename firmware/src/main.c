/*
 * mr-wobble: fixed-rate control loop skeleton (Zephyr, C).
 *
 * The loop runs at 200 Hz with an absolute deadline (next = next + 5 ms).
 * It measures the period and the wake-up delay, counts overruns,
 * and prints a summary once each second.
 */

#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define PERIOD_US        5000U
#define REPORT_PERIOD_MS 1000

struct loop_stats {
	uint32_t ticks;
	uint32_t overruns;
	uint32_t period_min_us;
	uint32_t period_max_us;
	uint32_t late_max_us;
};

static void stats_reset(struct loop_stats *s)
{
	s->ticks = 0;
	s->overruns = 0;
	s->period_min_us = UINT32_MAX;
	s->period_max_us = 0;
	s->late_max_us = 0;
}

static void control_step(void)
{
	/* Later: read the IMU, run the filter, run the controller, set the motor. */
}

int main(void)
{
	const k_ticks_t period_ticks = k_us_to_ticks_ceil64(PERIOD_US);
	struct loop_stats stats;

	stats_reset(&stats);
	printk("mr-wobble: control loop at %u us\n", PERIOD_US);

	k_ticks_t deadline = k_uptime_ticks();
	int64_t next_report_ms = k_uptime_get() + REPORT_PERIOD_MS;
	uint32_t last_cyc = k_cycle_get_32();

	while (1) {
		/* Wait until the absolute deadline. */
		deadline += period_ticks;
		k_sleep(K_TIMEOUT_ABS_TICKS(deadline));

		/* Measure the period and the wake-up delay. */
		uint32_t now_cyc = k_cycle_get_32();
		k_ticks_t now_ticks = k_uptime_ticks();

		uint32_t period_us = k_cyc_to_us_floor32(now_cyc - last_cyc);
		last_cyc = now_cyc;

		k_ticks_t late_ticks = now_ticks - deadline;
		uint32_t late_us = late_ticks > 0 ? k_ticks_to_us_floor32(late_ticks) : 0;

		stats.ticks++;
		stats.period_min_us = MIN(stats.period_min_us, period_us);
		stats.period_max_us = MAX(stats.period_max_us, period_us);
		stats.late_max_us = MAX(stats.late_max_us, late_us);

		/* Overrun: we woke up one full period late. Skip the lost ticks. */
		if (late_ticks >= period_ticks) {
			stats.overruns++;
			deadline = now_ticks;
		}

		control_step();

		/* Print a summary once each second. */
		if (k_uptime_get() >= next_report_ms) {
			printk("ticks=%u period_min=%uus period_max=%uus late_max=%uus overruns=%u\n",
			       stats.ticks, stats.period_min_us, stats.period_max_us,
			       stats.late_max_us, stats.overruns);
			stats_reset(&stats);
			next_report_ms += REPORT_PERIOD_MS;
		}
	}

	return 0;
}
