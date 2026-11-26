/*----------------------------------------------------------------------------
| uz_ocm_ring.h
|   Ring buffer of variable-length records in memory shared by the R5 and the
|   A53 (OCM). One producer core, one consumer core, no locks. Header only;
|   both applications include this file (ARMR5 selects the R5 cache code).
|
|   Each core keeps its own uz_ocm_ring_t (local state) that points at the
|   shared parts:
|     data   the records, written by the producer only
|     prod   one cache line, written by the producer only: write position
|     cons   one cache line, written by the consumer only: read position
|   A core never writes a line the other core writes, so cache maintenance
|   is enough for coherence: the producer cleans what it wrote before it
|   publishes the new write position, the consumer invalidates before it
|   reads. Positions are byte offsets into data (0 .. size-1).
|
|   Record: a 32-bit header {u16 len, u16 aux} followed by len payload
|   bytes, padded to 4 bytes. The XCP rings store XCP-on-Ethernet transport
|   layer messages as they go on the wire ([dlc][ctr][packet]): len is the
|   XCP dlc, aux the transport counter. A record never wraps: when the
|   space up to the end of data is too small, the producer writes a wrap
|   marker (len 0xFFFF) and continues at offset 0. The ring is full when
|   the next record would make the write position reach the read position
|   (equal positions mean empty).
|
|   Producer:  uz_ocm_ring_reserve() -> write payload -> ... ->
|              uz_ocm_ring_publish() (cleans the new records, then the
|              write position). Records reserved but not yet published are
|              invisible to the consumer.
|   Consumer:  uz_ocm_ring_poll() (reads the write position, invalidates the
|              new records) -> uz_ocm_ring_next()* -> uz_ocm_ring_release()
|              (publishes the read position, frees the space).
|
|   Start-up: each side starts with its own position equal to the other's
|   (uz_ocm_ring_*_init), i.e. with an empty ring, whichever core comes
|   first; a position that is out of range (OCM content after power-up) is
|   taken as 0.
|
|   Adapted from the JavaScope ring prototype (feature/ipc_ring_buffer_v2,
|   fixed 92-byte slots) to records of any length. UltraZohm.
 ----------------------------------------------------------------------------*/
#ifndef UZ_OCM_RING_H_
#define UZ_OCM_RING_H_

#include <stdint.h>

#define UZ_OCM_RING_LINE     64u      /* A53 cache line; the R5 uses 32 bytes */
#define UZ_OCM_RING_HDR      4u       /* record header {u16 len, u16 aux}     */
#define UZ_OCM_RING_WRAP_LEN 0xFFFFu  /* header len of the wrap marker        */
#define UZ_OCM_RING_PAD4(n)  (((uint32_t)(n) + 3u) & ~3u)

/* One shared index line. Only `pos` is part of the protocol; `count` is a
 * counter the owner publishes with it (records dropped, for diagnostics). */
typedef struct {
    volatile uint32_t pos;
    volatile uint32_t count;
    uint32_t reserved[(UZ_OCM_RING_LINE / 4u) - 2u];
} uz_ocm_ring_line_t;

typedef struct {
    uint8_t *data;              /* shared record area                        */
    uint32_t size;              /* bytes, multiple of 4                      */
    uint32_t max_len;           /* largest record payload accepted           */
    uz_ocm_ring_line_t *prod;   /* shared, producer writes                   */
    uz_ocm_ring_line_t *cons;   /* shared, consumer writes                   */
    /* producer state */
    uint32_t w;                 /* next record goes here                     */
    uint32_t pub;               /* published write position                  */
    uint32_t r_seen;            /* consumer position last read               */
    uint32_t dropped;           /* records refused because the ring was full */
    /* consumer state */
    uint32_t r;                 /* next record to read                       */
    uint32_t w_seen;            /* producer position of the last poll        */
    uint32_t bad;               /* resynchronisations after corrupt data     */
} uz_ocm_ring_t;

