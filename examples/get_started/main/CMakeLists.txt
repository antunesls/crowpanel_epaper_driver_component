idf_component_register(SRCS "main.c"
                       INCLUDE_DIRS "."
                       REQUIRES antunesls__crowpanel_epaper_driver_component esp_timer log driver freeRTOS)
