#include <nuttx/arch.h>
#include <nuttx/irq.h>

#include <stdbool.h>

static volatile irqstate_t g_irqstate_flags;
static volatile bool locked = false;

/*!***************************************************************************
* @brief Enable IRQ Interrupts
*
* @return -
*****************************************************************************/
void IRQ_UNLOCK(void)
{
	// do nothing if already in an interrupt context
	if (!up_interrupt_context() && locked) {
		locked = false;
		leave_critical_section(g_irqstate_flags);
	}
}

/*!***************************************************************************
* @brief Disable IRQ Interrupts
*
* @return -
*****************************************************************************/
void IRQ_LOCK(void)
{
	// do nothing if already in an interrupt context
	if (!up_interrupt_context() && !locked) {
		g_irqstate_flags = enter_critical_section();
		locked = true;
	}
}
