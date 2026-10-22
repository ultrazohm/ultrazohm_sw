# Raw UltraZohm R5 UART timing evidence

COM5, 115200 baud. Full JTAG reset and reload for each variant, 9 October 2026.
Each variant used 12 warm-up steps followed by 6,000 measured steps. Timer ticks are uncorrected.
R5: 100,000,000 ticks/s. A53: 33,333,332 ticks/s.

## Variant 0

FSD A53 variant=0 qp=6 status=0 measured=6000 failed_calls=0
R5_timer_hz=100000000 A53_timer_hz=33333332 init_roundtrip_ticks=11559 init_A53_ticks=3452
R5_roundtrip_ticks min=9633 mean=9771 max=9998 p95_us=100 p99_us=100 over100=0
A53_compute_ticks min=3021 mean=3065 max=3138 p95_us=94 p99_us=94

R5 ELF SHA-256: 0402c7586e890c348bccd8ac5292e3e3adcc234d31a64f7c49fe804e947df2c4
A53 ELF SHA-256: 9d114c0283bd4d2e8f0dadf763c06c3224f643294575ce09b3c12fb287324477
JTAG launch log: launch_0.log ended "UltraZohm successfully programmed and running."

## Variant 1

FSD A53 variant=1 qp=6 status=0 measured=6000 failed_calls=0
R5_timer_hz=100000000 A53_timer_hz=33333332 init_roundtrip_ticks=8068 init_A53_ticks=2286
R5_roundtrip_ticks min=6233 mean=6325 max=6465 p95_us=65 p99_us=65 over100=0
A53_compute_ticks min=1885 mean=1915 max=1961 p95_us=59 p99_us=59

R5 ELF SHA-256: 9915cc0b590ec9128e7490ba1743b53a61aa6e34329013798457add164fd587a
A53 ELF SHA-256: b3a1e3f857a882bfd41f8cd37e25366b50a5f45fdaa1c3750020bdcbb3fbb902
JTAG launch log: launch_1.log ended "UltraZohm successfully programmed and running."

## Variant 2

FSD A53 variant=2 qp=12 status=0 measured=6000 failed_calls=0
R5_timer_hz=100000000 A53_timer_hz=33333332 init_roundtrip_ticks=14329 init_A53_ticks=4366
R5_roundtrip_ticks min=12247 mean=12457 max=12786 p95_us=100 p99_us=100 over100=6000
A53_compute_ticks min=3897 mean=3960 max=4070 p95_us=100 p99_us=100

R5 ELF SHA-256: 93cee8f688fe67b4069cc0535208c671bdb5af70ac66672294f3634e6ceace29
A53 ELF SHA-256: a0ec7c168877d0249598e5814bd34b28e0ee3b91c81cb0157e7482e661d80b5e
JTAG launch log: launch_2.log ended "UltraZohm successfully programmed and running."

## Variant 3

FSD A53 variant=3 qp=1 status=0 measured=6000 failed_calls=0
R5_timer_hz=100000000 A53_timer_hz=33333332 init_roundtrip_ticks=4135 init_A53_ticks=972
R5_roundtrip_ticks min=2197 mean=2261 max=2385 p95_us=24 p99_us=24 over100=0
A53_compute_ticks min=545 mean=560 max=599 p95_us=18 p99_us=18

R5 ELF SHA-256: ac386d025e29741dc5e04b08eb45919828bf98113408063ef837c102358d68e1
A53 ELF SHA-256: 9bd6ead9b07dc2b679214cf64e1b0208467a7b32f69eb43ce68c32dd1939273d
JTAG launch log: launch_3.log ended "UltraZohm successfully programmed and running."

## Variant 4

FSD A53 variant=4 qp=1 status=0 measured=6000 failed_calls=0
R5_timer_hz=100000000 A53_timer_hz=33333332 init_roundtrip_ticks=3531 init_A53_ticks=770
R5_roundtrip_ticks min=1644 mean=1684 max=1745 p95_us=18 p99_us=18 over100=0
A53_compute_ticks min=360 mean=368 max=387 p95_us=12 p99_us=12

R5 ELF SHA-256: f2d94f45c69c6bf8355b272976b14d04dbf8475408242f7fcfbe1cd5dbd81fdc
A53 ELF SHA-256: 5e7d9cb8ea2db75a1dc5fd6af5fe859c4220c58f42a6b6bc7e270cd880331802
JTAG launch log: launch_4.log ended "UltraZohm successfully programmed and running."

## Variant 5

FSD A53 variant=5 qp=2 status=0 measured=6000 failed_calls=0
R5_timer_hz=100000000 A53_timer_hz=33333332 init_roundtrip_ticks=4639 init_A53_ticks=1127
R5_roundtrip_ticks min=2649 mean=2729 max=2898 p95_us=29 p99_us=29 over100=0
A53_compute_ticks min=692 mean=715 max=770 p95_us=23 p99_us=24

R5 ELF SHA-256: 90a612b64d57fefe6c219114963439d110769ebafcc12eb88aad8723851c5bd3
A53 ELF SHA-256: 61b3af813a6c2ad7c9c03562421f349aa4de6b7c80fa0227e52f9479f25c7da5
JTAG launch log: launch_5.log ended "UltraZohm successfully programmed and running."