/*--------------------------------------------------------------------------
 * Cache maintenance by address range.
 * R5: CP15 line operations (32-byte lines) without Xil_DCacheFlushRange's
 * interrupt lock, so the producer may run in the control ISR and the
 * consumer in the main loop without masking interrupts. A53: the BSP calls
 * (Xil_DCacheInvalidateRange cleans and invalidates, which is harmless here:
 * a core never holds dirty lines of an area the other core writes).
 *------------------------------------------------------------------------*/
#if defined(ARMR5)
#include "xpseudo_asm.h" /* mtcp(), dsb(), XREG_CP15_* */

static inline void uz_ocm_ring_clean(const volatile void *p, uint32_t len) {
    uintptr_t a = (uintptr_t)p & ~(uintptr_t)31u;
    const uintptr_t end = (uintptr_t)p + len;
    for (; a < end; a += 32u) {
        mtcp(XREG_CP15_CLEAN_INVAL_DC_LINE_MVA_POC, a);
    }
    dsb(); /* the write-back is complete before anything that follows */
}

static inline void uz_ocm_ring_inval(const volatile void *p, uint32_t len) {
    uintptr_t a = (uintptr_t)p & ~(uintptr_t)31u;
    const uintptr_t end = (uintptr_t)p + len;
    for (; a < end; a += 32u) {
        mtcp(XREG_CP15_INVAL_DC_LINE_MVA_POC, a);
    }
    dsb();
}
#else
#include "xil_cache.h"

static inline void uz_ocm_ring_clean(const volatile void *p, uint32_t len) {
    Xil_DCacheFlushRange((INTPTR)p, (INTPTR)len);
}

static inline void uz_ocm_ring_inval(const volatile void *p, uint32_t len) {
    Xil_DCacheInvalidateRange((INTPTR)p, (INTPTR)len);
}
#endif

/* Clean / invalidate the record bytes between two positions (wrap-aware). */
static inline void uz_ocm_ring_range_(const uz_ocm_ring_t *q, uint32_t from, uint32_t to, int clean) {
    if (from == to) {
        return;
    }
    if (from < to) {
        if (clean) uz_ocm_ring_clean(q->data + from, to - from);
        else       uz_ocm_ring_inval(q->data + from, to - from);
    } else {
        if (clean) { uz_ocm_ring_clean(q->data + from, q->size - from); uz_ocm_ring_clean(q->data, to); }
        else       { uz_ocm_ring_inval(q->data + from, q->size - from); uz_ocm_ring_inval(q->data, to); }
    }
}

static inline uint32_t uz_ocm_ring_pos_valid_(const uz_ocm_ring_t *q, uint32_t pos) {
    return (pos < q->size && (pos & 3u) == 0u) ? pos : 0u;
}

/* Describe a ring; no shared memory is touched. */
static inline void uz_ocm_ring_setup(uz_ocm_ring_t *q, void *data, uint32_t size, uint32_t max_len,
                                     void *prod_line, void *cons_line) {
    q->data = (uint8_t *)data;
    q->size = size & ~3u;
    q->max_len = max_len;
    q->prod = (uz_ocm_ring_line_t *)prod_line;
    q->cons = (uz_ocm_ring_line_t *)cons_line;
    q->w = q->pub = q->r_seen = q->dropped = 0u;
    q->r = q->w_seen = q->bad = 0u;
}

/*--------------------------------------------------------------------------
 * Producer
 *------------------------------------------------------------------------*/

/* Start with an empty ring: write position = the consumer's read position. */
static inline void uz_ocm_ring_producer_init(uz_ocm_ring_t *q) {
    uz_ocm_ring_inval(q->cons, sizeof(*q->cons));
    q->r_seen = uz_ocm_ring_pos_valid_(q, q->cons->pos);
    q->w = q->pub = q->r_seen;
    q->prod->pos = q->w;
    q->prod->count = q->dropped;
    uz_ocm_ring_clean(q->prod, sizeof(*q->prod));
}

