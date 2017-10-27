#include "vm/swap.h"
#include <bitmap.h>
#include <debug.h>
#include <stdio.h>
#include "vm/frame.h"
#include "vm/page.h"
#include "threads/synch.h"
#include "threads/vaddr.h"

/* The swap device. */
static struct block *swap_device;

/* Used swap frames. */
/* TODO (Phase 4): Implement data structure to track which frames
 * in swap space are in use. */

/* Protects data structure above. */
static struct lock swap_lock;

/* Number of sectors per page. */
#define PAGE_SECTORS (PGSIZE / BLOCK_SECTOR_SIZE)

/* Sets up swap. */
void
swap_init (void) 
{
  swap_device = block_get_role (BLOCK_SWAP);
  if (swap_device == NULL) 
    {
      printf ("no swap device--swap disabled\n");
    }
  else
    {
      /* TODO (Phase 4): Initialize swap-tracking data structure. */
    }
  lock_init (&swap_lock);
}

/* Swaps in page P, which must have a locked frame
   (and be swapped out). */
void
swap_in (struct page *p) 
{
  ASSERT (p->frame != NULL);
  ASSERT (lock_held_by_current_thread (&p->frame->lock));
  ASSERT (p->sector != (block_sector_t) -1);

  /* TODO (Phase 4): Read enough blocks to load page. */

  /* TODO (Phase 4): Mark swap frame as in use in tracking data structure. */

  p->sector = (block_sector_t) -1;
}

/* Swaps out page P, which must have a locked frame. */
bool
swap_out (struct page *p) 
{
  size_t slot;

  ASSERT (p->frame != NULL);
  ASSERT (lock_held_by_current_thread (&p->frame->lock));

  lock_acquire (&swap_lock);
  slot = 0;
  /* TODO (Phase 4): Assign a free swap frame to slot (instead of 0), and
   * mark that frame used in tracking data structure. */
  lock_release (&swap_lock);
  if (slot == BITMAP_ERROR) 
    return false; 

  p->sector = slot * PAGE_SECTORS;
  /* TODO (Phase 4): Write page across blocks on disk. */
  
  p->private = false;
  p->file = NULL;
  p->file_offset = 0;
  p->file_bytes = 0;

  return true;
}
