/************************************************************
 * up_irq.c
 *
 *   Copyright (C) 2007 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <spudmonkey@racsa.co.cr>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Gregory Nutt nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************/

/************************************************************
 * Included Files
 ************************************************************/

#include <nuttx/config.h>
#include <sys/types.h>
#include <nuttx/irq.h>
#include "up_internal.h"

/************************************************************
 * Definitions
 ************************************************************/

/************************************************************
 * Public Data
 ************************************************************/

/************************************************************
 * Private Data
 ************************************************************/

/************************************************************
 * Private Functions
 ************************************************************/

/************************************************************
 * Public Funtions
 ************************************************************/

/************************************************************
 * Name: irq_initialize
 ************************************************************/

void up_irqinitialize(void)
{
}

/************************************************************
 * Name: irqsave
 *
 * Description:
 *   Disable all IRQs
 *
 ************************************************************/

irqstate_t irqsave(void) _naked
{
  _asm
	mov	ie, dpl
	clr	ea
	ret
  _endasm;
}

/************************************************************
 * Name: irqrestore
 *
 * Description:
 *   Restore a previous interrupt state
 *
 ************************************************************/

void irqrestore(irqstate_t flags) __naked
{
  flags; /* Avoid compiler warning about unused argument */
  _asm
	mov	ie, dpl
	ret
  _endasm;
}

/************************************************************
 * Name: up_disable_irq
 *
 * Description:
 *   Disable the IRQ specified by 'irq'
 *
 ************************************************************/

static void _up_disable_irq(ubyte iebit) __naked
{
  _asm
	mov	a, ie
	orl	a, dpl
	mov	ie, a
	ret
  _endasm;
}

void up_disable_irq(int irq)
{
  if ((unsigned)irq < NR_IRQS)
    {
       _up_disable_irq(1 << irq);
    }
}

/************************************************************
 * Name: up_enable_irq
 *
 * Description:
 *   Enable the IRQ specified by 'irq'
 *
 ************************************************************/

static void _up_enable_irq(ubyte iebit) __naked
{
  _asm
	mov	a, ie
	anl	a, dpl
	mov	ie, a
	ret
  _endasm;
}

void up_enable_irq(int irq)
{
  if ((unsigned)irq < NR_IRQS)
    {
      _up_enable_irq(~(1 << irq));
    }
}