/* Can a record of `need` bytes (header included) start at w, or after a
 * wrap at 0, without the write position reaching r? Returns the start
 * offset, or q->size if it does not fit. */
static inline uint32_t uz_ocm_ring_fit_(const uz_ocm_ring_t *q, uint32_t need, uint32_t r) {
    const uint32_t w = q->w;
    if (w >= r) {
        const uint32_t tail = q->size - w;
        if (tail > need || (tail == need && r != 0u)) {
            return w;
        }
        return (need < r) ? 0u : q->size; /* wrap: [w, size) is skipped */
    }
    return (need < (r - w)) ? w : q->size;
}

/* Reserve a record of `len` payload bytes and write its header. Returns
 * the payload (4-byte aligned, PAD4(len) bytes usable) or NULL when the
 * ring is full or len is too large (counted in q->dropped). The consumer
 * position is read from shared memory only when the last one seen leaves
 * too little space. */
static inline uint8_t *uz_ocm_ring_reserve(uz_ocm_ring_t *q, uint32_t len, uint16_t aux) {
    if (len == 0u || len > q->max_len) {
        q->dropped++;
        return (uint8_t *)0;
    }
    const uint32_t need = UZ_OCM_RING_HDR + UZ_OCM_RING_PAD4(len);
    uint32_t at = uz_ocm_ring_fit_(q, need, q->r_seen);
    if (at == q->size) {
        uz_ocm_ring_inval(q->cons, sizeof(*q->cons));
        q->r_seen = uz_ocm_ring_pos_valid_(q, q->cons->pos);
        at = uz_ocm_ring_fit_(q, need, q->r_seen);
        if (at == q->size) {
            q->dropped++;
            return (uint8_t *)0;
        }
    }
    if (at != q->w) {
        /* Wrap marker; the tail is a multiple of 4 and not 0 (w < size). */
        *(volatile uint32_t *)(void *)(q->data + q->w) = UZ_OCM_RING_WRAP_LEN;
    }
    uint8_t *const rec = q->data + at;
    *(uint32_t *)(void *)rec = (uint32_t)len | ((uint32_t)aux << 16);
    q->w = at + need;
    if (q->w == q->size) {
        q->w = 0u;
    }
    return rec + UZ_OCM_RING_HDR;
}

/* Bytes reserved since the last publish. */
static inline uint32_t uz_ocm_ring_unpublished(const uz_ocm_ring_t *q) {
    return (q->w >= q->pub) ? (q->w - q->pub) : (q->size - q->pub + q->w);
}

/* Bytes in the ring as far as the producer knows (consumer position of the
 * last check), published or not. */
static inline uint32_t uz_ocm_ring_level(const uz_ocm_ring_t *q) {
    return (q->w >= q->r_seen) ? (q->w - q->r_seen) : (q->size - q->r_seen + q->w);
}

/* Make every reserved record visible to the consumer: clean the records,
 * then publish the write position (and the drop counter) in its own line.
 * Returns the number of bytes published. */
static inline uint32_t uz_ocm_ring_publish(uz_ocm_ring_t *q) {
    const uint32_t n = uz_ocm_ring_unpublished(q);
    if (n == 0u) {
        return 0u;
    }
    uz_ocm_ring_range_(q, q->pub, q->w, 1); /* ends with a DSB */
    q->prod->pos = q->w;
    q->prod->count = q->dropped;
    uz_ocm_ring_clean(q->prod, sizeof(*q->prod));
    q->pub = q->w;
    return n;
}

/* Would a record of `len` payload bytes fit now? Reads the consumer
 * position. */
