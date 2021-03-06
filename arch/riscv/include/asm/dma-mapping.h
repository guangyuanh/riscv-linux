/*
 * Copyright (C) 2003-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 2012 ARM Ltd.
 * Copyright (C) 2016 SiFive, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __ASM_RISCV_DMA_MAPPING_H
#define __ASM_RISCV_DMA_MAPPING_H

#ifdef __KERNEL__

/* Use ops->dma_mapping_error (if it exists) or assume success */
// #undef DMA_ERROR_CODE

static inline struct dma_map_ops *get_dma_ops(struct device *dev)
{
	if (unlikely(dev->archdata.dma_ops))
		return dev->archdata.dma_ops;
	else
		return &dma_noop_ops;
}

static inline bool dma_capable(struct device *dev, dma_addr_t addr, size_t size)
{
	if (!dev->dma_mask)
		return false;

	return addr + size - 1 <= *dev->dma_mask;
}

static inline dma_addr_t phys_to_dma(struct device *dev, phys_addr_t paddr)
{
	return (dma_addr_t)paddr;
}

static inline phys_addr_t dma_to_phys(struct device *dev, dma_addr_t dev_addr)
{
	return (phys_addr_t)dev_addr;
}

static inline void dma_cache_sync(struct device *dev, void *vaddr, size_t size, enum dma_data_direction dir)
{
	/*
	 * RISC-V is cache-coherent, so this is mostly a no-op.  However, we do need to
	 * ensure that dma_cache_sync() enforces order, hence the mb().
	 */
	mb();
}

#endif	/* __KERNEL__ */
#endif	/* __ASM_RISCV_DMA_MAPPING_H */
