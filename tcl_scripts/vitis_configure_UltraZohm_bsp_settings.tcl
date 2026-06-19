###########################################################################
# Copyright 2021-2026 Eyke Aufderheide, Tobias Schindler, Martin Geier
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
###########################################################################

proc uz_vitis_apply_freertos_bsp_settings {enable_dhcp} {
  puts "Info (UltraZohm): change FreeRTOS BSP settings"

  set disabled_ips {
    psu_ams
    psu_apm_0
    psu_apm_1
    psu_apm_2
    psu_apm_5
    psu_coresight_0
    psu_csudma
    psu_adma_0
    psu_adma_1
    psu_adma_2
    psu_adma_3
    psu_adma_4
    psu_adma_5
    psu_adma_6
    psu_adma_7
    psu_gdma_0
    psu_gdma_1
    psu_gdma_2
    psu_gdma_3
    psu_gdma_4
    psu_gdma_5
    psu_gdma_6
    psu_gdma_7
    psu_qspi_0
    psu_crf_apb
    psu_rtc
    psu_sd_1
    psu_spi_0
    psu_spi_1
    psu_rcpu_gic
    uz_system_axi_timebase_wdt_0
    uz_system_timer_uptime_64bit
    uz_system_uz_enable_axi_gpio_2
  }

  # Keep the FreeRTOS BSP limited to the libraries supported on A53.
  bsp setlib -name lwip211

  foreach ip $disabled_ips {
    bsp setdriver -ip $ip -driver none
  }

  # get list of configurable parameters for lwip lib
  #bsp listparams -lib lwip211
  bsp config api_mode SOCKET_API
  bsp config dhcp_does_arp_check $enable_dhcp
  bsp config lwip_dhcp $enable_dhcp
  # increase heap size of freertos, to fix javascope glitches
  bsp config total_heap_size 200000000
  # Save FPU/NEON context for ALL tasks (default 1 only covers tasks that call
  # vPortTaskUsesFPU(), but aarch64 GCC uses NEON Q-registers inside ordinary
  # memcpy -> a task preempted mid-copy would resume with corrupted registers).
  bsp config use_task_fpu_support 2
  platform write
}

proc uz_vitis_apply_baremetal_bsp_settings {} {
  puts "Info (UltraZohm): change Baremetal BSP settings"

  set disabled_ips {
    psu_ethernet_3
    psu_i2c_1
    psu_adma_0
    psu_adma_1
    psu_adma_2
    psu_adma_3
    psu_adma_4
    psu_adma_5
    psu_adma_6
    psu_adma_7
    psu_gdma_0
    psu_gdma_1
    psu_gdma_2
    psu_gdma_3
    psu_gdma_4
    psu_gdma_5
    psu_gdma_6
    psu_gdma_7
    psu_apm_0
    psu_apm_1
    psu_apm_2
    psu_apm_5
    psu_can_0
    psu_can_1
    psu_coresight_0
    psu_crf_apb
    psu_csudma
    psu_i2c_0
    psu_qspi_0
    psu_rtc
    psu_sd_1
    psu_spi_0
    psu_spi_1
    psu_ttc_0
    uz_system_axi_timebase_wdt_0
  }

  # Hide peripherals used by FreeRTOS/Linux from Baremetal(_domain).
  foreach ip $disabled_ips {
    bsp setdriver -ip $ip -driver none
  }

  platform write
}