static inline int uz_ocm_ring_fits(uz_ocm_ring_t *q, uint32_t len) {
    uz_ocm_ring_inval(q->cons, sizeof(*q->cons));
    q->r_seen = uz_ocm_ring_pos_valid_(q, q->cons->pos);
    return uz_ocm_ring_fit_(q, UZ_OCM_RING_HDR + UZ_OCM_RING_PAD4(len), q->r_seen) != q->size;
}

/* Has the consumer read everything published? Reads its position. */
static inline int uz_ocm_ring_drained(uz_ocm_ring_t *q) {
    uz_ocm_ring_inval(q->cons, sizeof(*q->cons));
    q->r_seen = uz_ocm_ring_pos_valid_(q, q->cons->pos);
    return q->r_seen == q->pub;
}

/*--------------------------------------------------------------------------
 * Consumer
 *------------------------------------------------------------------------*/

/* Start with an empty ring: read position = the producer's write position. */
static inline void uz_ocm_ring_consumer_init(uz_ocm_ring_t *q) {
    uz_ocm_ring_inval(q->prod, sizeof(*q->prod));
    q->r = q->w_seen = uz_ocm_ring_pos_valid_(q, q->prod->pos);
    q->cons->pos = q->r;
    q->cons->count = q->bad;
    uz_ocm_ring_clean(q->cons, sizeof(*q->cons));
}

/* Read the producer position and invalidate the records published since
 * the last poll. Returns the number of bytes available. */
static inline uint32_t uz_ocm_ring_poll(uz_ocm_ring_t *q) {
    uz_ocm_ring_inval(q->prod, sizeof(*q->prod));
    const uint32_t w = q->prod->pos;
    if (w >= q->size || (w & 3u) != 0u) {
        return 0u; /* not a position; checked again at the next poll */
    }
    if (w != q->w_seen) {
        uz_ocm_ring_range_(q, q->w_seen, w, 0);
        q->w_seen = w;
    }
    return (w >= q->r) ? (w - q->r) : (q->size - q->r + w);
}

/* Producer's drop counter as of the last poll. */
static inline uint32_t uz_ocm_ring_producer_dropped(const uz_ocm_ring_t *q) {
    return q->prod->count;
}

/* Next record up to the last poll: returns the record start (header
 * included; *len = payload length, *aux = header aux) and advances the
 * local read position, or NULL when nothing is left. The bytes stay valid
 * until uz_ocm_ring_release(). Corrupt data (impossible length) drops
 * everything up to the last poll and counts q->bad. */
static inline const uint8_t *uz_ocm_ring_next(uz_ocm_ring_t *q, uint16_t *len, uint16_t *aux) {
    for (;;) {
        if (q->r == q->w_seen) {
            return (const uint8_t *)0;
        }
        const uint8_t *rec = q->data + q->r;
        const uint32_t h = *(const volatile uint32_t *)(const void *)rec;
        const uint32_t l = h & 0xFFFFu;
        if (l == UZ_OCM_RING_WRAP_LEN) {
            if (q->r < q->w_seen) {
                break; /* a wrap marker cannot lie before the write position */
            }
            q->r = 0u;
            continue;
        }
        const uint32_t need = UZ_OCM_RING_HDR + UZ_OCM_RING_PAD4(l);
        const uint32_t avail = (q->w_seen >= q->r) ? (q->w_seen - q->r) : (q->size - q->r);
        if (l == 0u || l > q->max_len || need > avail) {
            break;
        }
        q->r += need;
        if (q->r == q->size) {
            q->r = 0u;
        }
        *len = (uint16_t)l;
        *aux = (uint16_t)(h >> 16);
        return rec;
    }
    q->bad++;
    q->r = q->w_seen;
    return (const uint8_t *)0;
}

/* Hand the space of the records read so far back to the producer. */
static inline void uz_ocm_ring_release(uz_ocm_ring_t *q) {
    q->cons->pos = q->r;
    q->cons->count = q->bad;
    uz_ocm_ring_clean(q->cons, sizeof(*q->cons));
}

#endif /* UZ_OCM_RING_H_ */
